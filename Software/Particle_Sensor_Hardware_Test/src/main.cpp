#include "mbed.h"
#include "ns_cmdline.h"
#include "commands.h"
#include "utils.h"

#define MAN_CMD_LED "Turn on or off LED outputs\r\n"\
                    "led <led_name> <bool>\r\n"\
                    "Parameters:\r\n"\
                    "<led_name>     Name of the LED to switch: Names are: stateRed, stateGreen, bat1, bat2, bat3\r\n"\
                    "<bool>         On/Off LED (e.g. 0, 1, on, off, true, false)\r\n"

#define MAN_CMD_BATLEVEL "Test battery level measurement\r\n"\
                         "batlevel (<option>)\r\n"\
                         "Options:\r\n"\
                         "-on       Turn voltage divider on\r\n"\
                         "-off      Turn voltage divider off\r\n"\
                         "-m        Read battery voltage from ADC\r\n"

#define MAN_CMD_SPS "Test particle sensor Sensirion SPS30\r\n"\
                    "sps (<option>)\r\n"\
                    "Options:\r\n"\
                    "(none)                     One measurement is done, one second after sensor start\r\n"\
                    "m <num_measurements>       With an interval of one second,\r\n"\
                    "                           <num_measurements> measurements are done.\r\n"

#define MAN_CMD_BME "Test environmental sensor Bosch BME280\r\n"\
                    "bme (<option>)\r\n"\
                    "Options:\r\n"\
                    "(none)                     One measurement is done, one second after sensor start\r\n"\
                    "m <num_measurements>       With an interval of one second,\r\n"\
                    "                           <num_measurements> measurements are done.\r\n"
#define MAN_CMD_PINGPONG "Test LoRa module with ping pong application\r\n"\
                         "pingpong <option>\r\n"\
                         "Options:\r\n"\
                         "-start      Start thread with ping pong application\r\n"\
                         "-stop       Stop thread running the ping pong application\r\n"\
                         "-ping       Send ping and then wait for pong\r\n"

#define MAN_CMD_TIME "Usage: time [COMMAND]\r\n"\
    "Commands:\r\n"\
    "\t<none>\t\t\t\tPrint current time\r\n"\
    "\tset YYYY-MM-DDTHH:MM:SS\t\tSet time in specified format\r\n"\
    "\ttick <num_ticks>\t\tPrint for <num_ticks> seconds every time, the RTC second counter toggles,\r\n"\
    "\t\t\t\t\tthe amount of passed seconds. Used to measure RTC time drift.\r\n"\
    "\tcalibrate <milliseconds>\tCalibrate the RTC by sending the time drift per day in milliseconds\r\n"

#define MAN_CMD_SLEEP "Set pins to low power configuration and sleep for a specified amount of seconds\r\n"\
                      "sleep (<option>)\r\n"\
                      "Options:\r\n"\
                      "(none)                     Sleep for 10 seconds\r\n"\
                      "m <duration>               Sleep for <duration> seconds\r\n"

DigitalOut rx_tx_led(PC_5);
BufferedSerial serial_port(STDIO_UART_TX, STDIO_UART_RX);

int main(void) {
  PinName bat_led_pins[] = MBED_CONF_APP_BATTERY_LEDS;
  DigitalOut(bat_led_pins[0], true);
  ThisThread::sleep_for(1s);
  DigitalOut(bat_led_pins[0], false);

  serial_port.set_baud(MBED_CONF_PLATFORM_STDIO_BAUD_RATE);
  serial_port.set_format(8, BufferedSerial::None, 1);

  cmd_init(0);
  cmd_set_ready_cb(cmd_ready_cb);
  cmd_add("led", cmd_led, "Turn on/off LEDs", MAN_CMD_LED);
  cmd_add("button", cmd_button, "Read button state", "Read button state (no options)");
  cmd_add("sdcard", cmd_sdcard, "Test micro SD card (slot)", "Test micro SD card (slot). (no options)");
  cmd_add("batlevel", cmd_batlevel, "Test battery level measurement", MAN_CMD_BATLEVEL);
  cmd_add("sps", cmd_sps, "Test particle sensor Sensirion SPS30", MAN_CMD_SPS);
  cmd_add("pingpong", cmd_pingpong, "LoRa ping pong application", MAN_CMD_PINGPONG);
  cmd_add("bme", cmd_bme, "Test environmental sensor Bosch BME280", MAN_CMD_BME);
  cmd_add("time", cmd_time, "Test RTC time keeping", MAN_CMD_TIME);
  cmd_add("usb", cmd_usb, "Test USB serial interface", "Test USB serial interface (no options)");
  cmd_add("sleep", cmd_sleep, "Sleep for specified amount of seconds", MAN_CMD_SLEEP);

  char line[MAXIMUM_LINE_SIZE] = {0};

  while (true) {
    read_line(line);
    cmd_exe(line);
  }
}