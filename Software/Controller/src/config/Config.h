
#ifndef CONTROLLER_CONFIG_H
#define CONTROLLER_CONFIG_H

#include "constants.h"
#include <array>

class Config {
private:
  struct sensor_config_s {
    /**
     * Time in seconds to wait between two consecutive measurements
     */
    int sample_time_sec = DEFAULT_SAMPLE_TIME_SEC;

    /**
     * Boolean value to specify if the sensor should be powered off between
     * two consecutive measurements (false), or should stay powered on (true).
     */
    bool keep_alive = DEFAULT_KEEP_ALIVE;
  };

public:
  /**
   * Struct which stores the configuration for one sensor
   */
  typedef struct sensor_config_s sensor_config_t;

  /**
   * Array of sensor configurations, one for each sensor slot.
   */
  std::array<sensor_config_t, NUM_SENSOR_SLOTS> sensor_configs;
};


#endif //CONTROLLER_CONFIG_H
