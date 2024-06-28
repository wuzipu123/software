#include "SensorBoardSerial.h"
#include "Logger.h"
#include "ThisThread.h"

SensorBoardSerial::SensorBoardSerial(PinName tx, PinName rx, PinName de_nre) : mbed::SerialBase(tx, rx,
                                                                                                MBED_CONF_APP_SENSOR_SERIAL_BAUD),
                                                                               _rs485_mode(de_nre, Rs485Mode::RECEIVE),
                                                                               _tx_irq_enabled(false),
                                                                               _rx_irq_enabled(false) {
}

mbed_error_status_t SensorBoardSerial::write(const void *buffer, size_t length) {
  _inter_message_timer.stop();
  int time_diff = SENSOR_SERIAL_INTER_CMD_TIMEOUT_MS - _inter_message_timer.read_ms();
  if (time_diff > 0) {
    rtos::ThisThread::sleep_for(std::max(time_diff, SENSOR_SERIAL_INTER_CMD_TIMEOUT_MS));
  }

  _rs485_mode = Rs485Mode::SEND;
  rtos::ThisThread::sleep_for(1);

  if (write_serial(buffer, length) != static_cast<ssize_t>(length)) {
    mbed_error_status_t error_status = MBED_MAKE_ERROR(MBED_MODULE_DRIVER_SERIAL, MBED_ERROR_WRITE_FAILED);
    Logger::log(Logger::Module::SENSOR_BOARD_SERIAL, Logger::Level::ERROR,
                "Writing to the sensor board serial interface failed");
    _rs485_mode = Rs485Mode::RECEIVE;
    return error_status;
  }

  rtos::ThisThread::sleep_for(4);
  _rs485_mode = Rs485Mode::RECEIVE;

  _inter_message_timer.reset();
  _inter_message_timer.start();

  return MBED_SUCCESS;
}


ssize_t SensorBoardSerial::write_serial(const void *buffer, size_t length) {
  size_t data_written = 0;
  const char *buf_ptr = static_cast<const char *>(buffer);

  if (length == 0) {
    return 0;
  }

  api_lock();

  while (data_written < length) {

    if (_txbuf.full()) {
      break;
    }

    while (data_written < length && !_txbuf.full()) {
      _txbuf.push(*buf_ptr++);
      data_written++;
    }

    core_util_critical_section_enter();
    if (_tx_enabled && !_tx_irq_enabled) {
      SensorBoardSerial::tx_irq();                // only write to hardware in one place
      if (!_txbuf.empty()) {
        enable_tx_irq();
      }
    }
    core_util_critical_section_exit();
  }

  api_unlock();

  return data_written != 0 ? (ssize_t) data_written : (ssize_t) -EAGAIN;
}

ssize_t SensorBoardSerial::read(void *buffer, size_t length) {
  size_t data_read = 0;

  char *ptr = static_cast<char *>(buffer);

  if (length == 0) {
    return 0;
  }

  api_lock();

  while (_rxbuf.empty()) {
    api_unlock();
    return -EAGAIN;
  }

  while (data_read < length && !_rxbuf.empty()) {
    _rxbuf.pop(*ptr++);
    data_read++;
  }

  core_util_critical_section_enter();
  if (_rx_enabled && !_rx_irq_enabled) {
    SensorBoardSerial::rx_irq();               // only read from hardware in one place
    if (!_rxbuf.full()) {
      enable_rx_irq();
    }
  }
  core_util_critical_section_exit();

  api_unlock();

  return data_read;
}

void SensorBoardSerial::api_lock() {
  _mutex.lock();
}

void SensorBoardSerial::api_unlock() {
  _mutex.unlock();
}

void SensorBoardSerial::rx_irq() {
  /* Fill in the receive buffer if the peripheral is readable
   * and receive buffer is not full. */
  while (!_rxbuf.full() && SerialBase::readable()) {
    char data = SerialBase::_base_getc();
    _rxbuf.push(data);
  }

  if (_rx_irq_enabled && _rxbuf.full()) {
    disable_rx_irq();
  }
}

// Also called from write to start transfer
void SensorBoardSerial::tx_irq() {
  char data;

  /* Write to the peripheral if there is something to write
   * and if the peripheral is available to write. */
  while (SerialBase::writeable() && _txbuf.pop(data)) {
    SerialBase::_base_putc(data);
  }

  if (_tx_irq_enabled && _txbuf.empty()) {
    disable_tx_irq();
  }
}

/* These are all called from critical section */
void SensorBoardSerial::enable_rx_irq() {
  SerialBase::attach(callback(this, &SensorBoardSerial::rx_irq), RxIrq);
  _rx_irq_enabled = true;
}

void SensorBoardSerial::disable_rx_irq() {
  SerialBase::attach(NULL, RxIrq);
  _rx_irq_enabled = false;
  _rxbuf.reset();
}

void SensorBoardSerial::enable_tx_irq() {
  SerialBase::attach(callback(this, &SensorBoardSerial::tx_irq), TxIrq);
  _tx_irq_enabled = true;
}

void SensorBoardSerial::disable_tx_irq() {
  SerialBase::attach(NULL, TxIrq);
  _tx_irq_enabled = false;
}