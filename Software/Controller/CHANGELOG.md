# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

The version number of the program is defined in src/constant/constants.h and needs to be adjusted
 according to the version in this file.

## [Unreleased]


## [0.0.5] - 2020-03-12
### Changed
- Move enum StateContext::Result to State::Result to avoid circular dependencies
- Fix USB serial interface receive problems occuring on windows systems

## [0.0.4] - 2020-09-01
### Added
- Log size of response if sensor board serial response error occurs
- Add 1ms timeout after switching RS485 transceiver to send mode

### Changed
- Immediately retry to read measurement data from sensor board if it fails
- Reset sensor error counter if a read operation was successful

## [0.0.3] - 2020-07-27
### Added
- Add custom_targets.json with two targets, for different PCB versions, because pin mapping is differs

### Changed
- Set PinMode of sensor error pin to PullDown
- Adjust target names and overrides in mbed_app.json and mbed_app_debug.json to work with added custom_targets.json
- Update README.md according to the target changes
- Override "target.clock_source" and "target.lse_available" in mbed_app.json to use external crystals

## [0.0.2] - 2020-07-22
### Added
- This CHANGELOG.md to keep track of changes

## [0.0.1] - 2020-07-22
### Added
- All source files
- Unit tests for the classes SensorData, JsonProtocol and BinProtocol
- Documentation of the source code
- README.md with information on how to use this project
