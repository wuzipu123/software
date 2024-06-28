

#include <ctime>
#include "utils.h"

namespace utils {
  void get_formatted_time_string(const char *format_string, std::string &dest) {
    time_t current_time = 1575979067;
    char time_string[100];
    strftime(time_string, 100, format_string, localtime(&current_time));
    dest.clear();
    dest.append(time_string);
  }

  void convert_to_exp_num_string(float num, std::string &dest) {
    //TODO(stefan): Check if it is better to replace with C++-style conversion
    char buffer[16];
    buffer[15] = 0;
    sprintf(buffer, "%.9e", num);
    dest.clear();
    dest += buffer;
  }

  std::string to_hex_string(uint32_t number) {
    char hex_string[20];
    sprintf(hex_string, "0x%lX", number);
    return std::string(hex_string);
  }
}