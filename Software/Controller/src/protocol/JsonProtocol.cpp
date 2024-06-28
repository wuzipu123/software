

#include "JsonProtocol.h"
#include "Logger.h"
#include "utils.h"

JsonProtocol::JsonProtocol(SensorBoardSerial &serial, SensorData &sensor_data)
    : Protocol(serial, sensor_data, "1.0") {
}

mbed_error_status_t JsonProtocol::init_measurement() {
  std::string command;
  build_json_cmd(_sensor_data.address, "init_meas", command);
  return _serial.write(command.c_str(), command.size());
}

mbed_error_status_t JsonProtocol::stop_measurement() {
  std::string command;
  build_json_cmd(_sensor_data.address, "sens_stop", command);
  return _serial.write(command.c_str(), command.size());
}

mbed_error_status_t JsonProtocol::datasets_from_json(const std::string &json_string) {
  const size_t capacity = 4096;
  DynamicJsonDocument json_doc(capacity);
  DeserializationError deserialization_error = deserializeJson(json_doc, json_string);
  if (deserialization_error) {
    std::string log_message = "Deserialization of datasets failed: ";
    log_message += deserialization_error.c_str();
    Logger::log(Logger::Module::JSON_PROTOCOL, Logger::Level::ERROR, log_message);
    return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_FAILED_OPERATION);
  }

  if (json_doc.containsKey("v")) {
    int dataset_size = json_doc["v"].size();
    _sensor_data.datasets.clear();
    for (int i = 0; i < dataset_size; i++) {
      if (json_doc["v"][i].containsKey("v")) {
        _sensor_data.datasets.push_back(json_doc["v"][i]["v"].as<float>());
      } else {
        _sensor_data.datasets.push_back(-1.0f);
      }
    }
  }

  if (static_cast<int>(_sensor_data.datasets.size()) != _sensor_data.num_datasets) {
    std::string log_message = "Number of reveived datasets (" + std::to_string(_sensor_data.datasets.size())
                              + ") does not match expected number of datasets (" +
                              std::to_string(_sensor_data.num_datasets) + ")";
    Logger::log(Logger::Module::JSON_PROTOCOL, Logger::Level::ERROR, log_message);
    return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_DATA_DETECTED);
  }
  return MBED_SUCCESS;
}

mbed_error_status_t JsonProtocol::read_data() {
  std::string command;
  std::string response;

  build_json_cmd(_sensor_data.address, "send_data", command);
  _serial.enable_rx_irq();
  TRY(_serial.write(command.c_str(), command.size()));

  TRY(get_json_response(response));

  DEBUG_PRINTF("JsonProtocol: Data read response: %s\n", response.c_str());

  TRY(datasets_from_json(response));

  return MBED_SUCCESS;
}
