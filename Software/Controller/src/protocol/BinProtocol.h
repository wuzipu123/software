
#ifndef CONTROLLER_BINPROTOCOL_H
#define CONTROLLER_BINPROTOCOL_H

#include "Protocol.h"

#define START_BYTE_POS            0U                  //!< Position of the start byte
#define SLAVE_ADDRESS_POS         1U                  //!< Position of the slave address byte
#define MESSAGE_LENGTH_POS        2U                  //!< Position of the first message length byte
#define DATA_POS                  4U                  //!< Position of the first data byte
#define CRC_POS(msg_length)       ((msg_length) - 2U) //!< Position of the first CRC value byte

#define START_BYTE_SIZE           1U                  //!< Size of the start byte
#define SLAVE_ADDRESS_SIZE        1U                  //!< Size of the slave address
#define MESSAGE_LENGTH_SIZE       2U                  //!< Size of the first message length
#define CRC_SIZE                  2U                  //!< Size of the CRC value
#define DATA_SIZE(msg_length)     ((msg_length) - START_BYTE_SIZE - SLAVE_ADDRESS_SIZE - MESSAGE_LENGTH_SIZE \
                                  - CRC_SIZE)         //!< Size of the data

#define BIN_PROTOCOL_START_BYTE   0xA5                //!< Start byte for the BinProtocol

/**
 * Class providing functionality to communicate with the sensor boards
 * using messages in binary format.
 */
class BinProtocol : public Protocol {
public:
  /**
   * Create a BinProtocol using the \p serial as communication channel and
   * \p sensor_data to store the data read from the sensor board.
   *
   * @param serial      Reference to the SensorBoardSerial object
   * @param sensor_data Reference to a SensorData object
   */
  BinProtocol(SensorBoardSerial &serial, SensorData &sensor_data);

  /** Default destructor */
  ~BinProtocol() override = default;

  /** \copydoc Protocol::init_measurement() */
  mbed_error_status_t init_measurement() override;

  /** \copydoc Protocol::stop_measurement() */
  mbed_error_status_t stop_measurement() override;

  /** \copydoc Protocol::read_data() */
  mbed_error_status_t read_data() override;

private:
  /**
   * Enum defining the binary codes for the sensor commands
   */
  enum class SensorCmd {
    SEND_INFO = 0x00U,
    INIT_MEAS = 0x01U,
    STOP_MEAS = 0x02U,
    SEND_DATA = 0x03U
  };

  /**
   * Struct to construct a sensor command message
   */
  struct __attribute__((packed)) command_s {
    uint8_t  start_byte = BIN_PROTOCOL_START_BYTE;
    uint8_t  address    = 0x00;
    uint16_t msg_length = sizeof(command_t);
    uint8_t  command    = 0x00;
    uint16_t crc        = 0x00;
  };

  typedef struct command_s command_t;

  /**
   * Constructs a binary command from \p address and \p sensor_cmd in the
   * format defined by command_t.
   *
   * @param address    Slave address of the sensor board
   * @param sensor_cmd The SensorCmd to send
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t send_bin_command(uint8_t address, SensorCmd sensor_cmd);

  /**
   * Receive a binary message from #_serial.
   * Leading zero-bytes in the message are ignored. The start byte, the address,
   * the message length, and the CRC value are checked.
   *
   * @param response Response in the binary format
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t get_bin_response(std::vector<uint8_t> &response);

  /**
   * Extracts the measured data from the \p response and stores it in the vector \p out.
   * Depending on the #SensorData::data_type, the measured values are interpreted as
   * float or as unsigned integer.
   *
   * @param response The whole response from the sensor board
   * @param out      Output vector with the measured data as float values
   * @return MBED_SUCCESS
   */
  mbed_error_status_t extract_datasets_from_response(const std::vector<uint8_t> &response, std::vector<float> &out);
};


#endif //CONTROLLER_BINPROTOCOL_H
