
#ifndef PARTICLE_SENSOR_SPSCOMMAND_H
#define PARTICLE_SENSOR_SPSCOMMAND_H

#include "Command.h"
#include "SensorSPS30.h"

/**
 * Class handling commands to test and control the SPS30 sensor
 * connected via UART serial interface
 */
class SpsCommand : virtual public Command {
public:
  /**
   * Create a SpsCommand object
   *
   * @param usb_serial reference to an USBSerial object
   * @param sps30 reference to the SensorSPS30 object which should be controlled
   */
  SpsCommand(USBSerial &usb_serial, SensorSPS30 &sps30);

  /**
   * Default destructor
   */
  ~SpsCommand() override = default;

private:
  /**
   * Executes the sps command according to the given parameters.
   * The usage of the command is described in the ::sps_command_description.
   *
   * @param parameter_map map holding the parameters that are given as key-value-pairs
   * @param parameter_vec vector holding the option parameters
   */
  void execute_command(std::map<std::string, std::string> &parameter_map,
                       std::vector<std::string> &parameter_vec) override;

  /**
   * Reference to the SensorSPS30 object used to control the sensor by calling
   * its member functions.
   */
  SensorSPS30 &_sps30;
};


#endif //PARTICLE_SENSOR_SPSCOMMAND_H
