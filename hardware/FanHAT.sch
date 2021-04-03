EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Raspberry Pi HAT"
Date ""
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Mechanical:MountingHole H1
U 1 1 5834BC4A
P 1750 7450
F 0 "H1" H 1600 7550 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 1750 7300 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 1650 7450 60  0001 C CNN
F 3 "" H 1650 7450 60  0001 C CNN
	1    1750 7450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5834BCDF
P 2750 7450
F 0 "H2" H 2600 7550 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 2750 7300 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 2650 7450 60  0001 C CNN
F 3 "" H 2650 7450 60  0001 C CNN
	1    2750 7450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5834BD62
P 1750 8000
F 0 "H3" H 1600 8100 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 1750 7850 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 1650 8000 60  0001 C CNN
F 3 "" H 1650 8000 60  0001 C CNN
	1    1750 8000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5834BDED
P 2800 8000
F 0 "H4" H 2650 8100 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 2800 7850 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 2700 8000 60  0001 C CNN
F 3 "" H 2700 8000 60  0001 C CNN
	1    2800 8000
	1    0    0    -1  
$EndComp
$Comp
L raspberrypi_hat:OX40HAT J3
U 1 1 58DFC771
P 2600 2250
F 0 "J3" H 2950 2350 50  0000 C CNN
F 1 "40HAT" H 2300 2350 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 2600 2450 50  0001 C CNN
F 3 "" H 1900 2250 50  0000 C CNN
	1    2600 2250
	1    0    0    -1  
$EndComp
$Comp
L raspberrypi_hat:DMG2305UX Q1
U 1 1 58E14EB1
P 6900 3000
F 0 "Q1" V 7050 3150 50  0000 R CNN
F 1 "DMG2305UX" V 7050 2950 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7100 3100 50  0001 C CNN
F 3 "" H 6900 3000 50  0000 C CNN
	1    6900 3000
	0    -1   -1   0   
$EndComp
Text Notes 1400 7150 0    118  ~ 24
Mounting Holes
Text Notes 1650 2000 0    118  ~ 24
40-Pin HAT Connector
Text Label 800  4150 0    60   ~ 0
GND
Wire Wire Line
	2000 4150 800  4150
Text Label 800  3450 0    60   ~ 0
GND
Wire Wire Line
	2000 3450 800  3450
Text Label 800  2650 0    60   ~ 0
GND
Wire Wire Line
	2000 2650 800  2650
Text Label 800  2250 0    60   ~ 0
P3V3_HAT
Wire Wire Line
	2000 2250 800  2250
Wire Wire Line
	3200 2850 4400 2850
Wire Wire Line
	3200 3150 4400 3150
Wire Wire Line
	3200 3650 4400 3650
Wire Wire Line
	3200 3850 4400 3850
Text Label 4400 2850 2    60   ~ 0
GND
Text Label 4400 3150 2    60   ~ 0
GND
Text Label 4400 3650 2    60   ~ 0
GND
Text Label 4400 3850 2    60   ~ 0
GND
Text Label 4400 2450 2    60   ~ 0
GND
Wire Wire Line
	3200 2450 4400 2450
Text Label 4400 2350 2    60   ~ 0
P5V_HAT
Wire Wire Line
	3200 2350 4400 2350
Text Label 4400 2250 2    60   ~ 0
P5V_HAT
Wire Wire Line
	3200 2250 4400 2250
Text Notes 850  1250 0    100  ~ 0
This is based on the official Raspberry Pi spec to be able to call an extension board a HAT.\nhttps://github.com/raspberrypi/hats/blob/master/designguide.md
$Comp
L Device:R R24
U 1 1 58E158A1
P 6900 3550
F 0 "R24" V 6980 3550 50  0000 C CNN
F 1 "1K" V 6900 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6830 3550 50  0001 C CNN
F 3 "" H 6900 3550 50  0001 C CNN
	1    6900 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3250 6900 3400
Wire Wire Line
	3200 3750 4400 3750
Text Label 4200 3750 0    50   ~ 0
PWM0
Wire Wire Line
	6900 3700 6900 3950
Text Label 6900 3950 1    50   ~ 0
PWM0
Text Label 5600 2100 0    60   ~ 0
P3V3_HAT
Text Label 5600 2300 0    60   ~ 0
P5V_HAT
$Comp
L Device:R R1
U 1 1 604CCCDA
P 6550 2100
F 0 "R1" V 6630 2100 50  0000 C CNN
F 1 "0" V 6550 2100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6480 2100 50  0001 C CNN
F 3 "" H 6550 2100 50  0001 C CNN
	1    6550 2100
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 604CD2D1
P 6550 2300
F 0 "R2" V 6630 2300 50  0000 C CNN
F 1 "0" V 6550 2300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6480 2300 50  0001 C CNN
F 3 "" H 6550 2300 50  0001 C CNN
	1    6550 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	5600 2100 6400 2100
Wire Wire Line
	5600 2300 6400 2300
Wire Wire Line
	6700 2100 7250 2100
Wire Wire Line
	7250 2100 7250 2300
Wire Wire Line
	7250 2300 6700 2300
Text Label 7250 2200 0    50   ~ 0
Power
Text Label 5350 3000 0    50   ~ 0
Power
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 604CF823
P 5900 2800
F 0 "J1" V 5864 2612 50  0000 R CNN
F 1 "Conn_01x02" V 5773 2612 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5900 2800 50  0001 C CNN
F 3 "~" H 5900 2800 50  0001 C CNN
	1    5900 2800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 604D1839
P 7500 3350
F 0 "R3" V 7580 3350 50  0000 C CNN
F 1 "0" V 7500 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7430 3350 50  0001 C CNN
F 3 "" H 7500 3350 50  0001 C CNN
	1    7500 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	7500 3500 7500 3950
Text Label 7500 3900 1    60   ~ 0
GND
Wire Wire Line
	5350 3000 5900 3000
Wire Wire Line
	6000 3000 6650 3000
Wire Wire Line
	7150 3000 7500 3000
Wire Wire Line
	7500 3000 7500 3200
$EndSCHEMATC
