#include "CommandHandler.h"
#include "TimeCommand.h"
#include "ConfigCommand.h"
#include "LogCommand.h"
#include "Config.h"
#include "FlashIAP.h"
#include <algorithm>
#include "PeripheralPins.h"

/**
 * Pin configuration for the USB serial interface.
 * Overwrites the weak configuration from PeripheralPins.c
 * to set USB_OTG_FS_VBUS, USB_OTG_FS_ID as not connected,
 * because the pins PA_9 and PA_10 are used for other peripherals
 */
const PinMap PinMap_USB_FS[] = {
    {NC,      USB_FS, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, GPIO_AF_NONE)}, // USB_OTG_FS_VBUS
    {NC,     USB_FS, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_PULLUP, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_ID
    {PA_11,     USB_FS, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_DM
    {PA_12,     USB_FS, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_DP
    {NC, NC, 0}
};

CommandHandler::CommandHandler(USBSerial &usb_serial, mbed::FlashIAP &flash, Config &config,
                               rtos::EventFlags &control_event_flags)
    : _usb_serial(usb_serial),
      _control_event_flags(control_event_flags) {
  _commands.push_back(new TimeCommand(_usb_serial));
  _commands.push_back(new ConfigCommand(_usb_serial, flash, config));
  _commands.push_back(new LogCommand(_usb_serial, flash));
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
    _usb_serial.printf("Controller software version %d.%d.%d\n", version.major, version.minor, version.build);
    print_prompt();
    Logger::log(Logger::Module::COMMAND_HANDLER, Logger::Level::DEBUG, "USB serial connected");
    return true;
  }
  return false;
}

void CommandHandler::disconnect() {
  _usb_serial.printf("\nController disconnected!\n");
  _usb_serial.endpoint_remove_all();
  _usb_serial.disconnect();
  _usb_serial.deinit();
  Logger::log(Logger::Module::COMMAND_HANDLER, Logger::Level::DEBUG, "USB serial disconnected");
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
      _control_event_flags.set(CONTROL_FLAG_RECEIVED_COMMAND);
    }
  }
}

void CommandHandler::handle_usb_serial_command() {
  std::string command_string;
  read_line_from_buffer(command_string);
  _usb_serial.printf("%s\n", command_string.c_str());

  std::string log_message = "Received command: " + command_string;
  Logger::log(Logger::Module::COMMAND_HANDLER, Logger::Level::DEBUG, log_message);

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

void CommandHandler::handle_command(const std::string &command_string) {
  std::string command_name;
  std::string parameters;
  separate_command_name(command_string, command_name, parameters);

  Command *command = find_command(command_name);
  if (command != nullptr) {
    command->execute(parameters);
  } else {
    std::string log_message = "Unknown command " + command_name;
    Logger::log(Logger::Module::COMMAND_HANDLER, Logger::Level::ERROR, log_message);
  }
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
