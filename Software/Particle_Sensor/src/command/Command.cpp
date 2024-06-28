
#include "Command.h"

Command::Command(std::string name, std::string description, USBSerial &serial)
    : _usb_serial(serial),
      _name(std::move(name)),
      _description(std::move(description)) {
}

const std::string &Command::get_name() const {
  return _name;
}

const std::string &Command::get_description() const {
  return _description;
}

size_t Command::split_string(const std::string &input_string, std::vector<std::string> &split_strings, char delimiter) {
  size_t part_begin = 0;
  size_t part_end = input_string.find_first_of(delimiter);
  std::string part;

  while (part_end != std::string::npos) {
    part = input_string.substr(part_begin, part_end - part_begin);
    if (!part.empty()) {
      split_strings.push_back(part);
    }
    part_begin = part_end + 1;

    part_end = input_string.find_first_of(delimiter, part_begin);
  }

  part = input_string.substr(part_begin, std::min(part_end, input_string.size()) - part_begin + 1);
  if (!part.empty()) {
    split_strings.push_back(part);
  }

  return split_strings.size();
}

void Command::execute(const std::string &parameter_string) {
  std::map<std::string, std::string> parameter_map;
  std::vector<std::string> parameter_vec;
  if (!extract_parameters(parameter_string, parameter_map, parameter_vec)) {
    _usb_serial.printf("Error: Wrong parameter format\n");
    return;
  }
  execute_command(parameter_map, parameter_vec);
}

bool Command::extract_parameters(const std::string &input_string, std::map<std::string, std::string> &parameter_map,
                                 std::vector<std::string> &parameter_vec) {
  std::vector<std::string> parameters;
  split_string(input_string, parameters, ' ');

  for (const auto &parameter : parameters) {
    std::vector<std::string> parameter_pair;
    int num_parts = split_string(parameter, parameter_pair, '=');
    if (num_parts == 2) {
      parameter_map[parameter_pair[0]] = parameter_pair[1];
    } else if (num_parts == 1) {
      parameter_vec.push_back(parameter_pair[0]);
    } else {
      return false;
    }
  }

  return true;
}
