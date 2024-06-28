
#ifndef CONTROLLER_CONFIGCOMMAND_H
#define CONTROLLER_CONFIGCOMMAND_H

#include "Command.h"
#include "Config.h"
#include "FlashIAP.h"
#include "mbed_error.h"

/**
 * Class handling commands to change the measurement configuration
 */
class ConfigCommand : virtual public Command {
public:
  /**
   * Create a ConfigCommand object
   *
   * @param usb_serial reference to an USBSerial object
   * @param flash      reference to a FlashIAP object
   * @param config     reference to a Config object
   */
  ConfigCommand(USBSerial &usb_serial, mbed::FlashIAP &flash, Config &config);

  /**
   * Default destructor
   */
  ~ConfigCommand() override = default;

  /**
   * Executes the config command according to the given parameters.
   * If \p parameter_string is empty, #_description is printed.
   * Detailed usage information for this command is described in
   * the #config_command_description in constants.h.
   *
   * @param parameter_string parameters as key-value pairs separated by spaces
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t execute(std::string &parameter_string) override;

private:
  /**
   * Reference to the Config object whose members can be configured
   * through commands.
   */
  Config &_config;

  /**
   * Referece to the FlashIAP object which handles the low level operations
   * to store the #_config in the flash memory if it is changed.
   */
  mbed::FlashIAP &_flash;

  /**
   * C-string constant of parameter name for Config::sensor_config_t::sample_time_sec
   */
  const char *const _sample_time_name = "sample_time";

  /**
   * C-string constant of parameter name for Config::sensor_config_t::keep_alive
   */
  const char *const _keep_alive_name = "keep_alive";

  /**
   * Prints the current configuration
   */
  void print_current_config();

  /**
   * Sets the members of #_config according to the given parameters.
   * If #_config was changed, the #_config object is written to the
   * flash memory at address \ref STORAGE_ADDR_CONFIG to store the
   * configuration persistently.
   *
   * @param parameter_map with parameters as key value pair
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t handle_parameters(const std::map<std::string, std::string> &parameter_map);
};


#endif //CONTROLLER_CONFIGCOMMAND_H
