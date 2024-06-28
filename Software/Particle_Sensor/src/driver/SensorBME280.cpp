
#include "SensorBME280.h"
#include "ThisThread.h"
#include "Logger.h"
#include "bme280.h"
#include "bme280_defs.h"

SensorBME280::SensorBME280() : _bme280_cs(MBED_CONF_APP_BME280_CHIP_SELECT, true),
                   _spi(MBED_CONF_APP_SPI_MOSI, MBED_CONF_APP_SPI_MISO, MBED_CONF_APP_SPI_CLK),
                   _dev({}),
                   _bme280_handle({&_bme280_cs, &_spi}) {
}

void SensorBME280::bme280_delay_us(uint32_t period, void *intf_ptr) {
  /*
   * Return control or wait,
   * for a period amount of milliseconds
   */
  rtos::ThisThread::sleep_for(std::chrono::milliseconds((period / 1000) + 1));
}

void SensorBME280::bme280_spi_init() {
  _spi.format(8, 0);
  _spi.frequency(1000000);

  // pull chip select of BME280 LOW for a short time to configure it for SPI
  _bme280_cs = false;
  rtos::ThisThread::sleep_for(std::chrono::milliseconds(1));
  _bme280_cs = true;
}

int8_t SensorBME280::bme280_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
  int8_t rslt = BME280_OK;
  bme280_handle_t *bme280_handle = (bme280_handle_t *) intf_ptr;

  bme280_handle->bme280_cs->write(0);

  bme280_handle->spi->write(reg_addr);
  for (uint32_t i = 0; i < len; i++) {
    reg_data[i] = bme280_handle->spi->write(0);
  }

  bme280_handle->bme280_cs->write(1);

  return rslt;
}

int8_t SensorBME280::bme280_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {
  int8_t rslt = BME280_OK;
  bme280_handle_t *bme280_handle = (bme280_handle_t *) intf_ptr;

  bme280_handle->bme280_cs->write(0);

  bme280_handle->spi->write(reg_addr);
  for (uint32_t i = 0; i < len; i++) {
    bme280_handle->spi->write(reg_data[i]);
  }

  bme280_handle->bme280_cs->write(1);

  return rslt;
}

int8_t SensorBME280::read_sensor_data(measurement_t *data) {
  int8_t rslt;

  uint32_t req_delay = bme280_cal_meas_delay(&(_dev.settings));
  rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, &_dev);
  if (BME280_OK != rslt) {
    return rslt;
  }
  _dev.delay_us(req_delay * 1000, _dev.intf_ptr);

  data->temperature = 0.0;
  data->pressure = 0.0;
  data->humidity = 0.0;
  rslt = bme280_get_sensor_data(BME280_ALL, data, &_dev);

  return rslt;
}

void SensorBME280::correct_data(measurement_t *data) {
  data->temperature = (data->temperature + Config::get<float>("temp_offset")) * Config::get<float>("temp_factor");
  data->pressure = (data->pressure + Config::get<float>("press_offset")) * Config::get<float>("press_factor");
  data->humidity = (data->humidity + Config::get<float>("hum_offset") * Config::get<float>("hum_factor"));
}

mbed_error_status_t SensorBME280::init() {
  int8_t rslt = BME280_OK;

  _dev.intf_ptr = &_bme280_handle;
  _dev.intf = BME280_SPI_INTF;
  _dev.read = bme280_spi_read;
  _dev.write = bme280_spi_write;
  _dev.delay_us = SensorBME280::bme280_delay_us;

  bme280_spi_init();

  rslt = bme280_init(&_dev);
  if (BME280_OK != rslt) {
    LOG(LVL_ERROR, "Initialization failed! result: %d\n", rslt);
    return MBED_ERROR_INITIALIZATION_FAILED;
  }

  _dev.settings.osr_h = BME280_OVERSAMPLING_16X;
  _dev.settings.osr_p = BME280_OVERSAMPLING_16X;
  _dev.settings.osr_t = BME280_OVERSAMPLING_16X;
  _dev.settings.filter = BME280_FILTER_COEFF_OFF;

  uint8_t settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

  rslt = bme280_set_sensor_settings(settings_sel, &_dev);
  if (BME280_OK != rslt) {
    LOG(LVL_ERROR, "Setting sensor settings failed! result: %d\n", rslt);
    return MBED_ERROR_INITIALIZATION_FAILED;
  }

  return MBED_SUCCESS;
}

mbed_error_status_t SensorBME280::read_measurement(measurement_t *data) {
  bme280_spi_init();
  int8_t rslt = read_sensor_data(data);
  correct_data(data);
  if (BME280_OK != rslt) {
    LOG(LVL_ERROR, "Reading measurement failed! result: %d", rslt);
    return MBED_ERROR_READ_FAILED;
  }
  return MBED_SUCCESS;
}
