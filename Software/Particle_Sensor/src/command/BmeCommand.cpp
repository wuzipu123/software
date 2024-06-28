
#include "BmeCommand.h"
#include "defines.h"

BmeCommand::BmeCommand(USBSerial &usb_serial, SensorBME280 &bme280)
    : Command(bme_command_name, bme_command_description, usb_serial),
      _bme280(bme280) {
}

void BmeCommand::execute_command(std::map<std::string, std::string> &parameter_map,
                                 std::vector<std::string> &parameter_vec) {
  if (parameter_map.empty() && parameter_vec.empty()) {
    _usb_serial.printf("Error: No argument provided\n");
    return;
  }

  if (parameter_vec.size() == 1) {
    if (parameter_vec.front() == "init") {
      if (_bme280.init() == MBED_SUCCESS) {
        _usb_serial.printf("Init successful!\n");
        _usb_serial.printf("Temperature [degC];Pressure [Pa];Humidity [%%]\n");
      } else {
        _usb_serial.printf("Error: Initialization failed!\n");
      }
    } else if (parameter_vec.front() == "read") {
      SensorBME280::measurement_t measurement = {0};
      if (_bme280.read_measurement(&measurement) == MBED_SUCCESS) {
        _usb_serial.printf("%.9e;%.9e;%.9e\n", measurement.temperature, measurement.pressure, measurement.humidity);
      } else {
        _usb_serial.printf("Error: Reading measurement failed!\n");
      }
    } else {
      _usb_serial.printf("Error: Unknown parameter\n");
    }
  } else {
    _usb_serial.printf("Error: Wrong number of parameters\n");
  }
}
