
#ifndef CONTROLLER_COMMAND_H
#define CONTROLLER_COMMAND_H

#include "USBSerial.h"
#include "mbed_error.h"
#include <string>
#include <vector>
#include <map>

/**
  * Abstract Command base class
  *
  * To add a new Command, create a derived class which implements
  * the method execute(std::string &parameter_string).
  */
class Command {
public:
  /**
   * Basic constructor
   *
   * @param name        Name of the command, should be defined in \ref constants.h
   * @param description Description and usage info for the command, should be defined in \ref constants.h
   * @param serial      Reference to the USBSerial interface object
   */
  Command(std::string name, std::string description, USBSerial &serial);

  /**
   * Virtual destructor
   */
  virtual ~Command() = default;

  /**
   * Executes the appropriate command and needs to be implemented in
   * every derived class. It needs to evaluate and handle the given
   * parameters from the \p parameter_string.
   *
   * @param  parameter_string Command specific parameters
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  virtual mbed_error_status_t execute(std::string &parameter_string) = 0;

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
   * USBSerial object used to read from and write to the USB virtual COM port
   */
  USBSerial &_usb_serial;

  /**
   * Splits an \p input_string at a given \p delimiter and pushes
   * the parts to the vector \p split_strings. Empty parts are not
   * added to \p split_strings.
   *
   * @param input_string  String to be splitted
   * @param split_strings Vector with the splitted parts of \p input_string
   * @param delimiter     Character on which the \p input_string is splitted
   * @return final size of \p split_strings
   */
  static size_t split_string(const std::string &input_string, std::vector<std::string> &split_strings, char delimiter);

  /**
   * Splits an \p input_string at a space using split_string() and then splits
   * every part by a '=' with split_string(). If the second split operation
   * returns exactly two parts, which where delimited by a '=', the two parts are
   * added to the \p output map as key and value pair.
   *
   * For example: An \p input_string "sensor=0,2,3 keep_alive=true"
   *              results in a map with: {{"sensor", "0,2,3"},
   *                                      {"keep_alive", "true"}}
   *
   * @param input_string String with multiple key-value pairs
   * @param output_map   Map with separated key-value pairs extracted from \p input_string
   * @return true if format of \p input_string was correct, else false
   */
  static bool parameter_string_to_map(const std::string &input_string, std::map<std::string, std::string> &output_map);

private:

  /**
   * Command name
   */
  const std::string _name;

  /**
   * Description and usage info for the command
   */
  const std::string _description;
};


#endif // CONTROLLER_COMMAND_H
