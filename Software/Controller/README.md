SensMat Controller Software
=========================== 

Controller software for the SensMat environmental logger

- [SensMat Controller Software](#sensmat-controller-software)
- [1. Application Usage](#1-application-usage)
  - [1.1. State Machine](#11-state-machine)
  - [1.2. LED States](#12-led-states)
  - [1.3. Buttons](#13-buttons)
- [2. Development](#2-development)
  - [2.1. Building](#21-building)
    - [2.1.1. Build Option 1: Using mbed-cli](#211-build-option-1-using-mbed-cli)
    - [2.1.2. Build Option 2: Using CMake project](#212-build-option-2-using-cmake-project)
    - [2.1.3. Build Option 3: Using Eclipse project](#213-build-option-3-using-eclipse-project)
    - [2.1.4. Build Option 4: Using Visual Studio Code project](#214-build-option-4-using-visual-studio-code-project)
  - [2.2. Flashing](#22-flashing)
  - [2.3. Debugging](#23-debugging)
  - [2.4. Testing](#24-testing)
    - [2.4.1. Unit tests](#241-unit-tests)
  - [2.5. Generate Documentation](#25-generate-documentation)
  - [2.6. Notes](#26-notes)

# 1. Application Usage
## 1.1. State Machine
The following flow chart shows all states of the state machine and the possible transitions between the states. Additionally, from the states IdleState, SDErrorState, MeasureState and CommandState it is also possible to reset the application. 
![State machine flow chart](FSM_Flow_Chart.svg)

## 1.2. LED States
The red LED on the front panel of the measurement box indicates the error type if an error occured, otherwise it is off.

The green LED indicates the state in which the state machine currently is.

The following table lists the most important LED states and its meanings.

| green LED               | red LED            | State                        | Error                                  |
|-------------------------|--------------------|------------------------------|----------------------------------------|
| on                      | off                | InitState, CheckSensorsState | no error                               |
| on                      | blink every 5s     | InitState, CheckSensorsState | Sensor error                           |
| blink every 15s         | off                | MeasureState                 | no error                               |
| blink every 15s         | blink every 5s     | MeasureState                 | Sensor error                           |
| blink every 5s          | off                | IdleState                    | no error                               |
| blink every 5s          | blink every 5s     | IdleState                    | Sensor error                           |
| blink every second      | blink every second | SDErrorState                 | SD card error                          |
| blink every second      | on                 | SDErrorState                 | SD full init error                     |
| blink every 250ms       | off                | FormatSDState                | no error                               |
| off                     | off                | Power off                    | no error                               |
| off                     | blink every 5s     | ShutdownState                | Sensor error or serial interface error |
| off                     | blink every second | ShutdownState                | SD card error                          |
| off                     | on                 | ShutdownState                | SD full measurement error              |
| blink inverted every 2s | off                | CommandState                 | no error                               |

## 1.3. Buttons
Two buttons on the front panel are used to control the measurement box and to change between the states of the state machine. 

In the table below the resulting state transitions for short and long button presses are listed.

| Button        | press duration | resulting transition |
|---------------|----------------|----------------------|
| left (inner)  | <= 3 seconds   | RESET_PRESSED        |
| left (inner)  | > 3 seconds    | FORMAT_SD_PRESSED    |
| right (outer) | <= 3 seconds   | START_STOP_PRESSED   |
| right (outer) | > 3 seconds    | COMMAND_PRESSED      |

# 2. Development
The application was developed with ARM Mbed OS version 5.15.5.
Check the Mbed OS version which is currently check out with:
```bash
git submoule
```

If another version is displayed, check out the correct one with:
```bash
git checkout mbed-os-5.15.5
```
in the mbed-os directory: ```Software/Framework/mbed-os```

## 2.1. Building
Install mbed-cli as described [here](https://os.mbed.com/docs/mbed-os/v5.15/tools/manual-installation.html).

There are multiple options to build the project. 
The project can be build with the mbed-cli or the mbed-cli can be used to export project files 
for other build systems and IDEs.

In custom_targets.json targets for different PCB versions are defined, because the pin mapping
differs between the PCB versions. When exporting and building the project with mbed-cli, one 
needs to specify the right target with the ```-m``` option.

In the following steps the build process is described for mbed-cli, cmake, eclipse and VS code projects.

### 2.1.1. Build Option 1: Using mbed-cli
To build the project with mbed-cli, type:
```bash
mbed compile -m BOX_CTRL_V3 --profile release --source . --source ../Framework/mbed-os
```
If the binary should be flashed directly after building, the flag `--flash` can be added.

### 2.1.2. Build Option 2: Using CMake project
To export cmake project files execute:
```bash
mbed export -i cmake_gcc_arm -m BOX_CTRL_V3 --profile debug --source . --source ../Framework/mbed-os
./scripts/remove_ignored.sh
```

This generates a `CMakeLists.txt` file and a `BUILD` folder. 

To build the project with cmake, go into the `BUILD` folder, generate the makefiles and build the project.
```bash
cd BUILD
cmake ..
make -j
```

### 2.1.3. Build Option 3: Using Eclipse project
To export eclipse project files execute:
```bash
mbed export -i eclipse_gcc_arm -m BOX_CTRL_V3 --profile debug --source . --source ../Framework/mbed-os
```

This generates the files `.project`, `.cproject`, `Makefile` and the folders `BUILD` and `eclipse-extras`. With the generated files, the project can be opened with eclipse CDT or SW4STM32.

To manually build the project with Make, execute `make` in the projects root folder.
 
### 2.1.4. Build Option 4: Using Visual Studio Code project
To export Visual Studio Code project files execute:
```bash
mbed export -i vscode_gcc_arm -m BOX_CTRL_V3 --profile debug --source . --source ../Framework/mbed-os
sed -i 's:}/Framework:}/../Framework:g' ./.vscode/c_cpp_properties.json
sed -i 's:\.\${:\${:g' ./.vscode/c_cpp_properties.json
```

This generates the file `Makefile` and the folders `BUILD` and `.vscode`. With the generated files, the project can be opened with Visual Studio Code.

To manually build the project with Make, execute `make` in the projects root folder.

Replace the content of the file .vscode/tasks.json with the following content:
```json
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
        {
            "label": "make",
            "type": "shell",
            "linux": {
                "command": "make"
            },
            "osx": {
                "command": "make"
            },
            "windows": {
                "command": "make.exe"
            },
            "args": ["-j"],
            "problemMatcher": {
                "owner": "cpp",
                "fileLocation": ["relative", "${workspaceRoot}/mbed-os"],
                "pattern": {
                    "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
                    "file": 1,
                    "line": 2,
                    "column": 3,
                    "severity": 4,
                    "message": 5
                }
            },
            "presentation": {
                "reveal": "always",
                "panel": "new"
            }
        },
        {
            "label": "flash",
            "type": "shell",
            "linux": {
                "command": "st-flash"
            },
            "args": ["--format", "ihex", "write", "${workspaceRoot}/BUILD/${workspaceRootFolderName}.hex"],
            "presentation": {
                "reveal": "always",
            }
        },
        {
            "label": "make and flash",
            "type": "shell",
            "command": "echo",
            "dependsOrder": "sequence",
            "dependsOn": ["make", "flash"]
        }
    ]
}
```
Replace the content of the file .vscode/launch.json with the following content:
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Controller Debug Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceRoot}/BUILD/${workspaceRootFolderName}.elf",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${workspaceRoot}",
            "environment": [],
            "externalConsole": false,
            "debugServerArgs": "-f /usr/share/openocd/scripts/board/st_nucleo_l476rg.cfg -f /usr/share/openocd/scripts/interface/stlink-v2-1.cfg -c init -c \"reset init\"",
            "serverLaunchTimeout": 20000,
            "filterStderr": true,
            "filterStdout": false,
            "serverStarted": "target halted due to debug-request, current mode: Thread",
            "setupCommands": [
                { "text": "-target-select remote localhost:3333", "description": "connect to target", "ignoreFailures": false },
                { "text": "-file-exec-and-symbols ${workspaceRoot}/BUILD/${workspaceRootFolderName}.elf", "description": "load file", "ignoreFailures": false},
                { "text": "-interpreter-exec console \"monitor endian little\"", "ignoreFailures": false },
                { "text": "-interpreter-exec console \"monitor reset\"", "ignoreFailures": false },
                { "text": "-interpreter-exec console \"monitor halt\"", "ignoreFailures": false },
                { "text": "-interpreter-exec console \"monitor arm semihosting enable\"", "ignoreFailures": false },
                { "text": "-target-download", "description": "flash target", "ignoreFailures": false }
            ],
            "logging": {
                "moduleLoad": true,
                "trace": true,
                "engineLogging": true,
                "programOutput": true,
                "exceptions": true
            },
            "linux": {
                "MIMode": "gdb",
                "MIDebuggerPath": "arm-none-eabi-gdb",
                "debugServerPath": "/usr/bin/openocd"
            },
            "osx": {
                "MIMode": "gdb",
                "MIDebuggerPath": "arm-none-eabi-gdb",
                "debugServerPath": "pyocd-gdbserver"
            },
            "windows": {
                "preLaunchTask": "make.exe",
                "MIMode": "gdb",
                "MIDebuggerPath": "arm-none-eabi-gdb.exe",
                "debugServerPath": "pyocd-gdbserver.exe",
                "setupCommands": [
                    { "text": "-environment-cd ${workspaceRoot}\\BUILD" },
                    { "text": "-target-select remote localhost:3333", "description": "connect to target", "ignoreFailures": false },
                    { "text": "-file-exec-and-symbols ${workspaceRootFolderName}.elf", "description": "load file", "ignoreFailures": false},
                    { "text": "-interpreter-exec console \"monitor endian little\"", "ignoreFailures": false },
                    { "text": "-interpreter-exec console \"monitor reset\"", "ignoreFailures": false },
                    { "text": "-interpreter-exec console \"monitor halt\"", "ignoreFailures": false },
                    { "text": "-interpreter-exec console \"monitor arm semihosting enable\"", "ignoreFailures": false },
                    { "text": "-target-download", "description": "flash target", "ignoreFailures": false }
                ]
            }
        }
    ]
}
```

If the `mbed_app.json` file was changed, delete the file `.vscode/c_cpp_properties.json` and execute the commands from the beginning of the section, used to export the project, again.

To build the project with Visual Studio Code, press `Ctrl+P` to open the command palette and type `task make` and press `Enter`.
To flash the built hex file, execute `task flash` from the command palette.

To debug the application change to the Run tab and run the `Controller Debug Launch` configuration at the top left corner of the window.

## 2.2. Flashing
To flash the application binary execute:
```bash
st-flash write BUILD/Controller.bin 0x8000000
```
It is also possible to flash the hex file with:
```bash
st-flash --format ihex write BUILD/Controller.hex
```

## 2.3. Debugging
To debug the application, the command line can be used, or an IDE can be set up to work with these command line tools. 

For debugging, another mbed configuration is needed, therefore add `--app-config mbed_app_debug.json` to the mbed-cli commands. Also use `--profile debug` and not `--profile release`.

Debugging from the command line is done by first flashing the application which was built with debug options enabled. Then OpenOCD is used as debug server and started with a command similar to:
```bash
openocd -f /usr/share/openocd/scripts/board/st_nucleo_l476rg.cfg -f /usr/share/openocd/scripts/interface/stlink-v2-1.cfg -c init -c "reset init"
```
In another terminal window start GDB with the path to the .elf file:
```bash
arm-none-eabi-gdb -tui BUILD/Controller.elf
```
Within GDB connect to the debug server with: `target remote localhost:3333`

## 2.4. Testing
### 2.4.1. Unit tests
To build and run the unit tests execute the following commands:
```bash
mkdir -p UNITTESTS/build       # create build folder if not existing
cd UNITTESTS/build             # go into build folder
cmake ..                       # run cmake
make -j                        # build unit tests
run-parts .                    # run all created unit tests 
ctest                          # Optional: run ctest which also executes all unit tests
```

## 2.5. Generate Documentation
To generate the documentation, execute: `doxygen Doxyfile`
This will generate a HTML documentation in the `doc/html` folder. Open the `index.html` file to view the documentation.

To also generate a documentation in latex set `GENERATE_LATEX = YES` in the `Doxyfile`.

If a single PDF documentation is wanted, execute `pdflatex refman.tex` in `doc/latex`, which generates a PDF named `refman.pdf` containing the whole documentation.
