
#include "MeasureState.h"
#include "Communication.h"
#include "Protocol.h"
#include "Logger.h"
#include "utils.h"
#include "Config.h"

MeasureState::MeasureState(LedIndicator &led_indicator, SDCard &sd_card, Communication &communication, SensorSPS30 &sps30,
                           SensorBME280 &bme280, rtos::EventFlags &event_flags) :
    State(led_indicator),
    _sd_card(sd_card),
    _communication(communication),
    _sps30(sps30),
    _sps30_state(SPS30State::OFF),
    _bme280(bme280),
    _event_flags(event_flags) {
}

mbed_error_status_t MeasureState::get_sps30_info() {
  std::string sps30_serial;
  mbed_error_status_t error_status = MBED_SUCCESS;

  _sps30.power_on();
  error_status = _sps30.get_serial(sps30_serial);
  if (MBED_SUCCESS != error_status) {
    _sps30.power_off();
    return error_status;
  }

  sps30_version_information sps30_version = {0};
  error_status = _sps30.read_version(&sps30_version);
  _sps30.power_off();
  if (MBED_SUCCESS != error_status) {
    return error_status;
  }

  _sps30_info = "SPS30 serial number: " + sps30_serial + "\n";
  _sps30_info += "SPS30 firmware version: " + std::to_string(sps30_version.firmware_major) + "." +
                 std::to_string(sps30_version.firmware_minor) + "\n";
  _sps30_info += "SPS30 SHDLC version: " + std::to_string(sps30_version.shdlc_major) + "." +
                 std::to_string(sps30_version.shdlc_minor) + "\n";
  _sps30_info += "SPS30 Hardware revision: " + std::to_string(sps30_version.hardware_revision) + "\n";

  return error_status;
}

mbed_error_status_t MeasureState::init_measurement_file() {
  std::string csv_header = "Software version: " + utils::app_version() + "\n";
  csv_header += "Software UUID: " + utils::to_hex_string(Protocol::get_sw_uuid()) + "\n";
  csv_header += "Hardware UUID: " + utils::to_hex_string(Protocol::get_hw_uuid()) + "\n";
  csv_header += _sps30_info;
  csv_header += "Timestamp;PM1.0 [ug/m^3];PM2.5 [ug/m^3];PM4.0 [ug/m^3];PM10.0 [ug/m^3];PN0.5 [#/cm^3];"
                "PN1.0 [#/cm^3];PN2.5 [#/cm^3];PN4.0 [#/cm^3];PN10.0 [#/cm^3];Typical Particle Size [um];"
                "Temperature [degC];Pressure [Pa];Humidity [%]\n";

  std::string time_string;
  utils::get_formatted_time_string("%Y-%m-%d_%H-%M-%S", time_string);
  _data_file_name = "data_" + time_string + ".csv";

  TRY(_sd_card.write(_data_file_name, csv_header));

  LOG(LVL_INFO, "Created new data file (%s)", _data_file_name.c_str());

  return MBED_SUCCESS;
}

void MeasureState::set_do_measurement_flag() {
  _event_flags.set(FLAG_DO_MEASUREMENT);
}

void MeasureState::set_create_new_file_flag() {
  _event_flags.set(FLAG_CREATE_NEW_FILE);
}

void MeasureState::set_sps30_startup_done_flag() {
  _event_flags.set(FLAG_SPS30_STARTUP_DONE);
}

State::Result MeasureState::handle() {
  LOG(LVL_INFO, "Enter MeasureState");
  _measurement_ticker.attach(mbed::callback(this, &MeasureState::set_do_measurement_flag),
                             std::chrono::seconds(Config::get<uint32_t>("sample_time_sec")));
  _new_file_ticker.attach(mbed::callback(this, &MeasureState::set_create_new_file_flag),
                          std::chrono::seconds(DATA_FILE_CREATION_PERIOD_SEC));
  if (MBED_SUCCESS != get_sps30_info()) {
    return State::Result::SENSOR_ERROR;
  }
  init_measurement_file();
  _sps30_state = SPS30State::OFF;
  _event_flags.clear();

  State::Result result = run();

  _measurement_ticker.detach();
  _new_file_ticker.detach();
  _sps30.stop_measurement();
  return result;
}

State::Result MeasureState::run() {
  SensorBME280::measurement_t bme280_measurement;
  SensorSPS30::measurement_t sps30_measurement;
  _avg_data.clear();
  set_do_measurement_flag();

  while (true) {
    uint32_t wait_flags = _event_flags.wait_any(FLAG_BUTTON_MEASURE | FLAG_BUTTON_STATUS | FLAG_BUTTON_COMMAND |
                                                FLAG_DO_MEASUREMENT | FLAG_CREATE_NEW_FILE | FLAG_SPS30_STARTUP_DONE);
    if (wait_flags & FLAG_BUTTON_MEASURE) {
      set_do_measurement_flag();
    } else if (wait_flags & FLAG_BUTTON_COMMAND) {
      return State::Result::COMMAND_PRESSED;
    } else if (wait_flags & FLAG_BUTTON_STATUS) {
      LOG(LVL_DEBUG, "Received FLAG_BUTTON_STATUS");
      _led_indicator.display_status_for(LedIndicator::Color::GREEN, 3000);
      _led_indicator.display_battery_level_for(3000);
#ifdef PRINT_STATS
      utils::print_statistics();
#endif // PRINT_STATS
    } else if (wait_flags & FLAG_DO_MEASUREMENT) {
      LOG(LVL_DEBUG, "Received FLAG_DO_MEASUREMENT");
      if (_sps30_state == SPS30State::STARTING) {
        continue;
      } else if (_sps30_state == SPS30State::RUNNING) {
        _event_flags.set(FLAG_SPS30_STARTUP_DONE);
      } else {
        if (MBED_SUCCESS != _sps30.start_measurement()) {
          return State::Result::SENSOR_ERROR;
        }
        _sps30_state = SPS30State::STARTING;
        _sps30_startup_timeout.attach(mbed::callback(this, &MeasureState::set_sps30_startup_done_flag),
                                      std::chrono::seconds(Config::get<uint32_t>("sps_startup_sec")));
      }
    } else if (wait_flags & FLAG_SPS30_STARTUP_DONE) {
      LOG(LVL_DEBUG, "Received FLAG_SPS30_STARTUP_DONE");
      _sps30_state = SPS30State::RUNNING;

      if (MBED_SUCCESS != _bme280.read_measurement(&bme280_measurement)) {
        return State::Result::SENSOR_ERROR;
      }

      if (MBED_SUCCESS != _sps30.read_measurement(&sps30_measurement)) {
        return State::Result::SENSOR_ERROR;
      }

      if (Config::get<uint32_t>("sample_time_sec") > Config::get<uint32_t>("sps_startup_sec") + 5) {
        _sps30.stop_measurement();
        _sps30_state = SPS30State::OFF;
      }

      if (MBED_SUCCESS != store_measurement_data(sps30_measurement, bme280_measurement)) {
        return State::Result::SD_CARD_ERROR;
      }

      send_measurement_data(sps30_measurement, bme280_measurement);
    }

    if (wait_flags & FLAG_CREATE_NEW_FILE) {
      LOG(LVL_DEBUG, "Received FLAG_CREATE_NEW_FILE");
      init_measurement_file();
    }
  }
  return State::Result::SUCCESS;
}

void MeasureState::send_measurement_data(const SensorSPS30::measurement_t &sps30_measurement,
                                         const SensorBME280::measurement_t &bme280_measurement) {

  avg_data_t avg = {};
  for(auto element : _avg_data) {
    avg += element;
  }
  avg /= _avg_data.size();

  Protocol::measured_data_t measured_data;
  measured_data.temp = static_cast<int16_t>(std::round(avg.temp * 100.0));
  measured_data.hum = static_cast<uint8_t>(std::round(avg.hum));
  measured_data.press = static_cast<uint16_t>(std::round(avg.press * 0.1));
  measured_data.pm2_5 = static_cast<uint32_t>(std::round(avg.pm2_5 * 1000.0));
  measured_data.particle_size = static_cast<uint8_t>(std::round(avg.particle_size * 10.0));

  LOG(LVL_DEBUG, "Send data: temp: %.5f, hum: %.5f, press: %.5f, pm2_5: %.5f, size: %.5f",
      avg.temp, avg.hum, avg.press, avg.pm2_5, avg.particle_size);
  LOG(LVL_DEBUG, "Send data (converted): temp: %d, hum: %u, press: %lu, pm2_5: %lu, size: %u",
      measured_data.temp, measured_data.hum, measured_data.press, measured_data.pm2_5, measured_data.particle_size);

  _communication.send_measured_data(measured_data);
}

mbed_error_status_t MeasureState::store_measurement_data(const SensorSPS30::measurement_t &sps30_measurement,
                                                         const SensorBME280::measurement_t &bme280_measurement) {
  if (!Config::get<bool>("sd_log_enable")) {
    return MBED_SUCCESS;
  }

  if(_avg_data.size() >= Config::get<uint32_t>("moving_avg_length")) {
    _avg_data.erase(_avg_data.begin());
  }
  _avg_data.push_back({(float)bme280_measurement.temperature,
                       (float)bme280_measurement.humidity,
                       (float)bme280_measurement.pressure,
                       sps30_measurement.mc_2p5,
                       sps30_measurement.typical_particle_size});

  // one value inclusive needs 15 characters + semicolon + (opt.)sign = 17, times 14 values
  char buffer[13 * 17 + 1] = {0};
  snprintf(buffer, 13 * 17, "%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e",
           sps30_measurement.mc_1p0, sps30_measurement.mc_2p5, sps30_measurement.mc_4p0, sps30_measurement.mc_10p0,
           sps30_measurement.nc_0p5, sps30_measurement.nc_1p0, sps30_measurement.nc_2p5, sps30_measurement.nc_4p0,
           sps30_measurement.nc_10p0, sps30_measurement.typical_particle_size,
           bme280_measurement.temperature, bme280_measurement.pressure, bme280_measurement.humidity);
  std::string line;
  utils::get_formatted_time_string("%FT%T;", line);
  line += buffer;
  line += '\n';
  return _sd_card.write(_data_file_name, line);
}
