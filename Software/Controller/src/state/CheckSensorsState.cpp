
#include "CheckSensorsState.h"
#include "Logger.h"
#include "ThisThread.h"
#include "constants.h"
#include "utils.h"

CheckSensorsState::CheckSensorsState(LedIndicator &led_indicator, std::vector<Sensor *> &sensors)
    : State(led_indicator),
      _sensors(sensors) {
}

State::Result CheckSensorsState::handle() {
  Logger::log(Logger::Module::CHECK_SENSOR_STATE, Logger::Level::DEBUG, "Enter CheckSensorState");

  for (auto sensor : _sensors) {
    sensor->power_on();
  }
  rtos::ThisThread::sleep_for(SENSOR_BOARD_STARTUP_TIME_MS);

  int num_active_sensors = 0;
  for (auto sensor : _sensors) {
    int retry_counter;
    for (retry_counter = 0; retry_counter < SENSOR_MAX_ERRORS; retry_counter++) {
      DEBUG_PRINTF("Init sensor %d\n", sensor->data.address);
      mbed_error_status_t error_status = sensor->init();
      if (MBED_SUCCESS == error_status) {
        sensor->is_active = true;
        num_active_sensors++;
        break;
      }
      std::string log_message = "Initialization of sensor at sensor slot "
                                + std::to_string(sensor->data.address) + " failed after "
                                + std::to_string(retry_counter + 1) + " attempt(s)";
      Logger::log(Logger::Module::CHECK_SENSOR_STATE, Logger::Level::ERROR, log_message);
    }

    if (sensor->is_active) {
      std::string log_message = "Successfully initialized sensor " + sensor->data.name
                                + " at sensor slot " + std::to_string(sensor->data.address);
      Logger::log(Logger::Module::CHECK_SENSOR_STATE, Logger::Level::INFO, log_message);
    }

    if (sensor->get_error_state()) {
      std::string log_message = "Error pin of sensor " + sensor->data.name + " at sensor slot "
                                + std::to_string(sensor->data.address) + " is high";
      Logger::log(Logger::Module::CHECK_SENSOR_STATE, Logger::Level::ERROR, log_message);
      _led_indicator.set_behavior_red_led(Led::Behavior::BLINK_5S);
    }

    sensor->power_off();
  }

  if (num_active_sensors == 0) {
    _led_indicator.set_behavior_red_led(Led::Behavior::BLINK_5S);
    return State::Result::NO_SENSOR_ACTIVE;
  }

  return State::Result::SUCCESS;
}
