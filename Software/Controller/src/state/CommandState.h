
#ifndef CONTROLLER_COMMANDSTATE_H
#define CONTROLLER_COMMANDSTATE_H

#include "State.h"
#include "CommandHandler.h"
#include "EventFlags.h"

/**
 * State that allows to execute commands received over the
 * USB virtual COM port to print and set various parameters.
 */
class CommandState : public State {
public:
  /**
   * Create a CommandState
   *
   * @param led_indicator       Reference to the LedIndicator to set the LED behavior
   * @param command_handler     Reference to the CommandHandler doing the actual command handling
   * @param control_event_flags Reference to the control event flags to react on button presses and incoming commands.
   */
  CommandState(LedIndicator &led_indicator, CommandHandler &command_handler, rtos::EventFlags &control_event_flags);

  /**
   * Default destructor
   */
  ~CommandState() override = default;

  /**
   * Handle the connection and incoming commands.
   * Waits in a endless loop for a serial terminal to connect.
   * If a serial terminal connected, CommandHandler::handle_usb_serial_command()
   * is called if #CONTROL_FLAG_RECEIVED_COMMAND is set.
   *
   * @return State::Result::RESET_PRESSED if the #CONTROL_FLAG_RESET was set,\n
   *         State::Result::COMMAND_PRESSED if the #CONTROL_FLAG_COMMAND was set
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
  rtos::EventFlags &_control_event_flags;
};


#endif //CONTROLLER_COMMANDSTATE_H
