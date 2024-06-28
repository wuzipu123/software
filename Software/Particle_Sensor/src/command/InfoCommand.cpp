
#include "InfoCommand.h"
#include "Protocol.h"
#include "defines.h"
#include "utils.h"

InfoCommand::InfoCommand(USBSerial &usb_serial)
    : Command(info_command_name, info_command_description, usb_serial) {
}

void InfoCommand::execute_command(std::map<std::string, std::string> &parameter_map,
                                  std::vector<std::string> &parameter_vec) {
  if (parameter_vec.empty() && parameter_map.empty()) {
    _usb_serial.printf("Software version: %s\n", utils::app_version().c_str());
    _usb_serial.printf("Software UUID: 0x%08lx\n", Protocol::get_sw_uuid());
    _usb_serial.printf("Hardware UUID: 0x%08lx\n", Protocol::get_hw_uuid());
  } else {
    _usb_serial.printf("Error: This command does not support any parameters\n");
  }
}