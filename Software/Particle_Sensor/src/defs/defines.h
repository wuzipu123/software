
#ifndef PARTICLE_SENSOR_DEFINES_H
#define PARTICLE_SENSOR_DEFINES_H

#include <cstdint>

//======================================================================================================================
// Version number
//======================================================================================================================
#define VERSION_MAJOR              0U //!< Major version
#define VERSION_MINOR              4U //!< Minor version
#define VERSION_BUILD              3U //!< Build version

struct version_number_s {
  uint8_t major;
  uint8_t minor;
  uint16_t build;
};

const struct version_number_s version = {VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD};

//======================================================================================================================
// Control Event Flags
//======================================================================================================================
#define FLAG_BUTTON_MEASURE      (1U << 1U)
#define FLAG_BUTTON_STATUS       (1U << 2U)
#define FLAG_BUTTON_COMMAND      (1U << 3U)

#define FLAG_RECEIVED_COMMAND    (1U << 4U)

#define FLAG_DO_MEASUREMENT      (1U << 5U)
#define FLAG_SPS30_STARTUP_DONE  (1U << 6U)
#define FLAG_CREATE_NEW_FILE     (1U << 7U)

//======================================================================================================================
// Flash Memory
//======================================================================================================================
/** @brief Flash address where the values of the \ref Config::global_config
 * are stored. Maximum size is FLASH_PAGE_SIZE (2kB). */
#define STORAGE_ADDR_CONFIG                               POST_APPLICATION_ADDR

//======================================================================================================================
// Buttons
//======================================================================================================================
/** @brief Minimum time in milliseconds a button must be pressed to signal a short button press */
#define BUTTON_DEBOUNCE_TIME                              50
/** @brief Minimum time in milliseconds the command-button must be pressed to signal a long button press */
#define BUTTON_COMMAND_MIN_PRESS_TIME                     3000

//======================================================================================================================
// Command
//======================================================================================================================
/** @brief Maximum buffer size for the USB serial interface. */
#define COMMAND_HANDLER_MAX_BUF_SIZE                      1024

const char *const time_command_name = "time";
const char *const time_command_description =
    "Usage: time [OPTIONS]\n"
    "Options:\n"
    "\t<none>\t\t\t\tPrint current time\n"
    "\tset YYYY-MM-DD HH:MM:SS\t\tSet time in specified format\n"
    "\ttick <num_ticks>\t\tPrint for <num_ticks> seconds every time, the RTC second counter toggles,\n"
    "\t\t\t\t\tthe amount of passed seconds. Used to measure RTC time drift.\n"
    "\tcalibrate <milliseconds>\tCalibrate the RTC by sending the time drift per day in milliseconds\n";

const char *const config_command_name = "config";
const char *const config_command_description =
    "Usage: config [OPTIONS]\n"
    "Options:\n"
    "\t<none>\t\t\tPrint current configuration\n"
    "\t<name>=<value>\t\tSet the configuration parameter <name> to the given <value>.\n"
    "\t\t\t\tMultiple parameters can be set in one command by seperating key-value-pairs with spaces.\n";

const char *const sps_command_name = "sps";
const char *const sps_command_description =
    "Usage: sps COMMAND\n"
    "Commands:\n"
    "\ton\t\tEnable SPS30 power supply\n"
    "\toff\t\tDisable SPS30 power supply\n"
    "\tprobe\t\tPerform probe, to check if SPS30 is responding\n"
    "\tserial\t\tPrint serial number\n"
    "\tversion\t\tPrint version numbers for firmware, SHDLC and hardware\n"
    "\tstart\t\tStart measurement procedure\n"
    "\tstop\t\tStop measurement procedure\n"
    "\tread\t\tRead measurement values from sensor\n"
    "\tclean\t\tStart fan cleaning (only works after \"sps start\")\n";

const char *const bme_command_name = "bme";
const char *const bme_command_description =
    "Usage: bme COMMAND\n"
    "Commands:\n"
    "\tinit\tInitialize BME280\n"
    "\tread\tRead measurement values from sensor (Make sure init is called in advance)\n";

const char *const info_command_name = "info";
const char *const info_command_description =
    "Usage: info\n"
    "Print software version and UUIDs\n";

//======================================================================================================================
// Logging
//======================================================================================================================
/**
 * Enum defining the supported log levels.
 */
enum LogLevel {
  LVL_SUPPRESS = 0,
  LVL_ERROR,
  LVL_INFO,
  LVL_DEBUG,
  NUM_LOG_LEVELS
};

/**
 * Names of the supported log levels.
 * The order of the names must be the same as in the #LogLevel enum from above.
 */
const char *const log_level_names[] = {
    "SUPPR",
    "ERROR",
    "INFO ",
    "DEBUG"
};

//======================================================================================================================
// Communication
//======================================================================================================================
/** @brief Time to wait before authentication request is sent again after a wrong response was received. **/
#define LORA_RESEND_WAIT_MS             10000
/** @brief Maximum time to wait for a response after sending a request or data to the gateway **/
#define LORA_RX_TIMEOUT_MS              5000
/** @brief Maximum number of attempts to send a data packet until a new authentication message is sent. **/
#define MAX_SEND_DATA_ATTEMPTS          3
/** @brief Event flag which is set as soon as transmission is done. **/
#define FLAG_LORA_TX_DONE               (1U << 0U)
/** @brief Event flag which is set as soon as a message is received. **/
#define FLAG_LORA_RX_DONE               (1U << 1U)
/** @brief Event flag which is set if a receive timeout occurred. **/
#define FLAG_LORA_RX_TIMEOUT            (1U << 2U)

//======================================================================================================================
// BME280
//======================================================================================================================
#define BME280_TEST_STARTUP_TIME_MS 1000

//======================================================================================================================
// Measurement
//======================================================================================================================
/** @brief Interval at which a new data file is created (24 hours) **/
#define DATA_FILE_CREATION_PERIOD_SEC 86400

#endif //PARTICLE_SENSOR_DEFINES_H
