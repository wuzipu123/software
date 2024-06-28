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
L Connector:Conn_ARM_JTAG_SWD_20 J?
U 1 1 5CE61FC6
P 8350 4050
AR Path="/5CE61FC6" Ref="J?"  Part="1" 
AR Path="/5CE57A6D/5CE61FC6" Ref="J7"  Part="1" 
F 0 "J7" H 8050 4850 50  0000 R CNN
F 1 "Conn_ARM_JTAG_SWD_20" H 9350 4850 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Vertical" H 8800 3000 50  0001 L TNN
F 3 "http://infocenter.arm.com/help/topic/com.arm.doc.dui0499b/DUI0499B_system_design_reference.pdf" V 8000 2800 50  0001 C CNN
	1    8350 4050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J?
U 1 1 5CE61FCD
P 8550 2100
AR Path="/5CE61FCD" Ref="J?"  Part="1" 
AR Path="/5CE57A6D/5CE61FCD" Ref="J8"  Part="1" 
F 0 "J8" H 8700 2450 50  0000 C CNN
F 1 "Conn_01x06_Male" H 8750 1700 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 8550 2100 50  0001 C CNN
F 3 "~" H 8550 2100 50  0001 C CNN
	1    8550 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 3550 9200 3550
Wire Wire Line
	8950 3950 9200 3950
Wire Wire Line
	8950 4050 9200 4050
Wire Wire Line
	8950 4150 9200 4150
Wire Wire Line
	8950 4250 9200 4250
$Comp
L Device:R R?
U 1 1 5CE61FDE
P 9400 4450
AR Path="/5CE61FDE" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5CE61FDE" Ref="R38"  Part="1" 
F 0 "R38" V 9300 4400 50  0000 L CNN
F 1 "10k" V 9500 4400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9330 4450 50  0001 C CNN
F 3 "~" H 9400 4450 50  0001 C CNN
	1    9400 4450
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5CE61FE5
P 9900 3350
AR Path="/5CE61FE5" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CE61FE5" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 9900 3200 50  0001 C CNN
F 1 "+3.3V" H 9915 3523 50  0000 C CNN
F 2 "" H 9900 3350 50  0001 C CNN
F 3 "" H 9900 3350 50  0001 C CNN
	1    9900 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5CE61FEB
P 9400 4750
AR Path="/5CE61FEB" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5CE61FEB" Ref="R39"  Part="1" 
F 0 "R39" V 9300 4700 50  0000 L CNN
F 1 "10k" V 9500 4700 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9330 4750 50  0001 C CNN
F 3 "~" H 9400 4750 50  0001 C CNN
	1    9400 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	8950 4450 9250 4450
Wire Wire Line
	8950 4550 9200 4550
Wire Wire Line
	9200 4550 9200 4750
Wire Wire Line
	9200 4750 9250 4750
$Comp
L Device:R R?
U 1 1 5CE61FF6
P 9900 4150
AR Path="/5CE61FF6" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5CE61FF6" Ref="R41"  Part="1" 
F 0 "R41" V 9800 4100 50  0000 L CNN
F 1 "10k" V 10000 4100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9830 4150 50  0001 C CNN
F 3 "~" H 9900 4150 50  0001 C CNN
	1    9900 4150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5CE61FFD
P 9900 3600
AR Path="/5CE61FFD" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5CE61FFD" Ref="R40"  Part="1" 
F 0 "R40" V 9800 3550 50  0000 L CNN
F 1 "DNP" V 10000 3550 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9830 3600 50  0001 C CNN
F 3 "~" H 9900 3600 50  0001 C CNN
	1    9900 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	9550 4750 9900 4750
Wire Wire Line
	9900 4750 9900 4450
Wire Wire Line
	9550 4450 9900 4450
Connection ~ 9900 4450
Wire Wire Line
	9900 4450 9900 4300
Wire Wire Line
	8950 3850 9900 3850
Wire Wire Line
	9900 3850 9900 4000
Wire Wire Line
	9900 3750 9900 3850
Connection ~ 9900 3850
Wire Wire Line
	9900 3450 9900 3350
$Comp
L power:+3.3V #PWR?
U 1 1 5CE6200E
P 8300 3150
AR Path="/5CE6200E" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CE6200E" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 8300 3000 50  0001 C CNN
F 1 "+3.3V" H 8315 3323 50  0000 C CNN
F 2 "" H 8300 3150 50  0001 C CNN
F 3 "" H 8300 3150 50  0001 C CNN
	1    8300 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 3250 8250 3200
Wire Wire Line
	8250 3200 8300 3200
Wire Wire Line
	8350 3200 8350 3250
Wire Wire Line
	8300 3200 8300 3150
Connection ~ 8300 3200
Wire Wire Line
	8300 3200 8350 3200
$Comp
L power:GND #PWR?
U 1 1 5CE6201A
P 8250 4950
AR Path="/5CE6201A" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CE6201A" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 8250 4700 50  0001 C CNN
F 1 "GND" H 8255 4777 50  0000 C CNN
F 2 "" H 8250 4950 50  0001 C CNN
F 3 "" H 8250 4950 50  0001 C CNN
	1    8250 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CE62020
P 9900 4850
AR Path="/5CE62020" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CE62020" Ref="#PWR041"  Part="1" 
F 0 "#PWR041" H 9900 4600 50  0001 C CNN
F 1 "GND" H 9905 4677 50  0000 C CNN
F 2 "" H 9900 4850 50  0001 C CNN
F 3 "" H 9900 4850 50  0001 C CNN
	1    9900 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 4750 9900 4850
Connection ~ 9900 4750
Wire Wire Line
	8250 4950 8250 4850
Wire Wire Line
	8950 3650 9200 3650
Wire Wire Line
	8750 2000 9050 2000
Wire Wire Line
	8750 2200 9050 2200
Wire Wire Line
	8750 2300 9050 2300
Wire Wire Line
	8750 2400 9050 2400
Text HLabel 9200 3550 2    50   Input ~ 0
TRST
Text HLabel 9200 3650 2    50   Input ~ 0
NRST
Text HLabel 9200 3950 2    50   Input ~ 0
SWCLK
Text HLabel 9200 4050 2    50   Input ~ 0
SWDIO
Text HLabel 9200 4150 2    50   Input ~ 0
SWO
Text HLabel 9200 4250 2    50   Input ~ 0
TDI
Text HLabel 9050 2300 2    50   Input ~ 0
NRST
Text HLabel 9050 2000 2    50   Input ~ 0
SWCLK
Text HLabel 9050 2200 2    50   Input ~ 0
SWDIO
Text HLabel 9050 2400 2    50   Input ~ 0
SWO
$Comp
L power:+3.3V #PWR?
U 1 1 5CF4D72C
P 9500 1900
AR Path="/5CF4D72C" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CF4D72C" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 9500 1750 50  0001 C CNN
F 1 "+3.3V" H 9515 2073 50  0000 C CNN
F 2 "" H 9500 1900 50  0001 C CNN
F 3 "" H 9500 1900 50  0001 C CNN
	1    9500 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CF4D749
P 9500 2100
AR Path="/5CF4D749" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CF4D749" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 9500 1850 50  0001 C CNN
F 1 "GND" H 9505 1927 50  0000 C CNN
F 2 "" H 9500 2100 50  0001 C CNN
F 3 "" H 9500 2100 50  0001 C CNN
	1    9500 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 1900 9500 1900
Wire Wire Line
	8750 2100 9500 2100
$Comp
L Connector:Micro_SD_Card_Det J?
U 1 1 5DFB3C50
P 4900 2500
AR Path="/5DFB3C50" Ref="J?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C50" Ref="J?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C50" Ref="J6"  Part="1" 
F 0 "J6" H 4900 1900 50  0000 C CNN
F 1 "Micro_SD_Card_Det" H 4900 1800 50  0000 C CNN
F 2 "Connector_Card:microSD_HC_Hirose_DM3D-SF" H 6950 3200 50  0001 C CNN
F 3 "https://www.hirose.com/product/en/download_file/key_name/DM3/category/Catalog/doc_file_id/49662/?file_category_id=4&item_id=195&is_series=1" H 4900 2600 50  0001 C CNN
	1    4900 2500
	1    0    0    -1  
$EndComp
Text Label 2050 2600 0    50   ~ 0
GND
Text Label 2050 2400 0    50   ~ 0
3.3V
Text Label 2050 2500 0    50   ~ 0
SD_CLK
Text Label 2050 2700 0    50   ~ 0
SD_D0
Text Label 2050 2800 0    50   ~ 0
SD_D1
Text Label 2050 2100 0    50   ~ 0
SD_D2
Text Label 2050 2200 0    50   ~ 0
SD_D3
Text Label 2050 2300 0    50   ~ 0
SD_CMD
$Comp
L power:GND #PWR?
U 1 1 5DFB3C5F
P 5750 3100
AR Path="/5DFB3C5F" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C5F" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C5F" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 5750 2850 50  0001 C CNN
F 1 "GND" H 5755 2927 50  0000 C CNN
F 2 "" H 5750 3100 50  0001 C CNN
F 3 "" H 5750 3100 50  0001 C CNN
	1    5750 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 3000 5750 3000
Wire Wire Line
	5750 3000 5750 3100
$Comp
L Device:R R?
U 1 1 5DFB3C67
P 2500 1800
AR Path="/5DFB3C67" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C67" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C67" Ref="R30"  Part="1" 
F 0 "R30" H 2550 1850 50  0000 L CNN
F 1 "47k" H 2550 1750 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2430 1800 50  0001 C CNN
F 3 "~" H 2500 1800 50  0001 C CNN
	1    2500 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 2100 2500 2100
$Comp
L Device:R R?
U 1 1 5DFB3C6F
P 2750 1800
AR Path="/5DFB3C6F" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C6F" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C6F" Ref="R31"  Part="1" 
F 0 "R31" H 2820 1846 50  0000 L CNN
F 1 "47k" H 2800 1750 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2680 1800 50  0001 C CNN
F 3 "~" H 2750 1800 50  0001 C CNN
	1    2750 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFB3C76
P 3000 1800
AR Path="/5DFB3C76" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C76" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C76" Ref="R32"  Part="1" 
F 0 "R32" H 3070 1846 50  0000 L CNN
F 1 "47k" H 3050 1750 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2930 1800 50  0001 C CNN
F 3 "~" H 3000 1800 50  0001 C CNN
	1    3000 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFB3C7D
P 3250 1800
AR Path="/5DFB3C7D" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C7D" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C7D" Ref="R34"  Part="1" 
F 0 "R34" H 3320 1846 50  0000 L CNN
F 1 "47k" H 3300 1750 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3180 1800 50  0001 C CNN
F 3 "~" H 3250 1800 50  0001 C CNN
	1    3250 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFB3C84
P 3500 1800
AR Path="/5DFB3C84" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C84" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C84" Ref="R35"  Part="1" 
F 0 "R35" H 3570 1846 50  0000 L CNN
F 1 "47k" H 3550 1750 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3430 1800 50  0001 C CNN
F 3 "~" H 3500 1800 50  0001 C CNN
	1    3500 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1950 2500 2100
Wire Wire Line
	2050 2200 2750 2200
Wire Wire Line
	2050 2300 3000 2300
Wire Wire Line
	2050 2700 3250 2700
Wire Wire Line
	2050 2800 3500 2800
Connection ~ 2500 2100
Wire Wire Line
	2750 1950 2750 2200
Connection ~ 2750 2200
Wire Wire Line
	3000 1950 3000 2300
Connection ~ 3000 2300
Wire Wire Line
	3250 1950 3250 2700
Connection ~ 3250 2700
Wire Wire Line
	3500 1950 3500 2800
Connection ~ 3500 2800
Wire Wire Line
	2500 1650 2500 1550
Wire Wire Line
	2500 1550 2750 1550
Wire Wire Line
	3500 1550 3500 1650
Wire Wire Line
	3250 1650 3250 1550
Connection ~ 3250 1550
Wire Wire Line
	3250 1550 3500 1550
Wire Wire Line
	3000 1650 3000 1550
Connection ~ 3000 1550
Wire Wire Line
	3000 1550 3250 1550
Wire Wire Line
	2750 1650 2750 1550
Connection ~ 2750 1550
Wire Wire Line
	2750 1550 3000 1550
Connection ~ 3500 1550
$Comp
L power:GND #PWR?
U 1 1 5DFB3CA6
P 4650 1600
AR Path="/5DFB3CA6" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CA6" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CA6" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 4650 1350 50  0001 C CNN
F 1 "GND" H 4655 1427 50  0000 C CNN
F 2 "" H 4650 1600 50  0001 C CNN
F 3 "" H 4650 1600 50  0001 C CNN
	1    4650 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DFB3CAC
P 3500 1400
AR Path="/5DFB3CAC" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CAC" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CAC" Ref="#PWR031"  Part="1" 
F 0 "#PWR031" H 3500 1250 50  0001 C CNN
F 1 "+3.3V" H 3515 1573 50  0000 C CNN
F 2 "" H 3500 1400 50  0001 C CNN
F 3 "" H 3500 1400 50  0001 C CNN
	1    3500 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DFB3CB2
P 4350 1550
AR Path="/5DFB3CB2" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CB2" Ref="C?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CB2" Ref="C17"  Part="1" 
F 0 "C17" V 4098 1550 50  0000 C CNN
F 1 "100n" V 4189 1550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4388 1400 50  0001 C CNN
F 3 "~" H 4350 1550 50  0001 C CNN
	1    4350 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 1550 4650 1550
Wire Wire Line
	4650 1550 4650 1600
Wire Wire Line
	3500 1550 3500 1400
$Comp
L power:GND #PWR?
U 1 1 5DFB3CBC
P 3950 3100
AR Path="/5DFB3CBC" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CBC" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CBC" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 3950 2850 50  0001 C CNN
F 1 "GND" H 3955 2927 50  0000 C CNN
F 2 "" H 3950 3100 50  0001 C CNN
F 3 "" H 3950 3100 50  0001 C CNN
	1    3950 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3000 3950 3000
Wire Wire Line
	3950 3000 3950 3100
Wire Wire Line
	2500 2100 4000 2100
Wire Wire Line
	2050 2500 4000 2500
Wire Wire Line
	2750 2200 4000 2200
Wire Wire Line
	3000 2300 4000 2300
Wire Wire Line
	3250 2700 4000 2700
Wire Wire Line
	3500 2800 4000 2800
Wire Wire Line
	3500 1550 3750 1550
$Comp
L Device:R R?
U 1 1 5DFB3CCB
P 3750 1800
AR Path="/5DFB3CCB" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CCB" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CCB" Ref="R36"  Part="1" 
F 0 "R36" H 3820 1846 50  0000 L CNN
F 1 "47k" H 3800 1750 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3680 1800 50  0001 C CNN
F 3 "~" H 3750 1800 50  0001 C CNN
	1    3750 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 1550 3750 1650
Connection ~ 3750 1550
Wire Wire Line
	3750 1550 4200 1550
Wire Wire Line
	3750 1950 3750 2900
Wire Wire Line
	3750 2900 4000 2900
Wire Wire Line
	3750 2900 2050 2900
Connection ~ 3750 2900
Text Label 2050 2900 0    50   ~ 0
SD_detect
Text HLabel 2050 2100 0    50   Input ~ 0
SD_D2
Text HLabel 2050 2200 0    50   Input ~ 0
SD_D3
Text HLabel 2050 2300 0    50   Input ~ 0
SD_CMD
Text HLabel 2050 2500 0    50   Input ~ 0
SD_CLK
Text HLabel 2050 2700 0    50   Input ~ 0
SD_D0
Text HLabel 2050 2800 0    50   Input ~ 0
SD_D1
Text HLabel 2050 2900 0    50   Input ~ 0
SD_detect
Wire Wire Line
	1550 2400 4000 2400
Wire Wire Line
	1550 2600 4000 2600
$Comp
L power:GND #PWR?
U 1 1 5DFB3CE3
P 1550 2600
AR Path="/5DFB3CE3" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CE3" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CE3" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 1550 2350 50  0001 C CNN
F 1 "GND" H 1555 2427 50  0000 C CNN
F 2 "" H 1550 2600 50  0001 C CNN
F 3 "" H 1550 2600 50  0001 C CNN
	1    1550 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DFB3CE9
P 1550 2400
AR Path="/5DFB3CE9" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CE9" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CE9" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 1550 2250 50  0001 C CNN
F 1 "+3.3V" H 1565 2573 50  0000 C CNN
F 2 "" H 1550 2400 50  0001 C CNN
F 3 "" H 1550 2400 50  0001 C CNN
	1    1550 2400
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J?
U 1 1 5DFBE218
P 2600 5550
AR Path="/5DFBE218" Ref="J?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE218" Ref="J?"  Part="1" 
AR Path="/5CE57A6D/5DFBE218" Ref="J5"  Part="1" 
F 0 "J5" H 2655 6017 50  0000 C CNN
F 1 "USB_B_Micro" H 2655 5926 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_GCT_USB3076-30-A" H 2750 5500 50  0001 C CNN
F 3 "~" H 2750 5500 50  0001 C CNN
	1    2600 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DFBE21F
P 2550 6050
AR Path="/5DFBE21F" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE21F" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFBE21F" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 2550 5800 50  0001 C CNN
F 1 "GND" H 2555 5877 50  0000 C CNN
F 2 "" H 2550 6050 50  0001 C CNN
F 3 "" H 2550 6050 50  0001 C CNN
	1    2550 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5950 2500 6000
Wire Wire Line
	2500 6000 2550 6000
Wire Wire Line
	2600 6000 2600 5950
Wire Wire Line
	2550 6050 2550 6000
Connection ~ 2550 6000
Wire Wire Line
	2550 6000 2600 6000
Text Notes 2950 5800 0    50   ~ 0
floating for USB_Slave
$Comp
L Device:R R?
U 1 1 5DFBE22C
P 3150 5050
AR Path="/5DFBE22C" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE22C" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFBE22C" Ref="R33"  Part="1" 
F 0 "R33" H 3000 5000 50  0000 C CNN
F 1 "1k5" H 3000 5100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3080 5050 50  0001 C CNN
F 3 "~" H 3150 5050 50  0001 C CNN
	1    3150 5050
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DFBE235
P 3150 4800
AR Path="/5DFBE235" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE235" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFBE235" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 3150 4650 50  0001 C CNN
F 1 "+3.3V" H 3165 4973 50  0000 C CNN
F 2 "" H 3150 4800 50  0001 C CNN
F 3 "" H 3150 4800 50  0001 C CNN
	1    3150 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 4800 3150 4900
Wire Wire Line
	2900 5550 3150 5550
Wire Wire Line
	3150 5200 3150 5550
Connection ~ 3150 5550
Text HLabel 3850 4750 2    50   Input ~ 0
VDD_USB
Text HLabel 5150 5450 2    50   Input ~ 0
USB_DP
Text HLabel 5150 5650 2    50   Input ~ 0
USB_DM
Wire Notes Line
	1250 950  6150 950 
Wire Notes Line
	6150 950  6150 3600
Wire Notes Line
	6150 3600 1250 3600
Wire Notes Line
	1250 3600 1250 950 
Wire Notes Line
	7550 1350 10400 1350
Wire Notes Line
	10400 1350 10400 5450
Wire Notes Line
	10400 5450 7550 5450
Wire Notes Line
	7550 5450 7550 1350
Wire Notes Line
	5700 4400 5700 6500
Wire Notes Line
	2000 6500 2000 4400
Text Notes 1350 1150 0    100  ~ 0
SD Card Reader
Text Notes 7650 1550 0    100  ~ 0
JTAG
Text Notes 2100 4600 0    100  ~ 0
USB
Wire Wire Line
	2900 5650 4000 5650
Wire Wire Line
	5000 5650 5150 5650
Wire Wire Line
	4000 5450 3800 5450
Wire Wire Line
	3800 5450 3800 5550
Wire Wire Line
	3150 5550 3800 5550
Wire Wire Line
	5000 5450 5150 5450
$Comp
L power:GND #PWR?
U 1 1 5EE51621
P 4500 6100
AR Path="/5EE51621" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5EE51621" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5EE51621" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 4500 5850 50  0001 C CNN
F 1 "GND" H 4505 5927 50  0000 C CNN
F 2 "" H 4500 6100 50  0001 C CNN
F 3 "" H 4500 6100 50  0001 C CNN
	1    4500 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 6050 4500 6100
Wire Notes Line
	2000 4400 5700 4400
Wire Notes Line
	2000 6500 5700 6500
Wire Wire Line
	3600 5350 3600 5050
Wire Wire Line
	3600 4750 3850 4750
Wire Wire Line
	2900 5350 3600 5350
$Comp
L Power_Protection:TPD2S017 U4
U 1 1 6118D2F9
P 4500 5550
F 0 "U4" H 4800 6050 50  0000 C CNN
F 1 "TPD2S017" H 4800 5950 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 3750 5200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tpd2s017.pdf" H 4500 5550 50  0001 C CNN
	1    4500 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6118E870
P 4050 5050
AR Path="/6118E870" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/6118E870" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/6118E870" Ref="R37"  Part="1" 
F 0 "R37" V 3950 5150 50  0000 C CNN
F 1 "0R" V 3950 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3980 5050 50  0001 C CNN
F 3 "~" H 4050 5050 50  0001 C CNN
	1    4050 5050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3900 5050 3600 5050
Connection ~ 3600 5050
Wire Wire Line
	4200 5050 4500 5050
Wire Wire Line
	3600 4750 3600 5050
$EndSCHEMATC
