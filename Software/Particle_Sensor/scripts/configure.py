from serial import Serial
import time
import argparse

# All commands from this list are sequentially sent to the SensMat Particle Sensor
command_list = [
    "time",
    "config log_level=2",
    "config sample_time_sec=3600",
    "config lora_enable=true",
    "config moving_avg_length=5",
    "config"
    ]
output = ""


def print_all(ser: Serial):
    global output
    line = ser.read_all().decode('ascii')
    output += line
    print(line, end='')


def send_cmd(ser: Serial, command):
    ser.write((command + '\r\n').encode('ascii'))
    time.sleep(0.2)
    print_all(ser)
    

def configure(ser: Serial):
    print_all(ser)
    time.sleep(0.2)
    for command in command_list:
        send_cmd(ser, command)


def main():
    parser = argparse.ArgumentParser(description='Configure SensMat Particle Sensor via its USB command interface.')
    parser.add_argument('port', type=str, help='usb port (e.g. /dev/ttyACM0 or COM6)')
    args = parser.parse_args()

    baudrate = 115200
    ser = Serial(args.port, baudrate, timeout=1)

    try:
        configure(ser)
    finally:
        time.sleep(0.1)
        ser.read_all()
        ser.close()


if __name__ == "__main__":
    main()
