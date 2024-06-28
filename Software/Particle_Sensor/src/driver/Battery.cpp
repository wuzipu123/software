#include "Battery.h"
#include "Logger.h"
#include "AnalogIn.h"
#include "DigitalOut.h"
#include "analogin_api.h"
#include "mbed_error.h"
#include "ThisThread.h"

using namespace std::chrono;

mbed::DigitalOut bat_level_en(MBED_CONF_APP_BATTERY_LEVEL_EN, false);
mbed::AnalogIn bat_level_input(MBED_CONF_APP_BATTERY_LEVEL);

/**
 * Overwrite the default ADC configuration to increase oversampling ratio
 * and thus increase the accuracy of the results.
 */
void analogin_init_direct(analogin_t *obj, const PinMap *pinmap) {
  analogin_init(obj, pinmap->pin);
  obj->handle.Init.OversamplingMode = ENABLE;
  obj->handle.Init.Oversampling.Ratio = ADC_OVERSAMPLING_RATIO_16;
  obj->handle.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_4;
  obj->handle.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  obj->handle.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;
// Enable ADC clock
  __HAL_RCC_ADC_CLK_ENABLE();
  __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_SYSCLK);

  if (HAL_ADC_Init(&obj->handle) != HAL_OK) {
    error("Cannot initialize ADC\n");
  }

  // ADC calibration is done only once
  if (!HAL_ADCEx_Calibration_GetValue(&obj->handle, ADC_SINGLE_ENDED)) {
    HAL_ADCEx_Calibration_Start(&obj->handle, ADC_SINGLE_ENDED);
  }
}

float Battery::read_voltage() {
  float bat_voltage = 0;

  bat_level_en = true;

  // Read ADC value 1000 times and average out the noise emitted by the DCDC regulator
  // Try reading battery voltage maximum 5 times, because sometimes bat_voltage is 0V
  int retries;
  for (retries = 0; retries < 5; retries++) {
    for (int i = 0; i < 1000; i++) {
      bat_voltage += bat_level_input.read_voltage();
    }
    bat_voltage /= 1000;

    if (bat_voltage > 0.5) {
      break;
    } else {
      bat_voltage = 0;
      rtos::ThisThread::sleep_for(100ms);
    }
  }

  if (retries > 0) {
    LOG(LVL_INFO, "Reading battery level failed %d time(s).", retries);
  }

  bat_level_en = false;

  return bat_voltage;
}