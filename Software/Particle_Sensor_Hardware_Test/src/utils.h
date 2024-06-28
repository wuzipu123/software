#ifndef SENSOR_NODE_LORA_SPS30_HW_TEST_UTILS_H
#define SENSOR_NODE_LORA_SPS30_HW_TEST_UTILS_H
#include "mbed.h"
#include <vector>

#define MAXIMUM_LINE_SIZE             1024

extern BufferedSerial serial_port;
extern DigitalOut rx_tx_led;

void read_line(char *line);

size_t split_string(const std::string &input_string, std::vector<std::string> &split_strings, char delimiter);

time_t parse_datetime(const char *time_c_string);

#endif //SENSOR_NODE_LORA_SPS30_HW_TEST_UTILS_H
