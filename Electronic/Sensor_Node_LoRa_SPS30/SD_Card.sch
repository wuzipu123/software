EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title "SensMat Particle Sensor"
Date "2020-10-13"
Rev "v2"
Comp "Graz University of Technology - Stefan Ertl"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 3850 2850 0    50   Input ~ 0
SD_DAT2
Wire Wire Line
	5700 3250 3850 3250
Text HLabel 3850 2950 0    50   Input ~ 0
SD_CD
Text HLabel 3850 3050 0    50   Input ~ 0
SD_CMD
$Comp
L power:+3.3V #PWR042
U 1 1 5EE22429
P 3250 2950
F 0 "#PWR042" H 3250 2800 50  0001 C CNN
F 1 "+3.3V" H 3265 3123 50  0000 C CNN
F 2 "" H 3250 2950 50  0001 C CNN
F 3 "" H 3250 2950 50  0001 C CNN
	1    3250 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3150 3250 3050
Wire Wire Line
	3250 3150 5700 3150
$Comp
L power:GND #PWR043
U 1 1 5EE2318D
P 3250 3400
F 0 "#PWR043" H 3250 3150 50  0001 C CNN
F 1 "GND" H 3255 3227 50  0000 C CNN
F 2 "" H 3250 3400 50  0001 C CNN
F 3 "" H 3250 3400 50  0001 C CNN
	1    3250 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3350 3250 3400
Wire Wire Line
	3250 3350 5700 3350
Text HLabel 3850 3250 0    50   Input ~ 0
SD_CLK
Text HLabel 3850 3450 0    50   Input ~ 0
SD_DAT0
Text HLabel 3850 3550 0    50   Input ~ 0
SD_DAT1
Text HLabel 3850 3650 0    50   Input ~ 0
SD_DET
$Comp
L power:GND #PWR044
U 1 1 5EE24718
P 3250 3800
F 0 "#PWR044" H 3250 3550 50  0001 C CNN
F 1 "GND" H 3255 3627 50  0000 C CNN
F 2 "" H 3250 3800 50  0001 C CNN
F 3 "" H 3250 3800 50  0001 C CNN
	1    3250 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3750 3250 3800
$Comp
L Connector:Micro_SD_Card_Det J5
U 1 1 5EE18C61
P 6600 3250
F 0 "J5" H 6550 4067 50  0000 C CNN
F 1 "Micro_SD_Card_Det" H 6550 3976 50  0000 C CNN
F 2 "Connector_Card:microSD_HC_Hirose_DM3AT-SF-PEJM5" H 8650 3950 50  0001 C CNN
F 3 "https://www.hirose.com/product/en/download_file/key_name/DM3/category/Catalog/doc_file_id/49662/?file_category_id=4&item_id=195&is_series=1" H 6600 3350 50  0001 C CNN
	1    6600 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 3800 7450 3750
Wire Wire Line
	7400 3750 7450 3750
$Comp
L power:GND #PWR045
U 1 1 5EE2FD89
P 7450 3800
F 0 "#PWR045" H 7450 3550 50  0001 C CNN
F 1 "GND" H 7550 3650 50  0000 R CNN
F 2 "" H 7450 3800 50  0001 C CNN
F 3 "" H 7450 3800 50  0001 C CNN
	1    7450 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3750 5700 3750
Wire Wire Line
	3850 3050 5700 3050
Wire Wire Line
	3850 2950 5700 2950
Wire Wire Line
	3850 2850 5700 2850
Wire Wire Line
	3850 3450 5700 3450
Wire Wire Line
	3850 3550 5700 3550
Wire Wire Line
	3850 3650 5700 3650
$Comp
L Device:C C21
U 1 1 5EE1C1FB
P 3100 3200
F 0 "C21" H 3000 3300 50  0000 C CNN
F 1 "100nF" H 2950 3100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3138 3050 50  0001 C CNN
F 3 "~" H 3100 3200 50  0001 C CNN
	1    3100 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3050 3250 3050
Connection ~ 3250 3050
Wire Wire Line
	3250 3050 3250 2950
Wire Wire Line
	3100 3350 3250 3350
Connection ~ 3250 3350
$EndSCHEMATC
