EESchema Schematic File Version 4
LIBS:Tochterplatine_BME280-cache
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
P 8150 4100
AR Path="/5D7682BA" Ref="U?"  Part="1" 
AR Path="/5D75A650/5D7682BA" Ref="U3"  Part="1" 
AR Path="/5CF4D87B/5D7682BA" Ref="U3"  Part="1" 
F 0 "U3" H 7900 4750 50  0000 C CNN
F 1 "MAX13432EESD" H 8550 4750 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 8150 3100 50  0001 C CIN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX13430E-MAX13433E.pdf" H 8150 4900 50  0001 C CNN
	1    8150 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5D7682C1
P 9600 4300
AR Path="/5D7682C1" Ref="R?"  Part="1" 
AR Path="/5D75A650/5D7682C1" Ref="R33"  Part="1" 
AR Path="/5CF4D87B/5D7682C1" Ref="R44"  Part="1" 
F 0 "R44" V 9800 4250 50  0000 L CNN
F 1 "120R" V 9700 4200 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9530 4300 50  0001 C CNN
F 3 "~" H 9600 4300 50  0001 C CNN
	1    9600 4300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5D7682C8
P 9600 3800
AR Path="/5D7682C8" Ref="R?"  Part="1" 
AR Path="/5D75A650/5D7682C8" Ref="R32"  Part="1" 
AR Path="/5CF4D87B/5D7682C8" Ref="R43"  Part="1" 
F 0 "R43" V 9800 3750 50  0000 L CNN
F 1 "120R" V 9700 3700 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9530 3800 50  0001 C CNN
F 3 "~" H 9600 3800 50  0001 C CNN
	1    9600 3800
	0    -1   -1   0   
$EndComp
Text Label 8850 4200 0    50   ~ 0
RS485_A
Text Label 8850 3700 0    50   ~ 0
RS485_Y
Wire Wire Line
	9450 3800 9450 3700
Wire Wire Line
	9750 3800 9750 3900
Text Label 8850 4400 0    50   ~ 0
RS485_B
Wire Wire Line
	9450 4200 9450 4300
Wire Wire Line
	9750 4300 9750 4400
Text Label 8850 3900 0    50   ~ 0
RS485_Z
$Comp
L power:GND #PWR?
U 1 1 5D7682E2
P 8300 4900
AR Path="/5D7682E2" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D7682E2" Ref="#PWR039"  Part="1" 
AR Path="/5CF4D87B/5D7682E2" Ref="#PWR021"  Part="1" 
F 0 "#PWR021" H 8300 4650 50  0001 C CNN
F 1 "GND" H 8305 4727 50  0000 C CNN
F 2 "" H 8300 4900 50  0001 C CNN
F 3 "" H 8300 4900 50  0001 C CNN
	1    8300 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 4800 8250 4850
Wire Wire Line
	8250 4850 8300 4850
Wire Wire Line
	8350 4850 8350 4800
Wire Wire Line
	8300 4900 8300 4850
Connection ~ 8300 4850
Wire Wire Line
	8300 4850 8350 4850
$Comp
L power:+3.3V #PWR?
U 1 1 5D7682EE
P 7600 3150
AR Path="/5D7682EE" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D7682EE" Ref="#PWR036"  Part="1" 
AR Path="/5CF4D87B/5D7682EE" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 7600 3000 50  0001 C CNN
F 1 "+3.3V" V 7600 3400 50  0000 C CNN
F 2 "" H 7600 3150 50  0001 C CNN
F 3 "" H 7600 3150 50  0001 C CNN
	1    7600 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 3600 7650 3600
$Comp
L power:+5V #PWR?
U 1 1 5D7682F5
P 8150 3150
AR Path="/5D7682F5" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D7682F5" Ref="#PWR038"  Part="1" 
AR Path="/5CF4D87B/5D7682F5" Ref="#PWR020"  Part="1" 
F 0 "#PWR020" H 8150 3000 50  0001 C CNN
F 1 "+5V" H 8165 3323 50  0000 C CNN
F 2 "" H 8150 3150 50  0001 C CNN
F 3 "" H 8150 3150 50  0001 C CNN
	1    8150 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5D7682FB
P 7000 3950
AR Path="/5D7682FB" Ref="R?"  Part="1" 
AR Path="/5D75A650/5D7682FB" Ref="R30"  Part="1" 
AR Path="/5CF4D87B/5D7682FB" Ref="R41"  Part="1" 
F 0 "R41" V 7050 4100 50  0000 L CNN
F 1 "DNP" V 7050 3650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6930 3950 50  0001 C CNN
F 3 "~" H 7000 3950 50  0001 C CNN
	1    7000 3950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5D768302
P 7000 4100
AR Path="/5D768302" Ref="R?"  Part="1" 
AR Path="/5D75A650/5D768302" Ref="R31"  Part="1" 
AR Path="/5CF4D87B/5D768302" Ref="R42"  Part="1" 
F 0 "R42" V 6950 4250 50  0000 L CNN
F 1 "DNP" V 6950 3800 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6930 4100 50  0001 C CNN
F 3 "~" H 7000 4100 50  0001 C CNN
	1    7000 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7300 3950 7300 4000
Connection ~ 7300 4000
Wire Wire Line
	7300 4000 7300 4100
Wire Wire Line
	6850 3950 6700 3950
$Comp
L Device:C C?
U 1 1 5D768312
P 8350 3250
AR Path="/5D768312" Ref="C?"  Part="1" 
AR Path="/5D75A650/5D768312" Ref="C15"  Part="1" 
AR Path="/5CF4D87B/5D768312" Ref="C10"  Part="1" 
F 0 "C10" V 8602 3250 50  0000 C CNN
F 1 "100n" V 8511 3250 50  0000 C CNN
F 2 "Capacitors_SMD:C_0805" H 8388 3100 50  0001 C CNN
F 3 "~" H 8350 3250 50  0001 C CNN
	1    8350 3250
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5D768319
P 7400 3250
AR Path="/5D768319" Ref="C?"  Part="1" 
AR Path="/5D75A650/5D768319" Ref="C13"  Part="1" 
AR Path="/5CF4D87B/5D768319" Ref="C8"  Part="1" 
F 0 "C8" V 7652 3250 50  0000 C CNN
F 1 "100n" V 7561 3250 50  0000 C CNN
F 2 "Capacitors_SMD:C_0805" H 7438 3100 50  0001 C CNN
F 3 "~" H 7400 3250 50  0001 C CNN
	1    7400 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7600 3150 7600 3250
Wire Wire Line
	7550 3250 7600 3250
Connection ~ 7600 3250
Wire Wire Line
	7600 3250 7600 3600
Wire Wire Line
	8150 3150 8150 3250
Wire Wire Line
	8200 3250 8150 3250
Connection ~ 8150 3250
Wire Wire Line
	8150 3250 8150 3400
$Comp
L power:GND #PWR?
U 1 1 5D768328
P 7200 3250
AR Path="/5D768328" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D768328" Ref="#PWR034"  Part="1" 
AR Path="/5CF4D87B/5D768328" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 7200 3000 50  0001 C CNN
F 1 "GND" V 7205 3122 50  0000 R CNN
F 2 "" H 7200 3250 50  0001 C CNN
F 3 "" H 7200 3250 50  0001 C CNN
	1    7200 3250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D76832E
P 8600 3250
AR Path="/5D76832E" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D76832E" Ref="#PWR040"  Part="1" 
AR Path="/5CF4D87B/5D76832E" Ref="#PWR022"  Part="1" 
F 0 "#PWR022" H 8600 3000 50  0001 C CNN
F 1 "GND" V 8605 3122 50  0000 R CNN
F 2 "" H 8600 3250 50  0001 C CNN
F 3 "" H 8600 3250 50  0001 C CNN
	1    8600 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7200 3250 7250 3250
Wire Wire Line
	8500 3250 8600 3250
Text Notes 6550 2800 2    100  ~ 0
RS485
Text Label 8150 1150 2    50   ~ 0
Vin_5V
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
Text HLabel 8150 2050 0    50   Input ~ 0
CP0
Text HLabel 8150 1950 0    50   Input ~ 0
CP1
Wire Wire Line
	8650 3900 9750 3900
Wire Wire Line
	8650 3700 9450 3700
Wire Wire Line
	8650 4200 9450 4200
Wire Wire Line
	8650 4400 9750 4400
Wire Wire Line
	6700 3800 7650 3800
Wire Wire Line
	7300 4000 7500 4000
Wire Wire Line
	7300 3950 7150 3950
Wire Wire Line
	7300 4100 7150 4100
Text HLabel 6700 3800 0    50   Input ~ 0
UART3_Rx
Text HLabel 6700 3950 0    50   Input ~ 0
UART3_RE
Text HLabel 7300 4300 0    50   Input ~ 0
UART3_Tx
Text HLabel 6700 4300 0    50   Input ~ 0
UART3_DE
Text Label 8150 1250 2    50   ~ 0
RS485_A
Text Label 8150 1350 2    50   ~ 0
RS485_B
Text Label 8150 1550 2    50   ~ 0
RS485_Y
Text Label 8150 1450 2    50   ~ 0
RS485_Z
Wire Wire Line
	7300 4300 7650 4300
Wire Wire Line
	6850 4100 6700 4100
Wire Wire Line
	6700 4100 6700 4500
Wire Wire Line
	6700 4500 7300 4500
Text HLabel 8150 1650 0    50   Output ~ 0
Adr2
Text HLabel 8150 1750 0    50   Output ~ 0
Adr1
Text HLabel 8150 1850 0    50   Output ~ 0
Adr0
$Comp
L Device:R R?
U 1 1 5CFFEECC
P 7500 4750
AR Path="/5CFFEECC" Ref="R?"  Part="1" 
AR Path="/5D75A650/5CFFEECC" Ref="R?"  Part="1" 
AR Path="/5CF4D87B/5CFFEECC" Ref="R8"  Part="1" 
F 0 "R8" V 7400 4650 50  0000 L CNN
F 1 "10k" V 7500 4700 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7430 4750 50  0001 C CNN
F 3 "~" H 7500 4750 50  0001 C CNN
	1    7500 4750
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5D000705
P 7300 4750
AR Path="/5D000705" Ref="R?"  Part="1" 
AR Path="/5D75A650/5D000705" Ref="R?"  Part="1" 
AR Path="/5CF4D87B/5D000705" Ref="R7"  Part="1" 
F 0 "R7" V 7200 4650 50  0000 L CNN
F 1 "DNP" V 7300 4700 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7230 4750 50  0001 C CNN
F 3 "~" H 7300 4750 50  0001 C CNN
	1    7300 4750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7500 4600 7500 4000
Connection ~ 7500 4000
Wire Wire Line
	7500 4000 7650 4000
Wire Wire Line
	7300 4600 7300 4500
Connection ~ 7300 4500
Wire Wire Line
	7300 4500 7650 4500
$Comp
L power:GND #PWR?
U 1 1 5D0034D4
P 7400 5000
AR Path="/5D0034D4" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D0034D4" Ref="#PWR?"  Part="1" 
AR Path="/5CF4D87B/5D0034D4" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 7400 4750 50  0001 C CNN
F 1 "GND" H 7405 4827 50  0000 C CNN
F 2 "" H 7400 5000 50  0001 C CNN
F 3 "" H 7400 5000 50  0001 C CNN
	1    7400 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 4900 7300 4950
Wire Wire Line
	7300 4950 7400 4950
Wire Wire Line
	7400 4950 7400 5000
Wire Wire Line
	7500 4900 7500 4950
Wire Wire Line
	7500 4950 7400 4950
Connection ~ 7400 4950
$Comp
L power:GND #PWR?
U 1 1 5D276482
P 8100 2200
AR Path="/5D276482" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D276482" Ref="#PWR?"  Part="1" 
AR Path="/5D75A650/5D276482" Ref="#PWR?"  Part="1" 
AR Path="/5CF4D87B/5D276482" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 8100 1950 50  0001 C CNN
F 1 "GND" H 8105 2027 50  0000 C CNN
F 2 "" H 8100 2200 50  0001 C CNN
F 3 "" H 8100 2200 50  0001 C CNN
	1    8100 2200
	1    0    0    -1  
$EndComp
Text Notes 9800 4150 0    50   ~ 0
Buslabels from Mainboard\nhave to be crossed out for\nrecieve/transmitt directions
$Comp
L Connector_Generic:Conn_01x11 J4
U 1 1 5DF4C8A4
P 8500 1650
F 0 "J4" H 8580 1692 50  0000 L CNN
F 1 "Conn_01x11" H 8580 1601 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x11_P2.54mm_Vertical" H 8500 1650 50  0001 C CNN
F 3 "~" H 8500 1650 50  0001 C CNN
	1    8500 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 1150 8300 1150
Wire Wire Line
	8150 1250 8300 1250
Wire Wire Line
	8150 1350 8300 1350
Wire Wire Line
	8150 1450 8300 1450
Wire Wire Line
	8150 1550 8300 1550
Wire Wire Line
	8150 1650 8300 1650
Wire Wire Line
	8150 1750 8300 1750
Wire Wire Line
	8150 1850 8300 1850
Wire Wire Line
	8150 1950 8300 1950
Wire Wire Line
	8150 2050 8300 2050
Wire Wire Line
	8300 2150 8100 2150
Wire Wire Line
	8100 2150 8100 2200
$EndSCHEMATC
