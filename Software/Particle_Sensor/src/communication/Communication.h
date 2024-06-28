
#ifndef PARTICLE_SENSOR_COMMUNICATION_H
#define PARTICLE_SENSOR_COMMUNICATION_H

#include "Lora.h"
#include "Protocol.h"
#include "LowPowerTicker.h"

/**
 * Class handling the LoRa communication control flow. The LoRa communication is done
 * in a separate thread, which can be started with start() and stopped with stop().
 */
class Communication : private mbed::NonCopyable<Communication> {
public:
  /**
   * Creates a Communication object
   */
  Communication();

  /**
   * Initialize #_lora and start the LoRa communication #_thread with the function run().
   * If "status_enable" is true in #Config::global_config, the #_status_update_ticker is started
   * to send periodic status updates with an interval defined by "status_interval_sec" in #Config::global_config.
   *
   * @return MBED_SUCCESS if thread was started, MBED_ERROR_FAILED_OPERATION otherwise
   */
  mbed_error_status_t start();

  /**
   * If the LoRa communication #_thread is running, it will be stopped, as well as the
   * #_status_update_ticker. The #_lora module is set to sleep mode.
   */
  void stop();

  /**
   * Copies \p data to #_measured_data and sets the #FLAG_SEND_MEASURED_DATA in #_flags.
   *
   * @param data measured data to be sent
   */
  void send_measured_data(const Protocol::measured_data_t &data);

private:
  /**
   * Enum defining the possible data packet types
   */
  enum PacketType {
    MEASURED_DATA,
    STATUS_DATA
  };

  /**
   * Endless running function executed in #_thread handling the LoRa communication
   * by reacting on event _flags.
   */
  void run();

  /**
   * If sensor is not authenticated at the gateway, it will send an authentication request
   * and wait for the gateway authentication response.
   * If no or an invalid response is received, a  new authentication message will be sent
   * after a random delay between 2 and 10 minutes.
   * This process will be repeated until a valid response is received.
   */
  void authenticate();

  /**
   * Depending on the \p packet_type, a measurement data packet or a status update packet
   * is sent to the gateway. If the gateway does not respond with an acknowledge, the
   * packet will be sent again after a random delay between 2 and 10 minutes.
   * If #MAX_SEND_DATA_ATTEMPTS times no or an invalid response is received, the connection
   * will be reset and a new authentication is necessary.
   *
   * @param packet_type Type of the packet to send
   * @return true if packet was sent, false otherwise
   */
  bool send_data(PacketType packet_type);

  /**
   * Initiates sending a status update packet by setting #FLAG_SEND_STATUS_DATA in #_flags.
   */
  void send_status_data();

  /**
   * Lora object used to control the LoRa module
   */
  Lora _lora;

  /**
   * Protocol object providing functions to communicate with the Smartmote gateway
   */
  Protocol _protocol;

  /**
   * The communication thread
   */
  rtos::Thread _thread;

  /**
   * Mutex to serialize read and write accesses to #_measured_data
   */
  PlatformMutex _data_mutex;

  /**
   * Buffer for the latest measured data to be sent next
   */
  Protocol::measured_data_t _measured_data = {};

  /**
   * EventFlags to signalize #_thread, when to send measurement data or a status update
   */
  rtos::EventFlags _flags;

  /**
   * Ticker to periodically initiate sending a status update
   */
  mbed::LowPowerTicker _status_update_ticker;
};


#endif //PARTICLE_SENSOR_COMMUNICATION_H
