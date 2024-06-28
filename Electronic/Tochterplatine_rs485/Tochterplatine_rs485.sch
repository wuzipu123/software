EESchema Schematic File Version 4
EELAYER 29 0
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
Text Notes 2800 2850 0    100  ~ 0
PCIE64 Connector
$Comp
L power:GND #PWR0101
U 1 1 5D9F96B4
P 3200 3800
AR Path="/5D9F96B4" Ref="#PWR0101"  Part="1" 
AR Path="/5CB6FAF3/5D9F96B4" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D9F96B4" Ref="#PWR?"  Part="1" 
AR Path="/5CF4D87B/5D9F96B4" Ref="#PWR?"  Part="1" 
F 0 "#PWR0101" H 3200 3550 50  0001 C CNN
F 1 "GND" H 3205 3627 50  0000 C CNN
F 2 "" H 3200 3800 50  0001 C CNN
F 3 "" H 3200 3800 50  0001 C CNN
	1    3200 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	3200 4900 2850 4900
Text Label 4550 3300 0    50   ~ 0
Vin_5V
Text HLabel 2850 4900 0    50   Input ~ 0
CP0
Text HLabel 4550 4900 2    50   Input ~ 0
CP1
Text Label 2850 4000 2    50   ~ 0
RS485_A
Text Label 2850 4100 2    50   ~ 0
RS485_B
Text Label 2850 4300 2    50   ~ 0
RS485_Y
Text Label 2850 4200 2    50   ~ 0
RS485_Z
Wire Wire Line
	4200 4900 4550 4900
Wire Wire Line
	3200 4300 2850 4300
Wire Wire Line
	3200 4200 2850 4200
Wire Wire Line
	3200 4000 2850 4000
Wire Wire Line
	3200 4100 2850 4100
Text HLabel 2850 3600 0    50   Output ~ 0
Adr2
Text HLabel 2850 3500 0    50   Output ~ 0
Adr1
Text HLabel 2850 3400 0    50   Output ~ 0
Adr0
Wire Wire Line
	3200 3500 2850 3500
Wire Wire Line
	3200 3400 2850 3400
$Comp
L samtec_pci:PCIE-064-02-F-D-TH-tochter J?
U 2 1 5D9F96CC
P 3700 4100
AR Path="/5CF4D87B/5D9F96CC" Ref="J?"  Part="2" 
AR Path="/5D9F96CC" Ref="J1"  Part="2" 
F 0 "J1" H 3700 5167 50  0000 C CNN
F 1 "PCIE-064-02-F-D-TH-tochter" H 3700 5076 50  0000 C CNN
F 2 "samtec_pci:SAMTEC_PCIE_064-02-F-D-TH-Tochter" H 3100 5100 50  0001 L BNN
F 3 "" H 3700 4100 50  0001 L BNN
	2    3700 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3300 4550 3300
Text Label 2850 3300 2    50   ~ 0
Vin_5V
Wire Wire Line
	3200 3300 2850 3300
$Comp
L power:GND #PWR0102
U 1 1 5D9F96D5
P 4200 3700
AR Path="/5D9F96D5" Ref="#PWR0102"  Part="1" 
AR Path="/5CB6FAF3/5D9F96D5" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D9F96D5" Ref="#PWR?"  Part="1" 
AR Path="/5CF4D87B/5D9F96D5" Ref="#PWR?"  Part="1" 
F 0 "#PWR0102" H 4200 3450 50  0001 C CNN
F 1 "GND" H 4205 3527 50  0000 C CNN
F 2 "" H 4200 3700 50  0001 C CNN
F 3 "" H 4200 3700 50  0001 C CNN
	1    4200 3700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2850 3600 3200 3600
Wire Wire Line
	3200 3700 3200 3800
Connection ~ 3200 3800
Wire Wire Line
	4200 3600 4200 3700
Connection ~ 4200 3700
Text Label 5700 3400 2    50   ~ 0
Vin_5V
$Comp
L power:GND #PWR0103
U 1 1 5DA1FC68
P 5700 4400
AR Path="/5DA1FC68" Ref="#PWR0103"  Part="1" 
AR Path="/5CB6FAF3/5DA1FC68" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5DA1FC68" Ref="#PWR?"  Part="1" 
AR Path="/5CF4D87B/5DA1FC68" Ref="#PWR?"  Part="1" 
F 0 "#PWR0103" H 5700 4150 50  0001 C CNN
F 1 "GND" H 5705 4227 50  0000 C CNN
F 2 "" H 5700 4400 50  0001 C CNN
F 3 "" H 5700 4400 50  0001 C CNN
	1    5700 4400
	1    0    0    -1  
$EndComp
Text HLabel 5700 4200 0    50   Input ~ 0
CP0
Text HLabel 5700 4300 0    50   Input ~ 0
CP1
Text Label 5700 3500 2    50   ~ 0
RS485_A
Text Label 5700 3600 2    50   ~ 0
RS485_B
Text Label 5700 3800 2    50   ~ 0
RS485_Y
Text Label 5700 3700 2    50   ~ 0
RS485_Z
Text HLabel 5700 3900 0    50   Output ~ 0
Adr2
Text HLabel 5700 4000 0    50   Output ~ 0
Adr1
Text HLabel 5700 4100 0    50   Output ~ 0
Adr0
$Comp
L Connector:Conn_01x11_Male J2
U 1 1 5DA21663
P 5900 3900
F 0 "J2" H 5872 3924 50  0000 R CNN
F 1 "Conn_01x11_Male" H 5872 3833 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x11_P2.54mm_Horizontal" H 5900 3900 50  0001 C CNN
F 3 "~" H 5900 3900 50  0001 C CNN
	1    5900 3900
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
