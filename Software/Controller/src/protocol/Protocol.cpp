#include "Protocol.h"
#include "Logger.h"
#include "utils.h"
#include "ThisThread.h"
#include <utility>

Protocol::Protocol(SensorBoardSerial &serial, SensorData &sensor_data, std::string protocol_version)
    : _protocol_version(std::move(protocol_version)), _serial(serial), _sensor_data(sensor_data) {
}

mbed_error_status_t Protocol::get_sensor_info() {
  std::string command;
  std::string response;

  build_json_cmd(_sensor_data.address, "send_info", command);
  _serial.enable_rx_irq();
  TRY(_serial.write(command.c_str(), command.size()));

  TRY(get_json_response(response));

  DEBUG_PRINTF("JsonProtocol: Sensor info response: %s\n", response.c_str());

  //FIXME: Moving ']' necessary, because otherwise received json is invalid
  size_t idx = response.find(']');
  if (idx != std::string::npos) {
    response.erase(idx, 1);
    response.insert(response.size() - 25, "]");
  }

  TRY(_sensor_data.from_json(response));

  return MBED_SUCCESS;
}

mbed_error_status_t Protocol::get_json_response(std::string &response) {
  char received_char[2] = {0, 0};

  for (int read_time = 0; read_time < MBED_CONF_APP_SENSOR_SERIAL_RX_TIMEOUT; read_time++) {
    while (_serial.read(&received_char, 1) == 1) {
      if (received_char[0] == json_start_byte) {
        continue;
      } else if (received_char[0] == json_stop_byte) {
        _serial.disable_rx_irq();
        return check_and_remove_crc(response);
      } else {
        response += received_char;
      }
    }
    rtos::ThisThread::sleep_for(1);
  }
  _serial.disable_rx_irq();

  Logger::log(Logger::Module::PROTOCOL, Logger::Level::INFO, "Received no or invalid response from sensor board");
  std::string log_message = "Received " + std::to_string(response.size()) + " bytes in " +
                            std::to_string(MBED_CONF_APP_SENSOR_SERIAL_RX_TIMEOUT) + " ms";
  Logger::log(Logger::Module::PROTOCOL, Logger::Level::DEBUG, log_message);

  return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_READ_FAILED);
}

void Protocol::build_json_cmd(uint8_t address, const std::string &cmd_string, std::string &dest) const {
  char hex_num_string[5];
  memset(hex_num_string, 0, 5);
  sprintf(hex_num_string, "0x%02x", address);

  const int capacity = JSON_OBJECT_SIZE(4);
  StaticJsonDocument<capacity> json_cmd;

  json_cmd["s_a"] = hex_num_string;
  json_cmd["cmd"] = cmd_string;

  dest.clear();
  serializeJson(json_cmd, dest);
  dest = json_start_byte + dest + json_stop_byte + json_stop_byte;
  //FIXME: Command has to be 35 chars long for sensor boards to recognize command
}

const std::string &Protocol::get_protocol_version() const {
  return _protocol_version;
}

uint32_t Protocol::compute_crc16(const void *const data, uint64_t size) {
  mbed::MbedCRC<POLY_16BIT_CCITT, 16> crc;
  uint32_t computed_crc_value = 0;
  crc.compute(data, size, &computed_crc_value);
  return computed_crc_value;
}

mbed_error_status_t Protocol::check_and_remove_crc(std::string &response) {
  if (response[response.size() - 1] != '}') {
    uint32_t crc_value = strtol(response.substr(response.size() - 4, 4).c_str(), nullptr, 16);
    uint32_t computed_crc = compute_crc16(response.c_str(), response.size() - 4);
    if (crc_value != computed_crc) {
      std::string log_message = "CRC error in response. received: " + utils::to_hex_string(crc_value) + ", computed: " +
                                utils::to_hex_string(computed_crc);
      Logger::log(Logger::Module::PROTOCOL, Logger::Level::ERROR, log_message);
      return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_CRC_ERROR);
    }
    response.resize(response.size() - 4);
  }
  return MBED_SUCCESS;
}