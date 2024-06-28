#include "Buttons.h"
#include "constants.h"

Buttons::Buttons(PinName start_stop_button_pin, PinName reset_format_sd_button_pin,
                 rtos::EventFlags &control_event_flags) : _start_stop_cmd_button(start_stop_button_pin,
                                                                                 PinMode::PullUp),
                                                          _reset_format_sd_button(reset_format_sd_button_pin,
                                                                                  PinMode::PullUp),
                                                          _control_event_flags(control_event_flags) {
  _start_stop_cmd_button.fall(mbed::callback(this, &Buttons::start_stop_cmd_press_handler));
  _start_stop_cmd_button.rise(mbed::callback(this, &Buttons::start_stop_cmd_release_handler));
  _reset_format_sd_button.fall(mbed::callback(this, &Buttons::reset_format_sd_press_handler));
  _reset_format_sd_button.rise(mbed::callback(this, &Buttons::reset_format_sd_release_handler));
}

void Buttons::start_stop_cmd_press_handler() {
  _start_stop_cmd_pressed_timer.reset();
  _start_stop_cmd_pressed_timer.start();
}

void Buttons::start_stop_cmd_release_handler() {
  _start_stop_cmd_pressed_timer.stop();
  int press_time = _start_stop_cmd_pressed_timer.read_ms();
  if (press_time > COMMAND_MIN_BUTTON_PRESS_DURATION) {
    _control_event_flags.set(CONTROL_FLAG_COMMAND);
  } else if (press_time > BUTTON_DEBOUNCE_TIME) {
    _control_event_flags.set(CONTROL_FLAG_START_STOP);
  }
}

void Buttons::reset_format_sd_press_handler() {
  _reset_format_sd_pressed_timer.reset();
  _reset_format_sd_pressed_timer.start();
}

void Buttons::reset_format_sd_release_handler() {
  _reset_format_sd_pressed_timer.stop();
  int press_time = _reset_format_sd_pressed_timer.read_ms();
  if (press_time > FORMAT_SD_MIN_BUTTON_PRESS_DURATION) {
    _control_event_flags.set(CONTROL_FLAG_FORMAT_SD);
  } else if (press_time > BUTTON_DEBOUNCE_TIME) {
    _control_event_flags.set(CONTROL_FLAG_RESET);
  }
}
