
#ifndef PARTICLE_SENSOR_SENSORBME280_H
#define PARTICLE_SENSOR_SENSORBME280_H

#include "bme280.h"
#include "mbed_error.h"
#include "NonCopyable.h"
#include "DigitalOut.h"
#include "SPI.h"

/**
 * Adapter class providing functions to control the Bosch BME280 environmental sensor
 */
class SensorBME280 : private mbed::NonCopyable<SensorBME280> {
public:
  /**
   * Data structure for BME280 measurement data
   */
  typedef struct bme280_data measurement_t;

  /**
   * Creates a SensorBME280 object
   */
  SensorBME280();

  /**
   * Default destructor
   */
  ~SensorBME280() = default;

  /**
   * Initialization function for the BME280 and the SPI bus.
   *
   * @return MBED_SUCCESS if initialization is successful, MBED_ERROR_INITIALIZATION_FAILED otherwise
   */
  mbed_error_status_t init();

  /**
   * Reads measurement data from BME280 and stores it into \p data
   *
   * @param data where the measurement data is stored to
   * @return MBED_SUCCESS if read operation succeeded, MBED_ERROR_READ_FAILED otherwise
   */
  mbed_error_status_t read_measurement(measurement_t *data);

private:
  /**
   * Structure for the handles which are passed to the bme280_spi_* functions
   * to provide access to the #_spi and the #_bme280_cs object.
   */
  typedef struct {
    mbed::DigitalOut *bme280_cs; // Pointer to #_bme280_cs
    mbed::SPI *spi;              // Pointer to #_spi
  } bme280_handle_t;

  /**
   * BME280 SPI chip select output
   */
  mbed::DigitalOut _bme280_cs;

  /**
   * SPI object for the communication with the BME280 sensor
   */
  mbed::SPI _spi;

  /**
   * BME280 device structure for the manufacturer driver
   */
  struct bme280_dev _dev;

  /**
   * Handle for the bme280_spi_* functions
   */
  bme280_handle_t _bme280_handle;

  /**
   * Delay function for the BME280 manufacturer driver
   *
   * @param period   Time to wait in Microseconds
   * @param intf_ptr Pointer to #_bme280_handle (not used in this function)
   */
  static void bme280_delay_us(uint32_t period, void *intf_ptr);

  /**
   * SPI read function for the BME280 manufacturer driver
   *
   * @param reg_addr BME280 register address to read from
   * @param reg_data Buffer where the read data is written to
   * @param len      Number of bytes to read
   * @param intf_ptr Pointer to #_bme280_handle
   * @return always BME280_OK (defined in bme280_defs.h)
   */
  static int8_t bme280_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);

  /**
   * SPI write function for the BME280 manufacturer driver
   *
   * @param reg_addr BME280 register address to write to
   * @param reg_data Data which should be written
   * @param len      Number of bytes to write
   * @param intf_ptr Pointer to #_bme280_handle
   * @return always BME280_OK (defined in bme280_defs.h)
   */
  static int8_t bme280_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);

  /**
   * Initialize the SPI for the BME280
   */
  void bme280_spi_init();

  /**
   * Read temperature, pressure and humidity from the sensor in forced mode.
   *
   * @param data Buffer to write the measured data to
   * @return BME280_OK on success, a negative error code (see bme280_defs.h) otherwise
   */
  int8_t read_sensor_data(measurement_t *data);

  /**
   * Apply a correction offset and factor to the measurement \p data.
   * The correction values are defined in #Config::global_config.
   *
   * @param data the measurement data to be corrected
   */
  void correct_data(measurement_t *data);
};


#endif //PARTICLE_SENSOR_SENSORBME280_H
