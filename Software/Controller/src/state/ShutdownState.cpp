
#include "ShutdownState.h"
#include "Logger.h"
#include "ThisThread.h"

ShutdownState::ShutdownState(LedIndicator &led_indicator)
    : State(led_indicator) {
}

State::Result ShutdownState::handle() {
  Logger::log(Logger::Module::SHUTDOWN_STATE, Logger::Level::INFO, "Enter ShutdownState");
  _led_indicator.set_behavior_green_led(Led::Behavior::OFF);

  rtos::ThisThread::sleep_for(osWaitForever); // sleep() did not work

  return State::Result::SUCCESS;
}
