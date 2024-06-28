
#ifndef PARTICLE_SENSOR_SENSORSPS30_H
#define PARTICLE_SENSOR_SENSORSPS30_H

#include "sps30.h"
#include "NonCopyable.h"
#include "DigitalOut.h"
#include "BufferedSerial.h"
#include "mbed_error.h"

/**
 * Adapter class providing functions to control the Sensirion SPS30
 * particulate matter sensor.
 */
class SensorSPS30 : private mbed::NonCopyable<SensorSPS30> {
public:
  /**
   * Data structure for SPS30 measurement data
   */
  typedef struct sps30_measurement measurement_t;

  /**
   * Creates a SensorSPS30 object
   */
  SensorSPS30();

  /**
   * Default destructor
   */
  ~SensorSPS30() = default;

  /**
   * Turn power supply on for SPS30
   */
  void power_on();

  /**
   * Turn power supply off for SPS30
   */
  void power_off();

  /**
   * Probe SPS30
   *
   * @return MBED_SUCCESS if probing was successful, MBED_ERROR_FAILED_OPERATION otherwise
   */
  mbed_error_status_t probe();

  /**
   * Read serial number string from SPS30
   *
   * @param serial string to write the serial number to
   * @return MBED_SUCCESS on success, an mbed_error_status_t otherwise
   */
  mbed_error_status_t get_serial(std::string &serial);

  /**
   * Read firmware, hardware and shdlc version number from SPS30
   *
   * @param version struct to store the version numbers to
   * @return MBED_SUCCESS on success, an mbed_error_status_t otherwise
   */
  mbed_error_status_t read_version(sps30_version_information *version);

  /**
   * Set the SPS30 into measurement mode. The SPS30 is then continuously measuring.
   *
   * @return MBED_SUCCESS on success, an mbed_error_status_t otherwise
   */
  mbed_error_status_t start_measurement();

  /**
   * Let the SPS30 exit the measurement mode and turn off the power supply.
   */
  void stop_measurement();

  /**
   * Read new measurement data from the SPS30 and correct the data with correct_data().
   *
   * @param measurement_data Struct to store the measured data to
   * @return MBED_SUCCESS on success, an mbed_error_status_t otherwise
   */
  mbed_error_status_t read_measurement(measurement_t *measurement_data);

  /**
   * Start a fan cleaning process which lasts about 10 seconds.
   *
   * @return MBED_SUCCESS on success, MBED_ERROR_FAILED_OPERATION otherwise
   */
  mbed_error_status_t start_manual_fan_cleaning();

private:
  /**
   * Correct the \p measurement_data with the correction values defined in #Config::global_config
   *
   * @param measurement_data the data to be corrected
   */
  void correct_data(measurement_t *measurement_data);

  /**
   * Digital output for the 5V supply enable
   */
  mbed::DigitalOut _supply_enable;

  /**
   * Serial interface handler
   */
  mbed::BufferedSerial _serial;
};


#endif //PARTICLE_SENSOR_SENSORSPS30_H
