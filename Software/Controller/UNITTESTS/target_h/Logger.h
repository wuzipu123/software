

#ifndef CONTROLLER_LOGGER_H
#define CONTROLLER_LOGGER_H

#include <string>

class Logger {
public:
  enum Module {
    LOGGER = 0,
    MAIN,
    SD_CARD,
    COMMAND,
    SENSOR,
    SENSOR_SERIAL,
    PROTOCOL,
    BIN_PROTOCOL,
    JSON_PROTOCOL,
    SENSOR_DATA,
    CHECK_SENSOR_STATE,
    NUM_MODULES
  };

  enum Level {
    SUPPRESS = 0,
    ERROR,
    INFO,
    DEBUG,
    NUM_LEVELS
  };

  static void log(Logger::Module module, Logger::Level level, const std::string &message);
};


#endif //CONTROLLER_LOGGER_H
