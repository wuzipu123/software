#ifndef CONTROLLER_CONSTANTS_H
#define CONTROLLER_CONSTANTS_H

#include "PinNames.h"

//======================================================================================================================
// Version and build date/time
//======================================================================================================================
#define VERSION_MAJOR              0U //!< Major version
#define VERSION_MINOR              5U //!< Minor version
#define VERSION_BUILD              0U //!< Build version

struct version_number_s {
  uint8_t major;
  uint8_t minor;
  uint16_t build;
};

const struct version_number_s version = {VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD};
const char *const build_date = __DATE__;
const char *const build_time = __TIME__;

//======================================================================================================================
// General
//======================================================================================================================

/** @brief Number of sensor slots on the board. Changing this can lead to unwanted side effects. */
#define NUM_SENSOR_SLOTS                                  sizeof(sensor_io_configs) / sizeof(io_config_t) //6U
/** @brief Control flag to signal for sensor at slot \p slave_address that data is ready to be read */
#define CONTROL_FLAG_SENSOR_DATA_READY(slave_address)     (1UL << (slave_address))
/** @brief Control flag to signal for sensor at slot \p slave_address that the time to start a measurement is reached */
#define CONTROL_FLAG_DO_MEASUREMENT(slave_address)        (1UL << ((slave_address) + NUM_SENSOR_SLOTS))
/** @brief Control flag to signal for sensor at slot \p slave_address that the sensor board startup time is over */
#define CONTROL_FLAG_SENSOR_BOARD_STARTED(slave_address)  (1UL << ((slave_address) + (2U * NUM_SENSOR_SLOTS)))
/** @brief Control flag to signal a start or stop button press */
#define CONTROL_FLAG_START_STOP                           (1UL << 30U)
/** @brief Control flag to signal a reset button press */
#define CONTROL_FLAG_RESET                                (1UL << 29U)
/** @brief Control flag to signal a longer button press to format the SD card */
#define CONTROL_FLAG_FORMAT_SD                            (1UL << 28U)
/** @brief Control flag to signal a longer button press to enter or exit the command handling state */
#define CONTROL_FLAG_COMMAND                              (1UL << 27U)
/** @brief Control flag to signal that a new command was received over the USB serial interface */
#define CONTROL_FLAG_RECEIVED_COMMAND                     (1UL << 26U)

/** @brief Flash address where the \ref Config object is stored. Maximum size is FLASH_PAGE_SIZE (2kB). */
#define STORAGE_ADDR_CONFIG                               POST_APPLICATION_ADDR

/** @brief Flash address where the Logger::log_levels are stored. Maximum size is FLASH_PAGE_SIZE (2kB). */
#define STORAGE_ADDR_LOG_LEVELS                           POST_APPLICATION_ADDR + FLASH_PAGE_SIZE

//======================================================================================================================
// Buttons
//======================================================================================================================
/** @brief Minimum time in milliseconds a button must be pressed to signal a short button press */
#define BUTTON_DEBOUNCE_TIME                              200
/** @brief Minimum time in milliseconds the format-SD-button must be pressed to signal a long button press */
#define FORMAT_SD_MIN_BUTTON_PRESS_DURATION               3000
/** @brief Minimum time in milliseconds the command-button must be pressed to signal a long button press */
#define COMMAND_MIN_BUTTON_PRESS_DURATION                 3000


//======================================================================================================================
// Command
//======================================================================================================================
/** @brief Maximum buffer size for the USB serial interface. */
#define COMMAND_HANDLER_MAX_BUF_SIZE                      1024

const char *const time_command_name = "time";
const char *const time_command_description =
    "Usage: time [OPTIONS]\n"
    "Options:\n"
    "    <none>                    Print current time\n"
    "    set YYYY-MM-DD HH:MM:SS   Set time in specified format\n";

const char *const config_command_name = "config";
const char *const config_command_description =
    "Usage: config [OPTIONS]\n"
    "Options:\n"
    "    <none>                        Print current configuration\n"
    "    sensor=<slave address(es)>    Specify sensor or multiple sensors,\n"
    "                                  if comma separated list of addresses is given (e.g. sensor=2,4,1)\n"
    "    keep_alive=<true|false>       Set keep alive. Possible values are true and false\n"
    "    sample_time=<seconds>         Set sample time in seconds (integer)";

const char *const log_command_name = "log";
const char *const log_command_description =
    "Usage: log [OPTIONS]\n"
    "Options:\n"
    "    <none>                      Print current log settings\n"
    "    global=<log level>          Set log level globally for all modules (e.g. global=INFO)\n"
    "    <log module>=<log level>    Set log level for specified module (e.g. Sensor=INFO)\n";

//======================================================================================================================
// Logger
//======================================================================================================================
/** @brief Maximum number of characters a log level name in #logger_module_names can have */
#define LOG_LEVEL_NAME_MAX_SIZE   5
/** @brief Maximum number of characters a log module name in #logger_module_names can have */
#define LOG_MODULE_NAME_MAX_SIZE  8

/**
 * Names of the supported log levels.
 * The order of the names must be the same as in the #Logger::Level enum.
 */
const char *const logger_level_names[] = {
    "SUPPR",
    "ERROR",
    "INFO",
    "DEBUG"
};

/**
 * Names of the log modules.
 * The order of the names must be the same as in the #Logger::Module enum.
 */
const constexpr char *const logger_module_names[] = {
    "Logger",
    "Main",
    "SDCard",
    "Command",
    "TimeCmd",
    "ConfCmd",
    "LogCmd",
    "CmdHandl",
    "Sensor",
    "SBSerial",
    "Protocol",
    "JsonProt",
    "BinProt",
    "SensData",
    "CheckSt",
    "InitSt",
    "IdleSt",
    "FormatSt",
    "CmdSt",
    "MeasSt",
    "SDErrSt",
    "ShutdoSt"
};

//======================================================================================================================
// SensorBoardSerial
//======================================================================================================================
/** @brief Sensor serial bus receive buffer size */
#define SENSOR_SERIAL_RXBUF_SIZE              1500
/** @brief Sensor serial bus transmit buffer size */
#define SENSOR_SERIAL_TXBUF_SIZE              1024
/** @brief Minimum timeout in milliseconds between the transmission of two consecutive sensor commands
 *  to ensure that the sensor boards receive every command. */
#define SENSOR_SERIAL_INTER_CMD_TIMEOUT_MS    100 // Minimum timeout between two sensor commands

//======================================================================================================================
// Sensor
//======================================================================================================================
/** @brief Maximum number of consecutive failed measurements until a sensor is marked as inactive */
#define SENSOR_MAX_ERRORS                     3
/** @brief Maximum number of attempts to read sensor data until sensor error counter is increased */
#define SENSOR_MAX_READ_ATTEMPTS              3
/** @brief Default measurement interval in seconds for #Config::sensor_config_s::sample_time_sec */
#define DEFAULT_SAMPLE_TIME_SEC               600
/** @brief Default setting for #Config::sensor_config_s::keep_alive */
#define DEFAULT_KEEP_ALIVE                    false
/** @brief Time in milliseconds to wait between powering on the sensor board and sending the first command to it. */
#define SENSOR_BOARD_STARTUP_TIME_MS          3000

struct io_config_s {
  uint8_t address;           //!< slave address of the sensor slot (0 to #NUM_SENSOR_SLOTS - 1)
  PinName supply_enable_pin; //!< Pin name for the supply enable pin
  PinName error_pin;         //!< Pin name for the error pin
  PinName data_ready_pin;    //!< Pin name for the data ready pin
};
/** @brief Struct to define the pin names for one sensor slot */
typedef struct io_config_s io_config_t;

/** @brief Array defining the pin names for all sensor slots */
const io_config_t sensor_io_configs[] = MBED_CONF_APP_SENSOR_BOARD_IO_MAPPING;

//======================================================================================================================
// MeasureState
//======================================================================================================================
/** @brief Time in seconds after which a new measurement data file is created. */
#define FILE_CREATION_INTERVAL_SEC (24 * 60 * 60)

#endif //CONTROLLER_CONSTANTS_H
