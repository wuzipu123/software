
#ifndef CONTROLLER_LED_H
#define CONTROLLER_LED_H

#include "LowPowerTicker.h"
#include "DigitalOut.h"

/**
 * Class handling the state and timing behavior of an LED
 */
class Led {
public:
  /**
   * Enum defining the possible behaviors of the LED
   */
  enum class Behavior {
    OFF = 0,      //!< LED constantly turned off
    ON,           //!< LED constantly turned on
    BLINK_250MS,  //!< Led is turned on every 250ms for 125ms
    BLINK_1S,     //!< Led is turned on every second for 250ms
    BLINK_5S,     //!< Led is turned on every 5s for 250ms
    BLINK_15S,    //!< Led is turned on every 15s for 250ms
    BLINK_INV_2S  //!< Led is turned off every 2s for 250ms
  };

  /**
   * Create a Led object for the given \p pin
   *
   * @param pin name of the pin connected to the LED
   */
  explicit Led(PinName pin);

  /**
   * Default destructor
   */
  virtual ~Led() = default;

  /**
   * Sets the behavior of the LED to the given \p behavior
   *
   * @param behavior to set the LED to
   */
  void set_behavior(Behavior behavior);

  /**
   * @return current #_behavior
   */
  Behavior get_behavior() const;

private:
  /**
   * Enum defining the digital states of the LED
   */
  enum State {
    ON = 0,
    OFF = 1
  };

  /**
   * The currently set behavior
   */
  Behavior _behavior;

  /**
   * DigitalOut object used to control the LED pin
   */
  mbed::DigitalOut _led;

  /**
   * Ticker used to repeatedly turn on the LED at a fixed time interval
   */
  mbed::LowPowerTicker _ticker_on;

  /**
   * Ticker used to repeatedly turn off the LED at a fixed time interval
   */
  mbed::LowPowerTicker _ticker_off;

  /**
   * If the #_behavior is set to blinking, the #_led is blinking every #_period seconds
   */
  float _period;

  /**
   * Flag which is set as soon as _turn_on() is attached to #_ticker_on
   */
  bool _ticker_on_attached;

  /**
   * Flag which is set as soon as _turn_off() is attached to #_ticker_off
   */
  bool _ticker_off_attached;

  /**
   * Callback function to turn the #_led on.
   */
  void _turn_on();

  /**
   * Callback function to turn the #_led off.
   */
  void _turn_off();

  /**
   * Set the two tickers #_ticker_on and #_ticker_off to let the #_led blink according
   * to the given parameters.
   *
   * @param time_shift Time in seconds within the period after which the led is turned on
   * @param period     Time in seconds defining the blinking period
   * @param on_time    Time in seconds defining how long the led is turned on within a period
   */
   void _set_tickers(float time_shift, float period, float on_time);
};


#endif //CONTROLLER_LED_H
