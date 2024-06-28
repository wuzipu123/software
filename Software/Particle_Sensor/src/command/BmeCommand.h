
#ifndef PARTICLE_SENSOR_BMECOMMAND_H
#define PARTICLE_SENSOR_BMECOMMAND_H

#include "Command.h"
#include "SensorBME280.h"

/**
 * Class handling commands to test and control the on-board BME280 sensor
 */
class BmeCommand : virtual public Command {
public:
  /**
   * Create a BmeCommand object
   *
   * @param usb_serial reference to an USBSerial object
   * @param bme280 reference to the SensorBME280 object which should be controlled
   */
  BmeCommand(USBSerial &usb_serial, SensorBME280 &bme280);

  /**
   * Default destructor
   */
  ~BmeCommand() override = default;

private:
  /**
   * Executes the bme command according to the given parameters.
   * The usage of the command is described in the ::bme_command_description.
   *
   * @param parameter_map map holding the parameters that are given as key-value-pairs
   * @param parameter_vec vector holding the option parameters
   */
  void execute_command(std::map<std::string, std::string> &parameter_map,
                       std::vector<std::string> &parameter_vec) override;

  /**
   * Reference to the SensorBME280 object used to control the sensor by calling
   * its member functions.
   */
  SensorBME280 &_bme280;
};


#endif //PARTICLE_SENSOR_BMECOMMAND_H
