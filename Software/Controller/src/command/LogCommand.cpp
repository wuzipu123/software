
#include "LogCommand.h"
#include "Logger.h"
#include "constants.h"

LogCommand::LogCommand(USBSerial &usb_serial, mbed::FlashIAP &flash)
    : Command(log_command_name, log_command_description, usb_serial),
      _flash(flash) {
}

mbed_error_status_t LogCommand::execute(std::string &parameter_string) {
  std::map<std::string, std::string> parameter_map;

  if (!parameter_string_to_map(parameter_string, parameter_map)) {
    _usb_serial.printf("Error: Wrong parameter format\n");
    return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_FORMAT);
  }

  if (parameter_map.empty()) {
    print_current_log_settings();
    return MBED_SUCCESS;
  }

  return handle_parameters(parameter_map);
}

void LogCommand::print_current_log_settings() {
  _usb_serial.printf("Current log settings:\n");
  for (int module = 0; module < Logger::Module::NUM_MODULES; module++) {
    _usb_serial.printf("%s=%s\n", logger_module_names[module],
                       logger_level_names[Logger::get_level_by_module(static_cast<Logger::Module>(module))]);
  }
}

mbed_error_status_t LogCommand::handle_parameters(std::map<std::string, std::string> &parameter_map) {
  if (parameter_map.find("global") != parameter_map.end()) {
    Logger::Level global_level = get_log_level_from_string(parameter_map.find("global")->second);
    if (global_level == Logger::NUM_LEVELS) {
      _usb_serial.printf("Error: Given log level (%s) is invalid\n", parameter_map.find("global")->second.c_str());
      return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_ARGUMENT);
    }
    Logger::set_level_global(global_level);
    parameter_map.erase("global");
    std::string log_message = "Set log level global=" + std::string(logger_level_names[global_level]);
    Logger::log(Logger::Module::LOG_COMMAND, Logger::Level::INFO, log_message);
  }

  for(const auto &parameter_pair : parameter_map) {
    Logger::Module module = get_log_module_from_string(parameter_pair.first);
    if (module == Logger::Module::NUM_MODULES) {
      _usb_serial.printf("Error: Given log module (%s) is invalid\n", parameter_pair.first.c_str());
      return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_ARGUMENT);
    }
    Logger::Level level = get_log_level_from_string(parameter_pair.second);
    if (level == Logger::NUM_LEVELS) {
      _usb_serial.printf("Error: Given log level (%s) is invalid\n", parameter_pair.second.c_str());
      return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_ARGUMENT);
    }
    Logger::set_level(module, level);
    std::string log_message = "Set log level for module " + parameter_pair.first + "=" + parameter_pair.second;
    Logger::log(Logger::Module::LOG_COMMAND, Logger::Level::INFO, log_message);
  }

  _flash.erase(STORAGE_ADDR_LOG_LEVELS, _flash.get_sector_size(STORAGE_ADDR_LOG_LEVELS));
  _flash.program(&Logger::log_levels, STORAGE_ADDR_LOG_LEVELS, sizeof(Logger::log_levels));

  return MBED_SUCCESS;
}

Logger::Level LogCommand::get_log_level_from_string(const std::string &log_level_string) {
  for (int level_idx = 0; level_idx < Logger::Level::NUM_LEVELS; level_idx++) {
    if(log_level_string == logger_level_names[level_idx]) {
      return static_cast<Logger::Level>(level_idx);
    }
  }
  return Logger::Level::NUM_LEVELS;
}

Logger::Module LogCommand::get_log_module_from_string(const std::string &log_module_string) {
  for (int module_idx = 0; module_idx < Logger::Module::NUM_MODULES; module_idx++) {
    if(log_module_string == logger_module_names[module_idx]) {
      return static_cast<Logger::Module>(module_idx);
    }
  }
  return Logger::Module::NUM_MODULES;
}
