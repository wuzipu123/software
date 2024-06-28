
#include "IdleState.h"
#include "Logger.h"
#include "constants.h"

IdleState::IdleState(LedIndicator &led_indicator, rtos::EventFlags &control_event_flags)
    : State(led_indicator),
      _control_event_flags(control_event_flags) {
}

State::Result IdleState::handle() {
  Logger::log(Logger::Module::IDLE_STATE, Logger::Level::INFO, "Enter IdleState");
  _led_indicator.set_behavior_green_led(Led::Behavior::BLINK_5S);

  uint32_t flags_read = _control_event_flags.wait_any(CONTROL_FLAG_START_STOP | CONTROL_FLAG_RESET |
                                                      CONTROL_FLAG_FORMAT_SD | CONTROL_FLAG_COMMAND);
  if (flags_read & CONTROL_FLAG_RESET) {
    return State::Result::RESET_PRESSED;
  }
  if (flags_read & CONTROL_FLAG_FORMAT_SD) {
    return State::Result::FORMAT_SD_PRESSED;
  }
  if (flags_read & CONTROL_FLAG_START_STOP) {
    return State::Result::START_STOP_PRESSED;
  }
  if (flags_read & CONTROL_FLAG_COMMAND) {
    return State::Result::COMMAND_PRESSED;
  }
  return State::Result::SUCCESS;
}
