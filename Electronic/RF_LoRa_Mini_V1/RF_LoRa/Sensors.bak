EESchema Schematic File Version 4
LIBS:RF_LoRa-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x05 J?
U 1 1 5E4F6D46
P 5600 2250
F 0 "J?" H 5520 1825 50  0000 C CNN
F 1 "CONN_SPS30" H 5520 1916 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B05B-XH-AM_1x05_P2.50mm_Vertical" H 5600 2250 50  0001 C CNN
F 3 "~" H 5600 2250 50  0001 C CNN
	1    5600 2250
	-1   0    0    1   
$EndComp
Wire Wire Line
	5800 2450 5950 2450
$Comp
L Device:C C?
U 1 1 5E4F6EBB
P 5950 2700
F 0 "C?" H 6065 2746 50  0000 L CNN
F 1 "100nF" H 6065 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 5988 2550 50  0001 C CNN
F 3 "~" H 5950 2700 50  0001 C CNN
	1    5950 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2550 5950 2450
Connection ~ 5950 2450
Wire Wire Line
	5950 2450 6200 2450
Wire Wire Line
	5950 2850 5950 2950
$Comp
L power:GND #PWR?
U 1 1 5E4F716E
P 5950 2950
F 0 "#PWR?" H 5950 2700 50  0001 C CNN
F 1 "GND" H 5955 2777 50  0000 C CNN
F 2 "" H 5950 2950 50  0001 C CNN
F 3 "" H 5950 2950 50  0001 C CNN
	1    5950 2950
	1    0    0    -1  
$EndComp
Text HLabel 6200 2450 2    50   Input ~ 0
+5V
Text HLabel 5950 2350 2    50   BiDi ~ 0
SDA
Text HLabel 5950 2250 2    50   BiDi ~ 0
SCL
Wire Wire Line
	5950 2250 5800 2250
Wire Wire Line
	5800 2350 5950 2350
$Comp
L power:GND #PWR?
U 1 1 5E4F74F0
P 6400 2050
F 0 "#PWR?" H 6400 1800 50  0001 C CNN
F 1 "GND" V 6405 1922 50  0000 R CNN
F 2 "" H 6400 2050 50  0001 C CNN
F 3 "" H 6400 2050 50  0001 C CNN
	1    6400 2050
	0    -1   -1   0   
$EndComp
Text Notes 5500 1750 0    50   ~ 0
Pin 4 com select, \nto GND I2C, floating UART
Wire Wire Line
	5800 2050 6300 2050
$Comp
L Device:R R?
U 1 1 5E449EB3
P 6050 2150
F 0 "R?" V 6100 2350 50  0000 C CNN
F 1 "DNP" V 6200 2400 50  0000 C CNN
F 2 "" V 5980 2150 50  0001 C CNN
F 3 "~" H 6050 2150 50  0001 C CNN
	1    6050 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	6200 2150 6300 2150
Wire Wire Line
	6300 2150 6300 2050
Connection ~ 6300 2050
Wire Wire Line
	6300 2050 6400 2050
Wire Wire Line
	5900 2150 5800 2150
$EndSCHEMATC
