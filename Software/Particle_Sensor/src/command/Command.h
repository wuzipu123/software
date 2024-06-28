
#ifndef PARTICLE_SENSOR_COMMAND_H
#define PARTICLE_SENSOR_COMMAND_H

#include "USBSerial.h"
#include <string>
#include <vector>
#include <map>

/**
  * Abstract Command base class
  *
  * To add a new Command, create a derived class which implements
  * the method execute_command().
  */
class Command {
public:
  /**
   * Basic constructor
   *
   * @param name        Name of the command, should be defined in \ref defines.h
   * @param description Description and usage info for the command, should be defined in \ref defines.h
   * @param serial      Reference to the USBSerial interface object
   */
  Command(std::string name, std::string description, USBSerial &serial);

  /**
   * Virtual destructor
   */
  virtual ~Command() = default;

  /**
   * Executes extract_parameters() with the \p parameter_string and then
   * the command specific execute_command() is called with the extracted parameters.
   *
   * @param  parameter_string Command specific parameter string
   */
  void execute(const std::string &parameter_string);

  /**
   * @return reference to _name
   */
  const std::string &get_name() const;

  /**
   * @return reference to _description
   */
  const std::string &get_description() const;

protected:
  /**
   * Reference to the USBSerial object used to read from and write to the USB virtual COM port
   */
  USBSerial &_usb_serial;

  /**
   * Splits an \p input_string at a given \p delimiter and pushes
   * the parts to the vector \p split_strings. Empty parts are not
   * added to \p split_strings.
   *
   * @param input_string  String to be split
   * @param split_strings Vector with the split parts of \p input_string
   * @param delimiter     Character on which the \p input_string is split
   * @return final size of \p split_strings
   */
  static size_t split_string(const std::string &input_string, std::vector<std::string> &split_strings, char delimiter);

  /**
   * Splits the \p input_string into parameters.
   * Parameters are delimited by one or multiple spaces and can be single words,
   * which are stored in the \p parameter_vec.
   * Parameters can be also key-value-pairs (e.g. key=value), which are stored in the \p parameter_map.
   *
   * @param input_string  The string, including the parameters to be extracted.
   * @param parameter_map Map where key-value-pair parameters are stored to.
   * @param parameter_vec Vector where option parameters are stored to.
   * @return false, if \p input_string has an invalid format, true otherwise
   */
  bool extract_parameters(const std::string &input_string, std::map<std::string, std::string> &parameter_map,
                          std::vector<std::string> &parameter_vec);

private:
  virtual void execute_command(std::map<std::string, std::string> &parameter_map,
                               std::vector<std::string> &parameter_vec) = 0;

  /**
   * Command name
   */
  const std::string _name;

  /**
   * Description and usage info for the command
   */
  const std::string _description;
};


#endif // PARTICLE_SENSOR_COMMAND_H
