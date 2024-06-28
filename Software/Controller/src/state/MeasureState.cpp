#include "MeasureState.h"
#include "Logger.h"
#include "ThisThread.h"
#include "constants.h"
#include "utils.h"

MeasureState::MeasureState(LedIndicator &led_indicator, SDCard &sd_card, std::vector<Sensor *> &sensors,
                           rtos::EventFlags &control_event_flags, const Config &config) : State(led_indicator),
                                                                                          _sd_card(sd_card),
                                                                                          _sensors(sensors),
                                                                                          _control_event_flags(
                                                                                              control_event_flags),
                                                                                          _config(config),
                                                                                          _file_creation_time(
                                                                                              time(nullptr)) {
}

mbed_error_status_t MeasureState::init_measurement_files() {
  for (auto sensor : _sensors) {
    if (sensor->is_active) {
      std::string csv_header;
      sensor->data.get_csv_header(csv_header);
      TRY(_sd_card.write(sensor->get_new_file_name(), csv_header));

      _file_creation_time = time(nullptr);
    }
  }
  return MBED_SUCCESS;
}

void MeasureState::start_measurement_tickers() {
  for (auto sensor : _sensors) {
    if (sensor->is_active) {
      sensor->start_measurement_ticker();
    }
  }
}

void MeasureState::power_off_sensors() {
  for (auto sensor : _sensors) {
    if (sensor->is_active) {
      sensor->stop_measurement_ticker();
      sensor->power_off();
    }
  }
}

State::Result MeasureState::handle() {
  Logger::log(Logger::Module::MEASURE_STATE, Logger::Level::INFO, "Enter MeasureState and start measuring");
  _led_indicator.set_behavior_green_led(Led::Behavior::BLINK_15S);

  uint32_t wait_flags = combine_control_flags();
  _control_event_flags.clear(wait_flags);

  if (init_measurement_files() != MBED_SUCCESS) {
    return State::Result::SD_CARD_ERROR;
  }

  start_measurement_tickers();

  while (true) {
    uint32_t flags_read = _control_event_flags.wait_any(wait_flags);
    if (flags_read & CONTROL_FLAG_RESET) {
      power_off_sensors();
      return State::Result::RESET_PRESSED;
    }
    if (flags_read & CONTROL_FLAG_START_STOP) {
      power_off_sensors();
      return State::Result::START_STOP_PRESSED;
    }
    int num_active_sensors = 0;
    for (auto sensor : _sensors) {
      if (!sensor->is_active) {
        continue;
      }
      num_active_sensors++;
      if (flags_read & CONTROL_FLAG_DO_MEASUREMENT(sensor->data.address)) {
        DEBUG_PRINTF("CONTROL_FLAG_DO_MEASUREMENT(%d)\n", sensor->data.address);
        if (sensor->get_state() == Sensor::State::POWER_OFF) {
          sensor->power_on();
        } else if (sensor->is_keep_alive() && sensor->get_state() == Sensor::State::MEASURING) {
          _control_event_flags.set(CONTROL_FLAG_SENSOR_DATA_READY(sensor->data.address));
        }
      } else if (flags_read & CONTROL_FLAG_SENSOR_BOARD_STARTED(sensor->data.address)) {
        DEBUG_PRINTF("CONTROL_FLAG_SENSOR_BOARD_STARTED(%d)\n", sensor->data.address);
        if (sensor->start_measurement() != MBED_SUCCESS) {
          power_off_sensors();
          _led_indicator.set_behavior_red_led(Led::Behavior::BLINK_5S);
          return State::Result::SERIAL_ERROR;
        }
      } else if (flags_read & CONTROL_FLAG_SENSOR_DATA_READY(sensor->data.address)) {
        DEBUG_PRINTF("CONTROL_FLAG_SENSOR_DATA_READY(%d)\n", sensor->data.address);
        if (sensor->get_state() != Sensor::State::MEASURING) {
          continue;
        }

        int attempt_counter;
        for (attempt_counter = 0; attempt_counter < SENSOR_MAX_READ_ATTEMPTS; attempt_counter++) {
          if (sensor->read_data() != MBED_SUCCESS) {
            log_read_retry(sensor, attempt_counter + 1);
          } else {
            if (!sensor->get_error_state()) {
              sensor->error_counter = 0;
            }
            std::string csv_data;
            sensor->data.get_csv_data(csv_data);
            if (_sd_card.write(sensor->get_file_name(), csv_data) != MBED_SUCCESS) {
              power_off_sensors();
              if (_sd_card.is_full()) {
                _led_indicator.set_behavior_red_led(Led::Behavior::ON);
                return State::Result::SD_CARD_FULL;
              } else {
                return State::Result::SD_CARD_ERROR;
              }
            }
            break;
          }
        }

        if (attempt_counter >= SENSOR_MAX_READ_ATTEMPTS) {
          sensor->error_counter++;
          log_read_failed(sensor);
        }

        if (sensor->get_error_state() && sensor->error_counter < SENSOR_MAX_ERRORS) {
          sensor->error_counter++;
          log_error_pin_high(sensor);
        }

        if (sensor->error_counter >= SENSOR_MAX_ERRORS) {
          sensor->power_off();
          sensor->is_active = false;
          num_active_sensors--;
          log_max_errors_reached(sensor);
          _led_indicator.set_behavior_red_led(Led::Behavior::BLINK_5S);
          continue;
        }

        if (!sensor->is_keep_alive()) {
          sensor->power_off();
        }
      }
    }

    if (num_active_sensors <= 0) {
      Logger::log(Logger::Module::MEASURE_STATE, Logger::Level::DEBUG, "No more active sensors");
      return State::Result::NO_SENSOR_ACTIVE;
    }

    if (time(nullptr) - _file_creation_time >= FILE_CREATION_INTERVAL_SEC) {
      if (init_measurement_files() != MBED_SUCCESS) {
        return State::Result::SD_CARD_ERROR;
      }
    }
  }

  power_off_sensors();
  return State::Result::SUCCESS;
}

uint32_t MeasureState::combine_control_flags() {
  uint32_t wait_flags = CONTROL_FLAG_RESET | CONTROL_FLAG_START_STOP;
  for (auto sensor : _sensors) {
    wait_flags |= CONTROL_FLAG_SENSOR_DATA_READY(sensor->data.address);
    wait_flags |= CONTROL_FLAG_DO_MEASUREMENT(sensor->data.address);
    wait_flags |= CONTROL_FLAG_SENSOR_BOARD_STARTED(sensor->data.address);
  }
  return wait_flags;
}

void MeasureState::log_read_failed(Sensor *sensor) {
  std::string log_message = "Reading measurement data of sensor " + sensor->data.name + " at sensor slot " +
                            std::to_string(sensor->data.address) + " failed. Error counter: " +
                            std::to_string(sensor->error_counter) + " of " + std::to_string(SENSOR_MAX_ERRORS);
  Logger::log(Logger::Module::MEASURE_STATE, Logger::Level::ERROR, log_message);
}

void MeasureState::log_read_retry(Sensor *sensor, int attempt) {
  std::string log_message = "Reading measurement data of sensor " + sensor->data.name + " at sensor slot " +
                            std::to_string(sensor->data.address) + " failed at trial " +
                            std::to_string(attempt) + " of " + std::to_string(SENSOR_MAX_READ_ATTEMPTS);
  Logger::log(Logger::Module::MEASURE_STATE, Logger::Level::ERROR, log_message);
}

void MeasureState::log_error_pin_high(Sensor *sensor) {
  std::string log_message =
      "Error pin of sensor " + sensor->data.name + " at sensor slot " + std::to_string(sensor->data.address) +
      " is high. Error counter: " + std::to_string(sensor->error_counter) + " of " + std::to_string(SENSOR_MAX_ERRORS);
  Logger::log(Logger::Module::MEASURE_STATE, Logger::Level::ERROR, log_message);
}

void MeasureState::log_max_errors_reached(Sensor *sensor) {
  std::string log_message =
      "Set sensor " + sensor->data.name + " at sensor slot " + std::to_string(sensor->data.address) +
      " as inactive. Error counter: " + std::to_string(sensor->error_counter) + " of " +
      std::to_string(SENSOR_MAX_ERRORS);
  Logger::log(Logger::Module::MEASURE_STATE, Logger::Level::ERROR, log_message);
}