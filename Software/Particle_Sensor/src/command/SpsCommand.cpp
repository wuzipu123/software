
#include "SpsCommand.h"
#include "defines.h"

SpsCommand::SpsCommand(USBSerial &usb_serial, SensorSPS30 &sps30)
    : Command(sps_command_name, sps_command_description, usb_serial),
      _sps30(sps30) {
}

void SpsCommand::execute_command(std::map<std::string, std::string> &parameter_map,
                                 std::vector<std::string> &parameter_vec) {
  if (parameter_map.empty() && parameter_vec.empty()) {
    _usb_serial.printf("Error: No argument provided\n");
    return;
  }

  if (parameter_vec.size() == 1) {
    if (parameter_vec.front() == "on") {
      _sps30.power_on();
    } else if (parameter_vec.front() == "off") {
      _sps30.power_off();
    } else if (parameter_vec.front() == "probe") {
      if (_sps30.probe() == MBED_SUCCESS) {
        _usb_serial.printf("Probing succeeded!\n");
      } else {
        _usb_serial.printf("Error: Probing failed!\n");
      }
    } else if (parameter_vec.front() == "serial") {
      std::string serial;
      if (_sps30.get_serial(serial) == MBED_SUCCESS) {
        _usb_serial.printf("Serial number: %s\n", serial.c_str());
      } else {
        _usb_serial.printf("Error: Reading serial number failed!\n");
      }
    } else if (parameter_vec.front() == "version") {
      sps30_version_information sps30_version = {0};
      if (_sps30.read_version(&sps30_version) == MBED_SUCCESS) {
        _usb_serial.printf("Firmware version:\t%d.%d\n", sps30_version.firmware_major, sps30_version.firmware_minor);
        _usb_serial.printf("SHDLC version:\t\t%d.%d\n", sps30_version.shdlc_major, sps30_version.shdlc_minor);
        _usb_serial.printf("Hardware revision:\t%d\n", sps30_version.hardware_revision);
      } else {
        _usb_serial.printf("Error: Reading version numbers failed!\n");
      }
    } else if (parameter_vec.front() == "start") {
      if (_sps30.start_measurement() == MBED_SUCCESS) {
        _usb_serial.printf("PM1.0 [ug/m^3];PM2.5 [ug/m^3];PM4.0 [ug/m^3];PM10.0 [ug/m^3];PN0.5 [#/cm^3];PN1.0 [#/cm^3];"
                           "PN2.5 [#/cm^3];PN4.0 [#/cm^3];PN10.0 [#/cm^3];Typical Particle Size [um]\n");
      } else {
        _usb_serial.printf("Error: Starting measurement failed!\n");
      }
    } else if (parameter_vec.front() == "stop") {
      _sps30.stop_measurement();
    } else if (parameter_vec.front() == "read") {
      SensorSPS30::measurement_t measurement = {0};
      if (_sps30.read_measurement(&measurement) == MBED_SUCCESS) {
        _usb_serial.printf("%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e;%.9e\n",
                           measurement.mc_1p0, measurement.mc_2p5, measurement.mc_4p0, measurement.mc_10p0,
                           measurement.nc_0p5, measurement.nc_1p0, measurement.nc_2p5, measurement.nc_4p0,
                           measurement.nc_10p0, measurement.typical_particle_size);
      } else {
        _usb_serial.printf("Error: Reading measurement failed!\n");
      }
    } else if (parameter_vec.front() == "clean") {
      if (_sps30.start_manual_fan_cleaning() == MBED_SUCCESS) {
        _usb_serial.printf("Fan cleaning started\n");
      } else {
        _usb_serial.printf("Error: Starting fan cleaning failed!\n");
      }
    } else {
      _usb_serial.printf("Error: Unknown parameter\n");
    }
  } else {
    _usb_serial.printf("Error: Wrong number of parameters\n");
  }
}