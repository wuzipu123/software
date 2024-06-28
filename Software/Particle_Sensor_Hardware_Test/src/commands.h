#ifndef SENSOR_NODE_LORA_SPS30_HW_TEST_COMMANDS_H
#define SENSOR_NODE_LORA_SPS30_HW_TEST_COMMANDS_H

#include "mbed.h"

void cmd_ready_cb(int retcode);

int cmd_led(int argc, char *argv[]);

int cmd_button(int argc, char *argv[]);

int cmd_batlevel(int argc, char *argv[]);

int cmd_sps(int argc, char *argv[]);

int cmd_sdcard(int argc, char *argv[]);

int cmd_pingpong(int argc, char *argv[]);

int cmd_bme(int argc, char *argv[]);

int cmd_time(int argc, char *argv[]);

int cmd_usb(int argc, char *argv[]);

int cmd_sleep(int argc, char *argv[]);

#endif //SENSOR_NODE_LORA_SPS30_HW_TEST_COMMANDS_H
