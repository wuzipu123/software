
#include "LedIndicator.h"
#include "Battery.h"
#include "Logger.h"
#include <chrono>

#define BATTERY_THRESHOLD_LED_1 7.07
#define BATTERY_THRESHOLD_LED_2 7.24
#define BATTERY_THRESHOLD_LED_3 7.64

using namespace std;

LedIndicator::LedIndicator() : _bat_led_1(MBED_CONF_APP_BATTERY_LED_1, false),
                               _bat_led_2(MBED_CONF_APP_BATTERY_LED_2, false),
                               _bat_led_3(MBED_CONF_APP_BATTERY_LED_3, false),
                               _status_led_green(MBED_CONF_APP_STATUS_LED_GREEN, false),
                               _status_led_red(MBED_CONF_APP_STATUS_LED_RED, false) {

}

void LedIndicator::turn_off_battery_leds() {
  _bat_led_1 = false;
  _bat_led_2 = false;
  _bat_led_3 = false;
}

void LedIndicator::switch_battery_leds(float level) {
  if (level >= BATTERY_THRESHOLD_LED_1 && level < BATTERY_THRESHOLD_LED_2) {
    _bat_led_1 = true;
    _bat_led_2 = false;
    _bat_led_3 = false;
  } else if (level >= BATTERY_THRESHOLD_LED_2 && level < BATTERY_THRESHOLD_LED_3) {
    _bat_led_1 = true;
    _bat_led_2 = true;
    _bat_led_3 = false;
  } else if (level >= BATTERY_THRESHOLD_LED_3) {
    _bat_led_1 = true;
    _bat_led_2 = true;
    _bat_led_3 = true;
  } else {
    turn_off_battery_leds();
  }
}

void LedIndicator::display_battery_level_for(uint32_t duration_ms) {
  float battery_level = Battery::read_voltage();
  switch_battery_leds(battery_level);
  LOG(LVL_DEBUG, "battery voltage: %.3fV", battery_level);
  _bat_led_timeout.attach(mbed::callback(this, &LedIndicator::turn_off_battery_leds),
                          std::chrono::milliseconds(duration_ms));
}

void LedIndicator::turn_off_status_leds() {
  _status_led_green = false;
  _status_led_red = false;
}

void LedIndicator::switch_status_leds(Color color) {
  switch (color) {
    case Color::OFF:
      _status_led_green = false;
      _status_led_red = false;
      break;
    case Color::GREEN:
      _status_led_green = true;
      _status_led_red = false;
      break;
    case Color::RED:
      _status_led_green = false;
      _status_led_red = true;
      break;
    case Color::ORANGE:
      _status_led_green = true;
      _status_led_red = true;
      break;
  }
}

void LedIndicator::display_status_for(Color color, uint32_t duration_ms) {
  switch_status_leds(color);
  if (duration_ms) {
    _status_led_timeout.attach(mbed::callback(this, &LedIndicator::turn_off_status_leds),
                               std::chrono::milliseconds(duration_ms));
  }
}