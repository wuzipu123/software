
#ifndef PARTICLE_SENSOR_BUTTONS_H
#define PARTICLE_SENSOR_BUTTONS_H

#include "EventFlags.h"
#include "InterruptIn.h"
#include "LowPowerTimer.h"
#include "NonCopyable.h"

/**
 * Class handling button input
 */
class Buttons : private mbed::NonCopyable<Buttons>  {
public:
  /**
   * Create a Buttons object and attach the rise and fall callback functions
   * to the #_button_left and the #_button_right
   *
   * @param event_flags reference to an EventFlags object
   */
  explicit Buttons(rtos::EventFlags &event_flags);

  /**
   * Function to check if #_button_left is currently pressed
   *
   * @return true if #_button_left is pressed, false otherwise
   */
  bool is_left_pressed();

  /**
   * Function to check if #_button_right is currently pressed
   *
   * @return true if #_button_right is pressed, false otherwise
   */
  bool is_right_pressed();

private:
  /**
   * Reference to the EventFlags object, which is used to
   * signal that a button was pressed.
   */
  rtos::EventFlags &_event_flags;

  /**
   * Interrupt input for the left button
   */
  mbed::InterruptIn _button_left;

  /**
   * Interrupt input for the right button
   */
  mbed::InterruptIn _button_right;

  /**
   * Timer measuring how long the #_button_left is pressed
   */
  mbed::LowPowerTimer _button_left_timer;

  /**
   * Timer measuring how long the #_button_right is pressed
   */
  mbed::LowPowerTimer _button_right_timer;

  /**
   * Interrupt handler that is called at the falling edge of #_button_left.
   */
  void button_left_pressed();

  /**
   * Interrupt handler that is called at the rising edge of #_button_right.
   */
  void button_right_pressed();

  /**
   * Interrupt handler that is called at the rising edge of #_button_left.
   * The #FLAG_BUTTON_MEASURE is set in #_event_flags.
   */
  void button_left_released();

  /**
   * Interrupt handler that is called at the rising edge of #_button_right.
   * Depending on the time how long the button was pressed, the #FLAG_BUTTON_STATUS
   * or the #FLAG_BUTTON_COMMAND is set in #_event_flags.
   */
  void button_right_released();
};


#endif //PARTICLE_SENSOR_BUTTONS_H
