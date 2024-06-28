SensMat Particle Sensor Hardware Test
=====================================

This software can be used to test the hardware components of the SensMat Particle Sensor PCB.
It is built on [ARM Mbed OS](https://os.mbed.com/mbed-os/).

## 1. Building
To build the project with mbed-cli, type:
```bash
mbed compile -m PART_SENS_V1 --profile debug --source . --source ../Framework/mbed-os 
```

If the binary should be flashed directly after building, the flag `--flash` can be added.
## 2. Flashing
To flash the binary file with [stlink](https://github.com/stlink-org/stlink), type:
```bash
 st-flash write BUILD/PART_SENS_V1/GCC_ARM-DEBUG/Particle_Sensor_Hardware_Test.bin 0x8000000
```

## 3. Usage
After flashing the binary, connect to the UART interface (115200, 8N1) on the board.

Pin 1: TX, Pin 2: RX, Pin 3: GND

When starting the board, by switching on the power, a command prompt should be visible 
in the serial terminal. Send a "help\r\n" over the serial terminal to get information about
the supported commands and their usage instructions in order to test each component of the board.
