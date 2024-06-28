
#ifndef PARTICLE_SENSOR_ERRORSTATE_H
#define PARTICLE_SENSOR_ERRORSTATE_H

#include "State.h"
#include "EventFlags.h"

/**
 * Error state that is entered if any other state returned with an error.
 */
class ErrorState : public State {
public:
  /**
   * Create an ErrorState
   *
   * @param led_indicator       Reference to the LedIndicator to control the status LED
   * @param control_event_flags Reference to the control event flags to react on button presses
   */
  ErrorState(LedIndicator &led_indicator, rtos::EventFlags &control_event_flags);

  /**
   * Set the status LED to red for 3 seconds and start reboot.
   * If an error occurs for MBED_CONF_PLATFORM_ERROR_REBOOT_MAX times, the system will
   * wait for one hour and then reboot again.
   *
   * @return Function never returns, only calls MBED_ERROR(), which results in a reboot
   */
  State::Result handle() override;

private:
  /**
   * Reference to the control event flags object to wait for control events to occur
   */
  rtos::EventFlags &_control_event_flags;
};


#endif //PARTICLE_SENSOR_ERRORSTATE_H
