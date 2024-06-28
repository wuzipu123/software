
#include "StateContext.h"

StateContext::StateContext(SDCard &sd_card, LedIndicator &led_indicator, std::vector<Sensor *> &sensors,
                           CommandHandler &command_handler, mbed::FlashIAP &flash,
                           rtos::EventFlags &control_event_flags, Config &config)
    : _init_state(new InitState(led_indicator, sd_card, config, flash)),
      _check_sensors_state(new CheckSensorsState(led_indicator, sensors)),
      _idle_state(new IdleState(led_indicator, control_event_flags)),
      _measure_state(new MeasureState(led_indicator, sd_card, sensors, control_event_flags, config)),
      _command_state(new CommandState(led_indicator, command_handler, control_event_flags)),
      _format_sd_state(new FormatSDState(led_indicator, sd_card)),
      _sd_error_state(new SDErrorState(led_indicator, sd_card, control_event_flags)),
      _shutdown_state(new ShutdownState(led_indicator)),
      _current_state(_init_state) {
}

StateContext::~StateContext() {
  delete _init_state;
  _init_state = nullptr;
  delete _check_sensors_state;
  _check_sensors_state = nullptr;
  delete _idle_state;
  _idle_state = nullptr;
  delete _measure_state;
  _measure_state = nullptr;
  delete _command_state;
  _command_state = nullptr;
  delete _format_sd_state;
  _format_sd_state = nullptr;
  delete _sd_error_state;
  _sd_error_state = nullptr;
  delete _shutdown_state;
  _shutdown_state = nullptr;
  _current_state = nullptr;
}

void StateContext::handle() {
  next_state(_current_state->handle());
}

void StateContext::next_state(State::Result result) {
  if (_current_state == _init_state) {
    switch (result) {
      case State::Result::SUCCESS:
        _current_state = _check_sensors_state;
        break;
      case State::Result::SD_CARD_ERROR:
        _current_state = _sd_error_state;
        break;
      default:
        break;
    }
  } else if (_current_state == _check_sensors_state) {
    switch (result) {
      case State::Result::SUCCESS:
        _current_state = _idle_state;
        break;
      case State::Result::NO_SENSOR_ACTIVE:
        _current_state = _shutdown_state;
        break;
      default:
        break;
    }
  } else if (_current_state == _idle_state) {
    switch (result) {
      case State::Result::SUCCESS:
        break;
      case State::Result::START_STOP_PRESSED:
        _current_state = _measure_state;
        break;
      case State::Result::FORMAT_SD_PRESSED:
        _current_state = _format_sd_state;
        break;
      case State::Result::COMMAND_PRESSED:
        _current_state = _command_state;
        break;
      case State::Result::RESET_PRESSED:
        HAL_NVIC_SystemReset();
        break;
      default:
        break;
    }
  } else if (_current_state == _measure_state) {
    switch (result) {
      case State::Result::SUCCESS:
        break;
      case State::Result::START_STOP_PRESSED:
        _current_state = _idle_state;
        break;
      case State::Result::RESET_PRESSED:
        HAL_NVIC_SystemReset();
        break;
      case State::Result::SD_CARD_ERROR:
        _current_state = _sd_error_state;
        break;
      case State::Result::SD_CARD_FULL:
        _current_state = _shutdown_state;
        break;
      case State::Result::SERIAL_ERROR:
        _current_state = _shutdown_state;
        break;
      case State::Result::NO_SENSOR_ACTIVE:
        _current_state = _shutdown_state;
        break;
      default:
        break;
    }
  } else if (_current_state == _command_state) {
    switch (result) {
      case State::Result::SUCCESS:
        _current_state = _idle_state;
        break;
      case State::Result::COMMAND_PRESSED:
        _current_state = _idle_state;
        break;
      case State::Result::RESET_PRESSED:
        HAL_NVIC_SystemReset();
        break;
      default:
        break;
    }
  } else if (_current_state == _format_sd_state) {
    switch (result) {
      case State::Result::SUCCESS:
        _current_state = _init_state;
        break;
      case State::Result::SD_CARD_ERROR:
        _current_state = _sd_error_state;
        break;
      default:
        break;
    }
  } else if (_current_state == _sd_error_state) {
    switch (result) {
      case State::Result::SUCCESS:
        break;
      case State::Result::RESET_PRESSED:
        HAL_NVIC_SystemReset();
        break;
      case State::Result::FORMAT_SD_PRESSED:
        _current_state = _format_sd_state;
        break;
      default:
        break;
    }
  } else if (_current_state == _shutdown_state) {
    switch (result) {
      case State::Result::SUCCESS:
        break;
      default:
        break;
    }
  }
}
