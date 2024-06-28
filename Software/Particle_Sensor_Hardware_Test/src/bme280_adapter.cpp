#include "bme280_defs.h"
#include "SPI.h"
#include "DigitalOut.h"
#include "ThisThread.h"
#include "bme280_adapter.h"
#include "bme280.h"
#include "ns_cmdline.h"

mbed::DigitalOut bme280_cs(MBED_CONF_APP_BME280_CHIP_SELECT, true);
mbed::SPI spi(MBED_CONF_APP_SPI_MOSI, MBED_CONF_APP_SPI_MISO, MBED_CONF_APP_SPI_CLK);

void user_delay_us(uint32_t period, void *intf_ptr)
{
  /*
   * Return control or wait,
   * for a period amount of milliseconds
   */
  rtos::ThisThread::sleep_for(std::chrono::milliseconds((period / 1000) + 1));
}

void user_spi_init() {
  spi.format(8, 0);
  spi.frequency(1000000);

  // pull chip select of BME280 LOW for a short time to configure it for SPI
  bme280_cs = false;
  rtos::ThisThread::sleep_for(std::chrono::milliseconds(1));
  bme280_cs = true;
}

int8_t user_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
  int8_t rslt = 0;

  bme280_cs = 0;

  spi.write(reg_addr);
  for (uint32_t i = 0; i < len; i++) {
    reg_data[i] = spi.write(0);
  }

  bme280_cs = 1;

  return rslt;
}

int8_t user_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
  int8_t rslt = 0;

  bme280_cs = 0;

  spi.write(reg_addr);
  for (uint32_t i = 0; i < len; i++) {
    spi.write(reg_data[i]);
  }

  bme280_cs = 1;

  return rslt;
}


void print_sensor_data(struct bme280_data *comp_data)
{
#ifdef BME280_FLOAT_ENABLE
  cmd_printf("%0.2f, %0.2f, %0.2f\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#else
  cmd_printf("%ld, %ld, %ld\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#endif
}

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev, uint32_t num_measurements)
{
	int8_t rslt;
	uint8_t settings_sel;
	struct bme280_data comp_data;

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	cmd_printf("Temperature, Pressure, Humidity\r\n");
	for (uint32_t i = 0; i < num_measurements; i++) {
		/* Delay while the sensor completes a measurement */
		dev->delay_us(1000000, dev->intf_ptr);
		rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		print_sensor_data(&comp_data);
	}

	return rslt;
}
