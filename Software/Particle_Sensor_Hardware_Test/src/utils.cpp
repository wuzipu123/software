#include "utils.h"
#include "ns_cmdline.h"

#define ESCAPE(x) "\x1b" x
#define CLEAR_UNTIL_END_OF_LINE ESCAPE("[0K")
#define ASCII_BACKSPACE 8

void read_line(char *line) {
  char char_buf[2] = {0, 0};
  int char_idx = 0;
  memset(line, '\0', MAXIMUM_LINE_SIZE);

  while (true) {
    if (serial_port.read(char_buf, 1)) {
      if (char_buf[0] == '\r') {
        return;
      } else if (char_buf[0] == ASCII_BACKSPACE) {
        if (char_idx > 0) {
          cmd_printf(CLEAR_UNTIL_END_OF_LINE);
          char_idx--;
          line[char_idx] = 0;
        }
      } else if(char_buf[0] != '\n') {
        line[char_idx] = char_buf[0];
        char_idx++;
        if (char_idx == MAXIMUM_LINE_SIZE - 1) {
          return;
        }
      }
    }
  }
}

size_t split_string(const std::string &input_string, std::vector<std::string> &split_strings, char delimiter) {
  size_t part_begin = 0;
  size_t part_end = input_string.find_first_of(delimiter);
  std::string part;

  while (part_end != std::string::npos) {
    part = input_string.substr(part_begin, part_end - part_begin);
    if (!part.empty()) {
      split_strings.push_back(part);
    }
    part_begin = part_end + 1;

    part_end = input_string.find_first_of(delimiter, part_begin);
  }

  part = input_string.substr(part_begin, std::min(part_end, input_string.size()) - part_begin + 1);
  if (!part.empty()) {
    split_strings.push_back(part);
  }

  return split_strings.size();
}

time_t parse_datetime(const char *time_c_string) {
  struct tm datetime = {};

  std::string time_string(time_c_string);
  std::vector<string> parameters;
  split_string(time_string, parameters, 'T');
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

  datetime.tm_year = strtol(date.at(0).c_str(), nullptr, 10) - 1900;
  datetime.tm_mon = strtol(date.at(1).c_str(), nullptr, 10) - 1;
  datetime.tm_mday = strtol(date.at(2).c_str(), nullptr, 10);
  datetime.tm_hour = strtol(time.at(0).c_str(), nullptr, 10);
  datetime.tm_min = strtol(time.at(1).c_str(), nullptr, 10);
  datetime.tm_sec = strtol(time.at(2).c_str(), nullptr, 10);

  return mktime(&datetime);
}

