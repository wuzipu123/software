
#include "FormatSDState.h"
#include "Logger.h"

FormatSDState::FormatSDState(LedIndicator &led_indicator, SDCard &sd_card)
    : State(led_indicator),
      _sd_card(sd_card) {
}

State::Result FormatSDState::handle() {
  Logger::log(Logger::Module::FORMAT_SD_STATE, Logger::Level::DEBUG, "Enter FormatSDState");
  _led_indicator.set_behavior(Led::Behavior::OFF, Led::Behavior::BLINK_250MS);

  if (_sd_card.format() != MBED_SUCCESS) {
    return State::Result::SD_CARD_ERROR;
  }
  return State::Result::SUCCESS;
}
