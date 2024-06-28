
#include "Logger.h"
#include "constants.h"
#include "utils.h"
#include "mbed_error.h"
#include <ctime>

bool Logger::_initialized = false;
SDCard *Logger::_sd_card = nullptr;
Logger::Level Logger::log_levels[Logger::Module::NUM_MODULES] = {};
std::string Logger::_file_name = "log.txt";

void Logger::init(SDCard *sd_card) {
  _file_name.clear();
  utils::get_formatted_time_string("%Y-%m-%d_%H-%M-%S", _file_name);
  _file_name = "log_" + _file_name + ".txt";

  if(!_initialized) {
    for(int i = 0; i < Module::NUM_MODULES; i++) {
      log_levels[i] = Level::DEBUG;
    }
    _sd_card = sd_card;

    _initialized = true;
  }
}

void Logger::log(Logger::Module module, Logger::Level level, const std::string &message) {
  if(module >= Module::NUM_MODULES || level >= Level::NUM_LEVELS) {
    mbed_error_status_t error_status = MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_ARGUMENT);
    MBED_WARNING1(error_status, "Value out of range for log module or log level", error);
    return;
  }
  if(level <= log_levels[module]) {
    std::string log_line;
    compose_log_line(log_line, module, level, message);
    DEBUG_PRINTF("%s", log_line.c_str());
    _sd_card->write(_file_name, log_line);
  }
}

void Logger::pad_string_to(std::string &str, const size_t num, const char padding_char) {
  if (num > str.size()) {
    str.insert(str.size(), num - str.size(), padding_char);
  }
}

void Logger::compose_log_line(std::string &log_line, Logger::Module module, Logger::Level level, const std::string &message) {
  std::string time_string;
  utils::get_formatted_time_string("%F %T", time_string);

  std::string module_name(logger_module_names[module]);
  pad_string_to(module_name, LOG_MODULE_NAME_MAX_SIZE);

  std::string level_name(logger_level_names[level]);
  pad_string_to(level_name, LOG_LEVEL_NAME_MAX_SIZE);

  log_line = log_line + time_string + " " + module_name + " [" + level_name + "]: " + message + "\n";
}

void Logger::set_level(Logger::Module module, Logger::Level level) {
  log_levels[module] = level;
}

void Logger::set_level_global(Logger::Level level) {
  for(int i = 0; i < Module::NUM_MODULES; i++) {
    log_levels[i] = level;
  }
}

Logger::Level Logger::get_level_by_module(Logger::Module module) {
  return log_levels[module];
}
