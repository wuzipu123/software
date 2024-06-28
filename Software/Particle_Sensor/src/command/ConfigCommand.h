
#ifndef PARTICLE_SENSOR_CONFIGCOMMAND_H
#define PARTICLE_SENSOR_CONFIGCOMMAND_H

#include "Command.h"
#include "FlashIAP.h"

/**
 * Class handling commands to change various configuration parameters
 */
class ConfigCommand : virtual public Command {
public:
  /**
   * Create a ConfigCommand object
   *
   * @param usb_serial reference to an USBSerial object
   * @param flash      reference to a FlashIAP object
   */
  ConfigCommand(USBSerial &usb_serial, mbed::FlashIAP &flash);

  /**
   * Default destructor
   */
  ~ConfigCommand() override = default;

private:
  /**
   * Executes the config command according to the given parameters.
   * The usage of the command is described in the ::config_command_description.
   *
   * @param parameter_map map holding the parameters that are given as key-value-pairs
   * @param parameter_vec vector holding the option parameters
   */
  void execute_command(std::map<std::string, std::string> &parameter_map,
                       std::vector<std::string> &parameter_vec) override;

  /**
   * Prints the current configuration
   */
  void print_current_config();

  /**
   * Sets the configuration parameters in #Config::global_config according to the given parameters.
   * The configuration is then written to the flash memory at address \ref STORAGE_ADDR_CONFIG
   * to store the configuration persistently.
   *
   * @param parameter_map Map with parameters as key-value pairs
   */
  void handle_parameters(const std::map<std::string, std::string> &parameter_map);

  /**
   * Referece to the FlashIAP object which handles the low level operations
   * to store the configuration in the flash memory.
   */
  mbed::FlashIAP &_flash;
};


#endif //PARTICLE_SENSOR_CONFIGCOMMAND_H
