#ifndef CONTROLLER_COMMANDHANDLER_H
#define CONTROLLER_COMMANDHANDLER_H

#include "Command.h"
#include "constants.h"
#include "Config.h"
#include "USBSerial.h"
#include "CircularBuffer.h"
#include "EventFlags.h"
#include "FlashIAP.h"
#include <string>
#include <vector>

/**
  * Class receiving and handling the commands from the
  * USB virtual com port interface
  * 
  */
class CommandHandler {
public:
  /**
   * Create a new CommandHandler and instantiate every command on the heap.
   *
   * @param usb_serial          reference to an USBSerial object
   * @param flash               reference to a FlashIAP object
   * @param config              reference to a Config object
   * @param control_event_flags reference to an EventFlags object
   */
  CommandHandler(USBSerial &usb_serial, mbed::FlashIAP &flash, Config &config, rtos::EventFlags &control_event_flags);

  /**
   * Destroy the CommandHandler and delete all Commands
   * from \ref #_commands stored on the heap
   */
  ~CommandHandler();

  /**
   * Tries to connect (non-blocking) to an USB serial terminal.
   * If connection succeeds, #_buffer is cleared
   * and controller software version and command prompt are printed.
   *
   * @return true if connected, false otherwise
   */
  bool connect();

  /**
   * Reads a line from #_buffer and executes the given
   * command with the given parameters if the command exists, otherwise
   * a usage information with the supported commands is printed.
   */
  void handle_usb_serial_command();

  /**
   * Executes the given command from the \p command_string with the
   * given parameters included in the \p command_string. If the
   * command does not exist, a log entry is created.
   *
   * @param command_string
   */
  void handle_command(const std::string &command_string);

  /**
   * Prints disconnect information and disconnects from
   * the USB serial terminal and calls _usb_serial.deinit() to
   * unlock deepsleep again.
   */
  void disconnect();

private:

  /**
   * Reference to the USBSerial object handling all the low level
   * operations for the connection, the input and the output.
   */
  USBSerial &_usb_serial;

  /**
   * Reference to the EventFlags object used to signal the
   * CommandState::handle() that a new command was received.
   */
  rtos::EventFlags &_control_event_flags;

  /**
   * Vector containing pointers to an instance of every command
   */
  std::vector<Command *> _commands;

  /**
   * Buffer used by serial_interrupt_handler()
   * to store received command strings until they are handled
   * by handle_usb_serial_command().
   */
  mbed::CircularBuffer<char, COMMAND_HANDLER_MAX_BUF_SIZE> _buffer;

  /**
   * Interrupt handler that receives commands from the USB serial interface
   * and stores them in #_buffer.
   * If a newline is received, the \ref CONTROL_FLAG_RECEIVED_COMMAND flag is
   * set in #_control_event_flags.
   */
  void serial_interrupt_handler();

  /**
   * Print help message containing a list of all supported commands.
   */
  void print_help();

  /**
   * Prints the command prompt.
   */
  void print_prompt();

  /**
   * Pops one line from #_buffer and pushes it to \p line.
   *
   * @param line Reference to string on which the line is pushed
   */
  void read_line_from_buffer(std::string &line);

  /**
   * Searches for a command in #_commands with the given \p command_name.
   *
   * @param command_name contains the name of the command
   * @return pointer to the Command object if the command exists, nullptr otherwise
   */
  Command *find_command(const std::string &command_name);

  /**
   * Splits the given \p command_string at the first space into the \p command_name
   * and the \p parameters.
   *
   * @param command_string whole command string
   * @param command_name   name of the command preceding the first space in \p command_string
   * @param parameters     parameters succeeding the first space in \p command_string
   */
  static void separate_command_name(const std::string &command_string, std::string &command_name,
                                    std::string &parameters);
};


#endif // CONTROLLER_COMMANDHANDLER_H
