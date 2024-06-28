EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Connector:Conn_01x05_Female J?
U 1 1 5DE9D921
P 1550 2000
F 0 "J?" V 1700 2000 50  0000 C CNN
F 1 "Conn_01x05_Female" V 1600 2000 50  0000 C CNN
F 2 "" H 1550 2000 50  0001 C CNN
F 3 "~" H 1550 2000 50  0001 C CNN
	1    1550 2000
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Female J?
U 1 1 5DE9D9DA
P 4850 2100
F 0 "J?" V 4900 2050 50  0000 L CNN
F 1 "Conn_01x08_Female" V 5000 1700 50  0000 L CNN
F 2 "" H 4850 2100 50  0001 C CNN
F 3 "~" H 4850 2100 50  0001 C CNN
	1    4850 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Hirose:hirose_conn_male_female_12pin U?
U 1 1 5DE9E0BF
P 3300 2350
F 0 "U?" V 3250 2350 50  0000 C CNN
F 1 "hirose_conn_male_female_12pin" V 3350 2350 50  0000 C CNN
F 2 "" H 3300 2350 50  0001 C CNN
F 3 "" H 3300 2350 50  0001 C CNN
	1    3300 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1800 2400 1800
Wire Wire Line
	2400 1800 2400 2800
Wire Wire Line
	2400 2800 3100 2800
Wire Wire Line
	3500 2800 4100 2800
Wire Wire Line
	4100 2800 4100 1800
Wire Wire Line
	4100 1800 4650 1800
Wire Wire Line
	1750 1900 2450 1900
Wire Wire Line
	2450 1900 2450 2400
Wire Wire Line
	2450 2400 3100 2400
Wire Wire Line
	3500 2400 4650 2400
Wire Wire Line
	3500 2100 4000 2100
Wire Wire Line
	3500 1800 4050 1800
Wire Wire Line
	2550 2000 2550 2100
Wire Wire Line
	1750 2000 2550 2000
Wire Wire Line
	2550 2100 3100 2100
Wire Wire Line
	2500 2100 2500 1800
Wire Wire Line
	1750 2100 2500 2100
Wire Wire Line
	2500 1800 3100 1800
Wire Wire Line
	4000 2300 4000 2100
Wire Wire Line
	4000 2300 4650 2300
Wire Wire Line
	4050 1800 4050 2100
Wire Wire Line
	4050 2100 4650 2100
Wire Wire Line
	1750 2200 2500 2200
Wire Wire Line
	2500 2200 2500 2600
Wire Wire Line
	2500 2600 3100 2600
Wire Wire Line
	3500 2600 4050 2600
Wire Wire Line
	4050 2600 4050 2500
Wire Wire Line
	4050 2500 4650 2500
Text Label 1750 1800 0    50   ~ 0
VDD
Text Label 1750 1900 0    50   ~ 0
SDA
Text Label 1750 2000 0    50   ~ 0
SCL
Text Label 1750 2100 0    50   ~ 0
GND*
Text Label 1750 2200 0    50   ~ 0
GND
Text Label 4650 1800 2    50   ~ 0
+5V
Text Label 4650 2100 2    50   ~ 0
GND*
Text Label 4650 2300 2    50   ~ 0
SCL
Text Label 4650 2400 2    50   ~ 0
SDA
Text Label 4650 2500 2    50   ~ 0
GND
Text Label 3100 1800 2    50   ~ 0
orange
Text Label 3500 1800 0    50   ~ 0
black
Text Label 3100 2100 2    50   ~ 0
blue
Text Label 3500 2100 0    50   ~ 0
green
Text Label 3500 2400 0    50   ~ 0
green
Text Label 3100 2400 2    50   ~ 0
white_(grey)
Text Label 3100 2600 2    50   ~ 0
white_(orange)
Text Label 3500 2600 0    50   ~ 0
black
Text Label 3100 2800 2    50   ~ 0
red
Text Label 3500 2800 0    50   ~ 0
red
NoConn ~ 4650 1900
NoConn ~ 4650 2000
NoConn ~ 4650 2200
NoConn ~ 3500 1900
NoConn ~ 3500 2000
NoConn ~ 3100 2000
NoConn ~ 3100 1900
NoConn ~ 3100 2200
NoConn ~ 3100 2300
NoConn ~ 3500 2300
NoConn ~ 3500 2200
NoConn ~ 3500 2500
NoConn ~ 3100 2500
NoConn ~ 3100 2700
NoConn ~ 3500 2700
NoConn ~ 3500 2900
NoConn ~ 3100 2900
Text Notes 3150 1650 0    50   ~ 0
Housing
Text Notes 4700 1650 0    50   ~ 0
PCB
Text Notes 1550 1650 0    50   ~ 0
Sensor
Text Notes 3150 1400 0    71   ~ 14
SPS30
Text Notes 7950 1400 0    71   ~ 14
OPC-N3
$Comp
L Connector_Hirose:hirose_conn_male_female_12pin U?
U 1 1 5DEA45E6
P 8150 2350
F 0 "U?" V 8100 2350 50  0000 C CNN
F 1 "hirose_conn_male_female_12pin" V 8200 2350 50  0000 C CNN
F 2 "" H 8150 2350 50  0001 C CNN
F 3 "" H 8150 2350 50  0001 C CNN
	1    8150 2350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Female J?
U 1 1 5DEA463E
P 9850 2100
F 0 "J?" V 9900 2050 50  0000 L CNN
F 1 "Conn_01x08_Female" V 10000 1700 50  0000 L CNN
F 2 "" H 9850 2100 50  0001 C CNN
F 3 "~" H 9850 2100 50  0001 C CNN
	1    9850 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Female J?
U 1 1 5DEA46AB
P 6200 2000
F 0 "J?" V 6350 2000 50  0000 C CNN
F 1 "Conn_01x06_Female" V 6250 2000 50  0000 C CNN
F 2 "" H 6200 2000 50  0001 C CNN
F 3 "~" H 6200 2000 50  0001 C CNN
	1    6200 2000
	-1   0    0    -1  
$EndComp
Text Notes 6200 1650 0    50   ~ 0
Sensor
Text Notes 8000 1650 0    50   ~ 0
Housing
Text Notes 9650 1650 0    50   ~ 0
PCB
Wire Wire Line
	6400 1800 7200 1800
Wire Wire Line
	7200 1800 7200 2800
Wire Wire Line
	7200 2800 7950 2800
Wire Wire Line
	8350 2800 9000 2800
Wire Wire Line
	9000 2800 9000 1800
Wire Wire Line
	9000 1800 9650 1800
Wire Wire Line
	6400 1900 7250 1900
Wire Wire Line
	7250 1900 7250 2500
Wire Wire Line
	7250 2500 7950 2500
Wire Wire Line
	8350 2500 8950 2500
Wire Wire Line
	8950 2500 8950 1900
Wire Wire Line
	8950 1900 9650 1900
Wire Wire Line
	6400 2000 7950 2000
Wire Wire Line
	8350 2000 9650 2000
Wire Wire Line
	6400 2100 7950 2100
Wire Wire Line
	8350 2100 9650 2100
Wire Wire Line
	6400 2200 7300 2200
Wire Wire Line
	7300 2200 7300 1900
Wire Wire Line
	7300 1900 7950 1900
Wire Wire Line
	8350 1900 8900 1900
Wire Wire Line
	8900 1900 8900 2200
Wire Wire Line
	8900 2200 9650 2200
Wire Wire Line
	6400 2300 7300 2300
Wire Wire Line
	7300 2300 7300 2600
Wire Wire Line
	7300 2600 7950 2600
Wire Wire Line
	8350 2600 8900 2600
Wire Wire Line
	8900 2600 8900 2300
Wire Wire Line
	8900 2300 9650 2300
Text Label 6400 1800 0    50   ~ 0
V_In
Text Label 6400 1900 0    50   ~ 0
SCK
Text Label 6400 2000 0    50   ~ 0
SDO
Text Label 6400 2100 0    50   ~ 0
SDI
Text Label 6400 2200 0    50   ~ 0
NSS
Text Label 6400 2300 0    50   ~ 0
GND
Text Label 9650 2300 2    50   ~ 0
GND
Text Label 9650 2200 2    50   ~ 0
NSS
Text Label 9650 2100 2    50   ~ 0
MOSI
Text Label 9650 2000 2    50   ~ 0
MISO
Text Label 9650 1900 2    50   ~ 0
SCK
Text Label 9650 1800 2    50   ~ 0
+5V
NoConn ~ 8350 1800
NoConn ~ 7950 1800
NoConn ~ 9650 2400
NoConn ~ 9650 2500
NoConn ~ 8350 2200
NoConn ~ 8350 2300
NoConn ~ 8350 2400
NoConn ~ 7950 2400
NoConn ~ 7950 2300
NoConn ~ 7950 2200
NoConn ~ 7950 2700
NoConn ~ 8350 2700
NoConn ~ 8350 2900
NoConn ~ 7950 2900
Text Label 7950 1900 2    50   ~ 0
yellow
Text Label 7950 2000 2    50   ~ 0
green
Text Label 7950 2100 2    50   ~ 0
blue
Text Label 7950 2500 2    50   ~ 0
white_(middle)
Text Label 7950 2600 2    50   ~ 0
white_(orange)
Text Label 7950 2800 2    50   ~ 0
red
Text Label 8350 2800 0    50   ~ 0
red
Text Label 8350 2600 0    50   ~ 0
black
Text Label 8350 2500 0    50   ~ 0
green
Text Label 8350 2100 0    50   ~ 0
green
Text Label 8350 2000 0    50   ~ 0
green
Text Label 8350 1900 0    50   ~ 0
green
$EndSCHEMATC
