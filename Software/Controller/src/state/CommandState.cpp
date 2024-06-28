
#include "CommandState.h"
#include "ThisThread.h"
#include "Logger.h"

CommandState::CommandState(LedIndicator &led_indicator, CommandHandler &command_handler,
                           rtos::EventFlags &control_event_flags)
    : State(led_indicator),
      _command_handler(command_handler),
      _control_event_flags(control_event_flags) {
}

State::Result CommandState::handle() {
  Logger::log(Logger::Module::COMMAND_STATE, Logger::Level::DEBUG, "Enter CommandState");
  _led_indicator.set_behavior_green_led(Led::Behavior::BLINK_INV_2S);

  while (true) {
    if (_command_handler.connect()) {
      break;
    }

    uint32_t flags_read = _control_event_flags.wait_any(CONTROL_FLAG_RESET | CONTROL_FLAG_COMMAND, 500);
    if(flags_read == osFlagsErrorTimeout) {
      continue;
    }
    if (flags_read & CONTROL_FLAG_RESET) {
      return State::Result::RESET_PRESSED;
    }
    if (flags_read & CONTROL_FLAG_COMMAND) {
      return State::Result::COMMAND_PRESSED;
    }
  }

  while (true) {
    uint32_t flags_read = _control_event_flags.wait_any(CONTROL_FLAG_RESET | CONTROL_FLAG_COMMAND
                                                        | CONTROL_FLAG_RECEIVED_COMMAND);
    if (flags_read & CONTROL_FLAG_RESET) {
      _command_handler.disconnect();
      return State::Result::RESET_PRESSED;
    }
    if (flags_read & CONTROL_FLAG_COMMAND) {
      _command_handler.disconnect();
      return State::Result::COMMAND_PRESSED;
    }
    if (flags_read & CONTROL_FLAG_RECEIVED_COMMAND) {
      _command_handler.handle_usb_serial_command();
    }
  }

  return State::Result::SUCCESS;
}
