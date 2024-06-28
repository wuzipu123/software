
#include "BinProtocol.h"
#include "Logger.h"
#include "utils.h"
#include "ThisThread.h"

BinProtocol::BinProtocol(SensorBoardSerial &serial, SensorData &sensor_data)
    : Protocol(serial, sensor_data, "2.0") {
}

mbed_error_status_t BinProtocol::init_measurement() {
  return send_bin_command(_sensor_data.address, BinProtocol::SensorCmd::INIT_MEAS);
}

mbed_error_status_t BinProtocol::stop_measurement() {
  return send_bin_command(_sensor_data.address, BinProtocol::SensorCmd::STOP_MEAS);
}

mbed_error_status_t BinProtocol::read_data() {
  _serial.enable_rx_irq();
  TRY(send_bin_command(_sensor_data.address, BinProtocol::SensorCmd::SEND_DATA));

  std::vector<uint8_t> response;
  TRY(get_bin_response(response));

  extract_datasets_from_response(response, _sensor_data.datasets);

  return MBED_SUCCESS;
}

mbed_error_status_t BinProtocol::send_bin_command(uint8_t address, BinProtocol::SensorCmd sensor_cmd) {
  command_t command;
  command.address = address;
  command.command = static_cast<uint8_t>(sensor_cmd);
  command.crc = compute_crc16(static_cast<void *>(&command), sizeof(command));
  return _serial.write(static_cast<void *>(&command), sizeof(command));
}

mbed_error_status_t BinProtocol::get_bin_response(std::vector<uint8_t> &response) {
  uint8_t receive_byte = 0;
  uint32_t receive_counter = 0;
  uint16_t message_length = UINT16_MAX;

  int read_time;
  for (read_time = 0; read_time < MBED_CONF_APP_SENSOR_SERIAL_RX_TIMEOUT; read_time++) {
    while (_serial.read(&receive_byte, 1) == 1) {
      response.push_back(receive_byte);
      // Because of an unknown side effect the sensor board sends a 0-byte before the message -> ignore leading 0-bytes
      if (receive_counter == START_BYTE_POS && receive_byte == 0x00) {
        response.clear();
        continue;
      } else if (receive_counter == START_BYTE_POS) {
        if (receive_byte != BIN_PROTOCOL_START_BYTE) {
          _serial.disable_rx_irq();
          std::string log_message = "Wrong start byte. received: " + utils::to_hex_string(receive_byte)
                                    + ", expected: " + utils::to_hex_string(BIN_PROTOCOL_START_BYTE);
          Logger::log(Logger::Module::BIN_PROTOCOL, Logger::Level::ERROR, log_message);
          return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_DATA_DETECTED);
        }
      } else if (receive_counter == SLAVE_ADDRESS_POS) {
        if (receive_byte != _sensor_data.address) {
          _serial.disable_rx_irq();
          std::string log_message = "Wrong slave address. received: " + std::to_string(receive_byte)
                                    + ", expected: " + std::to_string(_sensor_data.address);
          Logger::log(Logger::Module::BIN_PROTOCOL, Logger::Level::ERROR, log_message);
          return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_DATA_DETECTED);
        }
      } else if (receive_counter == MESSAGE_LENGTH_POS + 1) {
        message_length = (response[MESSAGE_LENGTH_POS + 1] << 8U) + response[MESSAGE_LENGTH_POS];
        if ((_sensor_data.data_type == SensorData::FLOAT32 &&
             DATA_SIZE(message_length) != _sensor_data.num_datasets * sizeof(float))
            || (_sensor_data.data_type == SensorData::UINT32 &&
                DATA_SIZE(message_length) != _sensor_data.num_datasets * sizeof(uint32_t))) {
          std::string log_message = "Message length error. received: " + std::to_string(message_length);
          Logger::log(Logger::Module::BIN_PROTOCOL, Logger::Level::ERROR, log_message);
          _serial.disable_rx_irq();
          return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_DATA_DETECTED);
        }
      } else if (receive_counter == CRC_POS(message_length) + 1) {
        uint16_t crc = (response[CRC_POS(message_length) + 1] << 8U) + response[CRC_POS(message_length)];
        uint32_t computed_crc = compute_crc16(response.data(), message_length - CRC_SIZE);
        if (crc != computed_crc) {
          std::string log_message = "CRC error in response. received: " + utils::to_hex_string(crc)
                                    + ", computed: " + utils::to_hex_string(computed_crc);
          Logger::log(Logger::Module::BIN_PROTOCOL, Logger::Level::ERROR, log_message);
          _serial.disable_rx_irq();
          return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_CRC_ERROR);
        } else {
          _serial.disable_rx_irq();
          return MBED_SUCCESS;
        }
      }
      receive_counter++;
    }
    rtos::ThisThread::sleep_for(1);
  }

  Logger::log(Logger::Module::BIN_PROTOCOL, Logger::Level::INFO,
              "Timeout while receiving response from sensor board");

  _serial.disable_rx_irq();
  return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_TIME_OUT);
}

mbed_error_status_t BinProtocol::extract_datasets_from_response(const std::vector<uint8_t> &response,
                                                                std::vector<float> &out) {
  uint8_t byte_counter = 0;
  uint32_t value = 0;
  out.clear();
  for (int i = DATA_POS; static_cast<uint32_t>(i) < CRC_POS(response.size()); i++) {
    value |= response[i] << (8U * byte_counter);

    if (byte_counter == sizeof(float) - 1) {
      byte_counter = 0;
      if (_sensor_data.data_type == SensorData::DatasetTypes::UINT32) {
        out.push_back(static_cast<float>(value));
      } else if (_sensor_data.data_type == SensorData::DatasetTypes::FLOAT32) {
        out.push_back(*((float *) &value));
      }
      value = 0;
    } else {
      byte_counter++;
    }
  }
  return MBED_SUCCESS;
}