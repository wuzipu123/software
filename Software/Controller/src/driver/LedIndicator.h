
#ifndef CONTROLLER_LEDINDICATOR_H
#define CONTROLLER_LEDINDICATOR_H

#include "Led.h"
#include "PinNames.h"

/**
 * Class combining two Led objects to provide a single interface to set
 * the behavior of the LEDs.
 */
class LedIndicator {
public:
  /**
   * Create a LedIndicator object with the defined pin names for
   * the red and the green LED.
   *
   * @param red_led_pin   pin name of the red LED
   * @param green_led_pin pin name of the green LED
   */
  LedIndicator(PinName red_led_pin, PinName green_led_pin);

  /**
   * Set the behavior for #_red_led and #_green_led
   *
   * @param red_led_behavior   the behavior for the #_red_led
   * @param green_led_behavior the behavior for the #_green_led
   */
  void set_behavior(Led::Behavior red_led_behavior, Led::Behavior green_led_behavior);

  /**
   * Set the behavior for the #_red_led
   *
   * @param red_led_behavior the behavior for the #_red_led
   */
  void set_behavior_red_led(Led::Behavior red_led_behavior);

  /**
   * Set the behavior for the #_green_led
   *
   * @param green_led_behavior the behavior for the #_green_led
   */
  void set_behavior_green_led(Led::Behavior green_led_behavior);

private:
  /**
   * Led object for the red LED
   */
  Led _red_led;

  /**
   * Led object for the green LED
   */
  Led _green_led;
};


#endif //CONTROLLER_LEDINDICATOR_H
