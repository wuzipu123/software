
#ifndef PARTICLE_SENSOR_INFOCOMMAND_H
#define PARTICLE_SENSOR_INFOCOMMAND_H

#include "Command.h"
#include <string>

/**
 * Class handling commands to print version and UUID information
 * about the sensor system.
 */
class InfoCommand : virtual public Command {
public:
  /**
   * Create a InfoCommand object
   *
   * @param usb_serial reference to an USBSerial object
   */
  explicit InfoCommand(USBSerial &usb_serial);

  /**
   * Default destructor
   */
  ~InfoCommand() override = default;

private:
  /**
   * Executes the info command and prints the versions and UUIDs.
   * The usage of the command is described in the ::info_command_description.
   *
   * @param parameter_map map holding the parameters that are given as key-value-pairs
   * @param parameter_vec vector holding the option parameters
   */
  void execute_command(std::map<std::string, std::string> &parameter_map,
                       std::vector<std::string> &parameter_vec) override;
};

#endif // PARTICLE_SENSOR_INFOCOMMAND_H
