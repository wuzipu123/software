#include "mbed.h"
#include "LedIndicator.h"
#include "SDCard.h"
#include "Logger.h"
#include "SensorSPS30.h"
#include "SensorBME280.h"
#include "Buttons.h"
#include "StateContext.h"
#include "Communication.h"


int main() {
  SDBlockDevice sd_block_device(MBED_CONF_SD_SPI_MOSI, MBED_CONF_SD_SPI_MISO, MBED_CONF_SD_SPI_CLK,
                                MBED_CONF_SD_SPI_CS);

  FATFileSystem fat_file_system("sdcard");

  SDCard sd_card(sd_block_device, fat_file_system);

  Logger::init(&sd_card);

  EventFlags event_flags;
  Buttons buttons(event_flags);

  Communication communication;
  LedIndicator led_indicator;

  FlashIAP flash;
  SensorSPS30 sps30;
  SensorBME280 bme280;

  USBSerial usb_serial(false);
  CommandHandler command_handler(usb_serial, flash, sps30, bme280, event_flags);

  StateContext state_context(sd_card, communication, led_indicator, command_handler, flash, event_flags, sps30,
                             bme280, buttons);

  state_context.run();
}
