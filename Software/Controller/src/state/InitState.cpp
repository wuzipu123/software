
#include "InitState.h"
#include "Logger.h"
#include "utils.h"

InitState::InitState(LedIndicator &led_indicator, SDCard &sd_card, Config &config, mbed::FlashIAP &flash)
    : State(led_indicator),
      _sd_card(sd_card),
      _flash(flash),
      _config(config) {
}

State::Result InitState::handle() {
  _led_indicator.set_behavior(Led::Behavior::OFF, Led::Behavior::ON);

  mbed_error_status_t error_status = _sd_card.init();
  if (MBED_SUCCESS != error_status) {
    return State::Result::SD_CARD_ERROR;
  }
  Logger::init(&_sd_card);

  _flash.init();
  init_from_flash(STORAGE_ADDR_LOG_LEVELS, (uint8_t *)&Logger::log_levels, sizeof(Logger::log_levels));
  init_from_flash(STORAGE_ADDR_CONFIG, (uint8_t *)&_config, sizeof(_config));

  Logger::log(Logger::Module::INIT_STATE, Logger::Level::INFO, "Initialization completed");

  return State::Result::SUCCESS;
}

void InitState::init_from_flash(uint32_t address, uint8_t *destination, size_t size) {
  if(size > _flash.get_sector_size(address)) {
    std::string log_message = "Could not data starting at address " + utils::to_hex_string(address)
                              + " with size " + utils::to_hex_string(size) + " from flash. Size too big.";
    Logger::log(Logger::Module::INIT_STATE, Logger::Level::ERROR, log_message);
    return;
  }

  uint8_t *buffer = new uint8_t[size];
  if(_flash.read(buffer, address, size) != 0) {
    std::string log_message = "Could not load data starting at address " + utils::to_hex_string(address)
                              + " with size " + utils::to_hex_string(size) + " from flash. Reading flash failed.";
    Logger::log(Logger::Module::INIT_STATE, Logger::Level::ERROR, log_message);
    delete[] buffer;
    return;
  }

  for(size_t i = 0; i < size; i++) {
    if(buffer[i] != _flash.get_erase_value()) {
      std::memcpy(destination, buffer, size);
      delete[] buffer;
      return;
    }
  }

  std::string log_message = "Area starting at address " + utils::to_hex_string(address) + " with size "
                            + utils::to_hex_string(size) + " is erased on flash. Init with default values.";
  Logger::log(Logger::Module::INIT_STATE, Logger::Level::INFO, log_message);

  delete[] buffer;
}