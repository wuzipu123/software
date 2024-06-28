#include "constants.h"
#include "mbed.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
#include "CommandHandler.h"
#include "SDCard.h"
#include "LedIndicator.h"
#include "Buttons.h"
#include "StateContext.h"
#include "Config.h"
#include "Sensor.h"
#include "Logger.h"
#include "utils.h"

int main() {
  printf("Test\n");
#ifdef PRINT_STATS
  Thread stats_thread(osPriorityNormal, 2048, nullptr, "stats_thread");
  stats_thread.start(utils::print_statistics);
#endif //PRINT_STATS

  DEBUG_PRINTF("Version: %d.%d.%d\n", version.major, version.minor, version.build);
  DEBUG_PRINTF("Build time: %s, %s\n", build_date, build_time);

  Config config;

  FlashIAP flash;

  SDBlockDevice sd_block_device(MBED_CONF_SD_SPI_MOSI, MBED_CONF_SD_SPI_MISO, MBED_CONF_SD_SPI_CLK,
                                MBED_CONF_SD_SPI_CS);

  FATFileSystem fat_file_system("sdcard");

  SDCard sd_card(sd_block_device, fat_file_system);

  USBSerial usb_serial(false);

  rtos::EventFlags control_event_flags("control_event_flags");

  CommandHandler command_handler(usb_serial, flash, config, control_event_flags);

  Buttons buttons(MBED_CONF_APP_START_STOP_BUTTON, MBED_CONF_APP_RESET_FORMAT_SD_BUTTON, control_event_flags);

  LedIndicator led_indicator(MBED_CONF_APP_RED_LED, MBED_CONF_APP_GREEN_LED);

  SensorBoardSerial sensor_board_serial(MBED_CONF_APP_SENSOR_SERIAL_TX, MBED_CONF_APP_SENSOR_SERIAL_RX,
                                        MBED_CONF_APP_SENSOR_RS485_DE_NRE);

  std::vector<Sensor *> sensors;
  for (uint32_t sensor_cnt = 0; sensor_cnt < NUM_SENSOR_SLOTS; sensor_cnt++) {
    sensors.push_back(new Sensor(sensor_io_configs[sensor_cnt], config.sensor_configs[sensor_cnt], sensor_board_serial,
                                 control_event_flags));
  }

  StateContext state_context(sd_card, led_indicator, sensors, command_handler, flash, control_event_flags, config);

  while (true) {
    state_context.handle();
  }

  for (auto sensor : sensors) {
    delete sensor;
  }
  sensors.clear();
}
