
#ifndef CONTROLLER_SHUTDOWNSTATE_H
#define CONTROLLER_SHUTDOWNSTATE_H

#include "State.h"

/**
 * State to shutdown the controller
 */
class ShutdownState : public State {
public:
  /**
   * Create a ShutdownState
   *
   * @param led_indicator Reference to the LedIndicator to set the LED behavior
   */
  explicit ShutdownState(LedIndicator &led_indicator);

  /**
   * Let the controller sleep forever.
   * Wakeup not possible. Restart controller through power cycle.
   *
   * @return Does not return
   */
  State::Result handle() override;
};


#endif //CONTROLLER_SHUTDOWNSTATE_H
