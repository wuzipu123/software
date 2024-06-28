
#ifndef PARTICLE_SENSOR_MEASURESTATE_H
#define PARTICLE_SENSOR_MEASURESTATE_H

#include "State.h"
#include "SDCard.h"
#include "Communication.h"
#include "SensorSPS30.h"
#include "SensorBME280.h"
#include "LowPowerTicker.h"
#include "EventFlags.h"
#include <vector>

/**
 * State handling the measurement process
 */
class MeasureState : public State {
public:
  /**
   * Create a MeasureState
   *
   * @param led_indicator Reference to the LedIndicator to set the LED behavior
   * @param sd_card       Reference to the SDCard to write the measurement files to
   * @param communication Reference to the Communication object to send measurement data via LoRa
   * @param sps30         Reference to the SensorSPS30
   * @param bme280        Reference to the SensorBME280
   * @param event_flags   Reference to the control event flags to react on occurring control events.
   */
  MeasureState(LedIndicator &led_indicator, SDCard &sd_card, Communication &communication, SensorSPS30 &sps30, SensorBME280 &bme280,
               rtos::EventFlags &event_flags);

  /**
   * Default destructor
   */
  ~MeasureState() override = default;

  /**
   * Start #_measurement_ticker and #_new_file_ticker to signalize when a measurement
   * needs to be done or a new measurement file needs to be created.
   * Init measurement file and the #_sps30_state and clear the #_event_flags.
   * Call run() to execute the measurement process.
   *
   * @return the returned value of run()
   */
  State::Result handle() override;

private:
  /**
   * Create a new measurement file and add the file header to the newly created file.
   *
   * @return MBED_SUCCESS on success, otherwise an mbed_error_status_t
   */
  mbed_error_status_t init_measurement_file();

  /**
   * Set #FLAG_DO_MEASUREMENT in #_event_flags
   */
  void set_do_measurement_flag();

  /**
   * Set #FLAG_CREATE_NEW_FILE in #_event_flags
   */
  void set_create_new_file_flag();

  /**
   * Set #FLAG_SPS30_STARTUP_DONE in #_event_flags
   */
  void set_sps30_startup_done_flag();

  /**
   * Handle the measurement process by reacting on set #_event_flags.\n
   * Depending on the flag, which is set, execute one of the following paths:\n
   * 1) #FLAG_BUTTON_MEASURE: Call set_do_measurement_flag()\n
   * 2) #FLAG_BUTTON_COMMAND: Return with State::Result::COMMAND_PRESSED\n
   * 3) #FLAG_BUTTON_STATUS: Show the program status and battery level with #_led_indicator\n
   * 4) #FLAG_DO_MEASUREMENT: Start SPS30 if it is not already starting or running and set #FLAG_SPS30_STARTUP_DONE
   *                          after a given start up timeout.
   *                          If the SPS30 is already running, set #FLAG_SPS30_STARTUP_DONE immediately.\n
   * 5) #FLAG_SPS30_STARTUP_DONE: Read the measurement data from the BME280 and the SPS30.
   *                              Stop the SPS30 if the next measurement does not start within the next 5 seconds,
   *                              otherwise keep the SPS30 running. Then write the measurement data to the SD card
   *                              and send it via LoRa.\n
   * 6) #FLAG_CREATE_NEW_FILE: Create a new measurment file with init_measurement_file()
   *
   * @return a State::Result depending on the return reason
   */
  State::Result run();

  /**
   * Scale \p sps30_measurement values and \p bme280_measurement values to match the protocol.
   * Send them to the LoRa communication thread, which will send the data to the gateway via LoRa.
   *
   * @param sps30_measurement  Measurement data of the SPS30 sensor
   * @param bme280_measurement Measurement data of the BME280 sensor
   */
  void send_measurement_data(const SensorSPS30::measurement_t &sps30_measurement,
                             const SensorBME280::measurement_t &bme280_measurement);

  /**
   * Store the \p sps30_measurement data and \p bme280_measurement data on the SD card.
   *
   * @param sps30_measurement  Measurement data of the SPS30 sensor
   * @param bme280_measurement Measurement data of the BME280 sensor
   * @return MBED_SUCCESS if write succeeded or SD card logging is turned off,
   *         an mbed_error_status_t otherwise.
   */
  mbed_error_status_t store_measurement_data(const SensorSPS30::measurement_t &sps30_measurement,
                                             const SensorBME280::measurement_t &bme280_measurement);

  /**
   * Retrieve the version and serial number from the SPS30 sensor and store it to #_sps30_info.
   *
   * @return MBED_SUCCESS on success, an mbed_error_status_t otherwise
   */
  mbed_error_status_t get_sps30_info();

  /**
   * Reference to the SDCard to write the measurement files to
   */
  SDCard &_sd_card;

  /**
   * Reference to the Communication handling the LoRa communication.
   */
  Communication &_communication;

  /**
   * Reference to the SensorSPS30 object
   */
  SensorSPS30 &_sps30;

  /**
   * Enum defining the SPS30 states
   */
  enum class SPS30State {
    OFF,
    STARTING,
    RUNNING
  };

  /**
   * Struct used to store the measurement points for
   * the moving average.
   * Overloaded operators are used to calculate the average.
   */
  typedef struct avg_data_s {
    float temp;
    float hum;
    float press;
    float pm2_5;
    float particle_size;

    struct avg_data_s& operator+=(const avg_data_s& rhs) {
      temp += rhs.temp;
      hum += rhs.hum;
      press += rhs.press;
      pm2_5 += rhs.pm2_5;
      particle_size += rhs.particle_size;
      return *this;
    }

    struct avg_data_s& operator/=(const size_t rhs) {
      temp /= rhs;
      hum /= rhs;
      press /= rhs;
      pm2_5 /= rhs;
      particle_size /= rhs;
      return *this;
    }
  } avg_data_t;

  /**
   * The current state of #_sps30
   */
  SPS30State _sps30_state;

  /**
   * Reference to the SensorBME280 object
   */
  SensorBME280 &_bme280;

  /**
   * Reference to the control event flags used to control the measurement process
   */
  rtos::EventFlags &_event_flags;

  /**
   * Timestamp when the currently used measurement file was created
   */
  std::string _data_file_name;

  /**
   * Version and serial numbers of the SPS30
   */
  std::string _sps30_info;

  /**
   * Ticker signalizing when it is time to do a measurement
   */
  mbed::LowPowerTicker _measurement_ticker;

  /**
   * Ticker signalizing when it is time to create a new measurement file
   */
  mbed::LowPowerTicker _new_file_ticker;

  /**
   * Timeout used to wait for the SPS30 to start up
   */
  mbed::LowPowerTimeout _sps30_startup_timeout;

  /**
   * Vector storing the latest SPS30 measurement values for the
   * moving average computation.
   */
  std::vector<SensorSPS30::measurement_t> _sps30_data_buffer;

  /**
   * Vector storing the latest measurement values for the
   * moving average computation.
   */
  std::vector<avg_data_t> _avg_data;
};


#endif //PARTICLE_SENSOR_MEASURESTATE_H
