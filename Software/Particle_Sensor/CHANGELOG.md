# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

The version number of the program is defined in src/defs/defines.h and needs to be adjusted
 according to the version in this file.

## [Unreleased]

## [0.4.3] - 2021-05-11
### Fixed
- Rename class BME280 to SensorBME280 and SPS30 to SensorSPS30 due to name conflicts on Windows

### Changed
- Update usage description for USB serial interface commands.

## [0.4.2] - 2021-02-25
### Added
- Compute moving average over a configurable number of measurement values

### Fixed
- Increase buffer size for measurement values written to SD card.
- Retry reading battery level maximum 5 times if it fails.

## [0.4.1] - 2021-01-07
### Changed
- Move StateContext::Result to State::Result to remove circular include dependency

### Removed
- Remove unused functions during code cleanup

## [0.4.0] - 2020-12-03
### Changed
- Switch off IIR filter on SensorBME280
- Use intf_ptr to pass SPI context to bme280_spi_* functions to avoid static objects

## [0.3.1] - 2020-11-30
### Changed
- Optimize imports, reformat code and document code

### Fixed
- Set time to 2020-01-01T00:00:00 if time is not set, otherwise LoRa communication fails

## [0.3.0] - 2020-11-23
### Added
- Configuration option to disable sending status messages

### Changed
- Change thing-ID and format for status messages

## [0.2.0] - 2020-11-19
### Added
- Configuration of correction offset and factor for every measured property
- Log SensorSPS30 serial numbers and UUIDs to measurement data CSV files
- Battery class with function to read battery voltage
- Send a status message with battery voltage, RSSI and SNR in fixed time intervals via LoRa

### Changed
- Wait 2-10min instead of 10-60s before retry to authenticate at gateway
- Reboot again after one hour if an error occured
- Print statistics on status button press if PRINT_STAT is defined

## [0.1.0] - 2020-11-10
### Added
- Functions to calibrate RTC
- SpsCommand and BmeCommand to control sensors via USB interface
- InfoCommand to display SWUUID, HWUUID and software version
- Possibility to restore default configuration by pressing both buttons during power on

### Changed
- Store and send only latest measurement values instead of maintaining a queue

### Fixed
- Fix LoRa module state switch delay bug

## [0.0.1] - 2020-11-02
### Added
- All source files with initial implementation
