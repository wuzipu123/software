
#include "TimeCommand.h"
#include "defines.h"
#include "Logger.h"
#include "utils.h"
#include "Thread.h"
#include "mbed_rtc_time.h"

#define MS_PER_DAY 86400000.0f

TimeCommand::TimeCommand(USBSerial &usb_serial)
    : Command(time_command_name, time_command_description, usb_serial) {
}

void TimeCommand::wait_for_second_toggle() {
  time_t t = time(nullptr);
  while (time(nullptr) < t + 1) { ; }
}

void TimeCommand::calibrate() {
  wait_for_second_toggle();
  for (uint32_t i = 0; i < _cal_time_sec + 1; i++) {
    wait_for_second_toggle();
    _usb_serial.printf("%04lu\n", i);
  }
}

void TimeCommand::execute_command(std::map<std::string, std::string> &parameter_map,
                                  std::vector<std::string> &parameter_vec) {
  if (parameter_vec.empty() && parameter_map.empty()) {
    std::string time_string;
    utils::get_formatted_time_string("%F %T", time_string);
    _usb_serial.printf("Current time: %s\n", time_string.c_str());
    return;
  }

  if (!parameter_map.empty()) {
    _usb_serial.printf("Error: Invalid parameter\n");
  }

  if (parameter_vec.front() == "set") {
    parameter_vec.erase(parameter_vec.begin());
    time_t new_time = parse_datetime(parameter_vec);
    if (new_time == -1) {
      _usb_serial.printf("Error: Invalid date and/or time format\n");
      return;
    }
    set_time(new_time);

    std::string time_string;
    utils::get_formatted_time_string("%F %T", time_string);
    LOG(LVL_INFO, "Set date/time to: %s", time_string.c_str());
  } else if (parameter_vec.front() == "tick") {
    if (parameter_vec.size() == 2 && utils::is_number(parameter_vec.back())) {
      _cal_time_sec = strtol(parameter_vec.back().c_str(), nullptr, 10);
      rtos::Thread cal_thread(osPriorityRealtime7);
      cal_thread.start(mbed::callback(this, &TimeCommand::calibrate));
      cal_thread.join();
    } else {
      _usb_serial.printf("Error: Invalid parameter(s)\n");
      return;
    }
  } else if (parameter_vec.front() == "calibrate") {
    if (parameter_vec.size() == 2 && utils::is_number(parameter_vec.back())) {
      int32_t drift_per_day_ms = strtol(parameter_vec.back().c_str(), nullptr, 10);
      uint32_t plus_pulses = drift_per_day_ms >= 0 ? RTC_SMOOTHCALIB_PLUSPULSES_RESET : RTC_SMOOTHCALIB_PLUSPULSES_SET;
      int32_t minus_pulses = ((drift_per_day_ms * 32 / MS_PER_DAY)) / (1.0f / 32678.0f);

      if (!utils::is_in_range(minus_pulses, -511l, 511l)) {
        _usb_serial.printf("Error: Invalid parameter(s)\n");
        return;
      }

      if (minus_pulses < 0) {
        minus_pulses = 512 - minus_pulses;
      }

      _usb_serial.printf("plus pulses: 0x%08lx, minus pulses: 0x%08lx\n", plus_pulses, (uint32_t)minus_pulses);

      RTC_HandleTypeDef hrtc;
      hrtc.Instance = RTC;
      HAL_StatusTypeDef ret = HAL_RTCEx_SetSmoothCalib(&hrtc, RTC_SMOOTHCALIB_PERIOD_32SEC, plus_pulses,
                                                       (uint32_t) minus_pulses);
      if (HAL_OK != ret) {
        _usb_serial.printf("Error: Setting smooth RTC calibration failed (%d)\n", ret);
      }
    } else {
      _usb_serial.printf("Error: Invalid parameter(s)\n");
    }
  } else {
    _usb_serial.printf("Error: Invalid parameter(s)\n");
  }
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

  for (auto num : date) {
    if (!utils::is_number(num)) {
      return -1;
    }
  }
  for (auto num : time) {
    if (!utils::is_number(num)) {
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