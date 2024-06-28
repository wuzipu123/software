
#ifndef PARTICLE_SENSOR_PROTOCOL_H
#define PARTICLE_SENSOR_PROTOCOL_H

#include "Lora.h"

/**
 * Implements the communication protocol between a sensor node and a smartmote gateway.
 */
class Protocol {
public:
  /**
   * Struct defining the format for the measurement data within a Protocol::node_measured_data_t packet
   */
  typedef struct __attribute__((__packed__)) {
    int16_t temp;
    uint8_t hum;
    uint16_t press;
    uint32_t pm2_5;
    uint8_t particle_size;
  } measured_data_t;

  /**
   * Struct defining the format for the status data within a Protocol::node_status_data_t packet
   */
  typedef struct __attribute__((__packed__)) {
    int16_t bat_level;
    int8_t rssi;
    int8_t snr;
  } status_data_t;

  /**
   * Creates a Protocol object which uses \p lora to exchange packets with the gateway.
   *
   * @param lora Reference to the Lora object acting as a driver for the LoRa module
   */
  explicit Protocol(Lora &lora);

  /**
   * Send an authentication message to the gateway.
   */
  void send_auth();

  /**
   * @return #_client_auth_done, which is true if the node is authenticated and false otherwise
   */
  bool is_auth_done();

  /**
   * Resets the connection by setting #_client_auth_done to false.
   */
  void auth_reset();

  /**
   * Send the given measured \p data in format of Protocol::node_measured_data_t via LoRa to the gateway
   *
   * @param data measured data to be sent
   */
  void send_measured_data(const measured_data_t &data);

  /**
   * Send the given status \p data in format of Protocol::node_status_data_t via LoRa to the gateway
   *
   * @param data status data to be sent
   */
  void send_status_data(const status_data_t &data);

  /**
   * Retrieve the received packets from #_lora and check the validity of the
   * packet with check_auth() or check_ack()
   *
   * @return MBED_SUCESS if a valid authentication responds or a valid acknowledge was received
   *                     and a mbed_error_status_t otherwise
   */
  mbed_error_status_t read_received();

  /**
   * Calculate the software UUID, which is the 32-bit CRC checksum
   * of the app version string.
   *
   * @return the 32-bit software UUID
   */
  static uint32_t get_sw_uuid();

  /**
   * Calculate the hardware UUID, which is the 32-bit CRC checksum
   * from the unique identifier of the microcontroller.
   *
   * @return the 32-bit hardware UUID
   */
  static uint32_t get_hw_uuid();

private:
  /**
   * Struct defining the format for a node authentication request packet
   */
  typedef struct __attribute__((__packed__)) {
    uint8_t smartmote_auth_id;
    uint16_t node_crc;
    uint16_t hw_id;
    uint32_t hw_uuid;
    uint32_t sw_uuid;
    uint16_t crc;
  } node_auth_t;

  /**
   * Struct defining the format for the base station authentication response packet
   */
  typedef struct __attribute__((__packed__)) {
    uint8_t node_id;
    uint16_t base_crc;
    uint16_t crc;
  } base_auth_t;

  /**
   * Struct defining the format for the measurement data packet sent by the node
   */
  typedef struct __attribute__((__packed__)) {
    uint8_t node_id;
    uint8_t type_id;
    measured_data_t values;
    uint16_t crc;
    uint16_t temp_crc;
  } node_measured_data_t;

  /**
   * Struct defining the format for the status data packet sent by the node
   */
  typedef struct __attribute__((__packed__)) {
    uint8_t node_id;
    uint8_t type_id;
    status_data_t values;
    uint16_t crc;
    uint16_t temp_crc;
  } node_status_data_t;

  /**
   * Struct defining the format for the base station acknowledge response on a data packet
   */
  typedef struct __attribute__((__packed__)) base_ack_s {
    uint8_t node_id;
    uint8_t ack;
    uint16_t crc;
  } base_ack_t;

  /**
   * Check if the CRC checksum at the end of \p buf is correct.
   *
   * @param buf  The buffer with a received packet
   * @param size The size of \p buf
   * @return MBED_SUCCESS if the CRC checksum is correct, MBED_ERROR_CRC_ERROR otherwise
   */
  mbed_error_status_t crc_check(const uint8_t *buf, uint16_t size);

  /**
   * Checks the authentication response from the gateway.
   * First, the length is checked, then the #_base_crc is extracted
   * and if the crc_check() was sucessful, the #_node_id is extracted and
   * #_client_auth_done is set to true.
   *
   * @param buf  The buffer with the received authentication response
   * @param size The size of the buffer
   * @return MBED_SUCCESS if the authentication succeeded,
   *         MBED_ERROR_INVALID_SIZE or MBED_ERROR_CRC_ERROR otherwise
   */
  mbed_error_status_t check_auth(const uint8_t *buf, uint16_t size);

  /**
   * Checks the response from the gateway on a sent data packet.
   * After checking the length, the CRC checksum, the _node_id
   * and the acknowledge byte are checked.
   *
   * @param buf  The buffer with the acknowledge packet
   * @param size The size of the buffer
   * @return MBED_SUCCESS if the a valid acknowledge was received, an mbed_error_status_t otherwise
   */
  mbed_error_status_t check_ack(const uint8_t *buf, uint16_t size);

  /**
   * Reference to the Lora object used to control the LoRa module
   */
  Lora &_lora;

  /**
   * The node CRC used to ensure message integrity
   */
  uint16_t _node_crc = 0;

  /**
   * The base CRC used to ensure message integrity
   */
  uint16_t _base_crc = 0;

  /**
   * The node ID assigned by the gateway
   */
  uint8_t _node_id = 0;

  /**
   * Authentication status
   */
  bool _client_auth_done = false;
};


#endif //PARTICLE_SENSOR_PROTOCOL_H
