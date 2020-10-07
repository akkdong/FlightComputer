EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 12
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
L FlightComputer_Library:MT48LC16M16A2P U4
U 1 1 5F7B0722
P 3700 3500
F 0 "U4" H 3700 5465 50  0000 C CNN
F 1 "MT48LC16M16A2P" H 3700 5374 50  0000 C CNN
F 2 "" H 3700 3500 50  0001 C CNN
F 3 "" H 3700 3500 50  0001 C CNN
	1    3700 3500
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:MT25QL512ABB8ESF U3
U 1 1 5F7B37AF
P 9000 2850
F 0 "U3" H 9000 3365 50  0000 C CNN
F 1 "MT25QL512ABB8ESF" H 9000 3274 50  0000 C CNN
F 2 "" H 9000 2850 50  0001 C CNN
F 3 "" H 9000 2850 50  0001 C CNN
	1    9000 2850
	1    0    0    -1  
$EndComp
Text Label 2050 1850 0    50   ~ 0
SDRAM_D0
Text Label 2050 1950 0    50   ~ 0
SDRAM_D1
Text Label 2050 2050 0    50   ~ 0
SDRAM_D2
Text Label 2050 2150 0    50   ~ 0
SDRAM_D3
Text Label 2050 2250 0    50   ~ 0
SDRAM_D4
Text Label 2050 2350 0    50   ~ 0
SDRAM_D5
Text Label 2050 2450 0    50   ~ 0
SDRAM_D6
Text Label 2050 2550 0    50   ~ 0
SDRAM_D7
Text Label 2050 2650 0    50   ~ 0
SDRAM_D8
Text Label 2050 2750 0    50   ~ 0
SDRAM_D9
Text Label 2050 2850 0    50   ~ 0
SDRAM_D10
Text Label 2050 2950 0    50   ~ 0
SDRAM_D11
Text Label 2050 3050 0    50   ~ 0
SDRAM_D12
Text Label 2050 3150 0    50   ~ 0
SDRAM_D13
Text Label 2050 3250 0    50   ~ 0
SDRAM_D14
Text Label 2050 3350 0    50   ~ 0
SDRAM_D15
Wire Bus Line
	5650 1400 5500 1250
Entry Wire Line
	5550 1850 5650 1950
Entry Wire Line
	5550 1950 5650 2050
Entry Wire Line
	5550 2050 5650 2150
Entry Wire Line
	5550 2150 5650 2250
Entry Wire Line
	5550 2250 5650 2350
Entry Wire Line
	5550 2350 5650 2450
Entry Wire Line
	5550 2450 5650 2550
Entry Wire Line
	5550 2550 5650 2650
Entry Wire Line
	5550 2650 5650 2750
Entry Wire Line
	5550 2750 5650 2850
Entry Wire Line
	5550 2850 5650 2950
Entry Wire Line
	5550 2950 5650 3050
Text Label 5000 1850 0    50   ~ 0
SDRAM_A0
Text Label 5000 1950 0    50   ~ 0
SDRAM_A1
Text Label 5000 2050 0    50   ~ 0
SDRAM_A2
Text Label 5000 2150 0    50   ~ 0
SDRAM_A3
Text Label 5000 2250 0    50   ~ 0
SDRAM_A4
Text Label 5000 2350 0    50   ~ 0
SDRAM_A5
Text Label 5000 2450 0    50   ~ 0
SDRAM_A6
Text Label 5000 2550 0    50   ~ 0
SDRAM_A7
Text Label 5000 2650 0    50   ~ 0
SDRAM_A8
Text Label 5000 2750 0    50   ~ 0
SDRAM_A9
Text Label 5000 2850 0    50   ~ 0
SDRAM_A10
Text Label 5000 2950 0    50   ~ 0
SDRAM_A11
Text Label 5000 3700 0    50   ~ 0
SDRAM_BA0
Text Label 5000 3800 0    50   ~ 0
SDRAM_BA1
Text Label 5000 4050 0    50   ~ 0
SDRAM_nBL0
Text Label 5000 4150 0    50   ~ 0
SDRAM_nBL1
Text Label 5000 4550 0    50   ~ 0
SDRAM_nWE
Text Label 5000 4650 0    50   ~ 0
SDRAM_nCAS
Text Label 5000 4750 0    50   ~ 0
SDRAM_nRAS
Text Label 5000 4850 0    50   ~ 0
SDRAM_nCS
Text Label 5000 5150 0    50   ~ 0
SDRAM_CKE
Text Label 5000 5050 0    50   ~ 0
SDRAM_CLK
NoConn ~ 8400 2750
Wire Wire Line
	7950 2850 7400 2850
Wire Wire Line
	7950 2950 7400 2950
Entry Wire Line
	10700 2600 10800 2700
Entry Wire Line
	10700 2700 10800 2800
Entry Wire Line
	10700 2800 10800 2900
Entry Wire Line
	10700 2900 10800 3000
Text Label 10250 2600 0    50   ~ 0
NOR_DQ0
Text Label 10250 2700 0    50   ~ 0
NOR_DQ1
Text Label 10250 2800 0    50   ~ 0
NOR_DQ2
Wire Bus Line
	10800 1300 10550 1050
Text Label 10250 2900 0    50   ~ 0
NOR_DQ3
Text Label 7450 2850 0    50   ~ 0
NOR_nCS
Text Label 7450 2950 0    50   ~ 0
NOR_CLK
$Comp
L Device:R_US R?
U 1 1 5F813C40
P 9900 2600
AR Path="/5F2A50C6/5F813C40" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F813C40" Ref="R66"  Part="1" 
F 0 "R66" V 9950 2750 50  0000 L CNN
F 1 "33R" V 9950 2350 50  0000 L CNN
F 2 "" V 9940 2590 50  0001 C CNN
F 3 "~" H 9900 2600 50  0001 C CNN
	1    9900 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F813C4F
P 2750 5150
AR Path="/5F2A50C6/5F813C4F" Ref="#PWR?"  Part="1" 
AR Path="/5F60AB0F/5F813C4F" Ref="#PWR076"  Part="1" 
F 0 "#PWR076" H 2750 4900 50  0001 C CNN
F 1 "GND" H 2755 4977 50  0000 C CNN
F 2 "" H 2750 5150 50  0001 C CNN
F 3 "" H 2750 5150 50  0001 C CNN
	1    2750 5150
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F813C59
P 6600 2850
AR Path="/5F2A50C6/5F813C59" Ref="C?"  Part="1" 
AR Path="/5F60AB0F/5F813C59" Ref="C42"  Part="1" 
F 0 "C42" H 6692 2896 50  0000 L CNN
F 1 "0.1uF" H 6692 2805 50  0000 L CNN
F 2 "" H 6600 2850 50  0001 C CNN
F 3 "~" H 6600 2850 50  0001 C CNN
	1    6600 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F813C5F
P 6600 3250
AR Path="/5F2A50C6/5F813C5F" Ref="#PWR?"  Part="1" 
AR Path="/5F60AB0F/5F813C5F" Ref="#PWR074"  Part="1" 
F 0 "#PWR074" H 6600 3000 50  0001 C CNN
F 1 "GND" H 6605 3077 50  0000 C CNN
F 2 "" H 6600 3250 50  0001 C CNN
F 3 "" H 6600 3250 50  0001 C CNN
	1    6600 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2600 6600 2600
Wire Wire Line
	6600 2750 6600 2600
Connection ~ 6600 2600
Wire Wire Line
	6600 2950 6600 3100
Wire Wire Line
	8400 3100 6600 3100
Connection ~ 6600 3100
Wire Wire Line
	6600 3100 6600 3250
Wire Wire Line
	6600 2600 6600 2400
$Comp
L FlightComputer_Library:VCC_PERIH #PWR073
U 1 1 5F815505
P 6600 2400
F 0 "#PWR073" H 6600 2250 50  0001 C CNN
F 1 "VCC_PERIH" H 6617 2573 50  0000 C CNN
F 2 "" H 6600 2400 50  0001 C CNN
F 3 "" H 6600 2400 50  0001 C CNN
	1    6600 2400
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_PERIH #PWR077
U 1 1 5F82225B
P 2400 6200
F 0 "#PWR077" H 2400 6050 50  0001 C CNN
F 1 "VCC_PERIH" H 2417 6373 50  0000 C CNN
F 2 "" H 2400 6200 50  0001 C CNN
F 3 "" H 2400 6200 50  0001 C CNN
	1    2400 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F813C46
P 2400 6600
AR Path="/5F2A50C6/5F813C46" Ref="C?"  Part="1" 
AR Path="/5F60AB0F/5F813C46" Ref="C43"  Part="1" 
F 0 "C43" H 2200 6550 50  0000 L CNN
F 1 "0.1uF" H 2100 6650 50  0000 L CNN
F 2 "" H 2400 6600 50  0001 C CNN
F 3 "~" H 2400 6600 50  0001 C CNN
	1    2400 6600
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F826C89
P 2800 6600
AR Path="/5F2A50C6/5F826C89" Ref="C?"  Part="1" 
AR Path="/5F60AB0F/5F826C89" Ref="C44"  Part="1" 
F 0 "C44" H 2600 6550 50  0000 L CNN
F 1 "0.1uF" H 2500 6650 50  0000 L CNN
F 2 "" H 2800 6600 50  0001 C CNN
F 3 "~" H 2800 6600 50  0001 C CNN
	1    2800 6600
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F826F17
P 3200 6600
AR Path="/5F2A50C6/5F826F17" Ref="C?"  Part="1" 
AR Path="/5F60AB0F/5F826F17" Ref="C45"  Part="1" 
F 0 "C45" H 3000 6550 50  0000 L CNN
F 1 "0.1uF" H 2900 6650 50  0000 L CNN
F 2 "" H 3200 6600 50  0001 C CNN
F 3 "~" H 3200 6600 50  0001 C CNN
	1    3200 6600
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F82713A
P 3600 6600
AR Path="/5F2A50C6/5F82713A" Ref="C?"  Part="1" 
AR Path="/5F60AB0F/5F82713A" Ref="C46"  Part="1" 
F 0 "C46" H 3400 6550 50  0000 L CNN
F 1 "0.1uF" H 3300 6650 50  0000 L CNN
F 2 "" H 3600 6600 50  0001 C CNN
F 3 "~" H 3600 6600 50  0001 C CNN
	1    3600 6600
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F827467
P 4000 6600
AR Path="/5F2A50C6/5F827467" Ref="C?"  Part="1" 
AR Path="/5F60AB0F/5F827467" Ref="C47"  Part="1" 
F 0 "C47" H 3800 6550 50  0000 L CNN
F 1 "0.1uF" H 3700 6650 50  0000 L CNN
F 2 "" H 4000 6600 50  0001 C CNN
F 3 "~" H 4000 6600 50  0001 C CNN
	1    4000 6600
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F82761C
P 4400 6600
AR Path="/5F2A50C6/5F82761C" Ref="C?"  Part="1" 
AR Path="/5F60AB0F/5F82761C" Ref="C48"  Part="1" 
F 0 "C48" H 4200 6550 50  0000 L CNN
F 1 "0.1uF" H 4100 6650 50  0000 L CNN
F 2 "" H 4400 6600 50  0001 C CNN
F 3 "~" H 4400 6600 50  0001 C CNN
	1    4400 6600
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F827811
P 4800 6600
AR Path="/5F2A50C6/5F827811" Ref="C?"  Part="1" 
AR Path="/5F60AB0F/5F827811" Ref="C49"  Part="1" 
F 0 "C49" H 4600 6550 50  0000 L CNN
F 1 "0.1uF" H 4500 6650 50  0000 L CNN
F 2 "" H 4800 6600 50  0001 C CNN
F 3 "~" H 4800 6600 50  0001 C CNN
	1    4800 6600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F827BDC
P 2400 6900
AR Path="/5F2A50C6/5F827BDC" Ref="#PWR?"  Part="1" 
AR Path="/5F60AB0F/5F827BDC" Ref="#PWR078"  Part="1" 
F 0 "#PWR078" H 2400 6650 50  0001 C CNN
F 1 "GND" H 2405 6727 50  0000 C CNN
F 2 "" H 2400 6900 50  0001 C CNN
F 3 "" H 2400 6900 50  0001 C CNN
	1    2400 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 6700 2400 6800
Wire Wire Line
	2400 6800 2800 6800
Wire Wire Line
	4800 6800 4800 6700
Connection ~ 2400 6800
Wire Wire Line
	2400 6800 2400 6900
Wire Wire Line
	4400 6700 4400 6800
Connection ~ 4400 6800
Wire Wire Line
	4400 6800 4800 6800
Wire Wire Line
	4000 6700 4000 6800
Connection ~ 4000 6800
Wire Wire Line
	4000 6800 4400 6800
Wire Wire Line
	3600 6700 3600 6800
Connection ~ 3600 6800
Wire Wire Line
	3600 6800 4000 6800
Wire Wire Line
	3200 6700 3200 6800
Connection ~ 3200 6800
Wire Wire Line
	3200 6800 3600 6800
Wire Wire Line
	2800 6700 2800 6800
Connection ~ 2800 6800
Wire Wire Line
	2800 6800 3200 6800
Wire Wire Line
	2400 6200 2400 6350
Wire Wire Line
	4800 6500 4800 6350
Wire Wire Line
	4800 6350 4400 6350
Connection ~ 2400 6350
Wire Wire Line
	2400 6350 2400 6500
Wire Wire Line
	2800 6500 2800 6350
Connection ~ 2800 6350
Wire Wire Line
	2800 6350 2400 6350
Wire Wire Line
	3200 6500 3200 6350
Connection ~ 3200 6350
Wire Wire Line
	3200 6350 2800 6350
Wire Wire Line
	3600 6500 3600 6350
Connection ~ 3600 6350
Wire Wire Line
	3600 6350 3200 6350
Wire Wire Line
	4000 6500 4000 6350
Connection ~ 4000 6350
Wire Wire Line
	4000 6350 3600 6350
Wire Wire Line
	4400 6500 4400 6350
Connection ~ 4400 6350
Wire Wire Line
	4400 6350 4000 6350
Wire Wire Line
	3100 5150 2950 5150
Wire Wire Line
	3100 5050 2950 5050
Wire Wire Line
	2950 5050 2950 5150
Wire Wire Line
	3100 4950 2950 4950
Wire Wire Line
	2950 4950 2950 5050
Connection ~ 2950 5050
Wire Wire Line
	3100 4850 2950 4850
Wire Wire Line
	2950 4850 2950 4950
Connection ~ 2950 4950
Wire Wire Line
	3100 4750 2950 4750
Wire Wire Line
	2950 4750 2950 4850
Connection ~ 2950 4850
Wire Wire Line
	3100 4650 2950 4650
Wire Wire Line
	2950 4650 2950 4750
Connection ~ 2950 4750
Wire Wire Line
	3100 4550 2950 4550
Wire Wire Line
	2950 4550 2950 4650
Connection ~ 2950 4650
$Comp
L FlightComputer_Library:VCC_PERIH #PWR075
U 1 1 5F85B6A4
P 2750 3700
F 0 "#PWR075" H 2750 3550 50  0001 C CNN
F 1 "VCC_PERIH" V 2768 3828 50  0000 L CNN
F 2 "" H 2750 3700 50  0001 C CNN
F 3 "" H 2750 3700 50  0001 C CNN
	1    2750 3700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2750 3700 2950 3700
Wire Wire Line
	2950 3700 2950 3800
Wire Wire Line
	2950 4300 3100 4300
Connection ~ 2950 3700
Wire Wire Line
	2950 3700 3100 3700
Wire Wire Line
	3100 4200 2950 4200
Connection ~ 2950 4200
Wire Wire Line
	2950 4200 2950 4300
Wire Wire Line
	3100 4100 2950 4100
Connection ~ 2950 4100
Wire Wire Line
	2950 4100 2950 4200
Wire Wire Line
	3100 4000 2950 4000
Connection ~ 2950 4000
Wire Wire Line
	2950 4000 2950 4100
Wire Wire Line
	3100 3900 2950 3900
Connection ~ 2950 3900
Wire Wire Line
	2950 3900 2950 4000
Wire Wire Line
	3100 3800 2950 3800
Connection ~ 2950 3800
Wire Wire Line
	2950 3800 2950 3900
Wire Wire Line
	2750 5150 2950 5150
Connection ~ 2950 5150
$Comp
L Device:R_US R?
U 1 1 5F8915DD
P 9900 2700
AR Path="/5F2A50C6/5F8915DD" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F8915DD" Ref="R69"  Part="1" 
F 0 "R69" V 9950 2850 50  0000 L CNN
F 1 "33R" V 9950 2450 50  0000 L CNN
F 2 "" V 9940 2690 50  0001 C CNN
F 3 "~" H 9900 2700 50  0001 C CNN
	1    9900 2700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F891801
P 9900 2800
AR Path="/5F2A50C6/5F891801" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F891801" Ref="R72"  Part="1" 
F 0 "R72" V 9950 2950 50  0000 L CNN
F 1 "33R" V 9950 2550 50  0000 L CNN
F 2 "" V 9940 2790 50  0001 C CNN
F 3 "~" H 9900 2800 50  0001 C CNN
	1    9900 2800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F89195A
P 9900 2900
AR Path="/5F2A50C6/5F89195A" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F89195A" Ref="R76"  Part="1" 
F 0 "R76" V 9950 3050 50  0000 L CNN
F 1 "33R" V 9950 2650 50  0000 L CNN
F 2 "" V 9940 2890 50  0001 C CNN
F 3 "~" H 9900 2900 50  0001 C CNN
	1    9900 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9600 2600 9750 2600
Wire Wire Line
	9600 2700 9750 2700
Wire Wire Line
	9600 2800 9750 2800
Wire Wire Line
	9600 2900 9750 2900
Wire Wire Line
	10050 2900 10700 2900
Wire Wire Line
	10050 2800 10700 2800
Wire Wire Line
	10700 2700 10050 2700
Wire Wire Line
	10050 2600 10700 2600
Text HLabel 7400 2850 0    50   Input ~ 0
NOR_nCS
Text HLabel 7400 2950 0    50   Input ~ 0
NOR_CLK
Text HLabel 5550 3700 2    50   Input ~ 0
SDRAM_BA0
Text HLabel 5550 3800 2    50   Input ~ 0
SDRAM_BA1
Text HLabel 5550 4050 2    50   Input ~ 0
SDRAM_nBL0
Text HLabel 5550 4150 2    50   Input ~ 0
SDRAM_nBL1
Text HLabel 5550 4550 2    50   Input ~ 0
SDRAM_nWE
Text HLabel 5550 4650 2    50   Input ~ 0
SDRAM_nCAS
Text HLabel 5550 4750 2    50   Input ~ 0
SDRAM_nRAS
Text HLabel 5550 4850 2    50   Input ~ 0
SDRAM_nCS
Text HLabel 5550 5050 2    50   Input ~ 0
SDRAM_CLK
Text HLabel 5550 5150 2    50   Input ~ 0
SDRAM_CKE
Entry Wire Line
	5550 3050 5650 3150
Text Label 5000 3050 0    50   ~ 0
SDRAM_A12
$Comp
L Device:R_US R?
U 1 1 5F92DC45
P 4600 3700
AR Path="/5F2A50C6/5F92DC45" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F92DC45" Ref="R85"  Part="1" 
F 0 "R85" V 4650 3850 50  0000 L CNN
F 1 "33R" V 4650 3450 50  0000 L CNN
F 2 "" V 4640 3690 50  0001 C CNN
F 3 "~" H 4600 3700 50  0001 C CNN
	1    4600 3700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F92DFEB
P 4600 3800
AR Path="/5F2A50C6/5F92DFEB" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F92DFEB" Ref="R86"  Part="1" 
F 0 "R86" V 4650 3950 50  0000 L CNN
F 1 "33R" V 4650 3550 50  0000 L CNN
F 2 "" V 4640 3790 50  0001 C CNN
F 3 "~" H 4600 3800 50  0001 C CNN
	1    4600 3800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F92E1EE
P 4600 4050
AR Path="/5F2A50C6/5F92E1EE" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F92E1EE" Ref="R87"  Part="1" 
F 0 "R87" V 4650 4200 50  0000 L CNN
F 1 "33R" V 4650 3800 50  0000 L CNN
F 2 "" V 4640 4040 50  0001 C CNN
F 3 "~" H 4600 4050 50  0001 C CNN
	1    4600 4050
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F92E4CA
P 4600 4150
AR Path="/5F2A50C6/5F92E4CA" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F92E4CA" Ref="R88"  Part="1" 
F 0 "R88" V 4650 4300 50  0000 L CNN
F 1 "33R" V 4650 3900 50  0000 L CNN
F 2 "" V 4640 4140 50  0001 C CNN
F 3 "~" H 4600 4150 50  0001 C CNN
	1    4600 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F92E5DF
P 4600 4550
AR Path="/5F2A50C6/5F92E5DF" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F92E5DF" Ref="R89"  Part="1" 
F 0 "R89" V 4650 4700 50  0000 L CNN
F 1 "33R" V 4650 4300 50  0000 L CNN
F 2 "" V 4640 4540 50  0001 C CNN
F 3 "~" H 4600 4550 50  0001 C CNN
	1    4600 4550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F92E712
P 4600 4650
AR Path="/5F2A50C6/5F92E712" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F92E712" Ref="R90"  Part="1" 
F 0 "R90" V 4650 4800 50  0000 L CNN
F 1 "33R" V 4650 4400 50  0000 L CNN
F 2 "" V 4640 4640 50  0001 C CNN
F 3 "~" H 4600 4650 50  0001 C CNN
	1    4600 4650
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F92E870
P 4600 4750
AR Path="/5F2A50C6/5F92E870" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F92E870" Ref="R91"  Part="1" 
F 0 "R91" V 4650 4900 50  0000 L CNN
F 1 "33R" V 4650 4500 50  0000 L CNN
F 2 "" V 4640 4740 50  0001 C CNN
F 3 "~" H 4600 4750 50  0001 C CNN
	1    4600 4750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F92E9C4
P 4600 4850
AR Path="/5F2A50C6/5F92E9C4" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F92E9C4" Ref="R92"  Part="1" 
F 0 "R92" V 4650 5000 50  0000 L CNN
F 1 "33R" V 4650 4600 50  0000 L CNN
F 2 "" V 4640 4840 50  0001 C CNN
F 3 "~" H 4600 4850 50  0001 C CNN
	1    4600 4850
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F92EB79
P 4600 5050
AR Path="/5F2A50C6/5F92EB79" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F92EB79" Ref="R93"  Part="1" 
F 0 "R93" V 4650 5200 50  0000 L CNN
F 1 "33R" V 4650 4800 50  0000 L CNN
F 2 "" V 4640 5040 50  0001 C CNN
F 3 "~" H 4600 5050 50  0001 C CNN
	1    4600 5050
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F92ED16
P 4600 5150
AR Path="/5F2A50C6/5F92ED16" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F92ED16" Ref="R94"  Part="1" 
F 0 "R94" V 4650 5300 50  0000 L CNN
F 1 "33R" V 4650 4900 50  0000 L CNN
F 2 "" V 4640 5140 50  0001 C CNN
F 3 "~" H 4600 5150 50  0001 C CNN
	1    4600 5150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 3700 4450 3700
Wire Wire Line
	4450 3800 4300 3800
Wire Wire Line
	4300 4050 4450 4050
Wire Wire Line
	4450 4150 4300 4150
Wire Wire Line
	4300 4550 4450 4550
Wire Wire Line
	4450 4650 4300 4650
Wire Wire Line
	4300 4750 4450 4750
Wire Wire Line
	4450 4850 4300 4850
Wire Wire Line
	4300 5050 4450 5050
Wire Wire Line
	4450 5150 4300 5150
Wire Wire Line
	4750 5150 5550 5150
Wire Wire Line
	4750 5050 5550 5050
Wire Wire Line
	5550 4850 4750 4850
Wire Wire Line
	4750 4750 5550 4750
Wire Wire Line
	5550 4650 4750 4650
Wire Wire Line
	4750 4550 5550 4550
Wire Wire Line
	5550 4150 4750 4150
Wire Wire Line
	4750 4050 5550 4050
Wire Wire Line
	4750 3800 5550 3800
Wire Wire Line
	5550 3700 4750 3700
$Comp
L Device:R_US R?
U 1 1 5F99BD81
P 4650 1850
AR Path="/5F2A50C6/5F99BD81" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F99BD81" Ref="R51"  Part="1" 
F 0 "R51" V 4700 2000 50  0000 L CNN
F 1 "33R" V 4700 1600 50  0000 L CNN
F 2 "" V 4690 1840 50  0001 C CNN
F 3 "~" H 4650 1850 50  0001 C CNN
	1    4650 1850
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A0EF6
P 4650 1950
AR Path="/5F2A50C6/5F9A0EF6" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A0EF6" Ref="R53"  Part="1" 
F 0 "R53" V 4700 2100 50  0000 L CNN
F 1 "33R" V 4700 1700 50  0000 L CNN
F 2 "" V 4690 1940 50  0001 C CNN
F 3 "~" H 4650 1950 50  0001 C CNN
	1    4650 1950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A1146
P 4650 2050
AR Path="/5F2A50C6/5F9A1146" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A1146" Ref="R55"  Part="1" 
F 0 "R55" V 4700 2200 50  0000 L CNN
F 1 "33R" V 4700 1800 50  0000 L CNN
F 2 "" V 4690 2040 50  0001 C CNN
F 3 "~" H 4650 2050 50  0001 C CNN
	1    4650 2050
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A12ED
P 4650 2150
AR Path="/5F2A50C6/5F9A12ED" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A12ED" Ref="R57"  Part="1" 
F 0 "R57" V 4700 2300 50  0000 L CNN
F 1 "33R" V 4700 1900 50  0000 L CNN
F 2 "" V 4690 2140 50  0001 C CNN
F 3 "~" H 4650 2150 50  0001 C CNN
	1    4650 2150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A145E
P 4650 2250
AR Path="/5F2A50C6/5F9A145E" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A145E" Ref="R59"  Part="1" 
F 0 "R59" V 4700 2400 50  0000 L CNN
F 1 "33R" V 4700 2000 50  0000 L CNN
F 2 "" V 4690 2240 50  0001 C CNN
F 3 "~" H 4650 2250 50  0001 C CNN
	1    4650 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A15B2
P 4650 2350
AR Path="/5F2A50C6/5F9A15B2" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A15B2" Ref="R61"  Part="1" 
F 0 "R61" V 4700 2500 50  0000 L CNN
F 1 "33R" V 4700 2100 50  0000 L CNN
F 2 "" V 4690 2340 50  0001 C CNN
F 3 "~" H 4650 2350 50  0001 C CNN
	1    4650 2350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A16AF
P 4650 2450
AR Path="/5F2A50C6/5F9A16AF" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A16AF" Ref="R63"  Part="1" 
F 0 "R63" V 4700 2600 50  0000 L CNN
F 1 "33R" V 4700 2200 50  0000 L CNN
F 2 "" V 4690 2440 50  0001 C CNN
F 3 "~" H 4650 2450 50  0001 C CNN
	1    4650 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A1803
P 4650 2550
AR Path="/5F2A50C6/5F9A1803" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A1803" Ref="R65"  Part="1" 
F 0 "R65" V 4700 2700 50  0000 L CNN
F 1 "33R" V 4700 2300 50  0000 L CNN
F 2 "" V 4690 2540 50  0001 C CNN
F 3 "~" H 4650 2550 50  0001 C CNN
	1    4650 2550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A190F
P 4650 2650
AR Path="/5F2A50C6/5F9A190F" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A190F" Ref="R68"  Part="1" 
F 0 "R68" V 4700 2800 50  0000 L CNN
F 1 "33R" V 4700 2400 50  0000 L CNN
F 2 "" V 4690 2640 50  0001 C CNN
F 3 "~" H 4650 2650 50  0001 C CNN
	1    4650 2650
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A1B33
P 4650 2750
AR Path="/5F2A50C6/5F9A1B33" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A1B33" Ref="R71"  Part="1" 
F 0 "R71" V 4700 2900 50  0000 L CNN
F 1 "33R" V 4700 2500 50  0000 L CNN
F 2 "" V 4690 2740 50  0001 C CNN
F 3 "~" H 4650 2750 50  0001 C CNN
	1    4650 2750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A1D61
P 4650 2850
AR Path="/5F2A50C6/5F9A1D61" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A1D61" Ref="R74"  Part="1" 
F 0 "R74" V 4700 3000 50  0000 L CNN
F 1 "33R" V 4700 2600 50  0000 L CNN
F 2 "" V 4690 2840 50  0001 C CNN
F 3 "~" H 4650 2850 50  0001 C CNN
	1    4650 2850
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A1EF4
P 4650 2950
AR Path="/5F2A50C6/5F9A1EF4" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A1EF4" Ref="R78"  Part="1" 
F 0 "R78" V 4700 3100 50  0000 L CNN
F 1 "33R" V 4700 2700 50  0000 L CNN
F 2 "" V 4690 2940 50  0001 C CNN
F 3 "~" H 4650 2950 50  0001 C CNN
	1    4650 2950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F9A206A
P 4650 3050
AR Path="/5F2A50C6/5F9A206A" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5F9A206A" Ref="R81"  Part="1" 
F 0 "R81" V 4700 3200 50  0000 L CNN
F 1 "33R" V 4700 2800 50  0000 L CNN
F 2 "" V 4690 3040 50  0001 C CNN
F 3 "~" H 4650 3050 50  0001 C CNN
	1    4650 3050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4500 1850 4300 1850
Wire Wire Line
	4300 1950 4500 1950
Wire Wire Line
	4500 2050 4300 2050
Wire Wire Line
	4300 2150 4500 2150
Wire Wire Line
	4500 2250 4300 2250
Wire Wire Line
	4300 2350 4500 2350
Wire Wire Line
	4500 2450 4300 2450
Wire Wire Line
	4300 2550 4500 2550
Wire Wire Line
	4500 2650 4300 2650
Wire Wire Line
	4300 2750 4500 2750
Wire Wire Line
	4500 2850 4300 2850
Wire Wire Line
	4300 2950 4500 2950
Wire Wire Line
	4300 3050 4500 3050
Wire Wire Line
	4800 3050 5550 3050
Wire Wire Line
	4800 2950 5550 2950
Wire Wire Line
	4800 2850 5550 2850
Wire Wire Line
	4800 2750 5550 2750
Wire Wire Line
	4800 2650 5550 2650
Wire Wire Line
	4800 2550 5550 2550
Wire Wire Line
	4800 2450 5550 2450
Wire Wire Line
	4800 2350 5550 2350
Wire Wire Line
	4800 2250 5550 2250
Wire Wire Line
	4800 2150 5550 2150
Wire Wire Line
	4800 2050 5550 2050
Wire Wire Line
	4800 1950 5550 1950
Wire Wire Line
	4800 1850 5550 1850
Text HLabel 1450 1050 0    50   Input ~ 0
NOR_DQ[0..3]
Text HLabel 1450 1250 0    50   Input ~ 0
SDRAM_A[0..12]
Text HLabel 1450 1450 0    50   Input ~ 0
SDRAM_D[0..15]
Wire Bus Line
	10550 1050 1450 1050
Wire Bus Line
	5500 1250 1450 1250
Entry Wire Line
	1950 3250 2050 3350
Entry Wire Line
	1950 3150 2050 3250
Entry Wire Line
	1950 3050 2050 3150
Entry Wire Line
	1950 2950 2050 3050
Entry Wire Line
	1950 2850 2050 2950
Entry Wire Line
	1950 2750 2050 2850
Entry Wire Line
	1950 2650 2050 2750
Entry Wire Line
	1950 2550 2050 2650
Entry Wire Line
	1950 2450 2050 2550
Entry Wire Line
	1950 2350 2050 2450
Entry Wire Line
	1950 2250 2050 2350
Entry Wire Line
	1950 2150 2050 2250
Entry Wire Line
	1950 2050 2050 2150
Entry Wire Line
	1950 1950 2050 2050
Entry Wire Line
	1950 1850 2050 1950
Entry Wire Line
	1950 1750 2050 1850
Wire Bus Line
	1800 1450 1450 1450
Wire Bus Line
	1950 1600 1800 1450
$Comp
L Device:R_US R?
U 1 1 5FA63B4C
P 2750 1850
AR Path="/5F2A50C6/5FA63B4C" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA63B4C" Ref="R50"  Part="1" 
F 0 "R50" V 2800 2000 50  0000 L CNN
F 1 "33R" V 2800 1600 50  0000 L CNN
F 2 "" V 2790 1840 50  0001 C CNN
F 3 "~" H 2750 1850 50  0001 C CNN
	1    2750 1850
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA63DF4
P 2750 1950
AR Path="/5F2A50C6/5FA63DF4" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA63DF4" Ref="R52"  Part="1" 
F 0 "R52" V 2800 2100 50  0000 L CNN
F 1 "33R" V 2800 1700 50  0000 L CNN
F 2 "" V 2790 1940 50  0001 C CNN
F 3 "~" H 2750 1950 50  0001 C CNN
	1    2750 1950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA63F30
P 2750 2050
AR Path="/5F2A50C6/5FA63F30" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA63F30" Ref="R54"  Part="1" 
F 0 "R54" V 2800 2200 50  0000 L CNN
F 1 "33R" V 2800 1800 50  0000 L CNN
F 2 "" V 2790 2040 50  0001 C CNN
F 3 "~" H 2750 2050 50  0001 C CNN
	1    2750 2050
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA640C3
P 2750 2150
AR Path="/5F2A50C6/5FA640C3" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA640C3" Ref="R56"  Part="1" 
F 0 "R56" V 2800 2300 50  0000 L CNN
F 1 "33R" V 2800 1900 50  0000 L CNN
F 2 "" V 2790 2140 50  0001 C CNN
F 3 "~" H 2750 2150 50  0001 C CNN
	1    2750 2150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA642A8
P 2750 2250
AR Path="/5F2A50C6/5FA642A8" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA642A8" Ref="R58"  Part="1" 
F 0 "R58" V 2800 2400 50  0000 L CNN
F 1 "33R" V 2800 2000 50  0000 L CNN
F 2 "" V 2790 2240 50  0001 C CNN
F 3 "~" H 2750 2250 50  0001 C CNN
	1    2750 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA643E9
P 2750 2350
AR Path="/5F2A50C6/5FA643E9" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA643E9" Ref="R60"  Part="1" 
F 0 "R60" V 2800 2500 50  0000 L CNN
F 1 "33R" V 2800 2100 50  0000 L CNN
F 2 "" V 2790 2340 50  0001 C CNN
F 3 "~" H 2750 2350 50  0001 C CNN
	1    2750 2350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA645BB
P 2750 2450
AR Path="/5F2A50C6/5FA645BB" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA645BB" Ref="R62"  Part="1" 
F 0 "R62" V 2800 2600 50  0000 L CNN
F 1 "33R" V 2800 2200 50  0000 L CNN
F 2 "" V 2790 2440 50  0001 C CNN
F 3 "~" H 2750 2450 50  0001 C CNN
	1    2750 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA64714
P 2750 2550
AR Path="/5F2A50C6/5FA64714" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA64714" Ref="R64"  Part="1" 
F 0 "R64" V 2800 2700 50  0000 L CNN
F 1 "33R" V 2800 2300 50  0000 L CNN
F 2 "" V 2790 2540 50  0001 C CNN
F 3 "~" H 2750 2550 50  0001 C CNN
	1    2750 2550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA64838
P 2750 2650
AR Path="/5F2A50C6/5FA64838" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA64838" Ref="R67"  Part="1" 
F 0 "R67" V 2800 2800 50  0000 L CNN
F 1 "33R" V 2800 2400 50  0000 L CNN
F 2 "" V 2790 2640 50  0001 C CNN
F 3 "~" H 2750 2650 50  0001 C CNN
	1    2750 2650
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA649AE
P 2750 2750
AR Path="/5F2A50C6/5FA649AE" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA649AE" Ref="R70"  Part="1" 
F 0 "R70" V 2800 2900 50  0000 L CNN
F 1 "33R" V 2800 2500 50  0000 L CNN
F 2 "" V 2790 2740 50  0001 C CNN
F 3 "~" H 2750 2750 50  0001 C CNN
	1    2750 2750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA64B16
P 2750 2850
AR Path="/5F2A50C6/5FA64B16" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA64B16" Ref="R73"  Part="1" 
F 0 "R73" V 2800 3000 50  0000 L CNN
F 1 "33R" V 2800 2600 50  0000 L CNN
F 2 "" V 2790 2840 50  0001 C CNN
F 3 "~" H 2750 2850 50  0001 C CNN
	1    2750 2850
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA64C13
P 2750 2950
AR Path="/5F2A50C6/5FA64C13" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA64C13" Ref="R77"  Part="1" 
F 0 "R77" V 2800 3100 50  0000 L CNN
F 1 "33R" V 2800 2700 50  0000 L CNN
F 2 "" V 2790 2940 50  0001 C CNN
F 3 "~" H 2750 2950 50  0001 C CNN
	1    2750 2950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA64DB0
P 2750 3050
AR Path="/5F2A50C6/5FA64DB0" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA64DB0" Ref="R80"  Part="1" 
F 0 "R80" V 2800 3200 50  0000 L CNN
F 1 "33R" V 2800 2800 50  0000 L CNN
F 2 "" V 2790 3040 50  0001 C CNN
F 3 "~" H 2750 3050 50  0001 C CNN
	1    2750 3050
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA64ECF
P 2750 3150
AR Path="/5F2A50C6/5FA64ECF" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA64ECF" Ref="R82"  Part="1" 
F 0 "R82" V 2800 3300 50  0000 L CNN
F 1 "33R" V 2800 2900 50  0000 L CNN
F 2 "" V 2790 3140 50  0001 C CNN
F 3 "~" H 2750 3150 50  0001 C CNN
	1    2750 3150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA65028
P 2750 3250
AR Path="/5F2A50C6/5FA65028" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA65028" Ref="R83"  Part="1" 
F 0 "R83" V 2800 3400 50  0000 L CNN
F 1 "33R" V 2800 3000 50  0000 L CNN
F 2 "" V 2790 3240 50  0001 C CNN
F 3 "~" H 2750 3250 50  0001 C CNN
	1    2750 3250
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA65147
P 2750 3350
AR Path="/5F2A50C6/5FA65147" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/5FA65147" Ref="R84"  Part="1" 
F 0 "R84" V 2800 3500 50  0000 L CNN
F 1 "33R" V 2800 3100 50  0000 L CNN
F 2 "" V 2790 3340 50  0001 C CNN
F 3 "~" H 2750 3350 50  0001 C CNN
	1    2750 3350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2050 1850 2600 1850
Wire Wire Line
	2600 1950 2050 1950
Wire Wire Line
	2050 2050 2600 2050
Wire Wire Line
	2600 2150 2050 2150
Wire Wire Line
	2050 2250 2600 2250
Wire Wire Line
	2600 2350 2050 2350
Wire Wire Line
	2050 2450 2600 2450
Wire Wire Line
	2600 2550 2050 2550
Wire Wire Line
	2050 2650 2600 2650
Wire Wire Line
	2600 2750 2050 2750
Wire Wire Line
	2050 2850 2600 2850
Wire Wire Line
	2600 2950 2050 2950
Wire Wire Line
	2050 3050 2600 3050
Wire Wire Line
	2600 3150 2050 3150
Wire Wire Line
	2050 3250 2600 3250
Wire Wire Line
	2600 3350 2050 3350
Wire Wire Line
	2900 3350 3100 3350
Wire Wire Line
	3100 3250 2900 3250
Wire Wire Line
	2900 3150 3100 3150
Wire Wire Line
	3100 3050 2900 3050
Wire Wire Line
	2900 2950 3100 2950
Wire Wire Line
	3100 2850 2900 2850
Wire Wire Line
	2900 2750 3100 2750
Wire Wire Line
	3100 2650 2900 2650
Wire Wire Line
	2900 2550 3100 2550
Wire Wire Line
	3100 2450 2900 2450
Wire Wire Line
	2900 2350 3100 2350
Wire Wire Line
	3100 2250 2900 2250
Wire Wire Line
	2900 2150 3100 2150
Wire Wire Line
	3100 2050 2900 2050
Wire Wire Line
	2900 1950 3100 1950
Wire Wire Line
	3100 1850 2900 1850
$Comp
L Device:R_US R?
U 1 1 601F48D0
P 8100 2850
AR Path="/5F2A50C6/601F48D0" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/601F48D0" Ref="R75"  Part="1" 
F 0 "R75" V 8150 3000 50  0000 L CNN
F 1 "33R" V 8150 2600 50  0000 L CNN
F 2 "" V 8140 2840 50  0001 C CNN
F 3 "~" H 8100 2850 50  0001 C CNN
	1    8100 2850
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 601F4D40
P 8100 2950
AR Path="/5F2A50C6/601F4D40" Ref="R?"  Part="1" 
AR Path="/5F60AB0F/601F4D40" Ref="R79"  Part="1" 
F 0 "R79" V 8150 3100 50  0000 L CNN
F 1 "33R" V 8150 2700 50  0000 L CNN
F 2 "" V 8140 2940 50  0001 C CNN
F 3 "~" H 8100 2950 50  0001 C CNN
	1    8100 2950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8250 2850 8400 2850
Wire Wire Line
	8400 2950 8250 2950
Wire Bus Line
	10800 1300 10800 3400
Wire Bus Line
	5650 1400 5650 3400
Wire Bus Line
	1950 1600 1950 3400
$EndSCHEMATC
