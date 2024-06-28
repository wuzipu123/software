
#ifndef PARTICLE_SENSOR_LOGGER_H
#define PARTICLE_SENSOR_LOGGER_H

#include "SDCard.h"
#include "defines.h"
#include "Config.h"
#include <string>
#include <array>
#include <map>
#include <cstring>

/**
 * Macro to extract filename without file extension and path from __FILE__
 */
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/**
 * Macro to create a log entry.
 * The filename, where the log entry is created is added automatically.
 */
#define LOG(lvl, fmt, args...) \
        Logger::log_internal(__FILENAME__, lvl, fmt, ## args)

/**
 * Class providing logging functionality.
 * This class does not need to and can not be instantiated,
 * because all members and member functions are static and the constructor is private.
 * Instead it is necessary to initialize the Logger once with init()
 */
class Logger {
public:
  /**
   * Initialize the Logger. Create a new log file on the SD card.
   *
   * @param sd_card Pointer to the SD card object
   */
  static void init(SDCard *sd_card);

  /**
   * Add a log line to the log file if given \p log_level is lower than the one
   * in the #Config::global_config.
   *
   * @param file_name     File name where the function is called from
   * @param log_level     Log level
   * @param format_string Format string for sprintf()
   * @param ...           Argument list for sprintf()
   */
  static void log_internal(const char *file_name, LogLevel log_level, const char *format_string, ...);

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

  /** File name of the currently used log file */
  static std::string _file_name;

  /**
   * Composes a log entry out of the \p file_name, the \p log_level name and
   * the log \p message and writes it to \p log_line.
   *
   * @param log_line  The destination where the composed log line is written to
   * @param file_name The file name where the #LOG was called from
   * @param log_level The log level
   * @param message   The message to be logged
   */
  static void compose_log_line(std::string &log_line, const char *file_name, LogLevel log_level, const std::string
  &message);
};


#endif //PARTICLE_SENSOR_LOGGER_H
