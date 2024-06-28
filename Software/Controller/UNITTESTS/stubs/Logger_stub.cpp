

#include "Logger.h"

void Logger::log(Logger::Module module, Logger::Level level, const std::string &message) {
  printf("Log: %s\n", message.c_str()); //TODO: Delete, prints log messages to stdout for debugging
}