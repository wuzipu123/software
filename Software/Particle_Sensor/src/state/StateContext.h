
#ifndef PARTICLE_SENSOR_STATECONTEXT_H
#define PARTICLE_SENSOR_STATECONTEXT_H

#include "SensorSPS30.h"
#include "SensorBME280.h"
#include "Communication.h"
#include "SDCard.h"
#include "LedIndicator.h"
#include "CommandHandler.h"
#include "Config.h"
#include "USBSerial.h"
#include "EventFlags.h"
#include "NonCopyable.h"
#include "FlashIAP.h"
#include "Buttons.h"
#include "State.h"
#include "InitState.h"
#include "MeasureState.h"
#include "CommandState.h"
#include "ErrorState.h"

/**
 * Class implementing a finite state machine, holding the State objects
 * and handling the state transitions.
 */
class StateContext : private mbed::NonCopyable<StateContext> {
public:
  /**
   * Create a StateContext
   * Create an instance of every State subclass on the heap.
   *
   * @param sd_card         Reference to the SDCard to perform operations on the SD card
   * @param communication   Reference to the Communication object
   * @param led_indicator   Reference to the LedIndicator to set the LED behavior
   * @param command_handler Reference to the CommandHandler handling commands over the USB serial COM port
   * @param flash           Reference to the FlashIAP to load and store configurations in the flash memory
   * @param event_flags     Reference to the event flags used to control the program flow
   * @param sps30           Reference to the SensorSPS30 object
   * @param bme280          Reference to the BME280 object
   * @param buttons         Reference to the Buttons object
   */
  StateContext(SDCard &sd_card, Communication &communication, LedIndicator &led_indicator,
               CommandHandler &command_handler, mbed::FlashIAP &flash, rtos::EventFlags &event_flags,
               SensorSPS30 &sps30, SensorBME280 &bme280, Buttons &buttons);

  /**
   * Destructor, delete all State objects from the heap.
   */
  ~StateContext();

  /**
   * Invoke State::handle() of the #_current_state and pass its
   * return value to next_state().
   */
  void run();

  /**
   * Depending \p result the next state is determined and the #_current_state
   * pointer is set to the next state.
   *
   * @param result The #State::Result of the #_current_state, used to determine the next state
   */
  void next_state(State::Result result);

private:
  ///@{
  /** A pointer to the instance of this State. */
  InitState *_init_state;
  MeasureState *_measure_state;
  CommandState *_command_state;
  ErrorState *_error_state;
  ///@}

  /** The current state */
  State *_current_state;
};


#endif //PARTICLE_SENSOR_STATECONTEXT_H
