
#ifndef PARTICLE_SENSOR_BATTERY_H
#define PARTICLE_SENSOR_BATTERY_H

/**
 * Static class providing functionality to read battery status
 */
class Battery {
public:
  /**
   * Read the battery level from the analog input.
   *
   * @return the battery level in volts
   */
  static float read_voltage();
};


#endif //PARTICLE_SENSOR_BATTERY_H