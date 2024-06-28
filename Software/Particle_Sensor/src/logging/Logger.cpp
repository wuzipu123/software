
#include "Logger.h"
#include "utils.h"
#include "mbed_debug.h"

bool Logger::_initialized = false;
SDCard *Logger::_sd_card = nullptr;
std::string Logger::_file_name = "log.txt";

void Logger::init(SDCard *sd_card) {
  _file_name.clear();
  utils::get_formatted_time_string("%Y-%m-%d_%H-%M-%S", _file_name);
  _file_name = "log_" + _file_name + ".txt";

  if (!_initialized) {
    _sd_card = sd_card;

    _initialized = true;
  }
}

void Logger::compose_log_line(std::string &log_line, const char *file_name, LogLevel log_level,
                              const std::string &message) {
  std::string time_string;
  utils::get_formatted_time_string("%FT%T", time_string);
  std::string module(file_name);
  module = module.substr(0, module.find('.'));

  std::string level_name(log_level_names[log_level]);

  log_line += time_string + " [" + level_name + "] " + module + ": " + message + "\n";
}

void Logger::log_internal(const char *file_name, LogLevel log_level, const char *format_string, ...) {
  if (log_level <= Config::get<uint32_t>("log_level")) {
    std::string log_message;
    std::string log_line;
    char buf[256];

    va_list args;
    va_start(args, format_string);
    vsnprintf(buf, 256, format_string, args);
    log_message += buf;
    va_end(args);

    compose_log_line(log_line, file_name, log_level, log_message);

    if (Config::get<uint32_t>("log_level") == LVL_DEBUG) {
      printf("%s", log_line.c_str());
    }
    _sd_card->write(_file_name, log_line);
  }
}
