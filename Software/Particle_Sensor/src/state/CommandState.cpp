
#include "CommandState.h"
#include "ThisThread.h"
#include "Thread.h"
#include "Logger.h"

CommandState::CommandState(LedIndicator &led_indicator, CommandHandler &command_handler,
                           rtos::EventFlags &event_flags)
    : State(led_indicator),
      _command_handler(command_handler),
      _event_flags(event_flags) {
}

State::Result CommandState::handle() {
  LOG(LVL_INFO, "Enter CommandState");
  _led_indicator.display_status_for(LedIndicator::Color::ORANGE);

  State::Result result = run();

  _led_indicator.display_status_for(LedIndicator::Color::OFF);

  return result;
}

State::Result CommandState::run() {
  while (true) {
    if (_command_handler.connect()) {
      break;
    }

    uint32_t wait_flags = _event_flags.wait_any(FLAG_BUTTON_COMMAND, 200);
    if (wait_flags == osFlagsErrorTimeout) {
      continue;
    }
    if (wait_flags & FLAG_BUTTON_COMMAND) {
      return State::Result::COMMAND_PRESSED;
    }

  }

  while (true) {
    uint32_t wait_flags = _event_flags.wait_any(FLAG_BUTTON_COMMAND | FLAG_RECEIVED_COMMAND);
    if (wait_flags & FLAG_BUTTON_COMMAND) {
      _command_handler.disconnect();
      return State::Result::COMMAND_PRESSED;
    }
    if (wait_flags & FLAG_RECEIVED_COMMAND) {
      _command_handler.handle_usb_serial_command();
    }
  }

  return State::Result::SUCCESS;
}