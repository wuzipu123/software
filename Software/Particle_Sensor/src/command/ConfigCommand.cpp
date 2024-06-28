
#include "ConfigCommand.h"
#include "Config.h"
#include "defines.h"

ConfigCommand::ConfigCommand(USBSerial &usb_serial, mbed::FlashIAP &flash)
    : Command(config_command_name, config_command_description, usb_serial),
      _flash(flash) {
}

void ConfigCommand::execute_command(std::map<std::string, std::string> &parameter_map,
                                    std::vector<std::string> &parameter_vec) {
  if (parameter_map.empty() && parameter_vec.empty()) {
    print_current_config();
    return;
  }

  if (parameter_map.empty()) {
    Config::entry_t entry;
    for (const auto &param : parameter_vec) {
      if (!Config::get_entry(param, entry)) {
        _usb_serial.printf("Error: Unknown parameter name %s\n", param.c_str());
        return;
      }
      _usb_serial.printf("%s: %s\n", entry.name.c_str(), entry.description.c_str());
    }
  }

  if (!parameter_map.empty() && !parameter_vec.empty()) {
    _usb_serial.printf("Error: Mixing assignment and non-assignment parameters is not allowed\n");
    return;
  }

  handle_parameters(parameter_map);
}

void ConfigCommand::print_current_config() {
  _usb_serial.printf("Current configuration:\n");

  for (const auto &entry : Config::global_config) {
    switch (entry.type) {
      case Config::ConfigType::BOOL:
        _usb_serial.printf("%-22s%s\n", entry.name.c_str(), entry.value.bool_v ? "true" : "false");
        break;
      case Config::ConfigType::UINT32:
        _usb_serial.printf("%-22s%lu\n", entry.name.c_str(), entry.value.uint32_v);
        break;
      case Config::ConfigType::FLOAT:
        _usb_serial.printf("%-22s%f\n", entry.name.c_str(), entry.value.float_v);
        break;
    }
  }
}

void ConfigCommand::handle_parameters(const std::map<std::string, std::string> &parameter_map) {
  for (const auto &pair : parameter_map) {
    if (!Config::set_value(pair.first, pair.second)) {
      _usb_serial.printf("Error: Unknown parameter name %s or invalid value %s\n",
                         pair.first.c_str(), pair.second.c_str());
      return;
    }
  }

  if (MBED_SUCCESS != Config::write_config_to_flash(_flash)) {
    _usb_serial.printf("Error: Failed to write config to flash memory\n");
  }
}

