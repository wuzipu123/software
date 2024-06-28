
#include "ConfigCommand.h"
#include "constants.h"
#include "Logger.h"
#include "utils.h"
#include "FlashIAP.h"
#include <map>
#include <cstdlib>

ConfigCommand::ConfigCommand(USBSerial &usb_serial, mbed::FlashIAP &flash, Config &config)
    : Command(config_command_name, config_command_description, usb_serial),
      _config(config),
      _flash(flash) {
}

mbed_error_status_t ConfigCommand::execute(std::string &parameter_string) {
  std::map<std::string, std::string> parameter_map;

  if (!parameter_string_to_map(parameter_string, parameter_map)) {
    _usb_serial.printf("Error: Wrong parameter format\n");
    return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_FORMAT);
  }

  if (parameter_map.empty()) {
    print_current_config();
    return MBED_SUCCESS;
  }

  return handle_parameters(parameter_map);
}

void ConfigCommand::print_current_config() {
  _usb_serial.printf("Current configuration:\n");

  for (size_t address = 0; address < _config.sensor_configs.size(); address++) {
    _usb_serial.printf("sensor=%d %s=%d %s=%s\n", address,
                       _sample_time_name,
                       _config.sensor_configs[address].sample_time_sec,
                       _keep_alive_name,
                       _config.sensor_configs[address].keep_alive ? "true" : "false");

  }
}

mbed_error_status_t ConfigCommand::handle_parameters(const std::map<std::string, std::string> &parameter_map) {
  std::vector<int> addresses;

  if (parameter_map.find("sensor") != parameter_map.end()) {
    std::vector<std::string> address_strings;
    split_string(parameter_map.find("sensor")->second, address_strings, ',');
    for (auto address_string : address_strings) {
      if (!utils::is_number(address_string)) {
        _usb_serial.printf("Error: Sensor address (%s) is not a number \n", address_string.c_str());
        return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_FORMAT);
      }
      int address = strtol(address_string.c_str(), nullptr, 10);
      if (address < 0 || address >= static_cast<int>(NUM_SENSOR_SLOTS)) {
        _usb_serial.printf("Error: Sensor address (%s) is out of range (0 - %d)\n", address_string.c_str(),
                           NUM_SENSOR_SLOTS - 1);
        return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_ARGUMENT);
      }
      addresses.push_back(address);
    }
  }

  if (parameter_map.find(_sample_time_name) != parameter_map.end()) {
    if (addresses.empty()) {
      _usb_serial.printf("Error: No sensor address(es) specified\n");
      return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_FORMAT);
    }
    std::string sample_time_string = parameter_map.find(_sample_time_name)->second;
    if (!utils::is_number(sample_time_string)) {
      _usb_serial.printf("Error: Given value (%s) for %s is not a number\n",
                         sample_time_string.c_str(), _sample_time_name);
      return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_ARGUMENT);
    }
    int sample_time = strtol(sample_time_string.c_str(), nullptr, 10);
    for (auto address : addresses) {
      _config.sensor_configs[address].sample_time_sec = sample_time;
      std::string log_message = "Set config for sensor at slot " + std::to_string(address)
                                + ": " + _sample_time_name + "=" + std::to_string(sample_time);
      Logger::log(Logger::Module::CONFIG_COMMAND, Logger::Level::INFO, log_message);
    }
  }

  if (parameter_map.find(_keep_alive_name) != parameter_map.end()) {
    if (addresses.empty()) {
      _usb_serial.printf("Error: No sensor address(es) specified\n");
      return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_FORMAT);
    }
    std::string keep_alive_string = parameter_map.find(_keep_alive_name)->second;
    bool keep_alive;
    if (keep_alive_string == "true") {
      keep_alive = true;
    } else if (keep_alive_string == "false") {
      keep_alive = false;
    } else {
      _usb_serial.printf("Error: Given value (%s) for %s is invalid\n",
                         keep_alive_string.c_str(), _keep_alive_name);
      return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_ARGUMENT);
    }

    for (auto address : addresses) {
      _config.sensor_configs[address].keep_alive = keep_alive;
      std::string log_message = "Set config for sensor at slot " + std::to_string(address)
                                + ": " + _keep_alive_name + "=" + keep_alive_string;
      Logger::log(Logger::Module::CONFIG_COMMAND, Logger::Level::INFO, log_message);
    }
  }

  _flash.erase(STORAGE_ADDR_CONFIG, _flash.get_sector_size(STORAGE_ADDR_CONFIG));
  _flash.program(&_config, STORAGE_ADDR_CONFIG, sizeof(_config));

  return MBED_SUCCESS;
}