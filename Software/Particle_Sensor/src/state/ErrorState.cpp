
#include "ErrorState.h"
#include "Logger.h"
#include "ThisThread.h"

using namespace std;

static int32_t error_reboot_count = 0;

void mbed_error_reboot_callback(mbed_error_ctx *error_context) {
  error_reboot_count = error_context->error_reboot_count;
  printf("\nReboot count: %ld\n\n", error_reboot_count);
}

ErrorState::ErrorState(LedIndicator &led_indicator, rtos::EventFlags &control_event_flags)
    : State(led_indicator),
      _control_event_flags(control_event_flags) {
}

State::Result ErrorState::handle() {
  LOG(LVL_ERROR, "Enter ErrorState");
  _led_indicator.display_status_for(LedIndicator::Color::RED, 3000);
  rtos::ThisThread::sleep_for(3000ms);

  if (error_reboot_count < MBED_CONF_PLATFORM_ERROR_REBOOT_MAX - 1) {
    MBED_ERROR(MBED_ERROR_UNKNOWN, "Application Error! See log file on SD card for details.");
    return State::Result::SUCCESS;
  }

  while (true) {
    LOG(LVL_ERROR, "Wait an hour, then reboot");
    uint32_t wait_flags = _control_event_flags.wait_any(FLAG_BUTTON_STATUS, 3600000);
    if (wait_flags == osFlagsErrorTimeout) {
      mbed_reset_reboot_count();
      MBED_ERROR(MBED_ERROR_UNKNOWN, "Try reboot");
      return State::Result::SUCCESS;
    }
    if (wait_flags & FLAG_BUTTON_STATUS) {
      _led_indicator.display_status_for(LedIndicator::Color::RED, 3000);
      _led_indicator.display_battery_level_for(3000);
    }
  }
}

