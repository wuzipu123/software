
#ifndef CONTROLLER_INITSTATE_H
#define CONTROLLER_INITSTATE_H

#include "State.h"
#include "SDCard.h"
#include "Config.h"
#include "FlashIAP.h"

/**
 * State initializing all objects which need explicit initialization
 */
class InitState : public State {
public:
  /**
   * Create an InitState
   *
   * @param led_indicator Reference to the LedIndicator to set the LED behavior
   * @param sd_card       Reference to the SDCard to initialize itself and the Logger
   * @param config        Reference to the Config to restore it from the flash memory
   * @param flash         Reference to the FlashIAP to restore configurations from the flash memory
   */
  InitState(LedIndicator &led_indicator, SDCard &sd_card, Config &config, mbed::FlashIAP &flash);

  /**
   * Default destructor
   */
  ~InitState() override = default;

  /**
   * Initialize the #_sd_card, Logger and the #_flash.
   * Load stored #_config and Logger#log_levels from the #_flash memory.
   *
   * @return
   */
  State::Result handle() override;

private:
  /**
   * Reference to the SDCard to initialize it and the Logger
   */
  SDCard &_sd_card;

  /**
   * Reference to the FlashIAP to initialize it and load configurations
   */
  mbed::FlashIAP &_flash;

  /**
   * Reference to the Config, which is overwritten with the config loaded from the flash memory
   */
  Config &_config;

  /**
   * Loads \p size bytes from the given flash \p address and writes
   * it to the \p destination.
   *
   * @param address     Address on the flash to read from
   * @param destination Buffer to write to
   * @param size        Size in bytes to load and write
   */
  void init_from_flash(uint32_t address, uint8_t *destination, size_t size);
};


#endif //CONTROLLER_INITSTATE_H
