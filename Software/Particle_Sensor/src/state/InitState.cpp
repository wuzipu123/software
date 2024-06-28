
#include "InitState.h"
#include "Logger.h"
#include "utils.h"
#include "mbed_error.h"
#include "mbed_rtc_time.h"

#define TIMESTAMP_20200101 1577836800

InitState::InitState(LedIndicator &led_indicator, SDCard &sd_card, Communication &communication, mbed::FlashIAP &flash,
                     SensorSPS30 &sps30, SensorBME280 &bme280, Buttons &buttons)
    : State(led_indicator),
      _sd_card(sd_card),
      _communication(communication),
      _flash(flash),
      _sps30(sps30),
      _bme280(bme280),
      _buttons(buttons) {
}

State::Result InitState::handle() {
  LOG(LVL_INFO, "Enter InitState");
  _led_indicator.display_status_for(LedIndicator::Color::ORANGE);
  State::Result error_status = init();
  if (State::Result::SUCCESS != error_status) {
    _led_indicator.display_status_for(LedIndicator::Color::RED, 3000);
  } else {
    _led_indicator.display_status_for(LedIndicator::Color::GREEN, 3000);
  }
  return error_status;
}

State::Result InitState::init() {
  mbed_error_status_t error_status = _sd_card.init();
  if (MBED_SUCCESS != error_status) {
    return State::Result::SD_CARD_ERROR;
  }

  init_rtc();

  Logger::init(&_sd_card);

  Config::save_default_config();
  if (_buttons.is_left_pressed() && _buttons.is_right_pressed()) {
    Config::reset_config();
    if (MBED_SUCCESS != Config::write_config_to_flash(_flash)) {
      LOG(LVL_ERROR, "Failed to write default config to flash");
      return State::Result::FLASH_ERROR;
    }
    LOG(LVL_INFO, "Reset config to default values");
  } else {
    if (MBED_SUCCESS != Config::read_config_from_flash(_flash)) {
      return State::Result::FLASH_ERROR;
    }
  }

  if (MBED_SUCCESS != sps30_test()) {
    LOG(LVL_ERROR, "SPS30 test failed");
    return State::Result::SENSOR_ERROR;
  }

  if (MBED_SUCCESS != bme280_test()) {
    LOG(LVL_ERROR, "BME280 test failed");
    return State::Result::SENSOR_ERROR;
  }

  if (Config::get<bool>("lora_enable")) {
    if (_communication.start() != MBED_SUCCESS) {
      LOG(LVL_ERROR, "Starting communication thread failed!");
      return State::Result::LORA_ERROR;
    }
  }

  mbed_reset_reboot_count();
  Logger::LOG(LVL_DEBUG, "Initialization completed");
  return State::Result::SUCCESS;
}

mbed_error_status_t InitState::sps30_test() {
  _sps30.power_on();
  mbed_error_status_t error_status = _sps30.probe();
  _sps30.power_off();
  return error_status;
}

mbed_error_status_t InitState::bme280_test() {
  TRY(_bme280.init());
  SensorBME280::measurement_t bme280_measurement = {-1000, -1000, -1000};
  rtos::ThisThread::sleep_for(std::chrono::milliseconds(BME280_TEST_STARTUP_TIME_MS));
  TRY(_bme280.read_measurement(&bme280_measurement));

  LOG(LVL_DEBUG, "BME280 Test: temp\tpress\t\thum");
  LOG(LVL_DEBUG, "BME280 Test: %0.2f\t%0.2f\t%0.2f", bme280_measurement.temperature, bme280_measurement.pressure,
      bme280_measurement.humidity);

  if (!utils::is_in_range(bme280_measurement.temperature, -30.0, 60.0) ||
      !utils::is_in_range(bme280_measurement.pressure, 20000.0, 110000.0) ||
      !utils::is_in_range(bme280_measurement.humidity, 0.0, 100.0)) {
    return MBED_ERROR_INVALID_DATA_DETECTED;
  }

  return MBED_SUCCESS;
}

void InitState::init_rtc() {
  if (time(nullptr) < TIMESTAMP_20200101) {
    set_time(TIMESTAMP_20200101);
  }
}