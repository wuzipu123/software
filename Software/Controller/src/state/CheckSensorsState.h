
#ifndef CONTROLLER_CHECKSENSORSSTATE_H
#define CONTROLLER_CHECKSENSORSSTATE_H

#include "State.h"
#include "Sensor.h"
#include <vector>

/**
 * State that checks which sensors are responding and
 * wether sensors show faulty behavior.
 */
class CheckSensorsState : public State {
public:
  /**
   * Create a CheckSensorsState
   *
   * @param led_indicator Reference to the LedIndicator to set the LED behavior
   * @param sensors       Reference to the sensors to be checked
   */
  CheckSensorsState(LedIndicator &led_indicator, std::vector<Sensor *> &sensors);

  /**
   * Default destructor
   */
  ~CheckSensorsState() override = default;

  /**
   * Check whether the sensor boards are responding or not.\n
   * 1) Power on all sensors\n
   * 2) Wait #SENSOR_BOARD_STARTUP_TIME_MS until the sensor board is started\n
   * 3) For every sensor:\n
   * ....a) For maximum #SENSOR_MAX_ERRORS times:\n
   * ...........If Sensor::init() returns MBED_SUCCESS, set sensor as active and break.\n
   * ....b) Power off sensor\n
   *
   * @return State::Result::SUCCESS if at least one sensor is active,
   *         State::Result::NO_SENSOR_ACTIVE if no sensor is active
   */
  State::Result handle() override;

private:
  /**
   * Reference to the sensors
   */
  std::vector<Sensor *> &_sensors;
};


#endif //CONTROLLER_CHECKSENSORSSTATE_H
