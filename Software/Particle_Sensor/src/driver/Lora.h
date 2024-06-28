
#ifndef PARTICLE_SENSOR_LORA_H
#define PARTICLE_SENSOR_LORA_H

#include "SX126X_LoRaRadio.h"
#include "EventFlags.h"
#include "LowPowerTimeout.h"
#include "mbed_error.h"
#include "NonCopyable.h"

#define LORA_CFG_MODEM            MODEM_LORA
#define LORA_CFG_TX_FDEV          25000
#define LORA_CFG_RX_BANDWITH_AFC  0
#define LORA_CFG_RX_PAYLOAD_LEN   255

/**
 * Class acting as an adapter to provide simple functions
 * to control the LoRa module.
 */
class Lora : private mbed::NonCopyable<Lora> {
public:
  /**
   * Create a new Lora object
   */
  Lora();

  /**
   * Initialize Lora object by setting the #_radio_callbacks initializing
   * the #_radio and setting radio specific parameters.
   */
  void init();

  /**
   * Set the LoRa module to sleep mode
   */
  void sleep();

  /**
   * Set LoRa module into standby mode, send \p data of the given \p size
   * via the LoRa module and wait until the transmission is done.
   *
   * @param data Data to be sent
   * @param size Size of the data
   */
  void send(uint8_t *data, uint8_t size);

  /**
   * Wait to receive a LoRa packet for a maximum time of #LORA_RX_TIMEOUT_MS.
   *
   * @return MBED_SUCCESS if a packet was received, MBED_ERROR_TIME_OUT on timeout
   */
  mbed_error_status_t receive();

  /**
   * Data buffer for the last packet received
   */
  uint8_t rx_payload[MAX_DATA_BUFFER_SIZE_SX126X];

  /**
   * Size of the last packet received
   */
  uint16_t rx_payload_len = 0;

  /**
   * Received Signal Strength Indicator (RSSI) for the last packet received
   */
  int8_t rx_rssi = 0;

  /**
   * Signal to Noise Ratio (SNR) for the last packet received
   */
  int8_t rx_snr = 0;

  /**
   * Set the TX parameters of #_radio to the values defined in the #Config::global_config
   */
  void set_tx_config();

  /**
   * Set the RX parameters of #_radio to the values defined in the #Config::global_config
   */
  void set_rx_config();

private:
  /**
   * Callback function which is called as soon as a LoRa packet is fully transmitted
   */
  void tx_done_cb();

  /**
   * Callback function which is called on a receive error
   */
  void rx_error_cb();

  /**
   * Callback function which is called if a transmit timeout occurs
   */
  void tx_timeout_cb();

  /**
   * Callback function which is called if a receive timeout occurs
   */
  void rx_timeout_cb();

  /**
   * Callback function which is called as soon as the
   * channel activity detection is done.(not used)
   *
   * @param arg true, if channel activity detected
   */
  void cad_done_cb(bool arg);

  /**
   * Callback function which is called if a LoRa packet was received.
   *
   * @param payload The received payload
   * @param size    Size of the received payload
   * @param rssi    RSSI of the received packet
   * @param snr     SNR of the received packet
   */
  void rx_done_cb(const uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

  /**
   * FHSS Change Channel callback (not used)
   *
   * @param channel The index number of the current channel
   */
  void fhss_change_channel_cb(uint8_t channel);

  /**
   * Radio object to control the LoRa module via the lower level
   * driver from mbed OS.
   */
  SX126X_LoRaRadio _radio;

  /**
   * Struct holding the callbacks for the #_radio
   */
  radio_events_t _radio_callbacks;

  /**
   * Event flags used for event handling within this Lora class
   */
  rtos::EventFlags _event_flags;

  /**
   * Receive timout object used in the receive() function
   */
  mbed::LowPowerTimeout _rx_timeout;
};


#endif //PARTICLE_SENSOR_LORA_H
