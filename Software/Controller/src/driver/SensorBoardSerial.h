
#ifndef CONTROLLER_SENSORBOARDSERIAL_H
#define CONTROLLER_SENSORBOARDSERIAL_H

#include "DigitalOut.h"
#include "constants.h"
#include "SerialBase.h"
#include "CircularBuffer.h"
#include "PlatformMutex.h"
#include "EventFlags.h"
#include "LowPowerTimer.h"
#include "mbed_error.h"

/**
 * Class providing a file like interface to write to and read from the UART
 * serial bus where the sensor boards are connected to.
 * Most of the functionality is adapted from UARTSerial.
 * The main difference between this class and UARTSerial is the
 * possibility to enable and disable the receive interrupt from outside this class.
 * This is necessary, because to unlock the deepsleep mode, the receive interrupt
 * must be disabled or no receive interrupt callback method is attached.
 */
class SensorBoardSerial : private mbed::SerialBase {
public:
  /**
   * Create a SensorBoardSerial port, connected to the specified
   * transmit, receive and drive enable pins.
   *
   * @param tx Transmit pin
   * @param rx Receive pin
   * @param de_nre drive enable and receive disable pin
   */
  SensorBoardSerial(PinName tx, PinName rx, PinName de_nre);

  /**
   * Wrapper function for write_serial() to ensure inter message timeout
   * and switch #_rs485_mode to #SEND before sending the
   * data and back to #RECEIVE after sending.
   *
   * @param buffer The buffer to write from
   * @param length The number of bytes to write
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t write(const void *buffer, size_t length);

  /**
   * Read (non-blocking) the contents of the receive buffer #_rxbuf into a \p buffer
   *
   * @param buffer   The buffer to read in to
   * @param length   The number of bytes to read
   * @return         The number of bytes read, negative error on failure
   */
  ssize_t read(void *buffer, size_t length);

  /**
   * Attach receive callback function rx_irq() and set #_rx_irq_enabled to true
   */
  void enable_rx_irq();

  /**
   * Detach receive callback function and set #_rx_irq_enabled to false
   */
  void disable_rx_irq();

private:
  /**
   * Enum defining the digital states for the drive enable and receive disable pin
   */
  enum Rs485Mode {
    RECEIVE = 0, //!< RS485 receive mode
    SEND = 1     //!< RS485 transmit mode
  };

  /**
   * DigitalOut object for RS485 mode pin. Possible states are defined by #Rs485Mode
   */
  mbed::DigitalOut _rs485_mode;

  /**
   * Timer to measure the time between two consecutive calls to write().
   * Used to ensure a minimum inter message timeout defined by #SENSOR_SERIAL_INTER_CMD_TIMEOUT_MS.
   */
  mbed::LowPowerTimer _inter_message_timer;

  /** Transmit buffer */
  mbed::CircularBuffer<char, SENSOR_SERIAL_TXBUF_SIZE> _txbuf;

  /** Receive buffer */
  mbed::CircularBuffer<char, SENSOR_SERIAL_RXBUF_SIZE> _rxbuf;

  /** Transmit interrupt enabled flag */
  bool _tx_irq_enabled;

  /** Receive interrupt enabled flag */
  bool _rx_irq_enabled;

  /** API mutex */
  PlatformMutex _mutex;

  /** Acquire mutex */
  virtual void api_lock();

  /** Release mutex */
  virtual void api_unlock();

  /**
   * Attach transmit callback function tx_irq() and set #_tx_irq_enabled to true
   */
  void enable_tx_irq();

  /**
   * Detach transmit callback function and set #_tx_irq_enabled to false
   */
  void disable_tx_irq();

  /**
   * ISR for serial transmit interrupts. Handles interrupts on transmit pin.
   * Writes #_txbuf byte-wise to the UART transmit data register.
   */
  void tx_irq();

  /**
   * ISR for serial receive interrupts. Handles interrupts on receive pin.
   * Writes UART receive data register byte-wise to #_rxbuf.
   */
  void rx_irq();

  /**
   * Write the contents of a \p buffer to the transmit buffer #_txbuf
   *
   * @param buffer The buffer to write from
   * @param length The number of bytes to write
   * @return The number of bytes written, negative error on failure
   */
  virtual ssize_t write_serial(const void *buffer, size_t length);
};


#endif //CONTROLLER_SENSORBOARDSERIAL_H
