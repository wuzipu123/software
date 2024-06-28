
#ifndef CONTROLLER_STATECONTEXT_H
#define CONTROLLER_STATECONTEXT_H

#include "SDCard.h"
#include "Sensor.h"
#include "SensorBoardSerial.h"
#include "CommandHandler.h"
#include "Config.h"
#include "USBSerial.h"
#include "EventFlags.h"
#include "NonCopyable.h"
#include "FlashIAP.h"
#include "State.h"
#include "InitState.h"
#include "IdleState.h"
#include "CheckSensorsState.h"
#include "MeasureState.h"
#include "CommandState.h"
#include "FormatSDState.h"
#include "SDErrorState.h"
#include "ShutdownState.h"

/**
 * Class implementing a finite state machine, holding the State objects
 * and handling the state transitions.
 */
class StateContext : private mbed::NonCopyable<StateContext> {
public:
  /**
   * Create a StateContext
   * Create an object of every State subclass on the heap.
   *
   * @param sd_card             Reference to the SDCard to perform operations on the SD card
   * @param led_indicator       Reference to the LedIndicator to set the LED behavior
   * @param sensors             Reference to the sensors
   * @param command_handler     Reference to the CommandHandler handling commands over the USB serial COM port
   * @param flash               Reference to the FlashIAP to load and store configurations in the flash memory
   * @param control_event_flags Reference to the control event flags to control program flow
   * @param config              Reference to the Config
   */
  StateContext(SDCard &sd_card, LedIndicator &led_indicator, std::vector<Sensor *> &sensors,
               CommandHandler &command_handler, mbed::FlashIAP &flash,
               rtos::EventFlags &control_event_flags, Config &config);

  /**
   * Destructor, delete all State objects from the heap.
   */
  ~StateContext();

  /**
   * Invoke State::handle() of the #_current_state and pass its
   * return value to next_state().
   */
  void handle();

  /**
   * Depending on the given \p result of the #_current_state,
   * the next state is determined and #_current_state is set
   * to point to the next state.
   *
   * @param result The returned #State::Result of the #_current_state, used to determine the next state
   */
  void next_state(State::Result result);

private:
  ///@{
  /** A pointer to the instance of this State. */
  InitState *_init_state;
  CheckSensorsState *_check_sensors_state;
  IdleState *_idle_state;
  MeasureState *_measure_state;
  CommandState *_command_state;
  FormatSDState *_format_sd_state;
  SDErrorState *_sd_error_state;
  ShutdownState *_shutdown_state;
  ///@}

  /** The current state */
  State *_current_state;
};


#endif //CONTROLLER_STATECONTEXT_H
