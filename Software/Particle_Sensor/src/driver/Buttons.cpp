
#include "Buttons.h"
#include "defines.h"

Buttons::Buttons(rtos::EventFlags &event_flags) :
    _event_flags(event_flags),
    _button_left(MBED_CONF_APP_BUTTON_1),
    _button_right(MBED_CONF_APP_BUTTON_2) {
  _button_left.fall(mbed::callback(this, &Buttons::button_left_pressed));
  _button_left.rise(mbed::callback(this, &Buttons::button_left_released));
  _button_right.fall(mbed::callback(this, &Buttons::button_right_pressed));
  _button_right.rise(mbed::callback(this, &Buttons::button_right_released));
}

void Buttons::button_left_pressed() {
  _button_left_timer.reset();
  _button_left_timer.start();
}

void Buttons::button_right_pressed() {
  _button_right_timer.reset();
  _button_right_timer.start();
}

void Buttons::button_left_released() {
  _button_left_timer.stop();
  uint32_t press_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      _button_left_timer.elapsed_time()).count();
  if (press_time > BUTTON_DEBOUNCE_TIME) {
    _event_flags.set(FLAG_BUTTON_MEASURE);
  }
}

void Buttons::button_right_released() {
  _button_right_timer.stop();
  uint32_t press_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      _button_right_timer.elapsed_time()).count();
  if (press_time > BUTTON_COMMAND_MIN_PRESS_TIME) {
    _event_flags.set(FLAG_BUTTON_COMMAND);
  } else if (press_time > BUTTON_DEBOUNCE_TIME) {
    _event_flags.set(FLAG_BUTTON_STATUS);
  }
}

bool Buttons::is_left_pressed() {
  return !_button_left;
}

bool Buttons::is_right_pressed() {
  return !_button_right;
}