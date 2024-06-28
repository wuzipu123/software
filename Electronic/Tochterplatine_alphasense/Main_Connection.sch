EESchema Schematic File Version 4
LIBS:Tochterplatine_alphasense-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L Interface_UART:MAX13432EESD U?
U 1 1 5D7682BA
P 3550 5800
AR Path="/5D7682BA" Ref="U?"  Part="1" 
AR Path="/5D75A650/5D7682BA" Ref="U3"  Part="1" 
AR Path="/5CF4D87B/5D7682BA" Ref="U3"  Part="1" 
F 0 "U3" H 3300 6450 50  0000 C CNN
F 1 "MAX13432EESD" H 3950 6450 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 3550 4800 50  0001 C CIN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX13430E-MAX13433E.pdf" H 3550 6600 50  0001 C CNN
	1    3550 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5D7682C1
P 5000 6000
AR Path="/5D7682C1" Ref="R?"  Part="1" 
AR Path="/5D75A650/5D7682C1" Ref="R33"  Part="1" 
AR Path="/5CF4D87B/5D7682C1" Ref="R44"  Part="1" 
F 0 "R44" V 5200 5950 50  0000 L CNN
F 1 "120R" V 5100 5900 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4930 6000 50  0001 C CNN
F 3 "~" H 5000 6000 50  0001 C CNN
	1    5000 6000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5D7682C8
P 5000 5500
AR Path="/5D7682C8" Ref="R?"  Part="1" 
AR Path="/5D75A650/5D7682C8" Ref="R32"  Part="1" 
AR Path="/5CF4D87B/5D7682C8" Ref="R43"  Part="1" 
F 0 "R43" V 5200 5450 50  0000 L CNN
F 1 "120R" V 5100 5400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4930 5500 50  0001 C CNN
F 3 "~" H 5000 5500 50  0001 C CNN
	1    5000 5500
	0    -1   -1   0   
$EndComp
Text Label 4250 5900 0    50   ~ 0
RS485_A
Text Label 4250 5400 0    50   ~ 0
RS485_Y
Wire Wire Line
	4850 5500 4850 5400
Wire Wire Line
	5150 5500 5150 5600
Text Label 4250 6100 0    50   ~ 0
RS485_B
Wire Wire Line
	4850 5900 4850 6000
Wire Wire Line
	5150 6000 5150 6100
Text Label 4250 5600 0    50   ~ 0
RS485_Z
$Comp
L power:GND #PWR?
U 1 1 5D7682E2
P 3700 6600
AR Path="/5D7682E2" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D7682E2" Ref="#PWR039"  Part="1" 
AR Path="/5CF4D87B/5D7682E2" Ref="#PWR021"  Part="1" 
F 0 "#PWR021" H 3700 6350 50  0001 C CNN
F 1 "GND" H 3705 6427 50  0000 C CNN
F 2 "" H 3700 6600 50  0001 C CNN
F 3 "" H 3700 6600 50  0001 C CNN
	1    3700 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 6500 3650 6550
Wire Wire Line
	3650 6550 3700 6550
Wire Wire Line
	3750 6550 3750 6500
Wire Wire Line
	3700 6600 3700 6550
Connection ~ 3700 6550
Wire Wire Line
	3700 6550 3750 6550
$Comp
L power:+3.3V #PWR?
U 1 1 5D7682EE
P 3000 4850
AR Path="/5D7682EE" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D7682EE" Ref="#PWR036"  Part="1" 
AR Path="/5CF4D87B/5D7682EE" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 3000 4700 50  0001 C CNN
F 1 "+3.3V" V 3000 5100 50  0000 C CNN
F 2 "" H 3000 4850 50  0001 C CNN
F 3 "" H 3000 4850 50  0001 C CNN
	1    3000 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 5300 3050 5300
$Comp
L power:+5V #PWR?
U 1 1 5D7682F5
P 3550 4850
AR Path="/5D7682F5" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D7682F5" Ref="#PWR038"  Part="1" 
AR Path="/5CF4D87B/5D7682F5" Ref="#PWR020"  Part="1" 
F 0 "#PWR020" H 3550 4700 50  0001 C CNN
F 1 "+5V" H 3565 5023 50  0000 C CNN
F 2 "" H 3550 4850 50  0001 C CNN
F 3 "" H 3550 4850 50  0001 C CNN
	1    3550 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5D7682FB
P 2400 5650
AR Path="/5D7682FB" Ref="R?"  Part="1" 
AR Path="/5D75A650/5D7682FB" Ref="R30"  Part="1" 
AR Path="/5CF4D87B/5D7682FB" Ref="R41"  Part="1" 
F 0 "R41" V 2450 5800 50  0000 L CNN
F 1 "DNP" V 2450 5350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2330 5650 50  0001 C CNN
F 3 "~" H 2400 5650 50  0001 C CNN
	1    2400 5650
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5D768302
P 2400 5800
AR Path="/5D768302" Ref="R?"  Part="1" 
AR Path="/5D75A650/5D768302" Ref="R31"  Part="1" 
AR Path="/5CF4D87B/5D768302" Ref="R42"  Part="1" 
F 0 "R42" V 2350 5950 50  0000 L CNN
F 1 "DNP" V 2350 5500 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2330 5800 50  0001 C CNN
F 3 "~" H 2400 5800 50  0001 C CNN
	1    2400 5800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2700 5650 2700 5700
Connection ~ 2700 5700
Wire Wire Line
	2700 5700 2700 5800
Wire Wire Line
	2250 5650 2100 5650
$Comp
L Device:C C?
U 1 1 5D768312
P 3750 4950
AR Path="/5D768312" Ref="C?"  Part="1" 
AR Path="/5D75A650/5D768312" Ref="C15"  Part="1" 
AR Path="/5CF4D87B/5D768312" Ref="C10"  Part="1" 
F 0 "C10" V 4002 4950 50  0000 C CNN
F 1 "100n" V 3911 4950 50  0000 C CNN
F 2 "Capacitors_SMD:C_0805" H 3788 4800 50  0001 C CNN
F 3 "~" H 3750 4950 50  0001 C CNN
	1    3750 4950
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5D768319
P 2800 4950
AR Path="/5D768319" Ref="C?"  Part="1" 
AR Path="/5D75A650/5D768319" Ref="C13"  Part="1" 
AR Path="/5CF4D87B/5D768319" Ref="C8"  Part="1" 
F 0 "C8" V 3052 4950 50  0000 C CNN
F 1 "100n" V 2961 4950 50  0000 C CNN
F 2 "Capacitors_SMD:C_0805" H 2838 4800 50  0001 C CNN
F 3 "~" H 2800 4950 50  0001 C CNN
	1    2800 4950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3000 4850 3000 4950
Wire Wire Line
	2950 4950 3000 4950
Connection ~ 3000 4950
Wire Wire Line
	3000 4950 3000 5300
Wire Wire Line
	3550 4850 3550 4950
Wire Wire Line
	3600 4950 3550 4950
Connection ~ 3550 4950
Wire Wire Line
	3550 4950 3550 5100
$Comp
L power:GND #PWR?
U 1 1 5D768328
P 2600 4950
AR Path="/5D768328" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D768328" Ref="#PWR034"  Part="1" 
AR Path="/5CF4D87B/5D768328" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 2600 4700 50  0001 C CNN
F 1 "GND" V 2605 4822 50  0000 R CNN
F 2 "" H 2600 4950 50  0001 C CNN
F 3 "" H 2600 4950 50  0001 C CNN
	1    2600 4950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D76832E
P 4000 4950
AR Path="/5D76832E" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D76832E" Ref="#PWR040"  Part="1" 
AR Path="/5CF4D87B/5D76832E" Ref="#PWR022"  Part="1" 
F 0 "#PWR022" H 4000 4700 50  0001 C CNN
F 1 "GND" V 4005 4822 50  0000 R CNN
F 2 "" H 4000 4950 50  0001 C CNN
F 3 "" H 4000 4950 50  0001 C CNN
	1    4000 4950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2600 4950 2650 4950
Wire Wire Line
	3900 4950 4000 4950
Text Notes 1950 4500 2    100  ~ 0
RS485
Text Notes 6550 2550 0    100  ~ 0
DSUB 15 Connector
$Comp
L power:GND #PWR?
U 1 1 5D768340
P 6050 3650
AR Path="/5D768340" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D768340" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D768340" Ref="#PWR042"  Part="1" 
AR Path="/5CF4D87B/5D768340" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 6050 3400 50  0001 C CNN
F 1 "GND" H 6055 3477 50  0000 C CNN
F 2 "" H 6050 3650 50  0001 C CNN
F 3 "" H 6050 3650 50  0001 C CNN
	1    6050 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 4750 5700 4750
Text Label 7400 3150 0    50   ~ 0
Vin_5V
Text Notes 8800 4150 0    50   ~ 0
DSUB 15 \n\nPin 1: VCC\nPin 9: VCC\nPin 2: NC\nPin 10: Control Pin1\nPin 3: Control Pin 0\nPin 11: RS485_Z\nPin 4: RS485_Y\nPin 12: RS485_B\nPin 5: RS485_A\nPin 13: Adr0\nPin 6: Adr1\nPin 14: Adr2\nPin 7: NC\nPin 15: GND\nPin 8: GND\n
Wire Wire Line
	3400 2650 3400 2800
$Comp
L power:GND #PWR?
U 1 1 5D768359
P 3400 2900
AR Path="/5D768359" Ref="#PWR?"  Part="1" 
AR Path="/5D798A2D/5D768359" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D768359" Ref="#PWR037"  Part="1" 
AR Path="/5CF4D87B/5D768359" Ref="#PWR019"  Part="1" 
F 0 "#PWR019" H 3400 2650 50  0001 C CNN
F 1 "GND" H 3405 2727 50  0000 C CNN
F 2 "" H 3400 2900 50  0001 C CNN
F 3 "" H 3400 2900 50  0001 C CNN
	1    3400 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2800 3400 2900
Connection ~ 3400 2800
$Comp
L Device:C C?
U 1 1 5D768361
P 4150 2550
AR Path="/5D768361" Ref="C?"  Part="1" 
AR Path="/5D798A2D/5D768361" Ref="C?"  Part="1" 
AR Path="/5D75A650/5D768361" Ref="C16"  Part="1" 
AR Path="/5CF4D87B/5D768361" Ref="C11"  Part="1" 
F 0 "C11" H 4035 2504 50  0000 R CNN
F 1 "1u" H 4035 2595 50  0000 R CNN
F 2 "Capacitors_SMD:C_0805" H 4188 2400 50  0001 C CNN
F 3 "~" H 4150 2550 50  0001 C CNN
	1    4150 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	4150 2250 4150 2400
$Comp
L Device:C C?
U 1 1 5D768369
P 3750 2550
AR Path="/5D768369" Ref="C?"  Part="1" 
AR Path="/5D798A2D/5D768369" Ref="C?"  Part="1" 
AR Path="/5D75A650/5D768369" Ref="C14"  Part="1" 
AR Path="/5CF4D87B/5D768369" Ref="C9"  Part="1" 
F 0 "C9" H 3635 2504 50  0000 R CNN
F 1 "10n" H 3635 2595 50  0000 R CNN
F 2 "Capacitors_SMD:C_0805" H 3788 2400 50  0001 C CNN
F 3 "~" H 3750 2550 50  0001 C CNN
	1    3750 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	3750 2700 3750 2800
Wire Wire Line
	3400 2800 3750 2800
Wire Wire Line
	4150 2800 4150 2700
Wire Wire Line
	3700 2250 4150 2250
Wire Wire Line
	3100 2250 3000 2250
Wire Wire Line
	3100 2350 3000 2350
Wire Wire Line
	3000 2350 3000 2250
Connection ~ 3000 2250
$Comp
L Device:C C?
U 1 1 5D768378
P 2800 2550
AR Path="/5D768378" Ref="C?"  Part="1" 
AR Path="/5D798A2D/5D768378" Ref="C?"  Part="1" 
AR Path="/5D75A650/5D768378" Ref="C12"  Part="1" 
AR Path="/5CF4D87B/5D768378" Ref="C7"  Part="1" 
F 0 "C7" H 2685 2504 50  0000 R CNN
F 1 "1u" H 2685 2595 50  0000 R CNN
F 2 "Capacitors_SMD:C_0805" H 2838 2400 50  0001 C CNN
F 3 "~" H 2800 2550 50  0001 C CNN
	1    2800 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	2800 2250 2800 2400
Wire Wire Line
	2800 2250 3000 2250
Wire Wire Line
	2800 2700 2800 2800
Wire Wire Line
	2800 2800 3400 2800
$Comp
L Regulator_Linear:LDK130-33_SOT23_SOT353 U?
U 1 1 5D768383
P 3400 2350
AR Path="/5D768383" Ref="U?"  Part="1" 
AR Path="/5D798A2D/5D768383" Ref="U?"  Part="1" 
AR Path="/5D75A650/5D768383" Ref="U2"  Part="1" 
AR Path="/5CF4D87B/5D768383" Ref="U2"  Part="1" 
F 0 "U2" H 3500 2700 50  0000 C CNN
F 1 "LDK130-33_SOT23_SOT353" H 3500 2600 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5_HandSoldering" H 3400 2675 50  0001 C CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/29/10/f7/87/2f/66/47/f4/DM00076097.pdf/files/DM00076097.pdf/jcr:content/translations/en.DM00076097.pdf" H 3400 2350 50  0001 C CNN
	1    3400 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5D76838A
P 4150 2100
AR Path="/5D76838A" Ref="#PWR?"  Part="1" 
AR Path="/5D798A2D/5D76838A" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D76838A" Ref="#PWR041"  Part="1" 
AR Path="/5CF4D87B/5D76838A" Ref="#PWR023"  Part="1" 
F 0 "#PWR023" H 4150 1950 50  0001 C CNN
F 1 "+3.3V" H 4165 2273 50  0000 C CNN
F 2 "" H 4150 2100 50  0001 C CNN
F 3 "" H 4150 2100 50  0001 C CNN
	1    4150 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2250 4150 2100
Connection ~ 2800 2250
Text Label 2600 2250 2    50   ~ 0
Vin_5V
$Comp
L power:+5V #PWR?
U 1 1 5D768393
P 2800 2100
AR Path="/5D768393" Ref="#PWR?"  Part="1" 
AR Path="/5D798A2D/5D768393" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D768393" Ref="#PWR035"  Part="1" 
AR Path="/5CF4D87B/5D768393" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 2800 1950 50  0001 C CNN
F 1 "+5V" H 2815 2273 50  0000 C CNN
F 2 "" H 2800 2100 50  0001 C CNN
F 3 "" H 2800 2100 50  0001 C CNN
	1    2800 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2250 2800 2100
Wire Wire Line
	2800 2250 2600 2250
Connection ~ 3750 2800
Wire Wire Line
	3750 2800 4150 2800
Wire Wire Line
	3700 2350 3750 2350
Wire Wire Line
	3750 2350 3750 2400
Connection ~ 4150 2250
Text Notes 1500 2350 0    100  ~ 0
Power \nSupply
Text HLabel 5700 4750 0    50   Input ~ 0
CP0
Text HLabel 7400 4750 2    50   Input ~ 0
CP1
Wire Wire Line
	4050 5600 5150 5600
Wire Wire Line
	4050 5400 4850 5400
Wire Wire Line
	4050 5900 4850 5900
Wire Wire Line
	4050 6100 5150 6100
Wire Wire Line
	2100 5500 3050 5500
Wire Wire Line
	2700 5700 2900 5700
Wire Wire Line
	2700 5650 2550 5650
Wire Wire Line
	2700 5800 2550 5800
Text HLabel 2100 5500 0    50   Input ~ 0
UART3_Rx
Text HLabel 2100 5650 0    50   Input ~ 0
UART3_RE
Text HLabel 2700 6000 0    50   Input ~ 0
UART3_Tx
Text HLabel 2100 6000 0    50   Input ~ 0
UART3_DE
Text Label 5700 3850 2    50   ~ 0
RS485_A
Text Label 5700 3950 2    50   ~ 0
RS485_B
Text Label 5700 4150 2    50   ~ 0
RS485_Y
Text Label 5700 4050 2    50   ~ 0
RS485_Z
Wire Wire Line
	2700 6000 3050 6000
Wire Wire Line
	2250 5800 2100 5800
Wire Wire Line
	2100 5800 2100 6200
Wire Wire Line
	2100 6200 2700 6200
Wire Wire Line
	7050 4750 7400 4750
Wire Wire Line
	6050 4150 5700 4150
Wire Wire Line
	6050 4050 5700 4050
Wire Wire Line
	6050 3850 5700 3850
Wire Wire Line
	6050 3950 5700 3950
Text HLabel 5700 3450 0    50   Output ~ 0
Adr2
Text HLabel 5700 3350 0    50   Output ~ 0
Adr1
Text HLabel 5700 3250 0    50   Output ~ 0
Adr0
Wire Wire Line
	6050 3350 5700 3350
Wire Wire Line
	6050 3250 5700 3250
$Comp
L Device:R R?
U 1 1 5CFFEECC
P 2900 6450
AR Path="/5CFFEECC" Ref="R?"  Part="1" 
AR Path="/5D75A650/5CFFEECC" Ref="R?"  Part="1" 
AR Path="/5CF4D87B/5CFFEECC" Ref="R8"  Part="1" 
F 0 "R8" V 2800 6350 50  0000 L CNN
F 1 "10k" V 2900 6400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2830 6450 50  0001 C CNN
F 3 "~" H 2900 6450 50  0001 C CNN
	1    2900 6450
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5D000705
P 2700 6450
AR Path="/5D000705" Ref="R?"  Part="1" 
AR Path="/5D75A650/5D000705" Ref="R?"  Part="1" 
AR Path="/5CF4D87B/5D000705" Ref="R7"  Part="1" 
F 0 "R7" V 2600 6350 50  0000 L CNN
F 1 "DNP" V 2700 6400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2630 6450 50  0001 C CNN
F 3 "~" H 2700 6450 50  0001 C CNN
	1    2700 6450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2900 6300 2900 5700
Connection ~ 2900 5700
Wire Wire Line
	2900 5700 3050 5700
Wire Wire Line
	2700 6300 2700 6200
Connection ~ 2700 6200
Wire Wire Line
	2700 6200 3050 6200
$Comp
L power:GND #PWR?
U 1 1 5D0034D4
P 2800 6700
AR Path="/5D0034D4" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D0034D4" Ref="#PWR?"  Part="1" 
AR Path="/5CF4D87B/5D0034D4" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 2800 6450 50  0001 C CNN
F 1 "GND" H 2805 6527 50  0000 C CNN
F 2 "" H 2800 6700 50  0001 C CNN
F 3 "" H 2800 6700 50  0001 C CNN
	1    2800 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 6600 2700 6650
Wire Wire Line
	2700 6650 2800 6650
Wire Wire Line
	2800 6650 2800 6700
Wire Wire Line
	2900 6600 2900 6650
Wire Wire Line
	2900 6650 2800 6650
Connection ~ 2800 6650
$Comp
L samtec_pci:PCIE-064-02-F-D-TH-tochter J4
U 2 1 5D21529E
P 6550 3950
F 0 "J4" H 6550 5017 50  0000 C CNN
F 1 "PCIE-064-02-F-D-TH-tochter" H 6550 4926 50  0000 C CNN
F 2 "samtec_pci:SAMTEC_PCIE_064-02-F-D-TH-Tochter" H 5950 4950 50  0001 L BNN
F 3 "" H 6550 3950 50  0001 L BNN
	2    6550 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 3150 7400 3150
Text Label 5700 3150 2    50   ~ 0
Vin_5V
Wire Wire Line
	6050 3150 5700 3150
$Comp
L power:GND #PWR?
U 1 1 5D276482
P 7050 3550
AR Path="/5D276482" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D276482" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D276482" Ref="#PWR?"  Part="1" 
AR Path="/5CF4D87B/5D276482" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 7050 3300 50  0001 C CNN
F 1 "GND" H 7055 3377 50  0000 C CNN
F 2 "" H 7050 3550 50  0001 C CNN
F 3 "" H 7050 3550 50  0001 C CNN
	1    7050 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5700 3450 6050 3450
Wire Wire Line
	6050 3550 6050 3650
Connection ~ 6050 3650
Wire Wire Line
	7050 3450 7050 3550
Connection ~ 7050 3550
Text Notes 5200 5850 0    50   ~ 0
Buslabels from Mainboard\nhave to be crossed out for\nrecieve/transmitt directions
$EndSCHEMATC
