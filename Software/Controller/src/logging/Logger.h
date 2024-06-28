
#include "SDCard.h"
#include <string>
#include <array>
#include <map>

#ifndef CONTROLLER_LOGGER_H
#define CONTROLLER_LOGGER_H

/**
 * Class providing logging functionality.
 * This class does not need to and can not be instantiated,
 * because all members and member functions are static and the constructor is private.
 * Instead it is necessary to initialize the Logger once with init()
 */
class Logger {
public:
  /**
   * Enum defining the log modules.
   * #NUM_MODULES is needed to know the number of log modules.
   * The order of the log modules must be the same as in #logger_module_names
   */
  enum Module {
    LOGGER = 0,
    MAIN,
    SD_CARD,
    COMMAND,
    TIME_COMMAND,
    CONFIG_COMMAND,
    LOG_COMMAND,
    COMMAND_HANDLER,
    SENSOR,
    SENSOR_BOARD_SERIAL,
    PROTOCOL,
    JSON_PROTOCOL,
    BIN_PROTOCOL,
    SENSOR_DATA,
    CHECK_SENSOR_STATE,
    INIT_STATE,
    IDLE_STATE,
    FORMAT_SD_STATE,
    COMMAND_STATE,
    MEASURE_STATE,
    SD_ERROR_STATE,
    SHUTDOWN_STATE,
    NUM_MODULES
  };

  /**
   * Enum defining the supported log levels.
   * #NUM_LEVELS is needed to know the number of log levels.
   * The order of the log levels must be the same as in #logger_level_names
   */
  enum Level {
    SUPPRESS = 0,
    ERROR,
    INFO,
    DEBUG,
    NUM_LEVELS
  };

  /**
   * Initialize the Logger.
   * Create a new log file on the SD card and set all log levels to #DEBUG
   *
   * @param sd_card Pointer to the SD card object
   */
  static void init(SDCard *sd_card);

  /**
   * Add a log line to the log file if given log \p level is lower than the one
   * in #log_levels for the given log \p module.
   *
   * @param module  Log module, where the log function was called from
   * @param level   Log level
   * @param message Log message to write
   */
  static void log(Module module, Level level, const std::string &message);

  /**
   * Returns the current log level for the given module
   *
   * @param module Log Module for which the log Level is searched
   * @return the current log Level for \p module set in #log_levels
   */
  static Level get_level_by_module(Module module);

  /**
   * Set the log level in #log_levels for the specified \p module to \p level
   *
   * @param module The module for which the log level should be set
   * @param level  The new log level
   */
  static void set_level(Module module, Level level);

  /**
   * Set the log level for all modules in #log_levels to the given \p level
   *
   * @param level The new log level
   */
  static void set_level_global(Level level);

  /**
   * Array storing the set log levels for every log module
   */
  static Level log_levels[Module::NUM_MODULES];

private:
  /** Private constructor */
  Logger() = default;

  /** Private destructor */
  ~Logger() = default;

  /** Private copy constructor */
  Logger(const Logger &);

  /** Private assignment operator */
  Logger &operator=(const Logger &);

  /**
   * Flag to keep track if the Logger is already initialized or not.
   * Is set to true in the init() function
   */
  static bool _initialized;

  /** Pointer to the SD card object */
  static SDCard *_sd_card;

  /** File name for the current log file */
  static std::string _file_name;

  /**
   * Adds \p padding_char to a given string \p str until it is \p num characters long
   *
   * @param str          The string to pad
   * @param num          The wanted string length
   * @param padding_char The character to pad the string with
   */
  static void pad_string_to(std::string &str, size_t num, char padding_char = ' ');

  /**
   * Composes a log entry out of the log \p module name, the log \p level name and
   * the log \p message and writes it to \p log_line.
   *
   * @param log_line The destination where the composed log line is written to
   * @param module   The log module
   * @param level    The log level
   * @param message  The log message
   */
  static void compose_log_line(std::string &log_line, Module module, Level level, const std::string &message);
};


#endif //CONTROLLER_LOGGER_H
