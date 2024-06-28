
#ifndef PARTICLE_SENSOR_STATE_H
#define PARTICLE_SENSOR_STATE_H

#include "LedIndicator.h"

/**
 * Abstract base class for all states
 */
class State {
public:
  /**
   * Enum defining the possible return values for the states
   */
  enum class Result {
    SUCCESS,
    SENSOR_ERROR,
    SD_CARD_ERROR,
    FLASH_ERROR,
    LORA_ERROR,
    COMMAND_PRESSED
  };

  /**
   * Base constructor
   *
   * @param _led_indicator Reference to the LedIndicator object
   */
  explicit State(LedIndicator &_led_indicator);

  /**
   * Virtual default destructor
   */
  virtual ~State() = default;

  /**
   * Pure virtual method handling the functions of the state.
   * This method is called infinitely as long as the state is active.
   *
   * @return result why the the handle function returned.
   *         This return value is used to decide which state is the next one
   */
  virtual State::Result handle() = 0;

protected:
  /**
   * Reference to the LedIndicator object.
   * Used to set the LEDs behavior according to the current state.
   */
  LedIndicator &_led_indicator;
};


#endif //PARTICLE_SENSOR_STATE_H
