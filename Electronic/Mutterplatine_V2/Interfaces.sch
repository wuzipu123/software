EESchema Schematic File Version 4
LIBS:Mutterplatine-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 7
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
L power:GND #PWR?
U 1 1 5D498478
P 850 1000
AR Path="/5D498478" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D498478" Ref="#PWR053"  Part="1" 
F 0 "#PWR053" H 850 750 50  0001 C CNN
F 1 "GND" H 855 827 50  0000 C CNN
F 2 "" H 850 1000 50  0001 C CNN
F 3 "" H 850 1000 50  0001 C CNN
	1    850  1000
	1    0    0    -1  
$EndComp
Text Notes 9550 2800 0    67   ~ 0
DSUB 15 \n\nPin 1: VCC\nPin 9: VCC\nPin 2: NC\nPin 10: Control Pin1\nPin 3: Control Pin 0\nPin 11: RS485_Z\nPin 4: RS485_Y\nPin 12: RS485_B\nPin 5: RS485_A\nPin 13: Adr0\nPin 6: Adr1\nPin 14: Adr2\nPin 7: NC\nPin 15: GND\nPin 8: GND\n
Text HLabel 1100 2500 0    50   Input ~ 0
C0CP0
Text HLabel 2100 2500 2    50   Input ~ 0
C0CP1
$Comp
L Power_Management:TPS22929D U?
U 1 1 5DFFBF5C
P 1900 5550
AR Path="/5DFFBF5C" Ref="U?"  Part="1" 
AR Path="/5CB6FAF3/5DFFBF5C" Ref="U6"  Part="1" 
F 0 "U6" H 1900 5650 50  0000 C CNN
F 1 "TPS22929D" H 1900 5926 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 1900 5150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps22929d.pdf" H 1800 6000 50  0001 C CNN
	1    1900 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DFFBF63
P 1950 5950
AR Path="/5DFFBF63" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5DFFBF63" Ref="#PWR054"  Part="1" 
F 0 "#PWR054" H 1950 5700 50  0001 C CNN
F 1 "GND" H 1955 5777 50  0000 C CNN
F 2 "" H 1950 5950 50  0001 C CNN
F 3 "" H 1950 5950 50  0001 C CNN
	1    1950 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 5350 1450 5350
Wire Wire Line
	1450 5350 1450 5450
Wire Wire Line
	1450 5450 1500 5450
Connection ~ 1450 5350
Text Label 2350 5350 0    50   ~ 0
Vout0
Text Label 4450 5350 0    50   ~ 0
Vout1
Text Label 2250 6800 0    50   ~ 0
Vout3
Text Label 4350 6800 0    50   ~ 0
Vout4
Text Label 6550 6800 0    50   ~ 0
Vout5
Text Label 6600 5400 0    50   ~ 0
Vout2
Text Label 1100 900  2    50   ~ 0
Vout0
Text HLabel 1250 5650 0    50   Input ~ 0
V0_en
Text HLabel 3350 5650 0    50   Input ~ 0
V1_en
Text HLabel 1150 7100 0    50   Input ~ 0
V3_en
Text HLabel 3250 7100 0    50   Input ~ 0
V4_en
Text HLabel 5450 7100 0    50   Input ~ 0
V5_en
Text HLabel 5500 5700 0    50   Input ~ 0
V2_en
$Comp
L power:+5V #PWR050
U 1 1 5E071104
P 1450 5100
F 0 "#PWR050" H 1450 4950 50  0001 C CNN
F 1 "+5V" H 1465 5273 50  0000 C CNN
F 2 "" H 1450 5100 50  0001 C CNN
F 3 "" H 1450 5100 50  0001 C CNN
	1    1450 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5E0713AD
P 1100 5150
AR Path="/5E0713AD" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5E0713AD" Ref="C21"  Part="1" 
F 0 "C21" V 1150 5350 50  0000 R CNN
F 1 "100n" V 1050 5100 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1138 5000 50  0001 C CNN
F 3 "~" H 1100 5150 50  0001 C CNN
	1    1100 5150
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5E0713B4
P 1100 5450
AR Path="/5E0713B4" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5E0713B4" Ref="C22"  Part="1" 
F 0 "C22" V 1150 5650 50  0000 R CNN
F 1 "10u" V 1150 5400 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1138 5300 50  0001 C CNN
F 3 "~" H 1100 5450 50  0001 C CNN
	1    1100 5450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E0713BB
P 850 5300
AR Path="/5E0713BB" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E0713BB" Ref="#PWR046"  Part="1" 
F 0 "#PWR046" H 850 5050 50  0001 C CNN
F 1 "GND" V 850 5100 50  0000 C CNN
F 2 "" H 850 5300 50  0001 C CNN
F 3 "" H 850 5300 50  0001 C CNN
	1    850  5300
	0    1    1    0   
$EndComp
Wire Wire Line
	950  5450 900  5450
Wire Wire Line
	850  5300 900  5300
Wire Wire Line
	2300 5350 2350 5350
Wire Wire Line
	1250 5650 1400 5650
$Comp
L Device:R R43
U 1 1 5E1ECD74
P 1400 5850
F 0 "R43" H 1470 5896 50  0000 L CNN
F 1 "10k" H 1470 5805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1330 5850 50  0001 C CNN
F 3 "~" H 1400 5850 50  0001 C CNN
	1    1400 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E1ECDC8
P 1400 6050
AR Path="/5E1ECDC8" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E1ECDC8" Ref="#PWR049"  Part="1" 
F 0 "#PWR049" H 1400 5800 50  0001 C CNN
F 1 "GND" H 1405 5877 50  0000 C CNN
F 2 "" H 1400 6050 50  0001 C CNN
F 3 "" H 1400 6050 50  0001 C CNN
	1    1400 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 5700 1400 5650
Connection ~ 1400 5650
Wire Wire Line
	1400 5650 1500 5650
Wire Wire Line
	1400 6000 1400 6050
$Comp
L Power_Management:TPS22929D U?
U 1 1 5E243C17
P 1800 7000
AR Path="/5E243C17" Ref="U?"  Part="1" 
AR Path="/5CB6FAF3/5E243C17" Ref="U7"  Part="1" 
F 0 "U7" H 1800 7100 50  0000 C CNN
F 1 "TPS22929D" H 1800 7376 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 1800 6600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps22929d.pdf" H 1700 7450 50  0001 C CNN
	1    1800 7000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E243C1E
P 1850 7400
AR Path="/5E243C1E" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E243C1E" Ref="#PWR055"  Part="1" 
F 0 "#PWR055" H 1850 7150 50  0001 C CNN
F 1 "GND" H 1855 7227 50  0000 C CNN
F 2 "" H 1850 7400 50  0001 C CNN
F 3 "" H 1850 7400 50  0001 C CNN
	1    1850 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 6800 2250 6800
Wire Wire Line
	1150 7100 1300 7100
$Comp
L Device:R R44
U 1 1 5E243C55
P 1300 7300
F 0 "R44" H 1370 7346 50  0000 L CNN
F 1 "10k" H 1370 7255 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1230 7300 50  0001 C CNN
F 3 "~" H 1300 7300 50  0001 C CNN
	1    1300 7300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E243C5C
P 1300 7500
AR Path="/5E243C5C" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E243C5C" Ref="#PWR051"  Part="1" 
F 0 "#PWR051" H 1300 7250 50  0001 C CNN
F 1 "GND" H 1305 7327 50  0000 C CNN
F 2 "" H 1300 7500 50  0001 C CNN
F 3 "" H 1300 7500 50  0001 C CNN
	1    1300 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 7150 1300 7100
Connection ~ 1300 7100
Wire Wire Line
	1300 7100 1400 7100
Wire Wire Line
	1300 7450 1300 7500
$Comp
L Power_Management:TPS22929D U?
U 1 1 5E2549DE
P 4000 5550
AR Path="/5E2549DE" Ref="U?"  Part="1" 
AR Path="/5CB6FAF3/5E2549DE" Ref="U8"  Part="1" 
F 0 "U8" H 4000 5650 50  0000 C CNN
F 1 "TPS22929D" H 4000 5926 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 4000 5150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps22929d.pdf" H 3900 6000 50  0001 C CNN
	1    4000 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E2549E5
P 4050 5950
AR Path="/5E2549E5" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E2549E5" Ref="#PWR063"  Part="1" 
F 0 "#PWR063" H 4050 5700 50  0001 C CNN
F 1 "GND" H 4055 5777 50  0000 C CNN
F 2 "" H 4050 5950 50  0001 C CNN
F 3 "" H 4050 5950 50  0001 C CNN
	1    4050 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5350 4450 5350
Wire Wire Line
	3350 5650 3500 5650
$Comp
L Device:R R45
U 1 1 5E254A1C
P 3500 5850
F 0 "R45" H 3570 5896 50  0000 L CNN
F 1 "10k" H 3570 5805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3430 5850 50  0001 C CNN
F 3 "~" H 3500 5850 50  0001 C CNN
	1    3500 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E254A23
P 3500 6050
AR Path="/5E254A23" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E254A23" Ref="#PWR058"  Part="1" 
F 0 "#PWR058" H 3500 5800 50  0001 C CNN
F 1 "GND" H 3505 5877 50  0000 C CNN
F 2 "" H 3500 6050 50  0001 C CNN
F 3 "" H 3500 6050 50  0001 C CNN
	1    3500 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 5700 3500 5650
Connection ~ 3500 5650
Wire Wire Line
	3500 5650 3600 5650
Wire Wire Line
	3500 6000 3500 6050
$Comp
L Power_Management:TPS22929D U?
U 1 1 5E268777
P 3900 7000
AR Path="/5E268777" Ref="U?"  Part="1" 
AR Path="/5CB6FAF3/5E268777" Ref="U9"  Part="1" 
F 0 "U9" H 3900 7100 50  0000 C CNN
F 1 "TPS22929D" H 3900 7376 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 3900 6600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps22929d.pdf" H 3800 7450 50  0001 C CNN
	1    3900 7000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E26877E
P 3950 7400
AR Path="/5E26877E" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E26877E" Ref="#PWR064"  Part="1" 
F 0 "#PWR064" H 3950 7150 50  0001 C CNN
F 1 "GND" H 3955 7227 50  0000 C CNN
F 2 "" H 3950 7400 50  0001 C CNN
F 3 "" H 3950 7400 50  0001 C CNN
	1    3950 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 6800 4350 6800
Wire Wire Line
	3250 7100 3400 7100
$Comp
L Device:R R46
U 1 1 5E2687B5
P 3400 7300
F 0 "R46" H 3470 7346 50  0000 L CNN
F 1 "10k" H 3470 7255 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3330 7300 50  0001 C CNN
F 3 "~" H 3400 7300 50  0001 C CNN
	1    3400 7300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E2687BC
P 3400 7500
AR Path="/5E2687BC" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E2687BC" Ref="#PWR060"  Part="1" 
F 0 "#PWR060" H 3400 7250 50  0001 C CNN
F 1 "GND" H 3405 7327 50  0000 C CNN
F 2 "" H 3400 7500 50  0001 C CNN
F 3 "" H 3400 7500 50  0001 C CNN
	1    3400 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 7150 3400 7100
Connection ~ 3400 7100
Wire Wire Line
	3400 7100 3500 7100
Wire Wire Line
	3400 7450 3400 7500
$Comp
L Power_Management:TPS22929D U?
U 1 1 5E2E7DC8
P 6150 5600
AR Path="/5E2E7DC8" Ref="U?"  Part="1" 
AR Path="/5CB6FAF3/5E2E7DC8" Ref="U10"  Part="1" 
F 0 "U10" H 6150 5700 50  0000 C CNN
F 1 "TPS22929D" H 6150 5976 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 6150 5200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps22929d.pdf" H 6050 6050 50  0001 C CNN
	1    6150 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E2E7DCF
P 6200 6000
AR Path="/5E2E7DCF" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E2E7DCF" Ref="#PWR071"  Part="1" 
F 0 "#PWR071" H 6200 5750 50  0001 C CNN
F 1 "GND" H 6205 5827 50  0000 C CNN
F 2 "" H 6200 6000 50  0001 C CNN
F 3 "" H 6200 6000 50  0001 C CNN
	1    6200 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 5400 6600 5400
Wire Wire Line
	5500 5700 5650 5700
$Comp
L Device:R R47
U 1 1 5E2E7E06
P 5650 5900
F 0 "R47" H 5720 5946 50  0000 L CNN
F 1 "10k" H 5720 5855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5580 5900 50  0001 C CNN
F 3 "~" H 5650 5900 50  0001 C CNN
	1    5650 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E2E7E0D
P 5650 6100
AR Path="/5E2E7E0D" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E2E7E0D" Ref="#PWR067"  Part="1" 
F 0 "#PWR067" H 5650 5850 50  0001 C CNN
F 1 "GND" H 5655 5927 50  0000 C CNN
F 2 "" H 5650 6100 50  0001 C CNN
F 3 "" H 5650 6100 50  0001 C CNN
	1    5650 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 5750 5650 5700
Connection ~ 5650 5700
Wire Wire Line
	5650 5700 5750 5700
Wire Wire Line
	5650 6050 5650 6100
$Comp
L Power_Management:TPS22929D U?
U 1 1 5E309E9A
P 6100 7000
AR Path="/5E309E9A" Ref="U?"  Part="1" 
AR Path="/5CB6FAF3/5E309E9A" Ref="U11"  Part="1" 
F 0 "U11" H 6100 7100 50  0000 C CNN
F 1 "TPS22929D" H 6100 7376 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 6100 6600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps22929d.pdf" H 6000 7450 50  0001 C CNN
	1    6100 7000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E309EA1
P 6150 7400
AR Path="/5E309EA1" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E309EA1" Ref="#PWR072"  Part="1" 
F 0 "#PWR072" H 6150 7150 50  0001 C CNN
F 1 "GND" H 6155 7227 50  0000 C CNN
F 2 "" H 6150 7400 50  0001 C CNN
F 3 "" H 6150 7400 50  0001 C CNN
	1    6150 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 6800 6550 6800
Wire Wire Line
	5450 7100 5600 7100
$Comp
L Device:R R48
U 1 1 5E309ED8
P 5600 7300
F 0 "R48" H 5670 7346 50  0000 L CNN
F 1 "10k" H 5670 7255 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5530 7300 50  0001 C CNN
F 3 "~" H 5600 7300 50  0001 C CNN
	1    5600 7300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E309EDF
P 5600 7500
AR Path="/5E309EDF" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5E309EDF" Ref="#PWR069"  Part="1" 
F 0 "#PWR069" H 5600 7250 50  0001 C CNN
F 1 "GND" H 5605 7327 50  0000 C CNN
F 2 "" H 5600 7500 50  0001 C CNN
F 3 "" H 5600 7500 50  0001 C CNN
	1    5600 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 7150 5600 7100
Connection ~ 5600 7100
Wire Wire Line
	5600 7100 5700 7100
Wire Wire Line
	5600 7450 5600 7500
Wire Wire Line
	1900 5850 1900 5900
Wire Wire Line
	1900 5900 1950 5900
Wire Wire Line
	2000 5900 2000 5850
Wire Wire Line
	1950 5950 1950 5900
Connection ~ 1950 5900
Wire Wire Line
	1950 5900 2000 5900
Wire Wire Line
	4000 5850 4000 5900
Wire Wire Line
	4000 5900 4050 5900
Wire Wire Line
	4100 5900 4100 5850
Wire Wire Line
	4050 5950 4050 5900
Connection ~ 4050 5900
Wire Wire Line
	4050 5900 4100 5900
Wire Wire Line
	6150 5900 6150 5950
Wire Wire Line
	6150 5950 6200 5950
Wire Wire Line
	6250 5950 6250 5900
Wire Wire Line
	6200 6000 6200 5950
Connection ~ 6200 5950
Wire Wire Line
	6200 5950 6250 5950
Wire Wire Line
	1800 7300 1800 7350
Wire Wire Line
	1800 7350 1850 7350
Wire Wire Line
	1900 7350 1900 7300
Wire Wire Line
	1850 7400 1850 7350
Connection ~ 1850 7350
Wire Wire Line
	1850 7350 1900 7350
Wire Wire Line
	3900 7300 3900 7350
Wire Wire Line
	3900 7350 3950 7350
Wire Wire Line
	4000 7350 4000 7300
Wire Wire Line
	3950 7400 3950 7350
Connection ~ 3950 7350
Wire Wire Line
	3950 7350 4000 7350
Wire Wire Line
	6100 7300 6100 7350
Wire Wire Line
	6100 7350 6150 7350
Wire Wire Line
	6200 7350 6200 7300
Wire Wire Line
	6150 7400 6150 7350
Connection ~ 6150 7350
Wire Wire Line
	6150 7350 6200 7350
Text HLabel 1100 1600 0    50   Input ~ 0
RS485_A
Text HLabel 1100 1700 0    50   Input ~ 0
RS485_B
Text HLabel 1100 1900 0    50   Input ~ 0
RS485_Y
Text HLabel 1100 1800 0    50   Input ~ 0
RS485_Z
Wire Wire Line
	900  5450 900  5300
Wire Wire Line
	900  5150 950  5150
Connection ~ 900  5300
Wire Wire Line
	900  5300 900  5150
Wire Wire Line
	1250 5450 1450 5450
Connection ~ 1450 5450
Wire Wire Line
	1250 5150 1450 5150
Wire Wire Line
	1450 5150 1450 5350
Wire Wire Line
	1450 5100 1450 5150
Connection ~ 1450 5150
Wire Wire Line
	3600 5350 3550 5350
Wire Wire Line
	3550 5350 3550 5450
Wire Wire Line
	3550 5450 3600 5450
Connection ~ 3550 5350
$Comp
L power:+5V #PWR059
U 1 1 5FC396D9
P 3550 5100
F 0 "#PWR059" H 3550 4950 50  0001 C CNN
F 1 "+5V" H 3565 5273 50  0000 C CNN
F 2 "" H 3550 5100 50  0001 C CNN
F 3 "" H 3550 5100 50  0001 C CNN
	1    3550 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FC396DF
P 3200 5150
AR Path="/5FC396DF" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5FC396DF" Ref="C25"  Part="1" 
F 0 "C25" V 3150 5350 50  0000 R CNN
F 1 "100n" V 3150 5100 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3238 5000 50  0001 C CNN
F 3 "~" H 3200 5150 50  0001 C CNN
	1    3200 5150
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FC396E6
P 3200 5450
AR Path="/5FC396E6" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5FC396E6" Ref="C26"  Part="1" 
F 0 "C26" V 3250 5650 50  0000 R CNN
F 1 "10u" V 3250 5400 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3238 5300 50  0001 C CNN
F 3 "~" H 3200 5450 50  0001 C CNN
	1    3200 5450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FC396ED
P 2950 5300
AR Path="/5FC396ED" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5FC396ED" Ref="#PWR056"  Part="1" 
F 0 "#PWR056" H 2950 5050 50  0001 C CNN
F 1 "GND" V 2950 5100 50  0000 C CNN
F 2 "" H 2950 5300 50  0001 C CNN
F 3 "" H 2950 5300 50  0001 C CNN
	1    2950 5300
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 5450 3000 5450
Wire Wire Line
	2950 5300 3000 5300
Wire Wire Line
	3000 5450 3000 5300
Wire Wire Line
	3000 5150 3050 5150
Connection ~ 3000 5300
Wire Wire Line
	3000 5300 3000 5150
Wire Wire Line
	3350 5450 3550 5450
Connection ~ 3550 5450
Wire Wire Line
	3350 5150 3550 5150
Wire Wire Line
	3550 5150 3550 5350
Wire Wire Line
	3550 5100 3550 5150
Connection ~ 3550 5150
Wire Wire Line
	1400 6800 1350 6800
Wire Wire Line
	1350 6800 1350 6900
Wire Wire Line
	1350 6900 1400 6900
Connection ~ 1350 6800
$Comp
L power:+5V #PWR052
U 1 1 5FD2C511
P 1350 6550
F 0 "#PWR052" H 1350 6400 50  0001 C CNN
F 1 "+5V" H 1365 6723 50  0000 C CNN
F 2 "" H 1350 6550 50  0001 C CNN
F 3 "" H 1350 6550 50  0001 C CNN
	1    1350 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FD2C517
P 1000 6600
AR Path="/5FD2C517" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5FD2C517" Ref="C23"  Part="1" 
F 0 "C23" V 950 6800 50  0000 R CNN
F 1 "100n" V 950 6550 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1038 6450 50  0001 C CNN
F 3 "~" H 1000 6600 50  0001 C CNN
	1    1000 6600
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FD2C51E
P 1000 6900
AR Path="/5FD2C51E" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5FD2C51E" Ref="C24"  Part="1" 
F 0 "C24" V 1050 7100 50  0000 R CNN
F 1 "10u" V 1050 6850 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1038 6750 50  0001 C CNN
F 3 "~" H 1000 6900 50  0001 C CNN
	1    1000 6900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FD2C525
P 750 6750
AR Path="/5FD2C525" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5FD2C525" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 750 6500 50  0001 C CNN
F 1 "GND" V 750 6550 50  0000 C CNN
F 2 "" H 750 6750 50  0001 C CNN
F 3 "" H 750 6750 50  0001 C CNN
	1    750  6750
	0    1    1    0   
$EndComp
Wire Wire Line
	850  6900 800  6900
Wire Wire Line
	750  6750 800  6750
Wire Wire Line
	800  6900 800  6750
Wire Wire Line
	800  6600 850  6600
Connection ~ 800  6750
Wire Wire Line
	800  6750 800  6600
Wire Wire Line
	1150 6900 1350 6900
Connection ~ 1350 6900
Wire Wire Line
	1150 6600 1350 6600
Wire Wire Line
	1350 6600 1350 6800
Wire Wire Line
	1350 6550 1350 6600
Connection ~ 1350 6600
Wire Wire Line
	3500 6800 3450 6800
Wire Wire Line
	3450 6800 3450 6900
Wire Wire Line
	3450 6900 3500 6900
Connection ~ 3450 6800
$Comp
L power:+5V #PWR061
U 1 1 5FDB8BAC
P 3450 6550
F 0 "#PWR061" H 3450 6400 50  0001 C CNN
F 1 "+5V" H 3465 6723 50  0000 C CNN
F 2 "" H 3450 6550 50  0001 C CNN
F 3 "" H 3450 6550 50  0001 C CNN
	1    3450 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FDB8BB2
P 3100 6600
AR Path="/5FDB8BB2" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5FDB8BB2" Ref="C27"  Part="1" 
F 0 "C27" V 3050 6800 50  0000 R CNN
F 1 "100n" V 3050 6550 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3138 6450 50  0001 C CNN
F 3 "~" H 3100 6600 50  0001 C CNN
	1    3100 6600
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FDB8BB9
P 3100 6900
AR Path="/5FDB8BB9" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5FDB8BB9" Ref="C28"  Part="1" 
F 0 "C28" V 3150 7100 50  0000 R CNN
F 1 "10u" V 3150 6850 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3138 6750 50  0001 C CNN
F 3 "~" H 3100 6900 50  0001 C CNN
	1    3100 6900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FDB8BC0
P 2850 6750
AR Path="/5FDB8BC0" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5FDB8BC0" Ref="#PWR057"  Part="1" 
F 0 "#PWR057" H 2850 6500 50  0001 C CNN
F 1 "GND" V 2850 6550 50  0000 C CNN
F 2 "" H 2850 6750 50  0001 C CNN
F 3 "" H 2850 6750 50  0001 C CNN
	1    2850 6750
	0    1    1    0   
$EndComp
Wire Wire Line
	2950 6900 2900 6900
Wire Wire Line
	2850 6750 2900 6750
Wire Wire Line
	2900 6900 2900 6750
Wire Wire Line
	2900 6600 2950 6600
Connection ~ 2900 6750
Wire Wire Line
	2900 6750 2900 6600
Wire Wire Line
	3250 6900 3450 6900
Connection ~ 3450 6900
Wire Wire Line
	3250 6600 3450 6600
Wire Wire Line
	3450 6600 3450 6800
Wire Wire Line
	3450 6550 3450 6600
Connection ~ 3450 6600
Wire Wire Line
	5750 5400 5700 5400
Wire Wire Line
	5700 5400 5700 5500
Wire Wire Line
	5700 5500 5750 5500
Connection ~ 5700 5400
$Comp
L power:+5V #PWR068
U 1 1 5FF2E177
P 5700 5150
F 0 "#PWR068" H 5700 5000 50  0001 C CNN
F 1 "+5V" H 5715 5323 50  0000 C CNN
F 2 "" H 5700 5150 50  0001 C CNN
F 3 "" H 5700 5150 50  0001 C CNN
	1    5700 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FF2E17D
P 5350 5200
AR Path="/5FF2E17D" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5FF2E17D" Ref="C29"  Part="1" 
F 0 "C29" V 5300 5400 50  0000 R CNN
F 1 "100n" V 5300 5150 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5388 5050 50  0001 C CNN
F 3 "~" H 5350 5200 50  0001 C CNN
	1    5350 5200
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FF2E184
P 5350 5500
AR Path="/5FF2E184" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5FF2E184" Ref="C30"  Part="1" 
F 0 "C30" V 5400 5700 50  0000 R CNN
F 1 "10u" V 5400 5450 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5388 5350 50  0001 C CNN
F 3 "~" H 5350 5500 50  0001 C CNN
	1    5350 5500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FF2E18B
P 5100 5350
AR Path="/5FF2E18B" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5FF2E18B" Ref="#PWR065"  Part="1" 
F 0 "#PWR065" H 5100 5100 50  0001 C CNN
F 1 "GND" V 5100 5150 50  0000 C CNN
F 2 "" H 5100 5350 50  0001 C CNN
F 3 "" H 5100 5350 50  0001 C CNN
	1    5100 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 5500 5150 5500
Wire Wire Line
	5100 5350 5150 5350
Wire Wire Line
	5150 5500 5150 5350
Wire Wire Line
	5150 5200 5200 5200
Connection ~ 5150 5350
Wire Wire Line
	5150 5350 5150 5200
Wire Wire Line
	5500 5500 5700 5500
Connection ~ 5700 5500
Wire Wire Line
	5500 5200 5700 5200
Wire Wire Line
	5700 5200 5700 5400
Wire Wire Line
	5700 5150 5700 5200
Connection ~ 5700 5200
Wire Wire Line
	5700 6800 5650 6800
Wire Wire Line
	5650 6800 5650 6900
Wire Wire Line
	5650 6900 5700 6900
Connection ~ 5650 6800
$Comp
L power:+5V #PWR070
U 1 1 5FF4F3E1
P 5650 6550
F 0 "#PWR070" H 5650 6400 50  0001 C CNN
F 1 "+5V" H 5665 6723 50  0000 C CNN
F 2 "" H 5650 6550 50  0001 C CNN
F 3 "" H 5650 6550 50  0001 C CNN
	1    5650 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FF4F3E7
P 5300 6600
AR Path="/5FF4F3E7" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5FF4F3E7" Ref="C31"  Part="1" 
F 0 "C31" V 5250 6800 50  0000 R CNN
F 1 "100n" V 5250 6550 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5338 6450 50  0001 C CNN
F 3 "~" H 5300 6600 50  0001 C CNN
	1    5300 6600
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FF4F3EE
P 5300 6900
AR Path="/5FF4F3EE" Ref="C?"  Part="1" 
AR Path="/5CB6FAF3/5FF4F3EE" Ref="C32"  Part="1" 
F 0 "C32" V 5350 7100 50  0000 R CNN
F 1 "10u" V 5350 6850 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5338 6750 50  0001 C CNN
F 3 "~" H 5300 6900 50  0001 C CNN
	1    5300 6900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FF4F3F5
P 5050 6750
AR Path="/5FF4F3F5" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5FF4F3F5" Ref="#PWR066"  Part="1" 
F 0 "#PWR066" H 5050 6500 50  0001 C CNN
F 1 "GND" V 5050 6550 50  0000 C CNN
F 2 "" H 5050 6750 50  0001 C CNN
F 3 "" H 5050 6750 50  0001 C CNN
	1    5050 6750
	0    1    1    0   
$EndComp
Wire Wire Line
	5150 6900 5100 6900
Wire Wire Line
	5050 6750 5100 6750
Wire Wire Line
	5100 6900 5100 6750
Wire Wire Line
	5100 6600 5150 6600
Connection ~ 5100 6750
Wire Wire Line
	5100 6750 5100 6600
Wire Wire Line
	5450 6900 5650 6900
Connection ~ 5650 6900
Wire Wire Line
	5450 6600 5650 6600
Wire Wire Line
	5650 6600 5650 6800
Wire Wire Line
	5650 6550 5650 6600
Connection ~ 5650 6600
Text HLabel 10350 3500 1    50   Input ~ 0
C0CP0
Text HLabel 10450 3500 1    50   Input ~ 0
C0CP1
Text HLabel 10650 4550 3    50   Input ~ 0
C1CP0
Text HLabel 10550 4550 3    50   Input ~ 0
C1CP1
Text HLabel 10450 4550 3    50   Input ~ 0
C2CP0
Text HLabel 10350 4550 3    50   Input ~ 0
C2CP1
Text HLabel 10250 4550 3    50   Input ~ 0
C3CP0
Text HLabel 10150 4550 3    50   Input ~ 0
C3CP1
$Comp
L power:GND #PWR?
U 1 1 6061C207
P 10800 3500
AR Path="/6061C207" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/6061C207" Ref="#PWR078"  Part="1" 
F 0 "#PWR078" H 10800 3250 50  0001 C CNN
F 1 "GND" H 10805 3327 50  0000 C CNN
F 2 "" H 10800 3500 50  0001 C CNN
F 3 "" H 10800 3500 50  0001 C CNN
	1    10800 3500
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR074
U 1 1 6061C2E4
P 9950 3500
F 0 "#PWR074" H 9950 3350 50  0001 C CNN
F 1 "+5V" H 9965 3673 50  0000 C CNN
F 2 "" H 9950 3500 50  0001 C CNN
F 3 "" H 9950 3500 50  0001 C CNN
	1    9950 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR076
U 1 1 6061C3D8
P 10050 3200
F 0 "#PWR076" H 10050 3050 50  0001 C CNN
F 1 "+3.3V" H 10065 3373 50  0000 C CNN
F 2 "" H 10050 3200 50  0001 C CNN
F 3 "" H 10050 3200 50  0001 C CNN
	1    10050 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 3500 9950 3600
Wire Wire Line
	10050 3200 10050 3600
Wire Wire Line
	10150 3500 10150 3600
Wire Wire Line
	10250 3500 10250 3600
Wire Wire Line
	10350 3500 10350 3600
Wire Wire Line
	10450 3500 10450 3600
Wire Wire Line
	10550 3500 10550 3600
Wire Wire Line
	10650 3500 10650 3600
Wire Wire Line
	10800 3500 10800 3550
Wire Wire Line
	10800 3550 10750 3550
Wire Wire Line
	10750 3550 10750 3600
Wire Wire Line
	10800 3550 10850 3550
Wire Wire Line
	10850 3550 10850 3600
Connection ~ 10800 3550
$Comp
L power:GND #PWR?
U 1 1 607CDC9B
P 10800 4550
AR Path="/607CDC9B" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/607CDC9B" Ref="#PWR079"  Part="1" 
F 0 "#PWR079" H 10800 4300 50  0001 C CNN
F 1 "GND" H 10805 4377 50  0000 C CNN
F 2 "" H 10800 4550 50  0001 C CNN
F 3 "" H 10800 4550 50  0001 C CNN
	1    10800 4550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10800 4550 10800 4500
Wire Wire Line
	10800 4500 10750 4500
Wire Wire Line
	10750 4500 10750 4450
Wire Wire Line
	10800 4500 10850 4500
Wire Wire Line
	10850 4500 10850 4450
Connection ~ 10800 4500
$Comp
L power:+5V #PWR075
U 1 1 607F4DDC
P 9950 4550
F 0 "#PWR075" H 9950 4400 50  0001 C CNN
F 1 "+5V" H 9965 4723 50  0000 C CNN
F 2 "" H 9950 4550 50  0001 C CNN
F 3 "" H 9950 4550 50  0001 C CNN
	1    9950 4550
	1    0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR077
U 1 1 607F4DE2
P 10050 4850
F 0 "#PWR077" H 10050 4700 50  0001 C CNN
F 1 "+3.3V" H 10065 5023 50  0000 C CNN
F 2 "" H 10050 4850 50  0001 C CNN
F 3 "" H 10050 4850 50  0001 C CNN
	1    10050 4850
	1    0    0    1   
$EndComp
Wire Wire Line
	9950 4550 9950 4450
Wire Wire Line
	10050 4850 10050 4450
Text HLabel 10550 3500 1    50   Input ~ 0
C4CP0
Text HLabel 10650 3500 1    50   Input ~ 0
C4CP1
Text HLabel 10150 3500 1    50   Input ~ 0
C5CP0
Text HLabel 10250 3500 1    50   Input ~ 0
C5CP1
Wire Wire Line
	10150 4550 10150 4450
Wire Wire Line
	10250 4550 10250 4450
Wire Wire Line
	10350 4550 10350 4450
Wire Wire Line
	10450 4550 10450 4450
Wire Wire Line
	10550 4550 10550 4450
Wire Wire Line
	10650 4550 10650 4450
Wire Notes Line
	11700 3850 11700 4500
Text Notes 9800 5500 0    100  ~ 0
for other use\nof Control Pins 
Wire Notes Line
	9550 2850 11200 2850
Wire Notes Line
	11200 2850 11200 5600
Wire Notes Line
	11200 5600 9550 5600
Wire Notes Line
	9550 5600 9550 2850
$Comp
L Connector:Conn_01x10_Female J18
U 1 1 5CFA8327
P 10450 3800
F 0 "J18" V 10522 3730 50  0000 C CNN
F 1 "Conn_01x10_Female" V 10613 3730 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 10450 3800 50  0001 C CNN
F 3 "~" H 10450 3800 50  0001 C CNN
	1    10450 3800
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x10_Female J19
U 1 1 5D01A6AA
P 10450 4250
F 0 "J19" V 10615 4180 50  0000 C CNN
F 1 "Conn_01x10_Female" V 10524 4180 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 10450 4250 50  0001 C CNN
F 3 "~" H 10450 4250 50  0001 C CNN
	1    10450 4250
	0    1    -1   0   
$EndComp
Text Label 2100 900  0    50   ~ 0
Vout0
Wire Wire Line
	1100 1000 850  1000
Connection ~ 1100 1000
Connection ~ 1100 1100
Wire Wire Line
	1100 1100 1100 1000
Wire Wire Line
	1100 1200 1100 1100
$Comp
L samtec_pci:PCIE-064-02-F-D-TH J12
U 2 1 5D3A3F2E
P 1600 1700
F 0 "J12" H 1600 2767 50  0000 C CNN
F 1 "PCIE-064-02-F-D-TH" H 1600 2676 50  0000 C CNN
F 2 "samtec_pci:SAMTEC_PCIE-064-02-F-D-TH" H 1000 2700 50  0001 L BNN
F 3 "" H 1600 1700 50  0001 L BNN
	2    1600 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D292E0F
P 2250 1300
AR Path="/5D292E0F" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D292E0F" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 2250 1050 50  0001 C CNN
F 1 "GND" H 2255 1127 50  0000 C CNN
F 2 "" H 2250 1300 50  0001 C CNN
F 3 "" H 2250 1300 50  0001 C CNN
	1    2250 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D5C093C
P 550 1400
AR Path="/5D5C093C" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D5C093C" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 550 1150 50  0001 C CNN
F 1 "GND" H 555 1227 50  0000 C CNN
F 2 "" H 550 1400 50  0001 C CNN
F 3 "" H 550 1400 50  0001 C CNN
	1    550  1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	550  1400 1100 1400
Wire Wire Line
	2100 1300 2250 1300
$Comp
L power:GND #PWR?
U 1 1 5D67BF0E
P 2750 1100
AR Path="/5D67BF0E" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D67BF0E" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 2750 850 50  0001 C CNN
F 1 "GND" H 2755 927 50  0000 C CNN
F 2 "" H 2750 1100 50  0001 C CNN
F 3 "" H 2750 1100 50  0001 C CNN
	1    2750 1100
	1    0    0    -1  
$EndComp
Text HLabel 3000 2500 0    50   Input ~ 0
C1CP0
Text HLabel 4000 2500 2    50   Input ~ 0
C1CP1
Text Label 3000 900  2    50   ~ 0
Vout1
Text HLabel 3000 1600 0    50   Input ~ 0
RS485_A
Text HLabel 3000 1700 0    50   Input ~ 0
RS485_B
Text HLabel 3000 1900 0    50   Input ~ 0
RS485_Y
Text HLabel 3000 1800 0    50   Input ~ 0
RS485_Z
Text Label 4000 900  0    50   ~ 0
Vout1
$Comp
L samtec_pci:PCIE-064-02-F-D-TH J14
U 2 1 5D67BF21
P 3500 1700
F 0 "J14" H 3500 2767 50  0000 C CNN
F 1 "PCIE-064-02-F-D-TH" H 3500 2676 50  0000 C CNN
F 2 "samtec_pci:SAMTEC_PCIE-064-02-F-D-TH" H 2900 2700 50  0001 L BNN
F 3 "" H 3500 1700 50  0001 L BNN
	2    3500 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D67BF27
P 4150 1300
AR Path="/5D67BF27" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D67BF27" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 4150 1050 50  0001 C CNN
F 1 "GND" H 4155 1127 50  0000 C CNN
F 2 "" H 4150 1300 50  0001 C CNN
F 3 "" H 4150 1300 50  0001 C CNN
	1    4150 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D67BF2D
P 2450 1400
AR Path="/5D67BF2D" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D67BF2D" Ref="#PWR0105"  Part="1" 
F 0 "#PWR0105" H 2450 1150 50  0001 C CNN
F 1 "GND" H 2455 1227 50  0000 C CNN
F 2 "" H 2450 1400 50  0001 C CNN
F 3 "" H 2450 1400 50  0001 C CNN
	1    2450 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 1400 3000 1400
Wire Wire Line
	4000 1300 4150 1300
$Comp
L power:GND #PWR?
U 1 1 5D705D05
P 4700 1000
AR Path="/5D705D05" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D705D05" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 4700 750 50  0001 C CNN
F 1 "GND" H 4705 827 50  0000 C CNN
F 2 "" H 4700 1000 50  0001 C CNN
F 3 "" H 4700 1000 50  0001 C CNN
	1    4700 1000
	1    0    0    -1  
$EndComp
Text HLabel 4950 2500 0    50   Input ~ 0
C2CP0
Text HLabel 5950 2500 2    50   Input ~ 0
C2CP1
Text Label 4950 900  2    50   ~ 0
Vout2
Text HLabel 4950 1600 0    50   Input ~ 0
RS485_A
Text HLabel 4950 1700 0    50   Input ~ 0
RS485_B
Text HLabel 4950 1900 0    50   Input ~ 0
RS485_Y
Text HLabel 4950 1800 0    50   Input ~ 0
RS485_Z
Text Label 5950 900  0    50   ~ 0
Vout2
$Comp
L samtec_pci:PCIE-064-02-F-D-TH J16
U 2 1 5D705D16
P 5450 1700
F 0 "J16" H 5450 2767 50  0000 C CNN
F 1 "PCIE-064-02-F-D-TH" H 5450 2676 50  0000 C CNN
F 2 "samtec_pci:SAMTEC_PCIE-064-02-F-D-TH" H 4850 2700 50  0001 L BNN
F 3 "" H 5450 1700 50  0001 L BNN
	2    5450 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D705D1C
P 6100 1300
AR Path="/5D705D1C" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D705D1C" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 6100 1050 50  0001 C CNN
F 1 "GND" H 6105 1127 50  0000 C CNN
F 2 "" H 6100 1300 50  0001 C CNN
F 3 "" H 6100 1300 50  0001 C CNN
	1    6100 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D705D22
P 4400 1400
AR Path="/5D705D22" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D705D22" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 4400 1150 50  0001 C CNN
F 1 "GND" H 4405 1227 50  0000 C CNN
F 2 "" H 4400 1400 50  0001 C CNN
F 3 "" H 4400 1400 50  0001 C CNN
	1    4400 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1400 4950 1400
Wire Wire Line
	5950 1300 6100 1300
$Comp
L power:GND #PWR?
U 1 1 5D7CEC53
P 850 3450
AR Path="/5D7CEC53" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D7CEC53" Ref="#PWR0109"  Part="1" 
F 0 "#PWR0109" H 850 3200 50  0001 C CNN
F 1 "GND" H 855 3277 50  0000 C CNN
F 2 "" H 850 3450 50  0001 C CNN
F 3 "" H 850 3450 50  0001 C CNN
	1    850  3450
	1    0    0    -1  
$EndComp
Text HLabel 1100 4750 0    50   Input ~ 0
C3CP0
Text HLabel 2100 4750 2    50   Input ~ 0
C3CP1
Text Label 1100 3150 2    50   ~ 0
Vout3
Text HLabel 1100 3850 0    50   Input ~ 0
RS485_A
Text HLabel 1100 3950 0    50   Input ~ 0
RS485_B
Text HLabel 1100 4150 0    50   Input ~ 0
RS485_Y
Text HLabel 1100 4050 0    50   Input ~ 0
RS485_Z
Text Label 2100 3150 0    50   ~ 0
Vout3
$Comp
L samtec_pci:PCIE-064-02-F-D-TH J13
U 2 1 5D7CEC66
P 1600 3950
F 0 "J13" H 1600 5017 50  0000 C CNN
F 1 "PCIE-064-02-F-D-TH" H 1600 4926 50  0000 C CNN
F 2 "samtec_pci:SAMTEC_PCIE-064-02-F-D-TH" H 1000 4950 50  0001 L BNN
F 3 "" H 1600 3950 50  0001 L BNN
	2    1600 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D7CEC6C
P 2250 3550
AR Path="/5D7CEC6C" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D7CEC6C" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 2250 3300 50  0001 C CNN
F 1 "GND" H 2255 3377 50  0000 C CNN
F 2 "" H 2250 3550 50  0001 C CNN
F 3 "" H 2250 3550 50  0001 C CNN
	1    2250 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D7CEC72
P 550 3650
AR Path="/5D7CEC72" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D7CEC72" Ref="#PWR0111"  Part="1" 
F 0 "#PWR0111" H 550 3400 50  0001 C CNN
F 1 "GND" H 555 3477 50  0000 C CNN
F 2 "" H 550 3650 50  0001 C CNN
F 3 "" H 550 3650 50  0001 C CNN
	1    550  3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	550  3650 1100 3650
Wire Wire Line
	2100 3550 2250 3550
Wire Wire Line
	1100 3450 850  3450
$Comp
L power:GND #PWR?
U 1 1 5D987C94
P 2750 3250
AR Path="/5D987C94" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D987C94" Ref="#PWR0112"  Part="1" 
F 0 "#PWR0112" H 2750 3000 50  0001 C CNN
F 1 "GND" H 2755 3077 50  0000 C CNN
F 2 "" H 2750 3250 50  0001 C CNN
F 3 "" H 2750 3250 50  0001 C CNN
	1    2750 3250
	1    0    0    -1  
$EndComp
Text HLabel 4000 4750 2    50   Input ~ 0
C4CP0
Text HLabel 3000 4750 0    50   Input ~ 0
C4CP1
Text Label 3000 3150 2    50   ~ 0
Vout4
Text HLabel 3000 3850 0    50   Input ~ 0
RS485_A
Text HLabel 3000 3950 0    50   Input ~ 0
RS485_B
Text HLabel 3000 4150 0    50   Input ~ 0
RS485_Y
Text HLabel 3000 4050 0    50   Input ~ 0
RS485_Z
Text Label 4000 3150 0    50   ~ 0
Vout4
$Comp
L samtec_pci:PCIE-064-02-F-D-TH J15
U 2 1 5D987CA2
P 3500 3950
F 0 "J15" H 3500 5017 50  0000 C CNN
F 1 "PCIE-064-02-F-D-TH" H 3500 4926 50  0000 C CNN
F 2 "samtec_pci:SAMTEC_PCIE-064-02-F-D-TH" H 2900 4950 50  0001 L BNN
F 3 "" H 3500 3950 50  0001 L BNN
	2    3500 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D987CA8
P 4150 3550
AR Path="/5D987CA8" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D987CA8" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 4150 3300 50  0001 C CNN
F 1 "GND" H 4155 3377 50  0000 C CNN
F 2 "" H 4150 3550 50  0001 C CNN
F 3 "" H 4150 3550 50  0001 C CNN
	1    4150 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D987CAE
P 2450 3650
AR Path="/5D987CAE" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D987CAE" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 2450 3400 50  0001 C CNN
F 1 "GND" H 2455 3477 50  0000 C CNN
F 2 "" H 2450 3650 50  0001 C CNN
F 3 "" H 2450 3650 50  0001 C CNN
	1    2450 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 3650 3000 3650
Wire Wire Line
	4000 3550 4150 3550
Wire Wire Line
	3000 3250 2750 3250
$Comp
L power:GND #PWR?
U 1 1 5D9FD893
P 4700 3300
AR Path="/5D9FD893" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D9FD893" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 4700 3050 50  0001 C CNN
F 1 "GND" H 4705 3127 50  0000 C CNN
F 2 "" H 4700 3300 50  0001 C CNN
F 3 "" H 4700 3300 50  0001 C CNN
	1    4700 3300
	1    0    0    -1  
$EndComp
Text HLabel 4950 4700 0    50   Input ~ 0
C5CP0
Text HLabel 5950 4700 2    50   Input ~ 0
C5CP1
Text Label 4950 3100 2    50   ~ 0
Vout5
Text HLabel 4950 3800 0    50   Input ~ 0
RS485_A
Text HLabel 4950 3900 0    50   Input ~ 0
RS485_B
Text HLabel 4950 4100 0    50   Input ~ 0
RS485_Y
Text HLabel 4950 4000 0    50   Input ~ 0
RS485_Z
Text Label 5950 3100 0    50   ~ 0
Vout5
$Comp
L samtec_pci:PCIE-064-02-F-D-TH J17
U 2 1 5D9FD8A1
P 5450 3900
F 0 "J17" H 5450 4967 50  0000 C CNN
F 1 "PCIE-064-02-F-D-TH" H 5450 4876 50  0000 C CNN
F 2 "samtec_pci:SAMTEC_PCIE-064-02-F-D-TH" H 4850 4900 50  0001 L BNN
F 3 "" H 5450 3900 50  0001 L BNN
	2    5450 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D9FD8A7
P 6100 3500
AR Path="/5D9FD8A7" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D9FD8A7" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 6100 3250 50  0001 C CNN
F 1 "GND" H 6105 3327 50  0000 C CNN
F 2 "" H 6100 3500 50  0001 C CNN
F 3 "" H 6100 3500 50  0001 C CNN
	1    6100 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D9FD8AD
P 4400 3600
AR Path="/5D9FD8AD" Ref="#PWR?"  Part="1" 
AR Path="/5CB6FAF3/5D9FD8AD" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 4400 3350 50  0001 C CNN
F 1 "GND" H 4405 3427 50  0000 C CNN
F 2 "" H 4400 3600 50  0001 C CNN
F 3 "" H 4400 3600 50  0001 C CNN
	1    4400 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 3600 4950 3600
Wire Wire Line
	5950 3500 6100 3500
Wire Wire Line
	4950 3300 4700 3300
Wire Wire Line
	3000 1200 2900 1200
Wire Wire Line
	2900 1100 3000 1100
Wire Wire Line
	2900 1100 2750 1100
Connection ~ 2900 1100
Wire Wire Line
	4700 1000 4900 1000
Wire Wire Line
	1100 1400 1100 1300
Connection ~ 1100 1400
Wire Wire Line
	2100 1300 2100 1200
Connection ~ 2100 1300
Wire Wire Line
	3000 1400 3000 1300
Connection ~ 3000 1400
Wire Wire Line
	4000 1300 4000 1200
Connection ~ 4000 1300
Wire Wire Line
	4950 1400 4950 1300
Connection ~ 4950 1400
Wire Wire Line
	5950 1300 5950 1200
Connection ~ 5950 1300
Wire Wire Line
	5950 3500 5950 3400
Connection ~ 5950 3500
Wire Wire Line
	4950 3600 4950 3500
Connection ~ 4950 3600
Wire Wire Line
	4000 3550 4000 3450
Connection ~ 4000 3550
Wire Wire Line
	3000 3650 3000 3550
Connection ~ 3000 3650
Wire Wire Line
	2100 3550 2100 3450
Connection ~ 2100 3550
Wire Wire Line
	1100 3550 1100 3650
Connection ~ 1100 3650
Wire Wire Line
	2900 1200 2900 1100
Wire Wire Line
	4950 1200 4900 1200
Wire Wire Line
	4900 1200 4900 1000
Connection ~ 4900 1000
Wire Wire Line
	4900 1000 4950 1000
Wire Wire Line
	3000 3350 3000 3250
Connection ~ 3000 3250
$EndSCHEMATC
