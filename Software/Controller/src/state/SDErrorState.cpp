
#include "SDErrorState.h"
#include "Logger.h"
#include "constants.h"

SDErrorState::SDErrorState(LedIndicator &led_indicator, SDCard &sd_card, rtos::EventFlags &control_event_flags)
    : State(led_indicator),
      _sd_card(sd_card),
      _control_event_flags(control_event_flags) {
}

State::Result SDErrorState::handle() {
  if (_sd_card.is_full()) {
    Logger::log(Logger::Module::SD_ERROR_STATE, Logger::Level::ERROR,
                "Enter SDErrorState because SD card is full");
    _led_indicator.set_behavior(Led::Behavior::ON, Led::Behavior::BLINK_1S);
  } else {
    _led_indicator.set_behavior(Led::Behavior::BLINK_1S, Led::Behavior::BLINK_1S);
  }

  uint32_t flags_read = _control_event_flags.wait_any(CONTROL_FLAG_RESET | CONTROL_FLAG_FORMAT_SD);
  if (flags_read & CONTROL_FLAG_RESET) {
    return State::Result::RESET_PRESSED;
  }
  if (flags_read & CONTROL_FLAG_FORMAT_SD) {
    return State::Result::FORMAT_SD_PRESSED;
  }
  return State::Result::SUCCESS;
}
