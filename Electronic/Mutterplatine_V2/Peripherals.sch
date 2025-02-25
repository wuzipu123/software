EESchema Schematic File Version 4
LIBS:Mutterplatine-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
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
L Connector:Conn_01x06_Male J?
U 1 1 5CE61FCD
P 9250 1300
AR Path="/5CE61FCD" Ref="J?"  Part="1" 
AR Path="/5CE57A6D/5CE61FCD" Ref="J8"  Part="1" 
F 0 "J8" H 9400 1650 50  0000 C CNN
F 1 "Conn_01x06_Male" H 9450 900 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 9250 1300 50  0001 C CNN
F 3 "~" H 9250 1300 50  0001 C CNN
	1    9250 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 1200 9750 1200
Wire Wire Line
	9450 1400 9750 1400
Wire Wire Line
	9450 1500 9750 1500
Wire Wire Line
	9450 1600 9750 1600
Text HLabel 9750 1500 2    50   Input ~ 0
NRST
Text HLabel 9750 1200 2    50   Input ~ 0
SWCLK
Text HLabel 9750 1400 2    50   Input ~ 0
SWDIO
Text HLabel 9750 1600 2    50   Input ~ 0
SWO
$Comp
L power:+3.3V #PWR?
U 1 1 5CF4D72C
P 10200 1100
AR Path="/5CF4D72C" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CF4D72C" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 10200 950 50  0001 C CNN
F 1 "+3.3V" H 10215 1273 50  0000 C CNN
F 2 "" H 10200 1100 50  0001 C CNN
F 3 "" H 10200 1100 50  0001 C CNN
	1    10200 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CF4D749
P 10200 1300
AR Path="/5CF4D749" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CF4D749" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 10200 1050 50  0001 C CNN
F 1 "GND" H 10205 1127 50  0000 C CNN
F 2 "" H 10200 1300 50  0001 C CNN
F 3 "" H 10200 1300 50  0001 C CNN
	1    10200 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 1100 10200 1100
Wire Wire Line
	9450 1300 10200 1300
$Comp
L Mutterplatine-rescue:Micro_SD_Card_Det-Connector J?
U 1 1 5DFB3C50
P 4350 2100
AR Path="/5DFB3C50" Ref="J?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C50" Ref="J?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C50" Ref="J6"  Part="1" 
F 0 "J6" H 4350 1500 50  0000 C CNN
F 1 "Micro_SD_Card_Det" H 4350 1400 50  0000 C CNN
F 2 "Connector_Card:microSD_HC_Hirose_DM3D-SF" H 6400 2800 50  0001 C CNN
F 3 "https://www.hirose.com/product/en/download_file/key_name/DM3/category/Catalog/doc_file_id/49662/?file_category_id=4&item_id=195&is_series=1" H 4350 2200 50  0001 C CNN
	1    4350 2100
	1    0    0    -1  
$EndComp
Text Label 1500 2200 0    50   ~ 0
GND
Text Label 1500 2000 0    50   ~ 0
3.3V
Text Label 1500 2100 0    50   ~ 0
SD_CLK
Text Label 1500 2300 0    50   ~ 0
SD_D0
Text Label 1500 2400 0    50   ~ 0
SD_D1
Text Label 1500 1700 0    50   ~ 0
SD_D2
Text Label 1500 1800 0    50   ~ 0
SD_CS
Text Label 1500 1900 0    50   ~ 0
SD_CMD
$Comp
L power:GND #PWR?
U 1 1 5DFB3C5F
P 5200 2700
AR Path="/5DFB3C5F" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C5F" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C5F" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 5200 2450 50  0001 C CNN
F 1 "GND" H 5205 2527 50  0000 C CNN
F 2 "" H 5200 2700 50  0001 C CNN
F 3 "" H 5200 2700 50  0001 C CNN
	1    5200 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2600 5200 2600
Wire Wire Line
	5200 2600 5200 2700
$Comp
L Device:R R?
U 1 1 5DFB3C67
P 1950 1400
AR Path="/5DFB3C67" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C67" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C67" Ref="R30"  Part="1" 
F 0 "R30" H 2000 1450 50  0000 L CNN
F 1 "47k" H 2000 1350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1880 1400 50  0001 C CNN
F 3 "~" H 1950 1400 50  0001 C CNN
	1    1950 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1700 1950 1700
$Comp
L Device:R R?
U 1 1 5DFB3C6F
P 2200 1400
AR Path="/5DFB3C6F" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C6F" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C6F" Ref="R31"  Part="1" 
F 0 "R31" H 2270 1446 50  0000 L CNN
F 1 "47k" H 2250 1350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2130 1400 50  0001 C CNN
F 3 "~" H 2200 1400 50  0001 C CNN
	1    2200 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFB3C76
P 2450 1400
AR Path="/5DFB3C76" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C76" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C76" Ref="R32"  Part="1" 
F 0 "R32" H 2520 1446 50  0000 L CNN
F 1 "47k" H 2500 1350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2380 1400 50  0001 C CNN
F 3 "~" H 2450 1400 50  0001 C CNN
	1    2450 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFB3C7D
P 2700 1400
AR Path="/5DFB3C7D" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C7D" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C7D" Ref="R34"  Part="1" 
F 0 "R34" H 2770 1446 50  0000 L CNN
F 1 "47k" H 2750 1350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2630 1400 50  0001 C CNN
F 3 "~" H 2700 1400 50  0001 C CNN
	1    2700 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFB3C84
P 2950 1400
AR Path="/5DFB3C84" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C84" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C84" Ref="R35"  Part="1" 
F 0 "R35" H 3020 1446 50  0000 L CNN
F 1 "47k" H 3000 1350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2880 1400 50  0001 C CNN
F 3 "~" H 2950 1400 50  0001 C CNN
	1    2950 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1550 1950 1700
Wire Wire Line
	1500 1800 2200 1800
Wire Wire Line
	1500 1900 2450 1900
Wire Wire Line
	1500 2300 2700 2300
Wire Wire Line
	1500 2400 2950 2400
Connection ~ 1950 1700
Wire Wire Line
	2200 1550 2200 1800
Connection ~ 2200 1800
Wire Wire Line
	2450 1550 2450 1900
Connection ~ 2450 1900
Wire Wire Line
	2700 1550 2700 2300
Connection ~ 2700 2300
Wire Wire Line
	2950 1550 2950 2400
Connection ~ 2950 2400
Wire Wire Line
	1950 1250 1950 1150
Wire Wire Line
	1950 1150 2200 1150
Wire Wire Line
	2950 1150 2950 1250
Wire Wire Line
	2700 1250 2700 1150
Connection ~ 2700 1150
Wire Wire Line
	2700 1150 2950 1150
Wire Wire Line
	2450 1250 2450 1150
Connection ~ 2450 1150
Wire Wire Line
	2450 1150 2700 1150
Wire Wire Line
	2200 1250 2200 1150
Connection ~ 2200 1150
Wire Wire Line
	2200 1150 2450 1150
Connection ~ 2950 1150
$Comp
L power:GND #PWR?
U 1 1 5DFB3CA6
P 4100 1200
AR Path="/5DFB3CA6" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CA6" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CA6" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 4100 950 50  0001 C CNN
F 1 "GND" H 4105 1027 50  0000 C CNN
F 2 "" H 4100 1200 50  0001 C CNN
F 3 "" H 4100 1200 50  0001 C CNN
	1    4100 1200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DFB3CAC
P 2950 1000
AR Path="/5DFB3CAC" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CAC" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CAC" Ref="#PWR031"  Part="1" 
F 0 "#PWR031" H 2950 850 50  0001 C CNN
F 1 "+3.3V" H 2965 1173 50  0000 C CNN
F 2 "" H 2950 1000 50  0001 C CNN
F 3 "" H 2950 1000 50  0001 C CNN
	1    2950 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DFB3CB2
P 3800 1150
AR Path="/5DFB3CB2" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CB2" Ref="C?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CB2" Ref="C17"  Part="1" 
F 0 "C17" V 3548 1150 50  0000 C CNN
F 1 "100n" V 3639 1150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3838 1000 50  0001 C CNN
F 3 "~" H 3800 1150 50  0001 C CNN
	1    3800 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 1150 4100 1150
Wire Wire Line
	4100 1150 4100 1200
Wire Wire Line
	2950 1150 2950 1000
$Comp
L power:GND #PWR?
U 1 1 5DFB3CBC
P 3400 2700
AR Path="/5DFB3CBC" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CBC" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CBC" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 3400 2450 50  0001 C CNN
F 1 "GND" H 3405 2527 50  0000 C CNN
F 2 "" H 3400 2700 50  0001 C CNN
F 3 "" H 3400 2700 50  0001 C CNN
	1    3400 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 2600 3400 2600
Wire Wire Line
	3400 2600 3400 2700
Wire Wire Line
	1950 1700 3450 1700
Wire Wire Line
	1500 2100 3450 2100
Wire Wire Line
	2200 1800 3450 1800
Wire Wire Line
	2450 1900 3450 1900
Wire Wire Line
	2700 2300 3450 2300
Wire Wire Line
	2950 2400 3450 2400
Wire Wire Line
	2950 1150 3200 1150
$Comp
L Device:R R?
U 1 1 5DFB3CCB
P 3200 1400
AR Path="/5DFB3CCB" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CCB" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CCB" Ref="R36"  Part="1" 
F 0 "R36" H 3270 1446 50  0000 L CNN
F 1 "47k" H 3250 1350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3130 1400 50  0001 C CNN
F 3 "~" H 3200 1400 50  0001 C CNN
	1    3200 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 1150 3200 1250
Connection ~ 3200 1150
Wire Wire Line
	3200 1150 3650 1150
Wire Wire Line
	3200 1550 3200 2500
Wire Wire Line
	3200 2500 3450 2500
Wire Wire Line
	3200 2500 1500 2500
Connection ~ 3200 2500
Text Label 1500 2500 0    50   ~ 0
SD_detect
Text HLabel 1500 1700 0    50   Input ~ 0
SD_D2
Text HLabel 1500 1800 0    50   Input ~ 0
SD_CS
Text HLabel 1500 1900 0    50   Input ~ 0
SD_CMD
Text HLabel 1500 2100 0    50   Input ~ 0
SD_CLK
Text HLabel 1500 2300 0    50   Input ~ 0
SD_D0
Text HLabel 1500 2400 0    50   Input ~ 0
SD_D1
Text HLabel 1500 2500 0    50   Input ~ 0
SD_detect
Wire Wire Line
	1000 2000 3450 2000
Wire Wire Line
	1000 2200 3450 2200
$Comp
L power:GND #PWR?
U 1 1 5DFB3CE3
P 1000 2200
AR Path="/5DFB3CE3" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CE3" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CE3" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 1000 1950 50  0001 C CNN
F 1 "GND" H 1005 2027 50  0000 C CNN
F 2 "" H 1000 2200 50  0001 C CNN
F 3 "" H 1000 2200 50  0001 C CNN
	1    1000 2200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DFB3CE9
P 1000 2000
AR Path="/5DFB3CE9" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CE9" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CE9" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 1000 1850 50  0001 C CNN
F 1 "+3.3V" H 1015 2173 50  0000 C CNN
F 2 "" H 1000 2000 50  0001 C CNN
F 3 "" H 1000 2000 50  0001 C CNN
	1    1000 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J?
U 1 1 5DFBE218
P 1200 6700
AR Path="/5DFBE218" Ref="J?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE218" Ref="J?"  Part="1" 
AR Path="/5CE57A6D/5DFBE218" Ref="J5"  Part="1" 
F 0 "J5" H 1255 7167 50  0000 C CNN
F 1 "USB_B_Micro" H 1255 7076 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_GCT_USB3076-30-A" H 1350 6650 50  0001 C CNN
F 3 "~" H 1350 6650 50  0001 C CNN
F 4 "6094613-1-ND" H 1200 6700 50  0001 C CNN "DigiKey"
	1    1200 6700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DFBE21F
P 1150 7200
AR Path="/5DFBE21F" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE21F" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFBE21F" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 1150 6950 50  0001 C CNN
F 1 "GND" H 1155 7027 50  0000 C CNN
F 2 "" H 1150 7200 50  0001 C CNN
F 3 "" H 1150 7200 50  0001 C CNN
	1    1150 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 7100 1100 7150
Wire Wire Line
	1100 7150 1150 7150
Wire Wire Line
	1200 7150 1200 7100
Wire Wire Line
	1150 7200 1150 7150
Connection ~ 1150 7150
Wire Wire Line
	1150 7150 1200 7150
Text Notes 1550 6950 0    50   ~ 0
floating for USB_Slave
$Comp
L Device:R R?
U 1 1 5DFBE22C
P 1750 6200
AR Path="/5DFBE22C" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE22C" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFBE22C" Ref="R33"  Part="1" 
F 0 "R33" H 1600 6150 50  0000 C CNN
F 1 "1k5" H 1600 6250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1680 6200 50  0001 C CNN
F 3 "~" H 1750 6200 50  0001 C CNN
	1    1750 6200
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DFBE235
P 1750 5950
AR Path="/5DFBE235" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE235" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFBE235" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 1750 5800 50  0001 C CNN
F 1 "+3.3V" H 1765 6123 50  0000 C CNN
F 2 "" H 1750 5950 50  0001 C CNN
F 3 "" H 1750 5950 50  0001 C CNN
	1    1750 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 5950 1750 6050
Wire Wire Line
	1500 6700 1750 6700
Wire Wire Line
	1750 6350 1750 6700
Text HLabel 3750 6800 2    50   Input ~ 0
USB_DP
Text HLabel 3750 6600 2    50   Input ~ 0
USB_DM
Wire Notes Line
	8250 550  11100 550 
Wire Notes Line
	11100 550  11100 4650
Wire Notes Line
	11100 4650 8250 4650
Wire Notes Line
	8250 4650 8250 550 
Wire Notes Line
	4300 5550 4300 7650
Wire Notes Line
	600  7650 600  5550
Text Notes 800  750  0    100  ~ 0
SD Card Reader
Text Notes 8350 750  0    100  ~ 0
JTAG
Text Notes 700  5750 0    100  ~ 0
USB
Wire Wire Line
	3600 6800 3750 6800
Wire Wire Line
	3600 6600 3750 6600
$Comp
L power:GND #PWR?
U 1 1 5EE51621
P 3100 7250
AR Path="/5EE51621" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5EE51621" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5EE51621" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 3100 7000 50  0001 C CNN
F 1 "GND" H 3105 7077 50  0000 C CNN
F 2 "" H 3100 7250 50  0001 C CNN
F 3 "" H 3100 7250 50  0001 C CNN
	1    3100 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 7200 3100 7250
Wire Notes Line
	600  5550 4300 5550
Wire Notes Line
	600  7650 4300 7650
Wire Wire Line
	2200 6500 2200 6200
Wire Wire Line
	1500 6500 2200 6500
$Comp
L Power_Protection:TPD2S017 U4
U 1 1 6118D2F9
P 3100 6700
F 0 "U4" H 3400 7200 50  0000 C CNN
F 1 "TPD2S017" H 3400 7100 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 2350 6350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tpd2s017.pdf" H 3100 6700 50  0001 C CNN
	1    3100 6700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6118E870
P 2650 6200
AR Path="/6118E870" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/6118E870" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/6118E870" Ref="R37"  Part="1" 
F 0 "R37" V 2550 6300 50  0000 C CNN
F 1 "0R" V 2550 6100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2580 6200 50  0001 C CNN
F 3 "~" H 2650 6200 50  0001 C CNN
	1    2650 6200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2500 6200 2200 6200
Wire Wire Line
	2800 6200 3100 6200
Text Notes 5300 1750 0    50   ~ 0
Belegung der SD-Karte bei \nAnsteuerung über SPI\n\nDAT2         -> n.c.\nDAT3/CD     -> CS\nCMD          -> MOSI\nVCC          -> VCC\nCLK          -> SCK\nGND          -> GND\nDAT0         -> MISO\nDAT1         -> n.c.\n
Wire Notes Line
	500  550  500  3000
Wire Notes Line
	500  3000 6500 3000
Wire Notes Line
	6500 3000 6500 550 
Wire Notes Line
	6500 550  500  550 
$Comp
L power:GND #PWR?
U 1 1 5D4A5AEF
P 6050 5550
AR Path="/5D4A5AEF" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5D4A5AEF" Ref="#PWR080"  Part="1" 
F 0 "#PWR080" H 6050 5300 50  0001 C CNN
F 1 "GND" H 6055 5377 50  0000 C CNN
F 2 "" H 6050 5550 50  0001 C CNN
F 3 "" H 6050 5550 50  0001 C CNN
	1    6050 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5D4A8805
P 6050 3750
AR Path="/5D4A8805" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5D4A8805" Ref="#PWR073"  Part="1" 
F 0 "#PWR073" H 6050 3600 50  0001 C CNN
F 1 "+3.3V" H 6065 3923 50  0000 C CNN
F 2 "" H 6050 3750 50  0001 C CNN
F 3 "" H 6050 3750 50  0001 C CNN
	1    6050 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 5050 7600 5050
Wire Wire Line
	7600 5050 7600 5200
Wire Wire Line
	6650 5150 7250 5150
Wire Wire Line
	7250 5150 7250 5300
Wire Wire Line
	7250 5300 7600 5300
$Comp
L Interface_UART:MAX3221 U16
U 1 1 5D5B3D29
P 6050 4650
F 0 "U16" H 6050 5731 50  0000 C CNN
F 1 "MAX3221" H 6050 5640 50  0000 C CNN
F 2 "Package_SO:TSSOP-16_4.4x5mm_P0.65mm" H 6100 4650 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/max3221.pdf" H 6050 5600 50  0001 C CNN
	1    6050 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5D5DB5DB
P 5300 4100
AR Path="/5D5DB5DB" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5D5DB5DB" Ref="C?"  Part="1" 
AR Path="/5CE57A6D/5D5DB5DB" Ref="C69"  Part="1" 
F 0 "C69" V 5048 4100 50  0000 C CNN
F 1 "100n" V 5139 4100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5338 3950 50  0001 C CNN
F 3 "~" H 5300 4100 50  0001 C CNN
	1    5300 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5D5DD978
P 5300 4600
AR Path="/5D5DD978" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5D5DD978" Ref="C?"  Part="1" 
AR Path="/5CE57A6D/5D5DD978" Ref="C70"  Part="1" 
F 0 "C70" V 5048 4600 50  0000 C CNN
F 1 "100n" V 5139 4600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5338 4450 50  0001 C CNN
F 3 "~" H 5300 4600 50  0001 C CNN
	1    5300 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5D5DFD6A
P 5650 3500
AR Path="/5D5DFD6A" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5D5DFD6A" Ref="C?"  Part="1" 
AR Path="/5CE57A6D/5D5DFD6A" Ref="C83"  Part="1" 
F 0 "C83" V 5398 3500 50  0000 C CNN
F 1 "100n" V 5489 3500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5688 3350 50  0001 C CNN
F 3 "~" H 5650 3500 50  0001 C CNN
	1    5650 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5D5E2107
P 6800 4350
AR Path="/5D5E2107" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5D5E2107" Ref="C?"  Part="1" 
AR Path="/5CE57A6D/5D5E2107" Ref="C84"  Part="1" 
F 0 "C84" V 6548 4350 50  0000 C CNN
F 1 "100n" V 6639 4350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6838 4200 50  0001 C CNN
F 3 "~" H 6800 4350 50  0001 C CNN
	1    6800 4350
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5D5E41C4
P 6800 4850
AR Path="/5D5E41C4" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5D5E41C4" Ref="C?"  Part="1" 
AR Path="/5CE57A6D/5D5E41C4" Ref="C85"  Part="1" 
F 0 "C85" V 6548 4850 50  0000 C CNN
F 1 "100n" V 6639 4850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6838 4700 50  0001 C CNN
F 3 "~" H 6800 4850 50  0001 C CNN
	1    6800 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 3950 5300 3950
Wire Wire Line
	5300 4350 5450 4350
Wire Wire Line
	5300 4250 5300 4350
Wire Wire Line
	5450 4450 5300 4450
Wire Wire Line
	5450 4850 5300 4850
Wire Wire Line
	5300 4850 5300 4750
$Comp
L power:GND #PWR?
U 1 1 5D5FA27A
P 6950 4850
AR Path="/5D5FA27A" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5D5FA27A" Ref="#PWR0120"  Part="1" 
F 0 "#PWR0120" H 6950 4600 50  0001 C CNN
F 1 "GND" H 6955 4677 50  0000 C CNN
F 2 "" H 6950 4850 50  0001 C CNN
F 3 "" H 6950 4850 50  0001 C CNN
	1    6950 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D5FC6F2
P 6950 4350
AR Path="/5D5FC6F2" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5D5FC6F2" Ref="#PWR0119"  Part="1" 
F 0 "#PWR0119" H 6950 4100 50  0001 C CNN
F 1 "GND" H 6955 4177 50  0000 C CNN
F 2 "" H 6950 4350 50  0001 C CNN
F 3 "" H 6950 4350 50  0001 C CNN
	1    6950 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D5FEC69
P 5650 3650
AR Path="/5D5FEC69" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5D5FEC69" Ref="#PWR062"  Part="1" 
F 0 "#PWR062" H 5650 3400 50  0001 C CNN
F 1 "GND" H 5655 3477 50  0000 C CNN
F 2 "" H 5650 3650 50  0001 C CNN
F 3 "" H 5650 3650 50  0001 C CNN
	1    5650 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5D601764
P 5650 3350
AR Path="/5D601764" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5D601764" Ref="#PWR041"  Part="1" 
F 0 "#PWR041" H 5650 3200 50  0001 C CNN
F 1 "+3.3V" H 5665 3523 50  0000 C CNN
F 2 "" H 5650 3350 50  0001 C CNN
F 3 "" H 5650 3350 50  0001 C CNN
	1    5650 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D60421D
P 5450 5350
AR Path="/5D60421D" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5D60421D" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 5450 5100 50  0001 C CNN
F 1 "GND" H 5455 5177 50  0000 C CNN
F 2 "" H 5450 5350 50  0001 C CNN
F 3 "" H 5450 5350 50  0001 C CNN
	1    5450 5350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5D606FE8
P 6650 5350
AR Path="/5D606FE8" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5D606FE8" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 6650 5200 50  0001 C CNN
F 1 "+3.3V" H 6665 5523 50  0000 C CNN
F 2 "" H 6650 5350 50  0001 C CNN
F 3 "" H 6650 5350 50  0001 C CNN
	1    6650 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 5350 5450 5250
Connection ~ 5450 5350
$Comp
L Connector:Conn_01x03_Female J2
U 1 1 5D6738EA
P 7800 5300
F 0 "J2" H 7828 5326 50  0000 L CNN
F 1 "Conn_01x03_Female" H 7828 5235 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 7800 5300 50  0001 C CNN
F 3 "~" H 7800 5300 50  0001 C CNN
	1    7800 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D680752
P 7600 5400
AR Path="/5D680752" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5D680752" Ref="#PWR0121"  Part="1" 
F 0 "#PWR0121" H 7600 5150 50  0001 C CNN
F 1 "GND" H 7605 5227 50  0000 C CNN
F 2 "" H 7600 5400 50  0001 C CNN
F 3 "" H 7600 5400 50  0001 C CNN
	1    7600 5400
	1    0    0    -1  
$EndComp
Text HLabel 5450 5050 0    50   Input ~ 0
PB6_UART1_TX
Text HLabel 5450 5150 0    50   Output ~ 0
PB7_UART1_RX
Wire Wire Line
	1500 6800 2200 6800
Wire Wire Line
	2200 6800 2200 6600
Wire Wire Line
	2200 6600 2600 6600
Wire Wire Line
	1750 6700 2600 6700
Wire Wire Line
	2600 6700 2600 6800
Connection ~ 1750 6700
$Comp
L Device:C C?
U 1 1 5D423531
P 3100 6050
AR Path="/5D423531" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5D423531" Ref="C?"  Part="1" 
AR Path="/5CE57A6D/5D423531" Ref="C87"  Part="1" 
F 0 "C87" V 2848 6050 50  0000 C CNN
F 1 "100n" V 2939 6050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3138 5900 50  0001 C CNN
F 3 "~" H 3100 6050 50  0001 C CNN
	1    3100 6050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D425CEA
P 3100 5900
AR Path="/5D425CEA" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5D425CEA" Ref="#PWR0127"  Part="1" 
F 0 "#PWR0127" H 3100 5650 50  0001 C CNN
F 1 "GND" H 3105 5727 50  0000 C CNN
F 2 "" H 3100 5900 50  0001 C CNN
F 3 "" H 3100 5900 50  0001 C CNN
	1    3100 5900
	-1   0    0    1   
$EndComp
Connection ~ 3100 6200
$EndSCHEMATC
