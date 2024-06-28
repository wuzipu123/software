from serial import Serial
import time
import argparse
from progress.bar import Bar
from colorama import Fore, init

cal_time_sec = 60

def wait_for_prompt(ser: Serial):
    ser.read_until('?> '.encode('ascii'))


def send_time_calibrate(ser: Serial, time_ms: int):
    wait_for_prompt(ser)
    cal_string = "time calibrate " + str(time_ms) + '\r\n'
    ser.write(cal_string.encode('ascii'))
    line = ser.readline()
    line = ser.readline()
    assert(line.decode('ascii').startswith('plus pulses: '))
    ser.read(3)


def calibrate_rtc(ser: Serial):
    diff_list = []

    send_time_calibrate(ser, 0)

    send_string = 'time tick ' + str(cal_time_sec) + '\r\n'
    ser.write(send_string.encode('ascii'))
    ser.readline()

    ser.timeout = 2
    line = ser.readline()
    start_time = time.time_ns()
    if not line.decode('ascii').strip() == '0000':
        raise ValueError
    
    with Bar('Calibrating', fill='#', suffix='%(percent).1f%% - %(eta)ds') as bar:
        for i in range(cal_time_sec):
            line = ser.readline()
            tmp_time = time.time_ns()
            if not int(line.decode('ascii').strip()) == i + 1:
                raise ValueError

            diff_ms = (tmp_time - start_time) / 1000000 - (i + 1) * 1000
            day_drift_ms = -diff_ms / ((i + 1) * 1000) * 24 * 60 * 60 * 1000
            diff_list.append(day_drift_ms)
            bar.next(100 / cal_time_sec)

    mean_diff = int(sum(diff_list[-10:])/10)
    send_time_calibrate(ser, mean_diff)
    print(Fore.GREEN + '+ RTC Calibration done! Measured time drift per day: ' + str(mean_diff) + 'ms')


def set_time(ser: Serial):
    wait_for_prompt(ser)
    set_time = int(time.time()) + 1
    local_time = time.localtime(set_time)
    time_str = time.strftime('%F %T', local_time)

    set_time_cmd = 'time set ' + time_str + '\r\n'
    while time.time() < set_time:
        pass
    ser.write(set_time_cmd.encode('ascii'))

    if read_time(ser) == time_str:
        print(Fore.GREEN + '+ Setting time and date to ' + time_str + ' done!')
    else:
        print(Fore.RED + '- Setting time and date failed!')


def read_time(ser: Serial):
    wait_for_prompt(ser)
    read_time_cmd = time.strftime('time\r\n')
    ser.write(read_time_cmd.encode('ascii'))
    line = ser.readline() + ser.readline()
    #read_time = ser.readline().decode('ascii')[14:].strip()
    read_time = line.decode('ascii').split('Current time: ')[1][:19].strip().replace('T', ' ')
    return read_time


def main():
    parser = argparse.ArgumentParser(description='Configure and calibrate RTC of SensMat Particle Sensor.')
    parser.add_argument('port', type=str, help='usb port (e.g. /dev/ttyACM0 or COM6)')
    parser.add_argument('-c', '--calibrate', dest='calibrate', action='store_true', help='Calibrate RTC')
    parser.add_argument('-s', '--set', dest="set", action='store_true', help='Set RTC to current date and time')
    args = parser.parse_args()

    baudrate = 115200
    ser = Serial(args.port, baudrate, timeout=1)
    init()

    try:
        if args.calibrate:
            calibrate_rtc(ser)
        if args.set:
            set_time(ser)
        if not args.calibrate and not args.set:
            t =  read_time(ser)
            if len(t) != 19:
                print(Fore.RED + '- Reading time and date failed!')
                exit(-1)
            print(Fore.GREEN + "+ Current RTC date and time:", t)
    finally:
        time.sleep(0.1)
        ser.read_all()
        ser.close()

if __name__ == "__main__":
    main()
