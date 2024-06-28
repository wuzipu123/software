
#ifndef PARTICLE_SENSOR_COMMANDSTATE_H
#define PARTICLE_SENSOR_COMMANDSTATE_H

#include "State.h"
#include "CommandHandler.h"
#include "EventFlags.h"

/**
 * State that allows to execute commands received over the
 * USB virtual COM port.
 */
class CommandState : public State {
public:
  /**
   * Create a CommandState
   *
   * @param led_indicator   Reference to the LedIndicator to set the LED behavior
   * @param command_handler Reference to the CommandHandler doing the actual command handling
   * @param event_flags     Reference to the control event flags to react on button presses and incoming commands.
   */
  CommandState(LedIndicator &led_indicator, CommandHandler &command_handler, rtos::EventFlags &event_flags);

  /**
   * Default destructor
   */
  ~CommandState() override = default;

  /**
   * Set the status LED color to orange and call run()
   * to handle the connection and incoming commands.
   *
   * @return State::Result::COMMAND_PRESSED
   */
  State::Result handle() override;

private:
  /**
   * CommandHandler object used to connect and disconnect to the serial terminal
   * and to dispatch the incoming commands.
   */
  CommandHandler &_command_handler;

  /**
   * Reference to the control event flags object to wait for control events to occur
   */
  rtos::EventFlags &_event_flags;

  /**
   * Handle connection and incoming commands in the following order:
   * Wait in an endless loop for a serial terminal to connect.
   * If a serial terminal connected, start handling incoming commands by
   * calling CommandHandler::handle_usb_serial_command() if #FLAG_RECEIVED_COMMAND is set.
   *
   * @return State::Result::COMMAND_PRESSED if the #FLAG_BUTTON_COMMAND was set
   */
  State::Result run();
};


#endif //PARTICLE_SENSOR_COMMANDSTATE_H
