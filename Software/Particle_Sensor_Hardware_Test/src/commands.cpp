#include "commands.h"
#include "utils.h"
#include "sps30.h"
#include "bme280.h"
#include "bme280_adapter.h"
#include "sensirion_uart.h"
#include "lora.h"
#include "ns_cmdline.h"
#include <map>
#include "SDBlockDevice.h"
#include "USBSerial.h"

#define MS_PER_DAY 86400000.0f

Thread lora_thread;

void cmd_ready_cb(int retcode) {
  cmd_next(retcode);
}

int cmd_led(int argc, char *argv[]) {
  PinName bat_leds[] = MBED_CONF_APP_BATTERY_LEDS;
  map<string, PinName> led_pin_map = {
      {"stateRed",   MBED_CONF_APP_STATE_LED_RED},
      {"stateGreen", MBED_CONF_APP_STATE_LED_GREEN},
      {"bat1", bat_leds[0]},
      {"bat2", bat_leds[1]},
      {"bat3", bat_leds[2]},
  };

  for (auto const &led_pin :led_pin_map) {
    bool value;
    if (cmd_parameter_bool(argc, argv, led_pin.first.c_str(), &value)) {
      cmd_printf("Set LED %s to %s", led_pin.first.c_str(), value ? "HIGH" : "LOW");
      DigitalOut(led_pin.second, value);
      return CMDLINE_RETCODE_SUCCESS;
    }
  }
  return CMDLINE_RETCODE_FAIL;
}

int cmd_button(int argc, char *argv[]) {
  DigitalIn button1(MBED_CONF_APP_BUTTON_1);
  cmd_printf("Button 1 is %s\n", button1.read() ? "HIGH" : "LOW");

  DigitalIn button2(MBED_CONF_APP_BUTTON_2);
  cmd_printf("Button 2 is %s\n", button2.read() ? "HIGH" : "LOW");

  return CMDLINE_RETCODE_SUCCESS;
}

int cmd_batlevel(int argc, char *argv[]) {
  int retcode = CMDLINE_RETCODE_INVALID_PARAMETERS;

  if (cmd_has_option(argc, argv, "off")) {
    DigitalOut bat_level_enable(MBED_CONF_APP_BATTERY_LEVEL_EN, false);
    cmd_printf("Battery level enable is OFF\n");
    retcode = CMDLINE_RETCODE_SUCCESS;
  } else if (cmd_has_option(argc, argv, "on")) {
    DigitalOut bat_level_enable(MBED_CONF_APP_BATTERY_LEVEL_EN, true);
    cmd_printf("Battery level enable is ON\n");
    retcode = CMDLINE_RETCODE_SUCCESS;
  }

  if (cmd_has_option(argc, argv, "-m")) {
    AnalogIn bat_level(MBED_CONF_APP_BATTERY_LEVEL);
    float val = bat_level.read();
    cmd_printf("Battery level is %.3f x 9.9V = %.3fV\n", val, val * 9.9);
    retcode = CMDLINE_RETCODE_SUCCESS;
  }

  return retcode;
}

int cmd_sps(int argc, char *argv[]) {
  int32_t num_measurements = 1;
  if (cmd_parameter_int(argc, argv, "m", &num_measurements)) {
    if (num_measurements < 1) {

      return CMDLINE_RETCODE_INVALID_PARAMETERS;
    }
  } else if (argc > 1) {
    return CMDLINE_RETCODE_INVALID_PARAMETERS;
  }

  struct sps30_measurement m;
  char serial[SPS30_MAX_SERIAL_LEN];
  const uint8_t AUTO_CLEAN_DAYS = 4;
  int16_t ret;

  DigitalOut supply_enable(MBED_CONF_APP_SPS30_SUPPLY_ENABLE, true);

  while (sensirion_uart_open() != 0) {
    cmd_printf("UART init failed\n");
    sensirion_sleep_usec(1000000);
  }

  while (sps30_probe() != 0) {
    cmd_printf("SPS30 sensor probing failed\n");
    sensirion_sleep_usec(1000000);
  }
  cmd_printf("SPS30 sensor probing successful\n");

  struct sps30_version_information version_information;
  ret = sps30_read_version(&version_information);
  if (ret) {
    cmd_printf("error %d reading version information\n", ret);
  } else {
    cmd_printf("FW: %u.%u HW: %u, SHDLC: %u.%u\n",
               version_information.firmware_major,
               version_information.firmware_minor,
               version_information.hardware_revision,
               version_information.shdlc_major,
               version_information.shdlc_minor);
  }

  ret = sps30_get_serial(serial);
  if (ret)
    cmd_printf("error %d reading serial\n", ret);
  else
    cmd_printf("SPS30 Serial: %s\n", serial);

  ret = sps30_set_fan_auto_cleaning_interval_days(AUTO_CLEAN_DAYS);
  if (ret)
    cmd_printf("error %d setting the auto-clean interval\n", ret);

  ret = sps30_start_measurement();
  if (ret < 0) {
    cmd_printf("error starting measurement\n");
  }

  cmd_printf("measurements started\n");
  cmd_printf("pm1.0;"
             "\tpm2.5;"
             "\tpm4.0;"
             "\tpm10.0;"
             "\tnc0.5;"
             "\tnc1.0;"
             "\tnc2.5;"
             "\tnc4.5;"
             "\tnc10.0;"
             "\ttypical particle size\n");

  for (int i = 0; i < num_measurements; ++i) {
    sensirion_sleep_usec(1000000);

    ret = sps30_read_measurement(&m);
    if (ret < 0) {
      cmd_printf("error reading measurement\n");
    } else {
      if (SPS30_IS_ERR_STATE(ret)) {
        cmd_printf(
            "Chip state: %u - measurements may not be accurate\n",
            SPS30_GET_ERR_STATE(ret));
      }

      /*cmd_printf("measured values:\n"
                 "\t%0.2f pm1.0\n"
                 "\t%0.2f pm2.5\n"
                 "\t%0.2f pm4.0\n"
                 "\t%0.2f pm10.0\n"
                 "\t%0.2f nc0.5\n"
                 "\t%0.2f nc1.0\n"
                 "\t%0.2f nc2.5\n"
                 "\t%0.2f nc4.5\n"
                 "\t%0.2f nc10.0\n"
                 "\t%0.2f typical particle size\n\n",
                 m.mc_1p0, m.mc_2p5, m.mc_4p0, m.mc_10p0, m.nc_0p5,
                 m.nc_1p0, m.nc_2p5, m.nc_4p0, m.nc_10p0,
                 m.typical_particle_size);*/
      cmd_printf("%0.2f;"
                 "\t%0.2f;"
                 "\t%0.2f;"
                 "\t%0.2f;"
                 "\t%0.2f;"
                 "\t%0.2f;"
                 "\t%0.2f;"
                 "\t%0.2f;"
                 "\t%0.2f;"
                 "\t%0.2f\n",
                 m.mc_1p0, m.mc_2p5, m.mc_4p0, m.mc_10p0, m.nc_0p5,
                 m.nc_1p0, m.nc_2p5, m.nc_4p0, m.nc_10p0,
                 m.typical_particle_size);
    }
  }

  if (version_information.firmware_major >= 2) {
    ret = sps30_sleep();
    if (ret) {
      cmd_printf("Entering sleep failed\n");
    }
  }

  if (version_information.firmware_major >= 2) {
    ret = sps30_wake_up();
    if (ret) {
      cmd_printf("Error %i waking up sensor\n", ret);
    }
  }

  if (sensirion_uart_close() != 0)
    cmd_printf("failed to close UART\n");

  supply_enable = false;

  return CMDLINE_RETCODE_SUCCESS;
}

int cmd_sdcard(int argc, char *argv[]) {
  DigitalIn detect(MBED_CONF_APP_SD_CARD_DETECT, PullUp);
  ThisThread::sleep_for(100ms);
  bool det_val = detect.read();
  cmd_printf("SD card %sdetected\n", det_val ? "NOT " : "");
  if (det_val) {
    return CMDLINE_RETCODE_FAIL;
  }

  SDBlockDevice sd(MBED_CONF_SD_SPI_MOSI,
                   MBED_CONF_SD_SPI_MISO,
                   MBED_CONF_SD_SPI_CLK,
                   MBED_CONF_SD_SPI_CS);

  if (0 != sd.init()) {
    cmd_printf("SD card init failed\n");
    return CMDLINE_RETCODE_FAIL;
  } else {
    cmd_printf("SD card init succeeded. Size: %llu\n", sd.size());
  }

  if (0 != sd.frequency(MBED_CONF_APP_SDCARD_SPI_FREQUENCY)) {
    cmd_printf("SD card setting frequency failed\n");
    sd.deinit();
    return CMDLINE_RETCODE_FAIL;
  }

  uint8_t block[512] = "Hello World!\n";

  if (0 == sd.program(block, 0, 512)) {
    cmd_printf("Wrote to SD card: %s", block);
    memset(block, 0, 512);
    if (0 == sd.read(block, 0, 512)) {
      cmd_printf("Read from SD card: %s", block);
    } else {
      cmd_printf("SD card read failed\n");
    }
  } else {
    cmd_printf("SD card write failed\n");
  }

  sd.deinit();
  return CMDLINE_RETCODE_SUCCESS;
}

int cmd_pingpong(int argc, char *argv[]) {
  if (cmd_has_option(argc, argv, "start")) {
    if (lora_thread.get_state() == Thread::State::Deleted) {
      lora_thread.start(ping_pong);
      cmd_printf("LoRa ping pong application started\n");
      return CMDLINE_RETCODE_SUCCESS;
    } else {
      cmd_printf("LoRa ping pong thread is already running\n");
      return CMDLINE_RETCODE_FAIL;
    }
  }

  if (cmd_has_option(argc, argv, "stop")) {
    if (lora_thread.get_state() == Thread::State::Deleted) {
      cmd_printf("LoRa ping pong thread is not running\n");
      return CMDLINE_RETCODE_FAIL;
    } else {
      radio_sleep();
      lora_thread.terminate();
      cmd_printf("LoRa ping pong application stopped\n");
      return CMDLINE_RETCODE_SUCCESS;
    }
  }

  if (cmd_has_option(argc, argv, "ping")) {
    if (lora_thread.get_state() == Thread::State::Deleted) {
      cmd_printf("LoRa ping pong thread is not running\n");
      return CMDLINE_RETCODE_FAIL;
    } else {
      button_pressed();
      return CMDLINE_RETCODE_SUCCESS;
    }
  }

  return CMDLINE_RETCODE_INVALID_PARAMETERS;
}

int cmd_bme(int argc, char *argv[]) {
  int32_t num_measurements = 1;
  if (cmd_parameter_int(argc, argv, "m", &num_measurements)) {
    if (num_measurements < 1) {
      return CMDLINE_RETCODE_INVALID_PARAMETERS;
    }
  } else if (argc > 1) {
    return CMDLINE_RETCODE_INVALID_PARAMETERS;
  }

  struct bme280_dev dev;

  int8_t rslt = BME280_OK;

  uint8_t dev_addr = 0;

  dev.intf_ptr = &dev_addr;
  dev.intf = BME280_SPI_INTF;
  dev.read = user_spi_read;
  dev.write = user_spi_write;
  dev.delay_us = user_delay_us;

  user_spi_init();

  rslt = bme280_init(&dev);
  cmd_printf("BME280 init rslt: %d\n", rslt);

  rslt = stream_sensor_data_normal_mode(&dev, num_measurements);
  cmd_printf("BME280 stream sensor data normal mode rslt: %d\n", rslt);

  return CMDLINE_RETCODE_SUCCESS;
}

void wait_for_second_toggle() {
  time_t t = time(nullptr);
  while (time(nullptr) < t + 1) { ; }
}

int cmd_time(int argc, char *argv[]) {
  int32_t num = 0;
  if (cmd_parameter_int(argc, argv, "tick", &num)) {
    wait_for_second_toggle();
    for (uint32_t i = 0; i < (uint32_t)num + 1; i++) {
      wait_for_second_toggle();
      cmd_printf("%04lu\n", i);
    }
    return CMDLINE_RETCODE_SUCCESS;
  }

  if (cmd_parameter_int(argc, argv, "calibrate", &num)) {
    int32_t drift_per_day_ms = num;
    uint32_t plus_pulses = drift_per_day_ms >= 0 ? RTC_SMOOTHCALIB_PLUSPULSES_RESET : RTC_SMOOTHCALIB_PLUSPULSES_SET;
    int32_t minus_pulses = ((drift_per_day_ms * 32 / MS_PER_DAY)) / (1.0f / 32678.0f);

    if (minus_pulses < -511l || minus_pulses > 511l) {
      cmd_printf("Error: Invalid parameter(s)\n");
      return CMDLINE_RETCODE_INVALID_PARAMETERS;
    }

    if (minus_pulses < 0) {
      minus_pulses = 512 - minus_pulses;
    }

    cmd_printf("plus pulses: 0x%08lx, minus pulses: 0x%08lx\n", plus_pulses, (uint32_t)minus_pulses);

    RTC_HandleTypeDef hrtc;
    hrtc.Instance = RTC;
    HAL_StatusTypeDef ret = HAL_RTCEx_SetSmoothCalib(&hrtc, RTC_SMOOTHCALIB_PERIOD_32SEC, plus_pulses,
                                                     (uint32_t) minus_pulses);
    if (HAL_OK != ret) {
      cmd_printf("Error: Setting smooth RTC calibration failed (%d)\n", ret);
    }

    return CMDLINE_RETCODE_SUCCESS;
  }

  if (argc == 1) {
    time_t current_time = time(nullptr);
    char time_string[20];
    strftime(time_string, 100, "%FT%T", localtime(&current_time));
    cmd_printf("Current time: %s\n", time_string);
    return CMDLINE_RETCODE_SUCCESS;
  } else if (argc == 3) {
    if (strncmp(argv[1], "set", 3) == 0) {
      time_t new_time = parse_datetime(argv[2]);
      if (new_time < 0) {
        return CMDLINE_RETCODE_INVALID_PARAMETERS;
      }
      set_time(new_time);
      return CMDLINE_RETCODE_SUCCESS;
    } else if (argv[1] == "tick") {

    }
  }

  return CMDLINE_RETCODE_INVALID_PARAMETERS;
}

int cmd_usb(int argc, char *argv[]) {
  USBSerial usb_serial(false);

  bool is_connected = false;
  int num_tries = 20;
  for (int i = 0; i < num_tries; i++) {
    cmd_printf("Try to connect to USB serial terminal. Attempt %d of %d.\n", i + 1, num_tries);
    usb_serial.connect();
    if(usb_serial.connected()) {
      is_connected = true;
      cmd_printf("Connected to USB serial terminal\n");
      break;
    }
    ThisThread::sleep_for(1s);
  }

  if(!is_connected) {
    cmd_printf("Connecting to USB serial terminal failed!\n");
    return CMDLINE_RETCODE_FAIL;
  }

  usb_serial.printf("If you can read this, the USB serial write operation works.\n"\
                     "To test the read operation, send any message to the USB serial interface, "\
                     "for the following 10 seconds it will be echoed back.\n");

  cmd_printf("Waiting for response.");
  char buf[1024] = { 0 };

  bool received_response = false;
  for (int i = 0; i < 10; i++) {
    int num_bytes_available = usb_serial.available();
    while(num_bytes_available > 0 && num_bytes_available < 1024) {
      usb_serial.read(buf, num_bytes_available);
      received_response = true;
      usb_serial.printf("\nReceived: %s", buf);
      cmd_printf("\nReceived: %s", buf);
      num_bytes_available = usb_serial.available();
      ThisThread::sleep_for(1ms);
    }
    ThisThread::sleep_for(1s);
    if(!received_response) {
      cmd_printf(".");
    }
  }

  if(received_response) {
    return CMDLINE_RETCODE_SUCCESS;
  }
  return CMDLINE_RETCODE_FAIL;
}

int cmd_sleep(int argc, char *argv[]) {
  int32_t time = 10;
  if (cmd_parameter_int(argc, argv, "m", &time)) {
    if (time < 1 || time > 600) {
      return CMDLINE_RETCODE_INVALID_PARAMETERS;
    }
  } else if (argc > 1) {
    return CMDLINE_RETCODE_INVALID_PARAMETERS;
  }

  serial_port.enable_input(false);
  //mbed::DigitalOut(PA_2 , true);
  //mbed::DigitalOut(PA_3 , true);
  mbed::DigitalOut(PA_0 , false);
  mbed::DigitalOut (PA_1 , false);
  mbed::DigitalOut(PA_4 , false);
  mbed::DigitalOut(PA_5 , false);
  mbed::DigitalOut(PA_6 , false);
  mbed::DigitalOut(PA_7 , false);
  mbed::DigitalOut(PA_8 , false);
  mbed::DigitalOut(PA_9 , false);
  mbed::DigitalOut(PA_10, false);
  mbed::DigitalOut(PA_11, false);
  mbed::DigitalOut(PA_12, false);
  mbed::DigitalOut(PA_13, false);
  mbed::DigitalOut(PA_14, false);
  mbed::DigitalOut(PA_15, false);
  mbed::DigitalOut(PB_0 , false);
  mbed::DigitalOut(PB_1 , false);
  mbed::DigitalOut(PB_2 , false);
  mbed::DigitalOut(PB_3 , false);
  mbed::DigitalOut(PB_4 , false);
  mbed::DigitalOut(PB_5 , false);
  mbed::DigitalOut(PB_6 , false);
  mbed::DigitalOut(PB_7 , true);
  mbed::DigitalOut(PB_8 , true);
  mbed::DigitalOut(PB_9 , false);
  mbed::DigitalOut(PB_10, false);
  mbed::DigitalOut(PB_11, false);
  mbed::DigitalOut(PB_12, false);
  mbed::DigitalOut(PB_13, false);
  mbed::DigitalOut(PB_14, false);
  mbed::DigitalOut(PB_15, false);
  mbed::DigitalOut(PC_0 , false);
  mbed::DigitalOut(PC_1 , false);
  mbed::DigitalOut(PC_2 , false);
  mbed::DigitalOut(PC_3 , false);
  mbed::DigitalOut(PC_4 , false);
  mbed::DigitalOut(PC_5 , false);
  mbed::DigitalOut(PC_6 , false);
  mbed::DigitalOut(PC_7 , false);
  mbed::DigitalOut(PC_8 , false);
  mbed::DigitalOut(PC_9 , false);
  mbed::DigitalOut(PC_10, false);
  mbed::DigitalOut(PC_11, false);
  mbed::DigitalOut(PC_12, false);
  mbed::DigitalOut(PC_13, false);
  mbed::DigitalOut(PC_14, false);
  mbed::DigitalOut(PC_15, false);
  mbed::DigitalOut(PD_2 , false);

  cmd_printf("Can deep sleep test check: %s\n", sleep_manager_can_deep_sleep_test_check() ? "true" : "false");
  cmd_printf("Now sleep for %ld seconds\n", time);

  ThisThread::sleep_for(chrono::seconds(time));

  mbed_stats_cpu_t stats;
  mbed_stats_cpu_get(&stats);
  printf("Uptime: %llu ", stats.uptime / 1000);
  printf("Sleep time: %llu ", stats.sleep_time / 1000);
  printf("Deep Sleep: %llu\n", stats.deep_sleep_time / 1000);
  serial_port.enable_input(true);
  return CMDLINE_RETCODE_SUCCESS;
}