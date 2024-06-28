
#ifndef CONTROLLER_TIMECOMMAND_H
#define CONTROLLER_TIMECOMMAND_H

#include "Command.h"
#include "mbed_error.h"
#include <string>

/**
 * Class handling commands to change and print the time and date
 */
class TimeCommand : virtual public Command {
public:
  /**
   * Create a TimeCommand object
   *
   * @param usb_serial reference to an USBSerial object
   */
  explicit TimeCommand(USBSerial &usb_serial);

  /**
   * Default destructor
   */
  ~TimeCommand() override = default;

  /**
   * Executes the time command according to the given parameters.
   * If \p parameter_string is empty, the current date and time are printed.
   * Detailed usage information for this command is described in
   * the #time_command_description in constants.h.
   *
   * @param parameter_string string with the parameters separated by spaces
   * @return MBED_SUCCESS on success, otherwise an mbed error status constructed with
   *         MBED_MAKE_ERROR(_mbed_module_type, _mbed_error_code) from mbed_error.h
   */
  mbed_error_status_t execute(std::string &parameter_string) override;

private:
  /**
   * Parses the date and time string into a struct tm
   * and returns the corresponding time_t.
   *
   * @param parameters vector with two strings, date and time
   * @return timestamp of the parsed time as time_t
   */
  static time_t parse_datetime(const std::vector<std::string> &parameters);
};

#endif // CONTROLLER_TIMECOMMAND_H
