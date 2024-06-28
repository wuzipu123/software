
#include "SensorSPS30.h"
#include "sensirion_uart.h"
#include "ThisThread.h"
#include "Logger.h"

using namespace std;

SensorSPS30::SensorSPS30() : _supply_enable(MBED_CONF_APP_SPS30_SUPPLY_ENABLE, false),
                 _serial(MBED_CONF_APP_SPS30_RX_SDA, MBED_CONF_APP_SPS30_TX_SCL) {
  _serial.set_blocking(false);
  _serial.enable_input(false);
}

mbed_error_status_t SensorSPS30::start_measurement() {
  power_on();
  _serial.enable_input(true);

  if (sps30_probe()) {
    LOG(LVL_ERROR, "Sensor probing failed");
    _serial.enable_input(false);
    power_off();
    return MBED_ERROR_INITIALIZATION_FAILED;
  }

  if (sps30_start_measurement()) {
    LOG(LVL_ERROR, "Starting measurement failed");
    _serial.enable_input(false);
    power_off();
    return MBED_ERROR_INITIALIZATION_FAILED;
  }
  _serial.enable_input(false);
  return MBED_SUCCESS;
}

void SensorSPS30::stop_measurement() {
  _serial.enable_input(true);
  sps30_stop_measurement();
  _serial.enable_input(false);
  sensirion_uart_close();
  power_off();
}

mbed_error_status_t SensorSPS30::read_measurement(measurement_t *measurement_data) {
  _serial.enable_input(true);
  int16_t ret = sps30_read_measurement(measurement_data);
  _serial.enable_input(false);
  correct_data(measurement_data);
  if (ret < 0) {
    LOG(LVL_ERROR, "Reading measurement failed! result: %d", ret);
    return MBED_ERROR_READ_FAILED;
  } else {
    if (SPS30_IS_ERR_STATE(ret)) {
      LOG(LVL_ERROR, "Chip state: %u - measurements may not be accurate", SPS30_GET_ERR_STATE(ret));
      return MBED_ERROR_READ_FAILED;
    }
  }
  return MBED_SUCCESS;
}

void SensorSPS30::correct_data(measurement_t *data) {
  data->mc_1p0 = (data->mc_1p0 + Config::get<float>("pm1.0_offset")) * Config::get<float>("pm1.0_factor");
  data->mc_2p5 = (data->mc_2p5 + Config::get<float>("pm2.5_offset")) * Config::get<float>("pm2.5_factor");
  data->mc_4p0 = (data->mc_4p0 + Config::get<float>("pm4.0_offset")) * Config::get<float>("pm4.0_factor");
  data->mc_10p0 = (data->mc_10p0 + Config::get<float>("pm10.0_offset")) * Config::get<float>("pm10.0_factor");
  data->nc_0p5 = (data->nc_0p5 + Config::get<float>("pn0.5_offset")) * Config::get<float>("pn0.5_factor");
  data->nc_1p0 = (data->nc_1p0 + Config::get<float>("pn1.0_offset")) * Config::get<float>("pn1.0_factor");
  data->nc_2p5 = (data->nc_2p5 + Config::get<float>("pn2.5_offset")) * Config::get<float>("pn2.5_factor");
  data->nc_4p0 = (data->nc_4p0 + Config::get<float>("pn4.0_offset")) * Config::get<float>("pn4.0_factor");
  data->nc_10p0 = (data->nc_10p0 + Config::get<float>("pn10.0_offset")) * Config::get<float>("pn10.0_factor");
  data->typical_particle_size =
      (data->typical_particle_size + Config::get<float>("part_size_offset")) * Config::get<float>("part_size_factor");
}

mbed_error_status_t SensorSPS30::start_manual_fan_cleaning() {
  _serial.enable_input(true);
  if (sps30_start_manual_fan_cleaning() != 0) {
    _serial.enable_input(false);
    return MBED_ERROR_FAILED_OPERATION;
  }
  _serial.enable_input(false);
  return MBED_SUCCESS;
}

mbed_error_status_t SensorSPS30::probe() {
  _serial.enable_input(true);
  if (sps30_probe() != 0) {
    _serial.enable_input(false);
    return MBED_ERROR_FAILED_OPERATION;
  }
  _serial.enable_input(false);
  return MBED_SUCCESS;
}

mbed_error_status_t SensorSPS30::get_serial(std::string &serial) {
  char serial_tmp[SPS30_MAX_SERIAL_LEN];
  _serial.enable_input(true);
  if (sps30_get_serial(serial_tmp) != 0) {
    _serial.enable_input(false);
    return MBED_ERROR_READ_FAILED;
  }
  _serial.enable_input(false);
  serial = std::string(serial_tmp);
  return MBED_SUCCESS;
}

mbed_error_status_t SensorSPS30::read_version(sps30_version_information *version) {
  _serial.enable_input(true);
  if (sps30_read_version(version) != 0) {
    _serial.enable_input(false);
    return MBED_ERROR_READ_FAILED;
  }
  _serial.enable_input(false);
  return MBED_SUCCESS;
}

void SensorSPS30::power_on() {
  sensirion_uart_open(&_serial);
  _supply_enable = true;
  sps30_wake_up();
}

void SensorSPS30::power_off() {
  sensirion_uart_close();
  _serial.enable_input(false);
  _supply_enable = false;
}
