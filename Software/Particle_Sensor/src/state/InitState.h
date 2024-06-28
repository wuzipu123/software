
#ifndef PARTICLE_SENSOR_INITSTATE_H
#define PARTICLE_SENSOR_INITSTATE_H

#include "State.h"
#include "SDCard.h"
#include "Communication.h"
#include "SensorSPS30.h"
#include "SensorBME280.h"
#include "Buttons.h"
#include "FlashIAP.h"

/**
 * State initializing all objects which need explicit initialization.
 * Also test if connected sensors are working.
 */
class InitState : public State {
public:
  /**
   * Create an Initstate
   *
   * @param led_indicator Reference to the LedIndicator to control the status LED
   * @param sd_card       Reference to the SDCard to initialize it and also the Logger
   * @param communication Reference to the Communication object to start the LoRa communication thread
   * @param flash         Reference to the FlashIAP to load config from flash
   * @param sps30         Reference to the SensorSPS30 to perform a start up test
   * @param bme280        Reference to the SensorBME280 to perform a start up test
   * @param buttons       Reference to the Buttons, to check if default config should be loaded
   */
  InitState(LedIndicator &led_indicator, SDCard &sd_card, Communication &communication, mbed::FlashIAP &flash,
            SensorSPS30 &sps30, SensorBME280 &bme280, Buttons &buttons);

  /**
   * Default destructor
   */
  ~InitState() override = default;

  /**
   * Set status LED to orange, execute init() and depending on the
   * return value, set status LED to green or red for 3 seconds.
   *
   * @return the return value of init()
   */
  State::Result handle() override;

private:
  /**
   * Initialize the #_sd_card, RTC, Logger, SensorSPS30 and SensorBME280 and the #_flash.
   * If the two buttons are pressed, the #Config::global_config is set to its default values.
   * Otherwise, the stored config is loaded from flash memory and written to #Config::global_config.
   *
   * @return State::Result::SUCCESS on success, an State::Result
   */
  State::Result init();

  /**
   * Test if the SPS30 is working by executing the SensorSPS30::probe() function.
   *
   * @return MBED_SUCCESS if SPS30 works, an mbed_error_status_t otherwise
   */
  mbed_error_status_t sps30_test();

  /**
   * Initialize the SensorBME280 and test if the BME280 is working by reading
   * measurement values and checking if they are in range.
   *
   * @return MBED_SUCCESS if SPS30 works, an mbed_error_status_t otherwise
   */
  mbed_error_status_t bme280_test();


  /**
   * If the RTC time is not set, i.e. it is set to a date earlier than
   * #TIMESTAMP_20200101, it will be set to #TIMESTAMP_20200101.
   * Note: This is necessary, otherwise odd timing problems occur.
   */
  void init_rtc();

  /**
   * Reference to the SDCard to initialize it and the Logger
   */
  SDCard &_sd_card;

  /**
   * Reference to the Communication object to start the LoRa communication thread.
   */
  Communication &_communication;

  /**
   * Reference to the FlashIAP to initialize it
   * and load stored configurations to #Config::global_config.
   */
  mbed::FlashIAP &_flash;

  /**
   * Reference to SensorSPS30 to test if SPS30 is working
   */
  SensorSPS30 &_sps30;

  /**
   * Reference to SensorBME280 to test if BME280 is working
   */
  SensorBME280 &_bme280;

  /**
   * Reference to Buttons. If both buttons are pressed, the default configuration
   * is used for #Config::default_config, otherwise the configuration is loaded from #_flash.
   */
  Buttons &_buttons;
};


#endif //PARTICLE_SENSOR_INITSTATE_H
