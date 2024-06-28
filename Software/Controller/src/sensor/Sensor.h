
#ifndef CONTROLLER_SENSOR_H
#define CONTROLLER_SENSOR_H

#include "Protocol.h"
#include "SensorData.h"
#include "SensorBoardSerial.h"
#include "Config.h"
#include "DigitalOut.h"
#include "InterruptIn.h"
#include "DigitalIn.h"
#include "EventFlags.h"
#include "LowPowerTimeout.h"
#include "LowPowerTicker.h"

/**
 * Class providing an interface to control the sensor board and
 * communicate with the sensor board.
 * One Sensor object per sensor slot is needed.
 */
class Sensor : private mbed::NonCopyable<Sensor> {
public:
  /**
   * Enum defining all possible states for the sensor (board)
   */
  enum class State {
    POWER_OFF = 0,         //!< Supply for the sensor board is disabled
    SENSOR_BOARD_STARTING, //!< Sensor board was powered on and starting
    IDLE,                  //!< Sensor board is in idle state
    SENSOR_STARTING,       //!< Measurement was started and sensor is starting up
    MEASURING              //!< Sensor is fully started and in measuring state
  };

  /**
   * Create a Sensor for the sensor board connected to the pins defined in \p io_config.
   *
   * @param io_config           Pin names and slave address of the sensor slot
   * @param sensor_config       Reference to the measurement configuration for the sensor
   * @param serial              Reference to the SensorBoardSerial object
   * @param control_event_flags Reference to the control event flags
   */
  Sensor(io_config_t io_config, Config::sensor_config_t &sensor_config, SensorBoardSerial &serial,
         rtos::EventFlags &control_event_flags);

  /**
   * Destructor deleting the #_protocol from the heap
   */
  virtual ~Sensor();

  /**
   * Power on sensor.
   * Set #_supply_enable to true and set the _state to State::SENSOR_BOARD_STARTING.
   * Attach set_sensor_board_started_flag() to #_sensor_board_start_timeout with a
   * timeout of #SENSOR_BOARD_STARTUP_TIME_MS.
   */
  void power_on();

  /**
   * Power off sensor.
   * Detach functions from LowPowerTimeout objects and disable #_data_ready irq if
   * necessary. #_supply_enable is set to false and _state to State::POWER_OFF
   */
  void power_off();

  /**
   * Init sensor by getting sensor info from sensor board and switch
   * protocol if higher protocol version is supported.
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t init();

  /**
   * Start the measurement and attach set_data_ready_flag() to #_sensor_start_timeout
   * or enable the #_data_ready IRQ if the sensor board supports setting the #_data_ready
   * pin as soon as the sensor is fully started.
   * Set #_state to State::SENSOR_STARTING.
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t start_measurement();

  /**
   * Get measurement data from the sensor board.
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t read_data();

  /**
   * Stop the measurement and set the #_state to State::IDLE
   *
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t stop_measurement();

  /**
   * Start the #_measurement_ticker to periodically call the set_do_measurement_flag() function.
   */
  void start_measurement_ticker();

  /**
   * Detach the callback function from the #_measurement_ticker
   */
  void stop_measurement_ticker();

  /**
   * @return true if sensor should and can stay alive between the measurements, otherwise false
   */
  bool is_keep_alive() const;

  /**
   * Create a new #_file_name including the current date and time.
   *
   * @return reference to the new #_file_name
   */
  std::string const &get_new_file_name();

  /**
   * @return reference to #_file_name
   */
  std::string const &get_file_name();

  /**
   * @return true if #_error pin is high, false otherwise
   */
  bool get_error_state();

  /**
   * @return current #_state
   */
  State get_state() const;

  /** SensorData object holding sensor information and last measured values */
  SensorData data;

  /** Flag if the sensor is active or inactive (not responding or #error_counter too high). */
  bool is_active = false;

  /** Error counter increased by MeasureState on error */
  int error_counter = 0;

private:
  /** Reference to measurement configuration for this sensor */
  Config::sensor_config_t &_sensor_config;

  /** Reference to the SensorBoardSerial object */
  SensorBoardSerial &_serial;

  /** Reference to the control event flags object */
  rtos::EventFlags &_control_event_flags;

  /** Pointer to the currently used communication protocol */
  Protocol *_protocol;

  /** Supply enable digital output (true for power on, false for power off) */
  mbed::DigitalOut _supply_enable;

  /** InterruptIn which is true if data can be read from the sensor board */
  mbed::InterruptIn _data_ready;

  /** Error pin digital input */
  mbed::DigitalIn _error;

  /** Ticker used periodically to signalize that it is time to read new measurement values */
  mbed::LowPowerTicker _measurement_ticker;

  /** Timeout used to signalize that the sensor board is started */
  mbed::LowPowerTimeout _sensor_board_start_timeout;

  /** Timeout used to signalize that the sensor is started */
  mbed::LowPowerTimeout _sensor_start_timeout;

  /** Name of the file containing the measurement data */
  std::string _file_name;

  /** State of the sensor (board) */
  State _state = State::POWER_OFF;

private:
  /**
   * Exchanges the #_protocol with the Protocol matching the given \p protocol_version
   *
   * @param protocol_version Protocol version to switch to
   */
  void switch_to_protocol(const std::string &protocol_version);

  /**
   * Set #_state to State::MEASURING and set the CONTROL_FLAG_SENSOR_DATA_READY() to
   * signalize that new measurement data can be read from the sensor board.
   */
  void set_data_ready_flag();

  /**
   * Set the CONTROL_FLAG_DO_MEASUREMENT() to signalize that it is time to get new
   * measurement values.
   */
  void set_do_measurement_flag();

  /**
   * Set #_state to State::IDLE and set the CONTROL_FLAG_SENSOR_BOARD_STARTED() to
   * signalize that the sensor board is started and the measurement can be started.
   */
  void set_sensor_board_started_flag();
};


#endif //CONTROLLER_SENSOR_H
