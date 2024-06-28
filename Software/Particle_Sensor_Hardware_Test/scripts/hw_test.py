from serial import Serial
import time
import argparse
from colorama import Fore, init

serial_port = '/dev/ttyACM0'
lora_endpoint_port = '/dev/ttyACM1'
usb_port = '/dev/ttyACM2'


def test_leds(ser: Serial):
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '===> LED test. Press Enter to continue...' + Fore.RESET)
    ser.write('led stateRed 1\r\n'.encode('ascii'))
    input(Fore.BLUE + '> Check if status LED lights red. Press Enter to continue...')
    ser.write('led stateRed 0\r\n'.encode('ascii'))
    
    ser.write('led stateGreen 1\r\n'.encode('ascii'))
    input('> Check if status LED lights green. Press Enter to continue...')
    ser.write('led stateGreen 0\r\n'.encode('ascii'))
    
    ser.write('led bat1 1\r\n'.encode('ascii'))
    input('> Check if battery LED 1 lights green. Press Enter to continue...')
    ser.write('led bat1 0\r\n'.encode('ascii'))
    
    ser.write('led bat2 1\r\n'.encode('ascii'))
    input('> Check if battery LED 2 lights green. Press Enter to continue...')
    ser.write('led bat2 0\r\n'.encode('ascii'))
    
    ser.write('led bat3 1\r\n'.encode('ascii'))
    input('> Check if battery LED 3 lights green. Press Enter to continue...' + Fore.RESET)
    ser.write('led bat3 0\r\n'.encode('ascii'))
    
    time.sleep(0.1)
    ser.read_all()


def test_uart(ser: Serial):
    print(Fore.YELLOW + '> Make sure, Particle_Sensor_Hardware_Test.bin is flashed to the MCU')
    print(Fore.YELLOW + '> Connect Particle Sensor UART port (ttyACM0), second LoRa endpoint with\r\n> Particle_Sensor_Hardware_Test.bin (ttyACM1) and microUSB serial interface (ttyACM2)\r\n> to the PC when necessary.')
    input(Fore.YELLOW + '> Remove micro SD card from slot and turn power switch OFF (left)\r\n> and then ON (right)! Press Enter to continue...')
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '> UART test. Press Enter to continue...' + Fore.RESET)
    
    if 'SensMat Particle Sensor Hardware Test' in ser.readline().decode('ascii'):
        print(Fore.GREEN + '+ UART TX is working')
    else:
        print(Fore.RED + '- UART TX not working!')
    
    ser.read_all()
    ser.write('echo test\r\n'.encode('ascii'))
    if 'test' in ser.readline().decode('ascii'):
        print(Fore.GREEN + '+ UART RX is working')
    else:
        print(Fore.RED + '- UART RX not working!')


def test_button(ser: Serial):
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '> Button test. Press Enter to continue...' + Fore.RESET)
    
    failed = False
    ser.write('button\r\n'.encode('ascii'))
    if not ser.readline() == b'Button 1 is HIGH\r\n':
        print(Fore.RED + '- Button 1 is not working! Is LOW, but should be HIGH.')
        failed = True
    if not ser.readline() == b'Button 2 is HIGH\r\n':
        print(Fore.RED + '- Button 2 is not working! Is LOW, but should be HIGH.')
        failed = True
        
    if failed:
        return
        
    input(Fore.YELLOW + '> Press and hold button 1 (left). Press Enter to continue...' + Fore.RESET)
    ser.read_all()
    ser.write('button\r\n'.encode('ascii'))
    if ser.readline() == b'Button 1 is LOW\r\n'and ser.readline() == b'Button 2 is HIGH\r\n':
        print(Fore.GREEN + '+ Button 1 is working. Release button 1.')
    else:
        print(Fore.RED + '- Button 1 is not working! Is HIGH, but should be LOW.')
        
    input(Fore.YELLOW + '> Press and hold button 2 (right). Press Enter to continue...' + Fore.RESET)
    ser.read_all()
    ser.write('button\r\n'.encode('ascii'))
    if ser.readline() == b'Button 1 is HIGH\r\n' and ser.readline() == b'Button 2 is LOW\r\n':
        print(Fore.GREEN + '+ Button 2 is working. Release button 2.')
    else:
        print(Fore.RED + '- Button 2 is not working! Is HIGH, but should be LOW.')


def test_batlevel(ser: Serial):
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '> Battery level measurement test. Press Enter to continue...' + Fore.RESET)
    
    try:
        ser.write('batlevel -on -m\r\n'.encode('ascii'))
        ser.readline().decode('ascii')
        bat_str = ser.readline().decode('ascii').split('=')[1].split('V')[0].strip()
        level = float(bat_str)
        if level < 5.0:
            raise Exception("")

        ser.write('batlevel -off -m\r\n'.encode('ascii'))
        ser.readline().decode('ascii')
        bat_str = ser.readline().decode('ascii').split('=')[1].split('V')[0].strip()
        if float(bat_str) > 0.1:
            raise Exception("")
        else:
            print(Fore.GREEN + '+ Battery level measurement is working. Battery level is ' + str(level) + 'V')
    except:
        print(Fore.RED + '- Battery level measurement is not working!')

def test_charging(ser: Serial):
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '> Battery charging test. Disconnect power supply. Press Enter to continue...' + Fore.RESET)
    
    try:
        ser.write('batlevel -on -m\r\n'.encode('ascii'))
        ser.readline().decode('ascii')
        bat_str = ser.readline().decode('ascii').split('=')[1].split('V')[0].strip()
        level_before = float(bat_str)
        if level_before < 5.0:
            raise Exception("")

        input(Fore.YELLOW + '> Connect power supply for charging. The charge LED should light orange. Press Enter to continue...' + Fore.RESET)
        ser.write('batlevel -on -m\r\n'.encode('ascii'))
        ser.readline().decode('ascii')
        bat_str = ser.readline().decode('ascii').split('=')[1].split('V')[0].strip()
        level_after = float(bat_str)
        if level_after < 5.0:
            raise Exception("")

        if level_after > level_before + 0.05:
            print(Fore.GREEN + '+ Battery charging is working. Battery levels: ' + str(level_before) + 'V -> ' + str(level_after) + 'V')
        else:
            print(Fore.RED + '- Battery charging is not working. Battery levels: ' + str(level_before) + 'V -> ' + str(level_after) + 'V')

    except:
        print(Fore.RED + '- Battery level measurement failed!')


def test_sps30(ser: Serial):
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '> SPS30 measurement test. Press Enter to continue...' + Fore.RESET)

    ser.read_all()
    try:
        ser.write('sps m 3\r\n'.encode('ascii'))
        time.sleep(0.5)
        ser.readline()
        ser.readline()
        serial_str = ser.readline().decode('ascii')
        ser.readline()
        serial = serial_str.split('SPS30 Serial: ')[1][0:16]

        if not len(serial) == 16:
            raise Exception('')

        print(Fore.GREEN + '+ SPS30 measurement is working. Serial number is ' + serial + Fore.RESET)
        line = ser.readline().decode('ascii')
        time.sleep(3)
        while line:
            if len(line) > 10:
                print("l", line, end='')
            line = ser.readline().decode('ascii')
        print('')

    except:
        print(Fore.RED + '- SPS30 measurement is not working!')
        time.sleep(3)

def test_bme280(ser: Serial):
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '> BME280 measurement test. Press Enter to continue...' + Fore.RESET)

    ser.read_all()
    try:
        ser.write('bme m 1\r\n'.encode('ascii'))
        time.sleep(0.5)
        init_line = ser.readline().decode('ascii')
        if not 'BME280 init rslt: 0' in init_line:
            print(Fore.RED + '- BME280 initialization is not working!')
            raise Exception('')

        print(Fore.GREEN + '+ BME280 measurement is working.' + Fore.RESET)
        out = ser.readline().decode('ascii') + ser.readline().decode('ascii')
        ser.readline().decode('ascii')
        print(out, end='')

    except:
        time.sleep(1)


def test_sdcard(ser: Serial):
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '> SD card test. Press Enter to continue...' + Fore.RESET)
    input(Fore.YELLOW + '> Remove micro SD card from slot. Press Enter to continue...' + Fore.RESET)

    ser.read_all()
    ser.write('sdcard\r\n'.encode('ascii'))
    a = ser.readline().decode('ascii')
    if not 'SD card NOT detected\r\n' in a:
        print(Fore.RED + '- SD card detection is not working!')
        print(a)
        return
    
    input(Fore.YELLOW + '> Insert micro SD card into slot. Press Enter to continue...')
    print('> Please wait 5 seconds...' + Fore.RESET)

    ser.write('sdcard\r\n'.encode('ascii'))
    time.sleep(5)
    lines = ser.read_all().decode('ascii')
    if 'SD card detected' in lines:
        print(Fore.GREEN + '+ SD card detection is working.' + Fore.RESET)
    else:
        print(Fore.RED + '- SD card detection is not working!')

    if 'Read from SD card: Hello World!' in lines:
        print(Fore.GREEN + '+ SD card W/R is working.' + Fore.RESET)
    else:
        print(Fore.RED + '- SD card W/R is not working!')


def test_usb_serial(ser: Serial):
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '> USB serial interface test. Press Enter to continue...' + Fore.RESET)
    input(Fore.YELLOW + '> Connect USB cable to PC and Particle sensor. Press Enter to continue...' + Fore.RESET)

    ser.write('usb\r\n'.encode('ascii'))
    print(ser.readline())
    time.sleep(3)

    try:
        usb = Serial(usb_port, 115200, timeout=1)
        print("usb", usb.readline())
        if usb.readline() == b'If you can read this, the USB serial write operation works.\n':
            print(Fore.GREEN + '+ USB serial terminal connection is working.' + Fore.RESET)
        else:
            time.sleep(0.5)
            usb.read_all()
            usb.close()
            raise Exception('')

        usb.write('test\r\n'.encode('ascii'))
        time.sleep(1)
        response = usb.read_all().decode('ascii')
        if 'Received: test' in response:
            print(Fore.GREEN + '+ USB serial RX and TX is working.' + Fore.RESET)
        else:
            print(Fore.RED + '- USB serial RX and TX is not working.' + Fore.RESET)
        print(Fore.YELLOW + '> Please wait 10 seconds until completion.' + Fore.RESET)
        time.sleep(10)
    except:
        print(Fore.RED + '- USB serial connection is not working.' + Fore.RESET)


def test_rtc(ser: Serial):
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '> RTC test. Press Enter to continue...' + Fore.RESET)

    time.sleep(1)
    ser.read_all()
    set_time = int(time.time()) + 1
    local_time = time.localtime(set_time)
    time_str = time.strftime('%FT%T', local_time)

    set_time_cmd = 'time ' + time_str + '\r\n'
    while time.time() < set_time:
        pass
    ser.write(set_time_cmd.encode('ascii'))
    time.sleep(0.2)

    ser.write('time\r\n'.encode('ascii'))
    if time_str in ser.readline().decode('ascii'):
        print(Fore.GREEN + '+ Setting time and date to ' + time_str + ' worked!')
    else:
        print(Fore.RED + '- Setting time and date failed!')


def test_lora(ser: Serial):
    print(Fore.YELLOW + 80*'-' + Fore.RESET)
    input(Fore.YELLOW + '> LoRa module test. Press Enter to continue...' + Fore.RESET)
    input(Fore.YELLOW + '> Attach antenna and connect second lora endpoint to PC. Press Enter to continue...' + Fore.RESET)

    try:
        lora = Serial(lora_endpoint_port, 115200, timeout=1)
        lora.write('pingpong -start\r\n'.encode('ascii'))
        time.sleep(1)
        start_msg = lora.read_all().decode('ascii')
        lora.read_all()
        lora.close()
        if ('Init radio done! Radio status: 0x00' in start_msg) or ('LoRa ping pong thread is already running' in start_msg):
            print(Fore.GREEN + '+ LoRa test module initialization done.' + Fore.RESET)
        else:
            print(Fore.RED + '- LoRa test module initialization failed.' + Fore.RESET)
            raise Exception('')

        ser.write('pingpong -start\r\n'.encode('ascii'))
        time.sleep(1)
        start_msg = ser.read_all().decode('ascii')
        print(start_msg)
        if 'Init radio done! Radio status: 0x00' in start_msg:
            print(Fore.GREEN + '+ LoRa module initialization is working.' + Fore.RESET)
        else:
            print(Fore.RED + '- LoRa module initialization is not working.' + Fore.RESET)
            raise Exception('')

        ser.write('pingpong -ping\r\n'.encode('ascii'))
        time.sleep(3)
        response_msg = ser.read_all().decode('ascii')
        if 'payload: 50 4f 4e 47' in response_msg:
            print(Fore.GREEN + '+ LoRa module is working.' + Fore.RESET)
        else:
            print(Fore.RED + '- LoRa module is not working.' + Fore.RESET)
    except:
        print(Fore.RED + '- LoRa module test failed' + Fore.RESET)

    ser.write('pingpong -stop\r\n'.encode('ascii'))
    time.sleep(0.2)
    ser.read_all()



def main():
    init()
    
    baudrate = 115200
    ser = Serial(serial_port, baudrate, timeout=1)

    try:
        test_uart(ser)
        test_leds(ser)
        test_button(ser)
        test_batlevel(ser)
        test_charging(ser)
        test_bme280(ser)
        test_sps30(ser)
        #test_usb_serial(ser)
        test_rtc(ser)
        test_lora(ser)
        test_sdcard(ser)


    finally:
        time.sleep(0.5)
        ser.read_all()
        ser.close()

if __name__ == "__main__":
    main()
