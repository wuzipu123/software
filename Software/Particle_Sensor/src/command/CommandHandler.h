
#ifndef PARTICLE_SENSOR_COMMANDHANDLER_H
#define PARTICLE_SENSOR_COMMANDHANDLER_H

#include "Command.h"
#include "CircularBuffer.h"
#include "EventFlags.h"
#include "FlashIAP.h"
#include "SensorSPS30.h"
#include "SensorBME280.h"
#include "defines.h"

/**
  * Class receiving and handling the commands from the
  * USB virtual COM port interface
  * 
  */
class CommandHandler {
public:
  /**
   * Create a new CommandHandler and instantiate every command on the heap.
   *
   * @param usb_serial  reference to an USBSerial object
   * @param flash       reference to a FlashIAP object
   * @param sps30       reference to a SensorSPS30 object
   * @param bme280      reference to a SensorBME280 object
   * @param event_flags reference to an EventFlags object
   */
  CommandHandler(USBSerial &usb_serial, mbed::FlashIAP &flash, SensorSPS30 &sps30, SensorBME280 &bme280,
                 rtos::EventFlags &event_flags);

  /**
   * The CommandHandler destructor deletes all Command objects from #_commands,
   * which are stored on the heap
   */
  ~CommandHandler();

  /**
   * Tries to connect (non-blocking) to an USB serial terminal.
   * If connection succeeds, #_buffer is cleared
   * and the software version and the command prompt are printed.
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
   * Prints disconnect information and disconnects from
   * the USB serial terminal and calls USBSerial::deinit() to
   * unlock deepsleep again.
   */
  void disconnect();

private:
  /**
   * Interrupt handler that receives commands from the USB serial interface
   * and stores them in #_buffer.
   * If a newline is received, the \ref FLAG_RECEIVED_COMMAND flag is
   * set in #_event_flags.
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
   * @param line Reference to the string on which the line is pushed
   */
  void read_line_from_buffer(std::string &line);

  /**
   * Searches for a command in #_commands with the given \p command_name.
   *
   * @param command_name the name of the searched command
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

  /**
   * Reference to the USBSerial object handling all the low level
   * operations for the connection, the input and the output.
   */
  USBSerial &_usb_serial;

  /**
   * Reference to the EventFlags object used to signal the
   * CommandState::handle() that a new command was received.
   */
  rtos::EventFlags &_event_flags;

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
};


#endif // PARTICLE_SENSOR_COMMANDHANDLER_H
