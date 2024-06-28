
#ifndef CONTROLLER_MEASURESTATE_H
#define CONTROLLER_MEASURESTATE_H

#include "State.h"
#include "EventFlags.h"
#include "SDCard.h"
#include "Config.h"
#include "Sensor.h"
#include <vector>

/**
 * State handling the measurement process
 */
class MeasureState : public State {
public:
  /**
   * Create a MeasureState
   *
   * @param led_indicator       Reference to the LedIndicator to set the LED behavior
   * @param sd_card             Reference to the SDCard to write the measurement files to
   * @param sensors             Reference to the sensors
   * @param control_event_flags Reference to the control event flags to react on occuring control events.
   * @param config              Reference to the Config to get the set measurement configurations
   */
  MeasureState(LedIndicator &led_indicator, SDCard &sd_card, std::vector<Sensor *> &sensors,
               rtos::EventFlags &control_event_flags, const Config &config);

  /**
   * Default destructor
   */
  ~MeasureState() override = default;

  /**
   * Handle the measurement process:\n
   * 1) Clear all #_control_event_flags (some could be set by a previous state)\n
   * 2) Start measurement tickers for all active sensors\n
   * 3) In an endless loop do:\n
   * ....a) Wait for any control event flag to be set\n
   * ....b) If #CONTROL_FLAG_RESET is set, power off sensors and return\n
   * .......If #CONTROL_FLAG_START_STOP is set, power off sensors and return\n
   * ....c) For every active sensor do:\n
   * ........i) If #CONTROL_FLAG_DO_MEASUREMENT is set for the sensor:\n
   * ...............If sensor is powered off, power on sensor.\n
   * ...............If sensor should alive on and sensor is in measuring state,\n
   * ...............directly set the #CONTROL_FLAG_SENSOR_DATA_READY.\n
   * ........ii) If #CONTROL_FLAG_SENSOR_BOARD_STARTED is set for the sensor:\n
   * ...............Send start measurement command to the sensor\n
   * ........iii) If #CONTROL_FLAG_SENSOR_DATA_READY is set for the sensor:\n
   * ...............If sensor is not in measuring state, continue with next sensor.\n
   * ...............Otherwise read sensor data and store the measured values on the SD card.\n
   * ...............If any sensor error occurs, the sensor error counter is increased.\n
   * ...............If Sensor#error_counter exceeds #SENSOR_MAX_ERRORS, power off sensor and set it as inactive.\n
   * ...............If SD card is full or a SD card error occurred, return.\n
   * ...............If sensor should not stay alive, powered it off.\n
   * ....d) If all sensors are inactive, return.\n
   * ....e) If the currently used measurement files were created more than #FILE_CREATION_INTERVAL_SEC seconds ago,\n
   * .......create new measurement files for all active sensors.\n
   *
   * @return State::Result::RESET_PRESSED if the #CONTROL_FLAG_RESET was set,\n
   *         State::Result::START_STOP_PRESSED if the #CONTROL_FLAG_START_STOP was set,\n
   *         State::Result::SD_CARD_ERROR if a SDCard operation failed,\n
   *         State::Result::SD_CARD_FULL if the SDCard is full,\n
   *         State::Result::SERIAL_ERROR if a SensorBoardSerial write operation failed,\n
   *         State::Result::NO_SENSOR_ACTIVE if all sensors are inactive.
   */
  State::Result handle() override;

private:
  /**
   * Reference to the SDCard to write the measurement files to
   */
  SDCard &_sd_card;

  /**
   * Reference to the sensors
   */
  std::vector<Sensor *> &_sensors;

  /**
   * Reference to the control event flags used to control the measurement process
   */
  rtos::EventFlags &_control_event_flags;

  /**
   * Reference to the Config holding the measurement configurations
   */
  const Config &_config;

  /**
   * Timestamp when the currently used measurement files were create
   */
  time_t _file_creation_time;

  /**
   * Creates a new measurement file for every active sensor and adds
   * the file header to the newly created file.
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t init_measurement_files();

  /**
   * Power off all active sensors and stop the measurement tickers
   */
  void power_off_sensors();

  /**
   * Add a log entry because reading measurement data from sensor board
   * failed #SENSOR_MAX_READ_ATTEMPTS times.
   *
   * @param sensor Sensor that caused the error
   */
  static void log_read_failed(Sensor *sensor);

  /**
   * Add a log entry because of a failed attempt to read measurement data from sensor board.
   *
   * @param sensor  Sensor that caused the error
   * @param attempt Number of failed attempts
   */
  static void log_read_retry(Sensor *sensor, int attempt);

  /**
   * Add a log entry because the error pin is high
   *
   * @param sensor Sensor that caused the error
   */
  static void log_error_pin_high(Sensor *sensor);

  /**
   * Add a log entry because the maximum number of errors is reached
   *
   * @param sensor Sensor that caused the error
   */
  static void log_max_errors_reached(Sensor *sensor);

  /**
   * Combine all control flags for which the controller has to wait for and react to
   *
   * @return The combined control flags
   */
  uint32_t combine_control_flags();

  /**
   * Start the measurement ticker for every active sensor
   */
  void start_measurement_tickers();
};


#endif //CONTROLLER_MEASURESTATE_H
