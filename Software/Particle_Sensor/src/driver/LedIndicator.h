
#ifndef PARTICLE_SENSOR_LEDINDICATOR_H
#define PARTICLE_SENSOR_LEDINDICATOR_H

#include "DigitalOut.h"
#include "LowPowerTimeout.h"
#include "NonCopyable.h"

/**
 * Class handling the behaviour ot the battery LEDs and the status LED.
 */
class LedIndicator : private mbed::NonCopyable<LedIndicator> {
public:
  /**
   * Enum defining the possible states for the bicolor status LED.
   */
  enum class Color {
    OFF,
    GREEN,
    RED,
    ORANGE
  };

  /**
   * Creates a new LedIndicator object
   */
  LedIndicator();

  /**
   * Default destructor
   */
  ~LedIndicator() = default;

  /**
   * Displays the battery level on the battery LEDs for the given time.
   *
   * @param duration_ms Time in milliseconds for how long the battery level is displayed
   */
  void display_battery_level_for(uint32_t duration_ms);

  /**
   * Displays the given \p color on the status LEDs for the given time.
   *
   * @param color       The color to be displayed
   * @param duration_ms Time in milliseconds for how long the status is displayed
   */
  void display_status_for(Color color, uint32_t duration_ms = 0);

private:
  /**
   * Switch the battery LEDs according to the given battery level using the
   * defined battery thresholds from LedIndicator.cpp.
   *
   * @param level The battery level in volts to be displayed
   */
  void switch_battery_leds(float level);

  /**
   * Turn off all battery LEDs.
   */
  void turn_off_battery_leds();

  /**
   * Switch the status LED to the given \p color
   *
   * @param color The color to be displayed
   */
  void switch_status_leds(Color color);

  /**
   * Turn off the status LED
   */
  void turn_off_status_leds();

  /**
   * The digital output for the left most battery LED
   */
  mbed::DigitalOut _bat_led_1;
  /**
   * The digital output for the middle battery LED
   */
  mbed::DigitalOut _bat_led_2;
  /**
   * The digital output for the right most battery LED
   */
  mbed::DigitalOut _bat_led_3;

  /**
   * The digital output for the green part of the status LED
   */
  mbed::DigitalOut _status_led_green;
  /**
   * The digital output for the red part of the status LED
   */
  mbed::DigitalOut _status_led_red;

  /**
   * Timeout for the battery LEDs used to switch them off after a specified timeout.
   */
  mbed::LowPowerTimeout _bat_led_timeout;

  /**
   * Timeout for the status LED used to switch it off after a specified timeout.
   */
  mbed::LowPowerTimeout _status_led_timeout;
};


#endif //PARTICLE_SENSOR_LEDINDICATOR_H
