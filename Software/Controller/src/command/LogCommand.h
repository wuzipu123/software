
#ifndef CONTROLLER_LOGCOMMAND_H
#define CONTROLLER_LOGCOMMAND_H

#include "Command.h"
#include "Logger.h"
#include "FlashIAP.h"

/**
 * Class handling commands to change the log settings
 */
class LogCommand : virtual public Command {
public:
  /**
   * Create a LogCommand object
   *
   * @param usb_serial reference to an USBSerial object
   * @param flash      reference to a FlashIAP object
   */
  LogCommand(USBSerial &usb_serial, mbed::FlashIAP &flash);

  /**
   * Default destructor
   */
  ~LogCommand() override = default;

  /**
   * Executes the log command according to the given parameters.
   * If \p parameter_string is empty, #_description is printed.
   * Detailed usage information for this command is described in
   * the #log_command_description in constants.h.
   *
   * @param parameter_string parameters as key-value pairs separated by spaces
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t execute(std::string &parameter_string) override;

private:
  /**
   * Referece to the FlashIAP object which handles the low level operations
   * to persistently store the Logger#log_levels in the flash memory if they are changed.
   */
  mbed::FlashIAP &_flash;

  /**
   * Sets the Logger#log_levels according to the given parameters.
   * If Logger#log_levels was changed, the array is written to the
   * flash memory at address \ref STORAGE_ADDR_LOG_LEVELS to store the
   * log level settings persistently.
   *
   * @param parameter_map with parameters as key value pair
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t handle_parameters(std::map<std::string, std::string> &parameter_map);

  /**
   * Prints the current log level settings for every module
   */
  void print_current_log_settings();

  /**
   * Searches in \ref logger_level_names for the given \p log_level_string.
   *
   * @param log_level_string String containing the log level name according to \ref logger_level_names
   * @return the corresponding Logger::Level if \p log_level_string exists in \ref logger_level_names,
   *         #Logger::NUM_LEVELS otherwise
   */
  static Logger::Level get_log_level_from_string(const std::string &log_level_string);

  /**
   * Searches in \ref logger_module_names for the given \p log_module_string.
   *
   * @param log_module_string String containing the log module name according to #logger_module_names
   * @return the corresponding \ref Logger::Module if \p log_level_string exists in #logger_module_names,
   *         #Logger::NUM_MODULES otherwise
   */
  static Logger::Module get_log_module_from_string(const std::string &log_module_string);
};


#endif //CONTROLLER_LOGCOMMAND_H
