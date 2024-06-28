
#ifndef CONTROLLER_BUTTONS_H
#define CONTROLLER_BUTTONS_H

#include "InterruptIn.h"
#include "EventFlags.h"
#include "LowPowerTimer.h"

/**
 * Class handling button input
 */
class Buttons {
public:
  /**
   * Create a Buttons object and attach the callback functions to the
   * #_start_stop_cmd_button and the #_reset_format_sd_button
   *
   * @param start_stop_cmd_button_pin  pin name of the start, stop and command button
   * @param reset_format_sd_button_pin pin name of the reset and format SD button
   * @param control_event_flags        reference to an EventFlags object
   */
  Buttons(PinName start_stop_cmd_button_pin, PinName reset_format_sd_button_pin, rtos::EventFlags &control_event_flags);

  /**
   * Default destructor
   */
  virtual ~Buttons() = default;

private:
  /**
   * Interrupt input for the button which is used to start or stop the measurement
   * or to enter and exit the command handling state.
   */
  mbed::InterruptIn _start_stop_cmd_button;

  /**
   * Interrupt input for the button which is used to reset the controller
   * or to initilize the formatting of the SD card.
   */
  mbed::InterruptIn _reset_format_sd_button;

  /**
   * Timer that measures how long the #_start_stop_cmd_button is pressed
   */
  mbed::LowPowerTimer _start_stop_cmd_pressed_timer;

  /**
   * Timer that measures how long the #_reset_format_sd_button is pressed
   */
  mbed::LowPowerTimer _reset_format_sd_pressed_timer;

  /**
   * Reference to the EventFlags object used to signal the
   * State objects that a button was pressed.
   */
  rtos::EventFlags &_control_event_flags;

  /**
   * Interrupt handler that is called at the falling edge of #_start_stop_cmd_button.
   */
  void start_stop_cmd_press_handler();

  /**
   * Interrupt handler that is called at the rising edge of #_start_stop_cmd_button.
   * Depending on the time how long the button was pressed, the #CONTROL_FLAG_START_STOP
   * or the #CONTROL_FLAG_COMMAND is set in #_control_event_flags.
   */
  void start_stop_cmd_release_handler();

  /**
   * Interrupt handler that is called at the falling edge of #_reset_format_sd_button.
   */
  void reset_format_sd_press_handler();

  /**
   * Interrupt handler that is called at the rising edge of #_reset_format_sd_button.
   * Depending on the time how long the button was pressed, the #CONTROL_FLAG_RESET
   * or the #CONTROL_FLAG_FORMAT_SD is set in #_control_event_flags.
   */
  void reset_format_sd_release_handler();
};


#endif //CONTROLLER_BUTTONS_H
