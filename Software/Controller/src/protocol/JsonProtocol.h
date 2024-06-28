
#ifndef CONTROLLER_JSONPROTOCOL_H
#define CONTROLLER_JSONPROTOCOL_H

#include "Protocol.h"

/**
 * Class providing functionality to communicate with the sensor boards
 * using messages in JSON format.
 */
class JsonProtocol : public Protocol {
public:
  /**
   * Create a JsonProtocol using the \p serial as communication channel and
   * \p sensor_data to store the data read from the sensor board.
   *
   * @param serial      Reference to the SensorBoardSerial object
   * @param sensor_data Reference to a SensorData object
   */
  JsonProtocol(SensorBoardSerial &serial, SensorData &sensor_data);

  /** Default destructor */
  ~JsonProtocol() override = default;

  /** \copydoc Protocol::init_measurement() */
  mbed_error_status_t init_measurement() override;

  /** \copydoc Protocol::stop_measurement() */
  mbed_error_status_t stop_measurement() override;

  /** \copydoc Protocol::read_data() */
  mbed_error_status_t read_data() override;

private:
  /**
   * Extract datasets with the measured values from the \p json_string
   * and store the received values in #_sensor_data
   *
   * @param json_string The measured values in a JSON string
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t datasets_from_json(const std::string &json_string);
};


#endif //CONTROLLER_JSONPROTOCOL_H
