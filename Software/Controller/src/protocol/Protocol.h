
#ifndef CONTROLLER_PROTOCOL_H
#define CONTROLLER_PROTOCOL_H

#include "SensorBoardSerial.h"
#include "SensorData.h"
#include "MbedCRC.h"
#include "mbed_error.h"

/**
 * Abstract class to derive a specific Protocol from.
 * Defines the protocol which is used to communicate with the sensor boards.
 */
class Protocol {
public:
  /** Start byte signalling the start of a message in the JSON format */
  const char json_start_byte = 0x02;

  /** Stop byte signalling the end of a message in the JSON format */
  const char json_stop_byte = 0x03;

  /**
   * Create a Protocol using the \p serial as communication channel and
   * \p sensor_data to store the data read from the sensor board.
   *
   * @param serial           Reference to the SensorBoardSerial object
   * @param sensor_data      Reference to a SensorData object
   * @param protocol_version Version of the protocol, e.g "2.0"
   */
  Protocol(SensorBoardSerial &serial, SensorData &sensor_data, std::string protocol_version);

  /** Virtual default destructor */
  virtual ~Protocol() = default;

  /**
   * Request sensor board to send information about the sensor.
   * The received information is stored in #_sensor_data.
   * To ensure backwards compatibility, this request and response
   * is always sent and received in the JSON format.
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t get_sensor_info();

  /**
   * Send init measurement command over the SensorBoardSerial bus
   * to let the sensor start the measurement.
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  virtual mbed_error_status_t init_measurement() = 0;

  /**
   * Send stop measurement command over the SensorBoardSerial bus
   * to let the sensor stop the measurement.
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  virtual mbed_error_status_t stop_measurement() = 0;

  /**
   * Send read data command over the SensorBoardSerial bus and wait for
   * the sensor board to respond with the latest measured values.
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  virtual mbed_error_status_t read_data() = 0;

  /**
   * @return const reference to #_protocol_version
   */
  const std::string &get_protocol_version() const;

protected:
  /** Version of the protocol */
  std::string _protocol_version;

  /** Reference to the SensorBoardSerial object */
  SensorBoardSerial &_serial;

  /** Reference to the SensorData object */
  SensorData &_sensor_data;

  /**
   * Read a JSON response from the #_serial beginning with a #json_start_byte
   * and ending with a #json_stop_byte. If the character before the #json_stop_byte
   * is not a '}', the four characters preceding the #json_stop_byte are the CRC value encoded
   * as hex string. This CRC is compared to the calculated CRC value.
   * The #json_start_byte, the #json_stop_byte and the optional CRC value
   * are not written to the \p response.
   *
   * @param response String where the response is written to
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t get_json_response(std::string &response);

  /**
   * Construct a JSON formatted command out of the slave \p address and a
   * command \p cmd_string.
   *
   * @param address    Slave address of the sensor board to send the command to
   * @param cmd_string Command string, e.g. init_meas
   * @param dest       String where the combined JSON command is written to
   */
  void build_json_cmd(uint8_t address, const std::string &cmd_string, std::string &dest) const;

  /**
   * Computes a 16-Bit CRC value out of the given \p data with the given \p size.
   * The used generating polynomial is POLY_16BIT_CCITT = 0x1021.
   *
   * @param data
   * @param size
   * @return
   */
  static uint32_t compute_crc16(const void *const data, uint64_t size);

  /**
   * Checks if \p response includes a CRC and if so, the CRC value is checked
   * and removed from the response.
   *
   * @param response
   * @return MBED_SUCESS if no CRC is included in \p response or CRC value is correct.
   *         MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_CRC_ERROR) if CRC is wrong.
   */
  static mbed_error_status_t check_and_remove_crc(std::string &response);
};


#endif //CONTROLLER_PROTOCOL_H
