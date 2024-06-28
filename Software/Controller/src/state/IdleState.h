
#ifndef CONTROLLER_IDLESTATE_H
#define CONTROLLER_IDLESTATE_H

#include "State.h"
#include "EventFlags.h"

/**
 * State waiting for a button press
 */
class IdleState : public State {
public:
  /**
   * Create an IdleState
   *
   * @param led_indicator
   * @param control_event_flags
   */
  IdleState(LedIndicator &led_indicator, rtos::EventFlags &control_event_flags);

  /**
   * Wait until a control flag is set caused by a button press
   *
   * @return State::Result::RESET_PRESSED if the CONTROL_FLAG_RESET was set,\n
   *         State::Result::FORMAT_SD_PRESSED if the CONTROL_FLAG_FORMAT_SD was set,\n
   *         State::Result::START_STOP_PRESSED if the CONTROL_FLAG_START_STOP was set,\n
   *         State::Result::COMMAND_PRESSED if the CONTROL_FLAG_COMMAND was set
   */
  State::Result handle() override;

private:
  rtos::EventFlags &_control_event_flags;
};


#endif //CONTROLLER_IDLESTATE_H
