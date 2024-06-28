#include "CommandHandler.h"
#include "TimeCommand.h"
#include "ConfigCommand.h"
#include "InfoCommand.h"
#include "SpsCommand.h"
#include "BmeCommand.h"
#include "ThisThread.h"
#include "Logger.h"

using namespace std;

CommandHandler::CommandHandler(USBSerial &usb_serial, mbed::FlashIAP &flash, SensorSPS30 &sps30, SensorBME280 &bme280,
                               rtos::EventFlags &event_flags)
    : _usb_serial(usb_serial),
      _event_flags(event_flags) {
  _commands.push_back(new TimeCommand(_usb_serial));
  _commands.push_back(new ConfigCommand(_usb_serial, flash));
  _commands.push_back(new SpsCommand(_usb_serial, sps30));
  _commands.push_back(new BmeCommand(_usb_serial, bme280));
  _commands.push_back(new InfoCommand(_usb_serial));
  _usb_serial.attach(this, &CommandHandler::serial_interrupt_handler);
  _usb_serial.deinit(); // to allow deep sleep
}

CommandHandler::~CommandHandler() {
  for (auto command : _commands) {
    delete command;
  }
  _commands.clear();
}

bool CommandHandler::connect() {
  _usb_serial.connect();
  if (_usb_serial.connected()) {
    _buffer.reset();
    _usb_serial.printf("SensMat Particle Sensor v%d.%d.%d\n", version.major, version.minor, version.build);

    print_prompt();
    LOG(LVL_DEBUG, "USB serial connected");
    return true;
  }
  return false;
}

void CommandHandler::disconnect() {
  _usb_serial.printf("\nSensMat Particle Sensor disconnected!\n");
  rtos::ThisThread::sleep_for(10ms); // Wait until disconnect message is sent
  _usb_serial.endpoint_remove_all();
  _usb_serial.disconnect();
  _usb_serial.deinit();
  LOG(LVL_DEBUG, "USB serial disconnected");
}

void CommandHandler::read_line_from_buffer(std::string &line) {
  char c;
  while (_buffer.pop(c)) {
    if (c == '\n') {
      break;
    }
    line.push_back(c);
  }
}

void CommandHandler::print_help() {
  _usb_serial.printf("The following commands are supported:\n");
  for (auto command : _commands) {
    _usb_serial.printf("%s\n", command->get_name().c_str());
  }
  _usb_serial.printf("For more information type:?> help <command>\n");
}

void CommandHandler::print_prompt() {
  _usb_serial.printf("?> ");
}

void CommandHandler::serial_interrupt_handler() {
  while (_usb_serial.available()) {
    char c = _usb_serial._getc();
    if (c != '\r') {
      if (!_buffer.full()) {
        _buffer.push(c);
      }
    }
    if (c == '\n') {
      _event_flags.set(FLAG_RECEIVED_COMMAND);
    }
  }
}

void CommandHandler::handle_usb_serial_command() {
  std::string command_string;
  read_line_from_buffer(command_string);
  _usb_serial.printf("%s\n", command_string.c_str());

  LOG(LVL_DEBUG, "Received command: %s", command_string.c_str());

  std::string command_name;
  std::string parameters;
  separate_command_name(command_string, command_name, parameters);

  Command *command = find_command(command_name);
  if (command != nullptr) {
    command->execute(parameters);
  } else if (command_name == "help") {
    command = find_command(parameters);
    if (command != nullptr) {
      _usb_serial.printf("%s\n", command->get_description().c_str());
    } else
      print_help();
  } else {
    print_help();
  }

  print_prompt();
}

Command *CommandHandler::find_command(const std::string &command_name) {
  for (auto command : _commands) {
    if (command->get_name() == command_name) {
      return command;
    }
  }
  return nullptr;
}

void CommandHandler::separate_command_name(const std::string &command_string, std::string &command_name,
                                           std::string &parameters) {
  size_t command_name_end = command_string.find_first_of(' ');

  if (command_name_end == std::string::npos) {
    command_name = command_string;
    parameters = "";
  } else {
    command_name = command_string.substr(0, command_name_end);
    parameters = command_string.substr(command_name_end + 1, command_string.size() - command_name_end - 1);
  }
}
