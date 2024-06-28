EESchema Schematic File Version 4
LIBS:Mutterplatine-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
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
P 1850 3850
AR Path="/5CE61FC6" Ref="J?"  Part="1" 
AR Path="/5CE57A6D/5CE61FC6" Ref="J?"  Part="1" 
F 0 "J?" H 1550 4650 50  0000 R CNN
F 1 "Conn_ARM_JTAG_SWD_20" H 2850 4650 50  0000 R CNN
F 2 "" H 2300 2800 50  0001 L TNN
F 3 "http://infocenter.arm.com/help/topic/com.arm.doc.dui0499b/DUI0499B_system_design_reference.pdf" V 1500 2600 50  0001 C CNN
	1    1850 3850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J?
U 1 1 5CE61FCD
P 1950 1800
AR Path="/5CE61FCD" Ref="J?"  Part="1" 
AR Path="/5CE57A6D/5CE61FCD" Ref="J?"  Part="1" 
F 0 "J?" H 2100 2150 50  0000 C CNN
F 1 "Conn_01x06_Male" H 2150 1400 50  0000 C CNN
F 2 "" H 1950 1800 50  0001 C CNN
F 3 "~" H 1950 1800 50  0001 C CNN
	1    1950 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 3350 2700 3350
Wire Wire Line
	2450 3750 2700 3750
Wire Wire Line
	2450 3850 2700 3850
Wire Wire Line
	2450 3950 2700 3950
Wire Wire Line
	2450 4050 2700 4050
$Comp
L Device:R R?
U 1 1 5CE61FDE
P 2900 4250
AR Path="/5CE61FDE" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5CE61FDE" Ref="R?"  Part="1" 
F 0 "R?" V 2800 4200 50  0000 L CNN
F 1 "10k" V 3000 4200 50  0000 L CNN
F 2 "" V 2830 4250 50  0001 C CNN
F 3 "~" H 2900 4250 50  0001 C CNN
	1    2900 4250
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5CE61FE5
P 3400 3150
AR Path="/5CE61FE5" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CE61FE5" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3400 3000 50  0001 C CNN
F 1 "+3.3V" H 3415 3323 50  0000 C CNN
F 2 "" H 3400 3150 50  0001 C CNN
F 3 "" H 3400 3150 50  0001 C CNN
	1    3400 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5CE61FEB
P 2900 4550
AR Path="/5CE61FEB" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5CE61FEB" Ref="R?"  Part="1" 
F 0 "R?" V 2800 4500 50  0000 L CNN
F 1 "10k" V 3000 4500 50  0000 L CNN
F 2 "" V 2830 4550 50  0001 C CNN
F 3 "~" H 2900 4550 50  0001 C CNN
	1    2900 4550
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 4250 2750 4250
Wire Wire Line
	2450 4350 2700 4350
Wire Wire Line
	2700 4350 2700 4550
Wire Wire Line
	2700 4550 2750 4550
$Comp
L Device:R R?
U 1 1 5CE61FF6
P 3400 3950
AR Path="/5CE61FF6" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5CE61FF6" Ref="R?"  Part="1" 
F 0 "R?" V 3300 3900 50  0000 L CNN
F 1 "10k" V 3500 3900 50  0000 L CNN
F 2 "" V 3330 3950 50  0001 C CNN
F 3 "~" H 3400 3950 50  0001 C CNN
	1    3400 3950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5CE61FFD
P 3400 3400
AR Path="/5CE61FFD" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5CE61FFD" Ref="R?"  Part="1" 
F 0 "R?" V 3300 3350 50  0000 L CNN
F 1 "DNP" V 3500 3350 50  0000 L CNN
F 2 "" V 3330 3400 50  0001 C CNN
F 3 "~" H 3400 3400 50  0001 C CNN
	1    3400 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	3050 4550 3400 4550
Wire Wire Line
	3400 4550 3400 4250
Wire Wire Line
	3050 4250 3400 4250
Connection ~ 3400 4250
Wire Wire Line
	3400 4250 3400 4100
Wire Wire Line
	2450 3650 3400 3650
Wire Wire Line
	3400 3650 3400 3800
Wire Wire Line
	3400 3550 3400 3650
Connection ~ 3400 3650
Wire Wire Line
	3400 3250 3400 3150
$Comp
L power:+3.3V #PWR?
U 1 1 5CE6200E
P 1800 2950
AR Path="/5CE6200E" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CE6200E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1800 2800 50  0001 C CNN
F 1 "+3.3V" H 1815 3123 50  0000 C CNN
F 2 "" H 1800 2950 50  0001 C CNN
F 3 "" H 1800 2950 50  0001 C CNN
	1    1800 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3050 1750 3000
Wire Wire Line
	1750 3000 1800 3000
Wire Wire Line
	1850 3000 1850 3050
Wire Wire Line
	1800 3000 1800 2950
Connection ~ 1800 3000
Wire Wire Line
	1800 3000 1850 3000
$Comp
L power:GND #PWR?
U 1 1 5CE6201A
P 1750 4750
AR Path="/5CE6201A" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CE6201A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1750 4500 50  0001 C CNN
F 1 "GND" H 1755 4577 50  0000 C CNN
F 2 "" H 1750 4750 50  0001 C CNN
F 3 "" H 1750 4750 50  0001 C CNN
	1    1750 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CE62020
P 3400 4650
AR Path="/5CE62020" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CE62020" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3400 4400 50  0001 C CNN
F 1 "GND" H 3405 4477 50  0000 C CNN
F 2 "" H 3400 4650 50  0001 C CNN
F 3 "" H 3400 4650 50  0001 C CNN
	1    3400 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 4550 3400 4650
Connection ~ 3400 4550
Wire Wire Line
	1750 4750 1750 4650
Wire Wire Line
	2450 3450 2700 3450
Wire Wire Line
	2150 1700 2450 1700
Wire Wire Line
	2150 1900 2450 1900
Wire Wire Line
	2150 2000 2450 2000
Wire Wire Line
	2150 2100 2450 2100
Text HLabel 2700 3350 2    50   Input ~ 0
TRST
Text HLabel 2700 3450 2    50   Input ~ 0
NRST
Text HLabel 2700 3750 2    50   Input ~ 0
SWCLK
Text HLabel 2700 3850 2    50   Input ~ 0
SWDIO
Text HLabel 2700 3950 2    50   Input ~ 0
SWO
Text HLabel 2700 4050 2    50   Input ~ 0
TDI
Text HLabel 2450 2000 2    50   Input ~ 0
NRST
Text HLabel 2450 1700 2    50   Input ~ 0
SWCLK
Text HLabel 2450 1900 2    50   Input ~ 0
SWDIO
Text HLabel 2450 2100 2    50   Input ~ 0
SWO
$Comp
L power:+3.3V #PWR?
U 1 1 5CF4D72C
P 2900 1600
AR Path="/5CF4D72C" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CF4D72C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2900 1450 50  0001 C CNN
F 1 "+3.3V" H 2915 1773 50  0000 C CNN
F 2 "" H 2900 1600 50  0001 C CNN
F 3 "" H 2900 1600 50  0001 C CNN
	1    2900 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CF4D749
P 2900 1800
AR Path="/5CF4D749" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5CF4D749" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2900 1550 50  0001 C CNN
F 1 "GND" H 2905 1627 50  0000 C CNN
F 2 "" H 2900 1800 50  0001 C CNN
F 3 "" H 2900 1800 50  0001 C CNN
	1    2900 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 1600 2900 1600
Wire Wire Line
	2150 1800 2900 1800
$Comp
L Connector:Micro_SD_Card_Det J?
U 1 1 5DFB3C50
P 9550 2300
AR Path="/5DFB3C50" Ref="J?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C50" Ref="J?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C50" Ref="J?"  Part="1" 
F 0 "J?" H 9550 1700 50  0000 C CNN
F 1 "Micro_SD_Card_Det" H 9550 1600 50  0000 C CNN
F 2 "" H 11600 3000 50  0001 C CNN
F 3 "https://www.hirose.com/product/en/download_file/key_name/DM3/category/Catalog/doc_file_id/49662/?file_category_id=4&item_id=195&is_series=1" H 9550 2400 50  0001 C CNN
	1    9550 2300
	1    0    0    -1  
$EndComp
Text Label 6700 2400 0    50   ~ 0
GND
Text Label 6700 2200 0    50   ~ 0
3.3V
Text Label 6700 2300 0    50   ~ 0
SD_CLK
Text Label 6700 2500 0    50   ~ 0
SD_D0
Text Label 6700 2600 0    50   ~ 0
SD_D1
Text Label 6700 1900 0    50   ~ 0
SD_D2
Text Label 6700 2000 0    50   ~ 0
SD_D3
Text Label 6700 2100 0    50   ~ 0
SD_CMD
$Comp
L power:GND #PWR?
U 1 1 5DFB3C5F
P 10400 2900
AR Path="/5DFB3C5F" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C5F" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C5F" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10400 2650 50  0001 C CNN
F 1 "GND" H 10405 2727 50  0000 C CNN
F 2 "" H 10400 2900 50  0001 C CNN
F 3 "" H 10400 2900 50  0001 C CNN
	1    10400 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 2800 10400 2800
Wire Wire Line
	10400 2800 10400 2900
$Comp
L Device:R R?
U 1 1 5DFB3C67
P 7150 1600
AR Path="/5DFB3C67" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C67" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C67" Ref="R?"  Part="1" 
F 0 "R?" H 7200 1650 50  0000 L CNN
F 1 "47k" H 7200 1550 50  0000 L CNN
F 2 "" V 7080 1600 50  0001 C CNN
F 3 "~" H 7150 1600 50  0001 C CNN
	1    7150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1900 7150 1900
$Comp
L Device:R R?
U 1 1 5DFB3C6F
P 7400 1600
AR Path="/5DFB3C6F" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C6F" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C6F" Ref="R?"  Part="1" 
F 0 "R?" H 7470 1646 50  0000 L CNN
F 1 "47k" H 7450 1550 50  0000 L CNN
F 2 "" V 7330 1600 50  0001 C CNN
F 3 "~" H 7400 1600 50  0001 C CNN
	1    7400 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFB3C76
P 7650 1600
AR Path="/5DFB3C76" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C76" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C76" Ref="R?"  Part="1" 
F 0 "R?" H 7720 1646 50  0000 L CNN
F 1 "47k" H 7700 1550 50  0000 L CNN
F 2 "" V 7580 1600 50  0001 C CNN
F 3 "~" H 7650 1600 50  0001 C CNN
	1    7650 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFB3C7D
P 7900 1600
AR Path="/5DFB3C7D" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C7D" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C7D" Ref="R?"  Part="1" 
F 0 "R?" H 7970 1646 50  0000 L CNN
F 1 "47k" H 7950 1550 50  0000 L CNN
F 2 "" V 7830 1600 50  0001 C CNN
F 3 "~" H 7900 1600 50  0001 C CNN
	1    7900 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFB3C84
P 8150 1600
AR Path="/5DFB3C84" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3C84" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3C84" Ref="R?"  Part="1" 
F 0 "R?" H 8220 1646 50  0000 L CNN
F 1 "47k" H 8200 1550 50  0000 L CNN
F 2 "" V 8080 1600 50  0001 C CNN
F 3 "~" H 8150 1600 50  0001 C CNN
	1    8150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 1750 7150 1900
Wire Wire Line
	6700 2000 7400 2000
Wire Wire Line
	6700 2100 7650 2100
Wire Wire Line
	6700 2500 7900 2500
Wire Wire Line
	6700 2600 8150 2600
Connection ~ 7150 1900
Wire Wire Line
	7400 1750 7400 2000
Connection ~ 7400 2000
Wire Wire Line
	7650 1750 7650 2100
Connection ~ 7650 2100
Wire Wire Line
	7900 1750 7900 2500
Connection ~ 7900 2500
Wire Wire Line
	8150 1750 8150 2600
Connection ~ 8150 2600
Wire Wire Line
	7150 1450 7150 1350
Wire Wire Line
	7150 1350 7400 1350
Wire Wire Line
	8150 1350 8150 1450
Wire Wire Line
	7900 1450 7900 1350
Connection ~ 7900 1350
Wire Wire Line
	7900 1350 8150 1350
Wire Wire Line
	7650 1450 7650 1350
Connection ~ 7650 1350
Wire Wire Line
	7650 1350 7900 1350
Wire Wire Line
	7400 1450 7400 1350
Connection ~ 7400 1350
Wire Wire Line
	7400 1350 7650 1350
Connection ~ 8150 1350
$Comp
L power:GND #PWR?
U 1 1 5DFB3CA6
P 9300 1400
AR Path="/5DFB3CA6" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CA6" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CA6" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9300 1150 50  0001 C CNN
F 1 "GND" H 9305 1227 50  0000 C CNN
F 2 "" H 9300 1400 50  0001 C CNN
F 3 "" H 9300 1400 50  0001 C CNN
	1    9300 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DFB3CAC
P 8150 1200
AR Path="/5DFB3CAC" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CAC" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CAC" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8150 1050 50  0001 C CNN
F 1 "+3.3V" H 8165 1373 50  0000 C CNN
F 2 "" H 8150 1200 50  0001 C CNN
F 3 "" H 8150 1200 50  0001 C CNN
	1    8150 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DFB3CB2
P 9000 1350
AR Path="/5DFB3CB2" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CB2" Ref="C?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CB2" Ref="C?"  Part="1" 
F 0 "C?" V 8748 1350 50  0000 C CNN
F 1 "100n" V 8839 1350 50  0000 C CNN
F 2 "" H 9038 1200 50  0001 C CNN
F 3 "~" H 9000 1350 50  0001 C CNN
	1    9000 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	9150 1350 9300 1350
Wire Wire Line
	9300 1350 9300 1400
Wire Wire Line
	8150 1350 8150 1200
$Comp
L power:GND #PWR?
U 1 1 5DFB3CBC
P 8600 2900
AR Path="/5DFB3CBC" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CBC" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CBC" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8600 2650 50  0001 C CNN
F 1 "GND" H 8605 2727 50  0000 C CNN
F 2 "" H 8600 2900 50  0001 C CNN
F 3 "" H 8600 2900 50  0001 C CNN
	1    8600 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 2800 8600 2800
Wire Wire Line
	8600 2800 8600 2900
Wire Wire Line
	7150 1900 8650 1900
Wire Wire Line
	6700 2300 8650 2300
Wire Wire Line
	7400 2000 8650 2000
Wire Wire Line
	7650 2100 8650 2100
Wire Wire Line
	7900 2500 8650 2500
Wire Wire Line
	8150 2600 8650 2600
Wire Wire Line
	8150 1350 8400 1350
$Comp
L Device:R R?
U 1 1 5DFB3CCB
P 8400 1600
AR Path="/5DFB3CCB" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CCB" Ref="R?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CCB" Ref="R?"  Part="1" 
F 0 "R?" H 8470 1646 50  0000 L CNN
F 1 "47k" H 8450 1550 50  0000 L CNN
F 2 "" V 8330 1600 50  0001 C CNN
F 3 "~" H 8400 1600 50  0001 C CNN
	1    8400 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 1350 8400 1450
Connection ~ 8400 1350
Wire Wire Line
	8400 1350 8850 1350
Wire Wire Line
	8400 1750 8400 2700
Wire Wire Line
	8400 2700 8650 2700
Wire Wire Line
	8400 2700 6700 2700
Connection ~ 8400 2700
Text Label 6700 2700 0    50   ~ 0
SD_detect
Text HLabel 6700 1900 0    50   Input ~ 0
SD_D2
Text HLabel 6700 2000 0    50   Input ~ 0
SD_D3
Text HLabel 6700 2100 0    50   Input ~ 0
SD_CMD
Text HLabel 6700 2300 0    50   Input ~ 0
SD_CLK
Text HLabel 6700 2500 0    50   Input ~ 0
SD_D0
Text HLabel 6700 2600 0    50   Input ~ 0
SD_D1
Text HLabel 6700 2700 0    50   Input ~ 0
SD_detect
Wire Wire Line
	6200 2200 8650 2200
Wire Wire Line
	6200 2400 8650 2400
$Comp
L power:GND #PWR?
U 1 1 5DFB3CE3
P 6200 2400
AR Path="/5DFB3CE3" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CE3" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CE3" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6200 2150 50  0001 C CNN
F 1 "GND" H 6205 2227 50  0000 C CNN
F 2 "" H 6200 2400 50  0001 C CNN
F 3 "" H 6200 2400 50  0001 C CNN
	1    6200 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DFB3CE9
P 6200 2200
AR Path="/5DFB3CE9" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFB3CE9" Ref="#PWR?"  Part="1" 
AR Path="/5CE57A6D/5DFB3CE9" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6200 2050 50  0001 C CNN
F 1 "+3.3V" H 6215 2373 50  0000 C CNN
F 2 "" H 6200 2200 50  0001 C CNN
F 3 "" H 6200 2200 50  0001 C CNN
	1    6200 2200
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J?
U 1 1 5DFBE218
P 6950 4900
AR Path="/5DFBE218" Ref="J?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE218" Ref="J?"  Part="1" 
F 0 "J?" H 7005 5367 50  0000 C CNN
F 1 "USB_B_Micro" H 7005 5276 50  0000 C CNN
F 2 "" H 7100 4850 50  0001 C CNN
F 3 "~" H 7100 4850 50  0001 C CNN
	1    6950 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DFBE21F
P 6900 5400
AR Path="/5DFBE21F" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE21F" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6900 5150 50  0001 C CNN
F 1 "GND" H 6905 5227 50  0000 C CNN
F 2 "" H 6900 5400 50  0001 C CNN
F 3 "" H 6900 5400 50  0001 C CNN
	1    6900 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 5300 6850 5350
Wire Wire Line
	6850 5350 6900 5350
Wire Wire Line
	6950 5350 6950 5300
Wire Wire Line
	6900 5400 6900 5350
Connection ~ 6900 5350
Wire Wire Line
	6900 5350 6950 5350
Text Notes 7300 5150 0    50   ~ 0
floating for USB_Slave
$Comp
L Device:R R?
U 1 1 5DFBE22C
P 7500 4400
AR Path="/5DFBE22C" Ref="R?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE22C" Ref="R?"  Part="1" 
F 0 "R?" H 7350 4350 50  0000 C CNN
F 1 "1k5" H 7350 4450 50  0000 C CNN
F 2 "" V 7430 4400 50  0001 C CNN
F 3 "~" H 7500 4400 50  0001 C CNN
	1    7500 4400
	-1   0    0    1   
$EndComp
Wire Wire Line
	7250 4700 7750 4700
Wire Wire Line
	7250 5000 7750 5000
$Comp
L power:+3.3V #PWR?
U 1 1 5DFBE235
P 7500 4150
AR Path="/5DFBE235" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFBE235" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7500 4000 50  0001 C CNN
F 1 "+3.3V" H 7515 4323 50  0000 C CNN
F 2 "" H 7500 4150 50  0001 C CNN
F 3 "" H 7500 4150 50  0001 C CNN
	1    7500 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 4150 7500 4250
Wire Wire Line
	7250 4900 7500 4900
Wire Wire Line
	7500 4550 7500 4900
Connection ~ 7500 4900
Wire Wire Line
	7500 4900 7750 4900
Text HLabel 7750 4700 2    50   Input ~ 0
VDD_USB
Text HLabel 7750 4900 2    50   Input ~ 0
USB_DP
Text HLabel 7750 5000 2    50   Input ~ 0
USB_DM
$EndSCHEMATC
