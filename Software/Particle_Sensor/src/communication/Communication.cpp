
#include "Communication.h"
#include "Battery.h"
#include "defines.h"
#include "Logger.h"

#define FLAG_SEND_MEASURED_DATA (1U << 0U)
#define FLAG_SEND_STATUS_DATA   (1U << 1U)

using namespace std;

Communication::Communication() :
    _protocol(_lora),
    _thread(osPriority_t::osPriorityHigh, OS_STACK_SIZE, nullptr, "comm") {
}

mbed_error_status_t Communication::start() {
  if (_thread.get_state() == rtos::Thread::State::Deleted) {
    _lora.init();
    if (Config::get<bool>("status_enable")) {
      _status_update_ticker.attach(mbed::callback(this, &Communication::send_status_data),
                                   std::chrono::seconds(Config::get<uint32_t>("status_interval_sec")));
      send_status_data();
    }
    _thread.start(mbed::callback(this, &Communication::run));
    return MBED_SUCCESS;
  }
  return MBED_ERROR_FAILED_OPERATION;
}

void Communication::stop() {
  if (_thread.get_state() != rtos::Thread::State::Deleted) {
    _status_update_ticker.detach();
    _thread.terminate();
    _lora.sleep();
  }
}

void Communication::send_measured_data(const Protocol::measured_data_t &data) {
  if (!Config::get<bool>("lora_enable")) {
    return;
  }

  _data_mutex.lock();
  _measured_data = data;
  _data_mutex.unlock();
  _flags.set(FLAG_SEND_MEASURED_DATA);
}

void Communication::run() {
  while (true) {
    authenticate();

    uint32_t wait_flags = _flags.wait_any(FLAG_SEND_MEASURED_DATA | FLAG_SEND_STATUS_DATA, osWaitForever, false);
    if (wait_flags & FLAG_SEND_MEASURED_DATA) {
      if (send_data(PacketType::MEASURED_DATA)) {
        _flags.clear(FLAG_SEND_MEASURED_DATA);
      }
    } else if (wait_flags & FLAG_SEND_STATUS_DATA) {
      if (send_data(PacketType::STATUS_DATA)) {
        _flags.clear(FLAG_SEND_STATUS_DATA);
      }
    }
  }
}

void Communication::authenticate() {
  while (!_protocol.is_auth_done()) {
    _protocol.send_auth();
    if (MBED_SUCCESS == _lora.receive()) {
      _lora.sleep();
      if (MBED_SUCCESS != _protocol.read_received()) {
        rtos::ThisThread::sleep_for(std::chrono::milliseconds(LORA_RESEND_WAIT_MS));
      }
    } else {
      uint32_t rand_wait_ms = 2 * 60 * 1000 + utils::get_rand() / 8948; // wait a random time from 2 to 10 minutes
      _lora.sleep();
      LOG(LVL_DEBUG, "RX Timeout! Try again in %dms", rand_wait_ms);
      rtos::ThisThread::sleep_for(std::chrono::milliseconds(rand_wait_ms));
    }
  }
}

bool Communication::send_data(PacketType packet_type) {
  for (int i = 0; i < MAX_SEND_DATA_ATTEMPTS; ++i) {
    Protocol::measured_data_t measured_data_temp;
    Protocol::status_data_t status_data;
    switch (packet_type) {
      case MEASURED_DATA:
        _data_mutex.lock();
        measured_data_temp = _measured_data;
        _data_mutex.unlock();
        _protocol.send_measured_data(measured_data_temp);
        break;
      case STATUS_DATA:
        status_data.bat_level = Battery::read_voltage() / 0.00122070312;
        status_data.bat_level = REVERSE_2_BYTE(status_data.bat_level);
        status_data.rssi = _lora.rx_rssi;
        status_data.snr = _lora.rx_snr;
        LOG(LVL_DEBUG, "Send status: Battery voltage: %.3fV, RSSI: %ddBm, SNR: %ddB",
            (REVERSE_2_BYTE(status_data.bat_level) * 0.00122070312), status_data.rssi, status_data.snr);
        _protocol.send_status_data(status_data);
        break;
    }

    while (true) {
      if (MBED_SUCCESS == _lora.receive()) {
        _lora.sleep();
        mbed_error_status_t error_status = _protocol.read_received();
        // received correct message, but no ACK byte (0x5a) -> send new auth message according to specification
        if (MBED_ERROR_FAILED_OPERATION == error_status) {
          _protocol.auth_reset();
          return false;
        } else if (MBED_SUCCESS == error_status) { // received ACK
          return true;
        }
      } else {
        uint32_t rand_wait_ms = 2 * 60 * 1000 + utils::get_rand() / 8948; // wait a random time from 2 to 10 minutes
        _lora.sleep();
        LOG(LVL_DEBUG, "No ACK received. Send data again in %dms.", rand_wait_ms);
        rtos::ThisThread::sleep_for(std::chrono::milliseconds(rand_wait_ms));
        break;
      }
    }
  }
  _protocol.auth_reset();
  return false;
}

void Communication::send_status_data() {
  _flags.set(FLAG_SEND_STATUS_DATA);
}