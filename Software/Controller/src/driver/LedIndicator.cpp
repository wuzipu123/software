
#include "LedIndicator.h"

LedIndicator::LedIndicator(PinName red_led_pin, PinName green_led_pin)
    : _red_led(red_led_pin),
      _green_led(green_led_pin) {
}

void LedIndicator::set_behavior(Led::Behavior red_led_behavior, Led::Behavior green_led_behavior) {
  _red_led.set_behavior(red_led_behavior);
  _green_led.set_behavior(green_led_behavior);
}

void LedIndicator::set_behavior_red_led(Led::Behavior red_led_behavior) {
  set_behavior(red_led_behavior, _green_led.get_behavior());
}

void LedIndicator::set_behavior_green_led(Led::Behavior green_led_behavior) {
  set_behavior(_red_led.get_behavior(), green_led_behavior);
}

