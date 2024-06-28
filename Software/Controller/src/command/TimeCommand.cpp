
#include "TimeCommand.h"
#include "Logger.h"
#include "constants.h"
#include "utils.h"
#include "mbed_rtc_time.h"
#include <cstdlib>

TimeCommand::TimeCommand(USBSerial &usb_serial)
    : Command(time_command_name, time_command_description, usb_serial) {
}

mbed_error_status_t TimeCommand::execute(std::string &parameter_string) {
  std::vector<std::string> parameters;
  size_t num_parameters = split_string(parameter_string, parameters, ' ');

  if (num_parameters == 0) {
    std::string time_string;
    utils::get_formatted_time_string("%F %T", time_string);
    _usb_serial.printf("Current time: %s\n", time_string.c_str());
    return MBED_SUCCESS;
  }

  if (parameters.front() == "set") {
    parameters.erase(parameters.begin());
    time_t new_time = parse_datetime(parameters);
    if (new_time == -1) {
      _usb_serial.printf("Error: Invalid date and/or time format\n");
      return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_FORMAT);
    }
    set_time(new_time);

    std::string log_message;
    utils::get_formatted_time_string("%F %T", log_message);
    log_message = "Set date/time to: " + log_message;
    Logger::log(Logger::Module::TIME_COMMAND, Logger::Level::INFO, log_message);
  } else {
    _usb_serial.printf("Error: Invalid parameter(s)\n");
    return MBED_MAKE_ERROR(MBED_MODULE_APPLICATION, MBED_ERROR_INVALID_ARGUMENT);
  }

  return MBED_SUCCESS;
}

time_t TimeCommand::parse_datetime(const std::vector<std::string> &parameters) {
  struct tm datetime = {};

  if (parameters.size() != 2) {
    return -1;
  }

  std::vector<std::string> date;
  std::vector<std::string> time;
  split_string(parameters.at(0), date, '-');
  split_string(parameters.at(1), time, ':');

  if (date.size() != 3 || time.size() != 3) {
    return -1;
  }

  for(auto num : date) {
    if(!utils::is_number(num)) {
      return -1;
    }
  }
  for(auto num : time) {
    if(!utils::is_number(num)) {
      return -1;
    }
  }

  datetime.tm_year = strtol(date.at(0).c_str(), nullptr, 10) - 1900;
  datetime.tm_mon = strtol(date.at(1).c_str(), nullptr, 10) - 1;
  datetime.tm_mday = strtol(date.at(2).c_str(), nullptr, 10);
  datetime.tm_hour = strtol(time.at(0).c_str(), nullptr, 10);
  datetime.tm_min = strtol(time.at(1).c_str(), nullptr, 10);
  datetime.tm_sec = strtol(time.at(2).c_str(), nullptr, 10);

  return mktime(&datetime);
}