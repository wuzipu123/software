
#ifndef PARTICLE_SENSOR_TIMECOMMAND_H
#define PARTICLE_SENSOR_TIMECOMMAND_H

#include "Command.h"

/**
 * Class handling commands to set, print and calibrate the time and date
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

private:
  /**
   * Parses the date and time string into a struct tm
   * and returns the corresponding time_t.
   *
   * @param parameters vector with two strings, date and time
   * @return timestamp of the parsed time as time_t
   */
  static time_t parse_datetime(const std::vector<std::string> &parameters);

  /**
   * Executes the time command according to the given parameters.
   * The usage of the command is described in the ::time_command_description.
   *
   * @param parameter_map map holding the parameters that are given as key-value-pairs
   * @param parameter_vec vector holding the option parameters
   */
  void execute_command(std::map<std::string, std::string> &parameter_map,
                       std::vector<std::string> &parameter_vec) override;

  /**
   * Emits a 1Hz clock over #_usb_serial by printing the number of passed seconds
   * every second. It uses wait_for_second_toggle() to wait until the RTC second
   * counter changes. This function is executed in a separate highest priority thread
   * to maximize the timing accuracy.
   */
  void calibrate();

  /**
   * Repeatedly polls the current RTC time until the RTC time is incremented, which
   * happens every second.
   */
  void wait_for_second_toggle();

  /**
   * The calibration time in seconds that indicates how long calibrate() will be executed.
   */
  uint32_t _cal_time_sec = 30;
};

#endif // PARTICLE_SENSOR_TIMECOMMAND_H
