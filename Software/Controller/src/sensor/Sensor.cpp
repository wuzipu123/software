#include "Sensor.h"
#include "JsonProtocol.h"
#include "BinProtocol.h"
#include "constants.h"
#include "utils.h"

#define MAX_READ_DATA_TIME_SEC 3

Sensor::Sensor(const io_config_t io_config, Config::sensor_config_t &sensor_config, SensorBoardSerial &serial,
               rtos::EventFlags &control_event_flags) : data(io_config.address), _sensor_config(sensor_config),
                                                        _serial(serial), _control_event_flags(control_event_flags),
                                                        _protocol(new JsonProtocol(_serial, data)),
                                                        _supply_enable(io_config.supply_enable_pin, false),
                                                        _data_ready(io_config.data_ready_pin),
                                                        _error(io_config.error_pin, PullDown) {
  _data_ready.rise(mbed::callback(this, &Sensor::set_data_ready_flag));
  _data_ready.disable_irq();
}

Sensor::~Sensor() {
  delete _protocol;
  _protocol = nullptr;
}

mbed_error_status_t Sensor::init() {
  TRY(_protocol->get_sensor_info());

  if (_protocol->get_protocol_version() != data.protocol_version) {
    switch_to_protocol(data.protocol_version);
  }
  return MBED_SUCCESS;
}

std::string const &Sensor::get_new_file_name() {
  _file_name.clear();
  utils::get_formatted_time_string("%Y-%m-%d_%H-%M-%S", _file_name);
  _file_name = "Data_" + data.name + "_" + std::to_string(data.address) + "_" + _file_name + ".csv";
  return _file_name;
}

std::string const &Sensor::get_file_name() {
  return _file_name;
}

mbed_error_status_t Sensor::start_measurement() {
  TRY(_protocol->init_measurement());

  if (data.supports_data_ready) {
    _data_ready.enable_irq();
  } else {
    _sensor_start_timeout.attach(mbed::callback(this, &Sensor::set_data_ready_flag),
                                 static_cast<float>(data.startup_time));
  }

  _state = State::SENSOR_STARTING;
  return MBED_SUCCESS;
}

void Sensor::start_measurement_ticker() {
  float sample_time;
  if (is_keep_alive()) {
    sample_time = std::max(_sensor_config.sample_time_sec, data.min_sample_time);
  } else {
    sample_time = std::max(_sensor_config.sample_time_sec, data.min_sample_time);
    sample_time = std::max(sample_time, static_cast<float>(SENSOR_BOARD_STARTUP_TIME_MS) / 1000 + data.startup_time +
                           MAX_READ_DATA_TIME_SEC);
  }

  set_do_measurement_flag();
  _measurement_ticker.attach(mbed::callback(this, &Sensor::set_do_measurement_flag), sample_time);
}

void Sensor::stop_measurement_ticker() {
  _measurement_ticker.detach();
}

mbed_error_status_t Sensor::read_data() {
  return _protocol->read_data();
}

mbed_error_status_t Sensor::stop_measurement() {
  _state = State::IDLE;
  if (data.supports_data_ready) {
    _data_ready.disable_irq();
  } else {
    _sensor_start_timeout.detach();
  }
  return _protocol->stop_measurement();
}

void Sensor::power_on() {
  _state = State::SENSOR_BOARD_STARTING;
  _supply_enable = true;
  _sensor_board_start_timeout.attach(mbed::callback(this, &Sensor::set_sensor_board_started_flag),
                                     static_cast<float>(SENSOR_BOARD_STARTUP_TIME_MS) / 1000);
}

void Sensor::power_off() {
  _sensor_board_start_timeout.detach();
  _sensor_start_timeout.detach();
  if (data.supports_data_ready) {
    _data_ready.disable_irq();
  } else {
    _sensor_start_timeout.detach();
  }
  _supply_enable = false;
  _state = State::POWER_OFF;
}

void Sensor::switch_to_protocol(const std::string &protocol_version) {
  delete _protocol;
  if (protocol_version == "2.0") {
    _protocol = new BinProtocol(_serial, data);
  } else {
    _protocol = new JsonProtocol(_serial, data);
  }
}

void Sensor::set_do_measurement_flag() {
  _control_event_flags.set(CONTROL_FLAG_DO_MEASUREMENT(data.address));
}

void Sensor::set_sensor_board_started_flag() {
  _state = State::IDLE;
  _control_event_flags.set(CONTROL_FLAG_SENSOR_BOARD_STARTED(data.address));
}

void Sensor::set_data_ready_flag() {
  _state = State::MEASURING;
  _control_event_flags.set(CONTROL_FLAG_SENSOR_DATA_READY(data.address));
}

bool Sensor::get_error_state() {
  return _error.read() != 0;
}

Sensor::State Sensor::get_state() const {
  return _state;
}

bool Sensor::is_keep_alive() const {
  return _sensor_config.keep_alive && data.supports_keep_alive;
}
