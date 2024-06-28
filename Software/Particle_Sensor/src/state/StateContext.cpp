
#include "StateContext.h"
#include "CommandHandler.h"
#include "InitState.h"
#include "MeasureState.h"
#include "CommandState.h"
#include "ErrorState.h"
#include "mbed.h"

StateContext::StateContext(SDCard &sd_card, Communication &communication, LedIndicator &led_indicator,
                           CommandHandler &command_handler, mbed::FlashIAP &flash, rtos::EventFlags &event_flags,
                           SensorSPS30 &sps30, SensorBME280 &bme280, Buttons &buttons)
    : _init_state(new InitState(led_indicator, sd_card, communication, flash, sps30, bme280, buttons)),
      _measure_state(new MeasureState(led_indicator, sd_card, communication, sps30, bme280, event_flags)),
      _command_state(new CommandState(led_indicator, command_handler, event_flags)),
      _error_state(new ErrorState(led_indicator, event_flags)),
      _current_state(_init_state) {
}

StateContext::~StateContext() {
  delete _init_state;
  _init_state = nullptr;
  delete _measure_state;
  _measure_state = nullptr;
  delete _command_state;
  _command_state = nullptr;
  _current_state = nullptr;
}

void StateContext::run() {
  while (true) {
    next_state(_current_state->handle());
  }
}

void StateContext::next_state(State::Result result) {
  if (_current_state == _init_state) {
    switch (result) {
      case State::Result::SUCCESS:
        _current_state = _measure_state;
        break;
      default:
        _current_state = _error_state;
        break;
    }
  } else if (_current_state == _measure_state) {
    switch (result) {
      case State::Result::SUCCESS:
        break;
      case State::Result::COMMAND_PRESSED:
        _current_state = _command_state;
        break;
      default:
        _current_state = _error_state;
        break;
    }
  } else if (_current_state == _command_state) {
    switch (result) {
      case State::Result::SUCCESS:
        break;
      case State::Result::COMMAND_PRESSED:
        _current_state = _measure_state;
        break;
      default:
        _current_state = _error_state;
        break;
    }
  } else if (_current_state == _error_state) {
    switch (result) {
      default:
        break;
    }
  }
}
