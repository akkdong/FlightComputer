EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 12
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
L FlightComputer_Library:WM8960 U?
U 1 1 5F335E9D
P 4700 2800
AR Path="/5F335E9D" Ref="U?"  Part="1" 
AR Path="/5F2A50A6/5F335E9D" Ref="U1"  Part="1" 
F 0 "U1" H 4700 2800 50  0000 C CNN
F 1 "WM8960" H 4700 2700 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-32-1EP_5x5mm_P0.5mm_EP3.3x3.3mm_ThermalVias" H 4700 2450 50  0001 C CNN
F 3 "" H 4700 2450 50  0001 C CNN
	1    4700 2800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5F349038
P 9050 2950
F 0 "J2" H 9130 2942 50  0000 L CNN
F 1 "Conn_01x02" H 9130 2851 50  0000 L CNN
F 2 "Connector_Molex:Molex_SPOX_5268-02A_1x02_P2.50mm_Horizontal" H 9050 2950 50  0001 C CNN
F 3 "~" H 9050 2950 50  0001 C CNN
	1    9050 2950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5F3490DA
P 9050 3250
F 0 "J3" H 9130 3242 50  0000 L CNN
F 1 "Conn_01x02" H 9130 3151 50  0000 L CNN
F 2 "Connector_Molex:Molex_SPOX_5268-02A_1x02_P2.50mm_Horizontal" H 9050 3250 50  0001 C CNN
F 3 "~" H 9050 3250 50  0001 C CNN
	1    9050 3250
	1    0    0    -1  
$EndComp
$Comp
L Oscillator:ASE-xxxMHz X1
U 1 1 5F349789
P 9100 5300
F 0 "X1" H 9400 5150 50  0000 L CNN
F 1 "24MHz" H 9350 5050 50  0000 L CNN
F 2 "Oscillator:Oscillator_SMD_Abracon_ASE-4Pin_3.2x2.5mm_HandSoldering" H 9800 4950 50  0001 C CNN
F 3 "http://www.abracon.com/Oscillators/ASV.pdf" H 9000 5300 50  0001 C CNN
	1    9100 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1650 4500 1650
Wire Wire Line
	4500 1650 4500 1750
Connection ~ 4400 1650
Wire Wire Line
	4400 1650 4400 1750
Wire Wire Line
	4500 1650 4600 1650
Wire Wire Line
	4600 1650 4600 1750
Connection ~ 4500 1650
Wire Wire Line
	4800 1650 4900 1650
Wire Wire Line
	4900 1650 4900 1750
Connection ~ 4800 1650
Wire Wire Line
	4800 1650 4800 1750
$Comp
L power:GND #PWR013
U 1 1 5F349CF8
P 4500 4150
F 0 "#PWR013" H 4500 3900 50  0001 C CNN
F 1 "GND" H 4505 3977 50  0000 C CNN
F 2 "" H 4500 4150 50  0001 C CNN
F 3 "" H 4500 4150 50  0001 C CNN
	1    4500 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3950 4500 4050
Wire Wire Line
	4500 4050 4600 4050
Wire Wire Line
	4600 4050 4600 3950
Connection ~ 4500 4050
Wire Wire Line
	4500 4050 4500 4150
Wire Wire Line
	4600 4050 4800 4050
Wire Wire Line
	4800 4050 4800 3950
Connection ~ 4600 4050
Wire Wire Line
	4800 4050 4900 4050
Wire Wire Line
	4900 4050 4900 3950
Connection ~ 4800 4050
Wire Wire Line
	4900 4050 5100 4050
Wire Wire Line
	5100 4050 5100 3950
Connection ~ 4900 4050
$Comp
L Device:C_Small C?
U 1 1 5F352A03
P 6050 3950
AR Path="/5F2A50C6/5F352A03" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F352A03" Ref="C15"  Part="1" 
F 0 "C15" H 6150 3900 50  0000 L CNN
F 1 "4.7uF" H 6150 4000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6050 3950 50  0001 C CNN
F 3 "~" H 6050 3950 50  0001 C CNN
	1    6050 3950
	1    0    0    1   
$EndComp
Wire Wire Line
	5750 3700 6050 3700
Wire Wire Line
	6050 3700 6050 3850
$Comp
L Device:C_Small C?
U 1 1 5F353F8C
P 5300 1500
AR Path="/5F2A50C6/5F353F8C" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F353F8C" Ref="C4"  Part="1" 
F 0 "C4" H 5100 1450 50  0000 L CNN
F 1 "4.7uF" H 5000 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5300 1500 50  0001 C CNN
F 3 "~" H 5300 1500 50  0001 C CNN
	1    5300 1500
	-1   0    0    1   
$EndComp
$Comp
L Device:CP1_Small C?
U 1 1 5F353F93
P 6200 2300
AR Path="/5F2A50C6/5F353F93" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F353F93" Ref="C9"  Part="1" 
F 0 "C9" V 6250 2400 50  0000 L CNN
F 1 "10uF" V 6250 2000 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-1608-08_AVX-J_Pad1.25x1.05mm_HandSolder" H 6200 2300 50  0001 C CNN
F 3 "~" H 6200 2300 50  0001 C CNN
	1    6200 2300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4900 1650 5300 1650
Wire Wire Line
	5300 1650 5300 1600
Connection ~ 4900 1650
Wire Wire Line
	5300 1650 5700 1650
Wire Wire Line
	5700 1650 5700 1600
Connection ~ 5300 1650
$Comp
L Device:C_Small C?
U 1 1 5F3555B5
P 4150 1500
AR Path="/5F2A50C6/5F3555B5" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F3555B5" Ref="C3"  Part="1" 
F 0 "C3" H 4300 1450 50  0000 L CNN
F 1 "0.1uF" H 4250 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4150 1500 50  0001 C CNN
F 3 "~" H 4150 1500 50  0001 C CNN
	1    4150 1500
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F3555E7
P 3750 1500
AR Path="/5F2A50C6/5F3555E7" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F3555E7" Ref="C2"  Part="1" 
F 0 "C2" H 3900 1450 50  0000 L CNN
F 1 "0.1uF" H 3850 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3750 1500 50  0001 C CNN
F 3 "~" H 3750 1500 50  0001 C CNN
	1    3750 1500
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F35561B
P 3350 1500
AR Path="/5F2A50C6/5F35561B" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F35561B" Ref="C1"  Part="1" 
F 0 "C1" H 3550 1450 50  0000 L CNN
F 1 "0.1uF" H 3450 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3350 1500 50  0001 C CNN
F 3 "~" H 3350 1500 50  0001 C CNN
	1    3350 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	4400 1650 4150 1650
Wire Wire Line
	3350 1650 3350 1600
Wire Wire Line
	3750 1600 3750 1650
Connection ~ 3750 1650
Wire Wire Line
	3750 1650 3350 1650
Wire Wire Line
	4150 1600 4150 1650
Connection ~ 4150 1650
Wire Wire Line
	4150 1650 3750 1650
$Comp
L power:GND #PWR01
U 1 1 5F356A47
P 3350 1300
F 0 "#PWR01" H 3350 1050 50  0001 C CNN
F 1 "GND" H 3355 1127 50  0000 C CNN
F 2 "" H 3350 1300 50  0001 C CNN
F 3 "" H 3350 1300 50  0001 C CNN
	1    3350 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	3350 1300 3350 1350
Wire Wire Line
	3350 1350 3750 1350
Wire Wire Line
	3750 1350 3750 1400
Connection ~ 3350 1350
Wire Wire Line
	3350 1350 3350 1400
Wire Wire Line
	3750 1350 4150 1350
Wire Wire Line
	4150 1350 4150 1400
Connection ~ 3750 1350
$Comp
L power:GND #PWR04
U 1 1 5F358BB9
P 5700 1300
F 0 "#PWR04" H 5700 1050 50  0001 C CNN
F 1 "GND" H 5705 1127 50  0000 C CNN
F 2 "" H 5700 1300 50  0001 C CNN
F 3 "" H 5700 1300 50  0001 C CNN
	1    5700 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	5700 1300 5700 1350
Wire Wire Line
	5700 1350 5300 1350
Wire Wire Line
	5300 1350 5300 1400
Connection ~ 5700 1350
Wire Wire Line
	5700 1350 5700 1400
$Comp
L Device:C_Small C?
U 1 1 5F35A8DD
P 3300 3950
AR Path="/5F2A50C6/5F35A8DD" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F35A8DD" Ref="C14"  Part="1" 
F 0 "C14" H 3392 3996 50  0000 L CNN
F 1 "4.7uF" H 3392 3905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3300 3950 50  0001 C CNN
F 3 "~" H 3300 3950 50  0001 C CNN
	1    3300 3950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3650 3750 3300 3750
Wire Wire Line
	3300 3750 3300 3850
$Comp
L power:GND #PWR012
U 1 1 5F35B454
P 3300 4150
F 0 "#PWR012" H 3300 3900 50  0001 C CNN
F 1 "GND" H 3305 3977 50  0000 C CNN
F 2 "" H 3300 4150 50  0001 C CNN
F 3 "" H 3300 4150 50  0001 C CNN
	1    3300 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1_Small C?
U 1 1 5F3620D6
P 6200 2100
AR Path="/5F2A50C6/5F3620D6" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F3620D6" Ref="C8"  Part="1" 
F 0 "C8" V 6250 2200 50  0000 L CNN
F 1 "10uF" V 6250 1800 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-1608-08_AVX-J_Pad1.25x1.05mm_HandSolder" H 6200 2100 50  0001 C CNN
F 3 "~" H 6200 2100 50  0001 C CNN
	1    6200 2100
	0    -1   -1   0   
$EndComp
$Comp
L pspice:INDUCTOR L?
U 1 1 5F362C51
P 6850 2100
AR Path="/5F2A50C6/5F362C51" Ref="L?"  Part="1" 
AR Path="/5F2A50A6/5F362C51" Ref="L1"  Part="1" 
F 0 "L1" H 6750 2200 50  0000 C CNN
F 1 "Ferrite" H 7000 2200 50  0000 C CNN
F 2 "Inductor_SMD:L_0402_1005Metric" H 6850 2100 50  0001 C CNN
F 3 "~" H 6850 2100 50  0001 C CNN
	1    6850 2100
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L?
U 1 1 5F36394B
P 6850 2300
AR Path="/5F2A50C6/5F36394B" Ref="L?"  Part="1" 
AR Path="/5F2A50A6/5F36394B" Ref="L2"  Part="1" 
F 0 "L2" H 6750 2400 50  0000 C CNN
F 1 "Ferrite" H 7000 2400 50  0000 C CNN
F 2 "Inductor_SMD:L_0402_1005Metric" H 6850 2300 50  0001 C CNN
F 3 "~" H 6850 2300 50  0001 C CNN
	1    6850 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2300 6100 2300
Wire Wire Line
	5750 2200 5900 2200
Wire Wire Line
	5900 2200 5900 2100
Wire Wire Line
	5900 2100 6100 2100
$Comp
L Device:C_Small C?
U 1 1 5F36C299
P 7500 1750
AR Path="/5F2A50C6/5F36C299" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F36C299" Ref="C6"  Part="1" 
F 0 "C6" H 7700 1700 50  0000 L CNN
F 1 "220pF" H 7650 1800 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7500 1750 50  0001 C CNN
F 3 "~" H 7500 1750 50  0001 C CNN
	1    7500 1750
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F36C2F7
P 7700 1750
AR Path="/5F2A50C6/5F36C2F7" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F36C2F7" Ref="C7"  Part="1" 
F 0 "C7" H 7450 1700 50  0000 L CNN
F 1 "220pF" H 7400 1800 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7700 1750 50  0001 C CNN
F 3 "~" H 7700 1750 50  0001 C CNN
	1    7700 1750
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5F36E50D
P 7500 1450
F 0 "#PWR05" H 7500 1200 50  0001 C CNN
F 1 "GND" H 7505 1277 50  0000 C CNN
F 2 "" H 7500 1450 50  0001 C CNN
F 3 "" H 7500 1450 50  0001 C CNN
	1    7500 1450
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5F36E53E
P 7700 1450
F 0 "#PWR06" H 7700 1200 50  0001 C CNN
F 1 "GND" H 7705 1277 50  0000 C CNN
F 2 "" H 7700 1450 50  0001 C CNN
F 3 "" H 7700 1450 50  0001 C CNN
	1    7700 1450
	-1   0    0    1   
$EndComp
Wire Wire Line
	7500 1450 7500 1650
Wire Wire Line
	7700 1450 7700 1650
Text Label 7550 2500 0    50   ~ 0
HPDETECT
$Comp
L Device:R_US R?
U 1 1 5F372276
P 8200 1850
AR Path="/5F2A50C6/5F372276" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F372276" Ref="R1"  Part="1" 
F 0 "R1" H 8268 1896 50  0000 L CNN
F 1 "100K" H 8268 1805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8240 1840 50  0001 C CNN
F 3 "~" H 8200 1850 50  0001 C CNN
	1    8200 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 1450 8200 1700
$Comp
L Device:R_US R?
U 1 1 5F374D26
P 3250 1950
AR Path="/5F2A50C6/5F374D26" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F374D26" Ref="R2"  Part="1" 
F 0 "R2" V 3200 1700 50  0000 L CNN
F 1 "33R" V 3200 2050 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 1940 50  0001 C CNN
F 3 "~" H 3250 1950 50  0001 C CNN
	1    3250 1950
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F374F21
P 3250 2050
AR Path="/5F2A50C6/5F374F21" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F374F21" Ref="R3"  Part="1" 
F 0 "R3" V 3200 1800 50  0000 L CNN
F 1 "33R" V 3200 2150 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 2040 50  0001 C CNN
F 3 "~" H 3250 2050 50  0001 C CNN
	1    3250 2050
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F374F63
P 3250 2150
AR Path="/5F2A50C6/5F374F63" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F374F63" Ref="R4"  Part="1" 
F 0 "R4" V 3200 1900 50  0000 L CNN
F 1 "33R" V 3200 2250 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 2140 50  0001 C CNN
F 3 "~" H 3250 2150 50  0001 C CNN
	1    3250 2150
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F374FA3
P 3250 2250
AR Path="/5F2A50C6/5F374FA3" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F374FA3" Ref="R5"  Part="1" 
F 0 "R5" V 3200 2000 50  0000 L CNN
F 1 "33R" V 3200 2350 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 2240 50  0001 C CNN
F 3 "~" H 3250 2250 50  0001 C CNN
	1    3250 2250
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F37502B
P 3250 2450
AR Path="/5F2A50C6/5F37502B" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F37502B" Ref="R6"  Part="1" 
F 0 "R6" V 3200 2200 50  0000 L CNN
F 1 "33R" V 3200 2550 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 2440 50  0001 C CNN
F 3 "~" H 3250 2450 50  0001 C CNN
	1    3250 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 2450 3400 2450
Wire Wire Line
	3400 2250 3650 2250
Wire Wire Line
	3650 2150 3600 2150
Wire Wire Line
	3650 2050 3400 2050
Wire Wire Line
	3650 1950 3400 1950
Wire Wire Line
	3600 2150 3600 2350
Connection ~ 3600 2150
Wire Wire Line
	3600 2150 3400 2150
Wire Wire Line
	3600 2350 3650 2350
$Comp
L Device:R_US R?
U 1 1 5F38B1D7
P 3250 2650
AR Path="/5F2A50C6/5F38B1D7" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F38B1D7" Ref="R7"  Part="1" 
F 0 "R7" V 3200 2400 50  0000 L CNN
F 1 "33R" V 3200 2750 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 2640 50  0001 C CNN
F 3 "~" H 3250 2650 50  0001 C CNN
	1    3250 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F38B21F
P 3250 2750
AR Path="/5F2A50C6/5F38B21F" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F38B21F" Ref="R8"  Part="1" 
F 0 "R8" V 3200 2500 50  0000 L CNN
F 1 "33R" V 3200 2850 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 2740 50  0001 C CNN
F 3 "~" H 3250 2750 50  0001 C CNN
	1    3250 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 2650 3650 2650
Wire Wire Line
	3400 2750 3650 2750
Wire Wire Line
	8500 5300 8800 5300
$Comp
L power:GND #PWR016
U 1 1 5F3B97FD
P 8500 5800
F 0 "#PWR016" H 8500 5550 50  0001 C CNN
F 1 "GND" H 8505 5627 50  0000 C CNN
F 2 "" H 8500 5800 50  0001 C CNN
F 3 "" H 8500 5800 50  0001 C CNN
	1    8500 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 5300 10550 5300
Text Label 10550 5300 2    50   ~ 0
I2S_MCLK
Wire Wire Line
	9100 5600 9100 5700
Wire Wire Line
	8500 5600 8500 5700
$Comp
L Device:R_US R?
U 1 1 5F3C8E96
P 3250 3050
AR Path="/5F2A50C6/5F3C8E96" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F3C8E96" Ref="R9"  Part="1" 
F 0 "R9" V 3200 2800 50  0000 L CNN
F 1 "33R" V 3200 3150 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 3040 50  0001 C CNN
F 3 "~" H 3250 3050 50  0001 C CNN
	1    3250 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F3C8F0A
P 3250 3250
AR Path="/5F2A50C6/5F3C8F0A" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F3C8F0A" Ref="R11"  Part="1" 
F 0 "R11" V 3200 3000 50  0000 L CNN
F 1 "N/C" V 3200 3350 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 3240 50  0001 C CNN
F 3 "~" H 3250 3250 50  0001 C CNN
	1    3250 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F3C8F5C
P 3250 3350
AR Path="/5F2A50C6/5F3C8F5C" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F3C8F5C" Ref="R12"  Part="1" 
F 0 "R12" V 3200 3100 50  0000 L CNN
F 1 "N/C" V 3200 3450 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 3340 50  0001 C CNN
F 3 "~" H 3250 3350 50  0001 C CNN
	1    3250 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 3050 3650 3050
Wire Wire Line
	3400 3250 3650 3250
Wire Wire Line
	3650 3350 3400 3350
$Comp
L FlightComputer_Library:TEA5767_Radio_Module M1
U 1 1 5F41020E
P 3950 6350
F 0 "M1" H 3950 6815 50  0000 C CNN
F 1 "TEA5767_Radio_Module" H 3950 6724 50  0000 C CNN
F 2 "FlightComputer_Library:TEA5756-TJ-102BC" H 3950 5900 50  0001 C CNN
F 3 "" H 3950 5900 50  0001 C CNN
	1    3950 6350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F410428
P 3050 6150
AR Path="/5F2A50C6/5F410428" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F410428" Ref="R16"  Part="1" 
F 0 "R16" V 3000 5900 50  0000 L CNN
F 1 "33R" V 3000 6250 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3090 6140 50  0001 C CNN
F 3 "~" H 3050 6150 50  0001 C CNN
	1    3050 6150
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F4108D0
P 3050 6250
AR Path="/5F2A50C6/5F4108D0" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F4108D0" Ref="R17"  Part="1" 
F 0 "R17" V 3000 6000 50  0000 L CNN
F 1 "33R" V 3000 6350 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3090 6240 50  0001 C CNN
F 3 "~" H 3050 6250 50  0001 C CNN
	1    3050 6250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR018
U 1 1 5F410926
P 3400 6350
F 0 "#PWR018" H 3400 6100 50  0001 C CNN
F 1 "GND" V 3405 6222 50  0000 R CNN
F 2 "" H 3400 6350 50  0001 C CNN
F 3 "" H 3400 6350 50  0001 C CNN
	1    3400 6350
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 6350 3500 6350
$Comp
L pspice:INDUCTOR L?
U 1 1 5F417E20
P 2000 6550
AR Path="/5F2A50C6/5F417E20" Ref="L?"  Part="1" 
AR Path="/5F2A50A6/5F417E20" Ref="L7"  Part="1" 
F 0 "L7" H 1850 6650 50  0000 C CNN
F 1 "Ferrite" H 2100 6650 50  0000 C CNN
F 2 "Inductor_SMD:L_0402_1005Metric" H 2000 6550 50  0001 C CNN
F 3 "~" H 2000 6550 50  0001 C CNN
	1    2000 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F41EDB4
P 2650 6750
AR Path="/5F2A50C6/5F41EDB4" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F41EDB4" Ref="C19"  Part="1" 
F 0 "C19" H 2742 6796 50  0000 L CNN
F 1 "0.1uF" H 2742 6705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 2650 6750 50  0001 C CNN
F 3 "~" H 2650 6750 50  0001 C CNN
	1    2650 6750
	-1   0    0    -1  
$EndComp
$Comp
L Device:CP1_Small C?
U 1 1 5F42068D
P 2950 6750
AR Path="/5F2A50C6/5F42068D" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F42068D" Ref="C20"  Part="1" 
F 0 "C20" H 3041 6796 50  0000 L CNN
F 1 "10uF" H 3041 6705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2950 6750 50  0001 C CNN
F 3 "~" H 2950 6750 50  0001 C CNN
	1    2950 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 6550 2950 6550
Wire Wire Line
	2650 6550 2650 6650
Connection ~ 2950 6550
Wire Wire Line
	2950 6550 3350 6550
Wire Wire Line
	2950 6550 2950 6650
Wire Wire Line
	3200 6150 3500 6150
Wire Wire Line
	3500 6250 3200 6250
Text HLabel 2200 6150 0    50   Input ~ 0
I2C_SDA
Text HLabel 2200 6250 0    50   Input ~ 0
I2C_SCL
Connection ~ 2650 6550
Wire Wire Line
	2900 6250 2200 6250
Wire Wire Line
	2200 6150 2900 6150
$Comp
L power:GND #PWR017
U 1 1 5F454319
P 4500 6250
F 0 "#PWR017" H 4500 6000 50  0001 C CNN
F 1 "GND" V 4505 6122 50  0000 R CNN
F 2 "" H 4500 6250 50  0001 C CNN
F 3 "" H 4500 6250 50  0001 C CNN
	1    4500 6250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5F4543C0
P 4500 6550
F 0 "#PWR020" H 4500 6300 50  0001 C CNN
F 1 "GND" V 4505 6422 50  0000 R CNN
F 2 "" H 4500 6550 50  0001 C CNN
F 3 "" H 4500 6550 50  0001 C CNN
	1    4500 6550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4400 6550 4500 6550
Wire Wire Line
	4400 6250 4500 6250
$Comp
L power:GND #PWR021
U 1 1 5F45D6AC
P 2650 6950
F 0 "#PWR021" H 2650 6700 50  0001 C CNN
F 1 "GND" H 2655 6777 50  0000 C CNN
F 2 "" H 2650 6950 50  0001 C CNN
F 3 "" H 2650 6950 50  0001 C CNN
	1    2650 6950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5F45D7C8
P 2950 6950
F 0 "#PWR022" H 2950 6700 50  0001 C CNN
F 1 "GND" H 2955 6777 50  0000 C CNN
F 2 "" H 2950 6950 50  0001 C CNN
F 3 "" H 2950 6950 50  0001 C CNN
	1    2950 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 6850 2950 6950
Wire Wire Line
	2650 6850 2650 6950
$Comp
L Device:C_Small C?
U 1 1 5F468C3D
P 5200 6450
AR Path="/5F2A50C6/5F468C3D" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F468C3D" Ref="C18"  Part="1" 
F 0 "C18" V 5100 6550 50  0000 L CNN
F 1 "10uF" V 5100 6200 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5200 6450 50  0001 C CNN
F 3 "~" H 5200 6450 50  0001 C CNN
	1    5200 6450
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F468F46
P 5200 6200
AR Path="/5F2A50C6/5F468F46" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F468F46" Ref="C17"  Part="1" 
F 0 "C17" V 5100 6300 50  0000 L CNN
F 1 "10uF" V 5100 5950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5200 6200 50  0001 C CNN
F 3 "~" H 5200 6200 50  0001 C CNN
	1    5200 6200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4400 6450 5100 6450
Wire Wire Line
	4400 6350 4950 6350
Wire Wire Line
	4950 6350 4950 6200
Wire Wire Line
	4950 6200 5100 6200
Wire Wire Line
	5300 6200 5850 6200
Wire Wire Line
	5300 6450 5850 6450
Text Label 5850 6200 2    50   ~ 0
RADIO_R
Text Label 5850 6450 2    50   ~ 0
RADIO_L
NoConn ~ 3500 6450
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 5F48463F
P 5000 5950
F 0 "J4" H 5080 5992 50  0000 L CNN
F 1 "Conn_01x01" H 5080 5901 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.2mm_L10.2mm_W2.9mm_FlatFork" H 5000 5950 50  0001 C CNN
F 3 "~" H 5000 5950 50  0001 C CNN
	1    5000 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 6150 4650 6150
Wire Wire Line
	4650 6150 4650 5950
Wire Wire Line
	4650 5950 4800 5950
$Comp
L FlightComputer_Library:VCC_3V3 #PWR019
U 1 1 5FC8BC9C
P 1500 6400
F 0 "#PWR019" H 1500 6250 50  0001 C CNN
F 1 "VCC_3V3" H 1517 6573 50  0000 C CNN
F 2 "" H 1500 6400 50  0001 C CNN
F 3 "" H 1500 6400 50  0001 C CNN
	1    1500 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 6550 1500 6550
Wire Wire Line
	1500 6550 1500 6400
$Comp
L FlightComputer_Library:VCC_3V3 #PWR015
U 1 1 5FC91A41
P 8500 4750
F 0 "#PWR015" H 8500 4600 50  0001 C CNN
F 1 "VCC_3V3" H 8517 4923 50  0000 C CNN
F 2 "" H 8500 4750 50  0001 C CNN
F 3 "" H 8500 4750 50  0001 C CNN
	1    8500 4750
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_3V3 #PWR07
U 1 1 5FC921AE
P 8200 1450
F 0 "#PWR07" H 8200 1300 50  0001 C CNN
F 1 "VCC_3V3" H 8217 1623 50  0000 C CNN
F 2 "" H 8200 1450 50  0001 C CNN
F 3 "" H 8200 1450 50  0001 C CNN
	1    8200 1450
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_5V #PWR03
U 1 1 5FC92224
P 4800 1300
F 0 "#PWR03" H 4800 1150 50  0001 C CNN
F 1 "VCC_5V" H 4817 1473 50  0000 C CNN
F 2 "" H 4800 1300 50  0001 C CNN
F 3 "" H 4800 1300 50  0001 C CNN
	1    4800 1300
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_3V3 #PWR02
U 1 1 5FC9228A
P 4400 1300
F 0 "#PWR02" H 4400 1150 50  0001 C CNN
F 1 "VCC_3V3" H 4417 1473 50  0000 C CNN
F 2 "" H 4400 1300 50  0001 C CNN
F 3 "" H 4400 1300 50  0001 C CNN
	1    4400 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1300 4400 1650
Wire Wire Line
	4800 1300 4800 1650
Wire Wire Line
	7100 2100 7500 2100
Wire Wire Line
	7100 2300 7700 2300
Wire Wire Line
	8750 2400 8200 2400
Wire Wire Line
	8200 2400 8200 2000
Wire Wire Line
	7550 2500 8750 2500
$Comp
L Device:R_US R?
U 1 1 601233A0
P 8500 5100
AR Path="/5F2A50C6/601233A0" Ref="R?"  Part="1" 
AR Path="/5F2A508D/601233A0" Ref="R?"  Part="1" 
AR Path="/5F741CFB/601233A0" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/601233A0" Ref="R14"  Part="1" 
F 0 "R14" H 8250 5050 50  0000 L CNN
F 1 "10K" H 8250 5150 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8540 5090 50  0001 C CNN
F 3 "~" H 8500 5100 50  0001 C CNN
	1    8500 5100
	1    0    0    1   
$EndComp
Wire Wire Line
	8500 4750 8500 4850
Wire Wire Line
	8500 5250 8500 5300
Connection ~ 8500 5300
Wire Wire Line
	8500 4950 8500 4850
Wire Wire Line
	8500 4850 9100 4850
Wire Wire Line
	9100 4850 9100 5000
Wire Wire Line
	8500 5400 8500 5300
$Comp
L Device:C_Small C?
U 1 1 5F3BE829
P 8500 5500
AR Path="/5F2A50C6/5F3BE829" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F3BE829" Ref="C16"  Part="1" 
F 0 "C16" H 8600 5450 50  0000 L CNN
F 1 "0.1uF" H 8600 5550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8500 5500 50  0001 C CNN
F 3 "~" H 8500 5500 50  0001 C CNN
	1    8500 5500
	-1   0    0    1   
$EndComp
Connection ~ 3350 6550
Wire Wire Line
	3350 6550 3500 6550
$Comp
L pspice:INDUCTOR L?
U 1 1 5F8190C8
P 6400 2950
AR Path="/5F2A50C6/5F8190C8" Ref="L?"  Part="1" 
AR Path="/5F2A50A6/5F8190C8" Ref="L3"  Part="1" 
F 0 "L3" H 6050 3000 50  0000 C CNN
F 1 "Ferrite" H 6800 3000 50  0000 C CNN
F 2 "Inductor_SMD:L_0402_1005Metric" H 6400 2950 50  0001 C CNN
F 3 "~" H 6400 2950 50  0001 C CNN
	1    6400 2950
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L?
U 1 1 5F81955C
P 6400 3050
AR Path="/5F2A50C6/5F81955C" Ref="L?"  Part="1" 
AR Path="/5F2A50A6/5F81955C" Ref="L4"  Part="1" 
F 0 "L4" H 6050 3100 50  0000 C CNN
F 1 "Ferrite" H 6800 3100 50  0000 C CNN
F 2 "Inductor_SMD:L_0402_1005Metric" H 6400 3050 50  0001 C CNN
F 3 "~" H 6400 3050 50  0001 C CNN
	1    6400 3050
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L?
U 1 1 5F81971C
P 6400 3250
AR Path="/5F2A50C6/5F81971C" Ref="L?"  Part="1" 
AR Path="/5F2A50A6/5F81971C" Ref="L5"  Part="1" 
F 0 "L5" H 6050 3300 50  0000 C CNN
F 1 "Ferrite" H 6800 3300 50  0000 C CNN
F 2 "Inductor_SMD:L_0402_1005Metric" H 6400 3250 50  0001 C CNN
F 3 "~" H 6400 3250 50  0001 C CNN
	1    6400 3250
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L?
U 1 1 5F81987A
P 6400 3350
AR Path="/5F2A50C6/5F81987A" Ref="L?"  Part="1" 
AR Path="/5F2A50A6/5F81987A" Ref="L6"  Part="1" 
F 0 "L6" H 6050 3400 50  0000 C CNN
F 1 "Ferrite" H 6800 3400 50  0000 C CNN
F 2 "Inductor_SMD:L_0402_1005Metric" H 6400 3350 50  0001 C CNN
F 3 "~" H 6400 3350 50  0001 C CNN
	1    6400 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F81B2C7
P 7400 3700
AR Path="/5F2A50C6/5F81B2C7" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F81B2C7" Ref="C10"  Part="1" 
F 0 "C10" H 7600 3750 50  0000 L CNN
F 1 "220pF" H 7500 3650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7400 3700 50  0001 C CNN
F 3 "~" H 7400 3700 50  0001 C CNN
	1    7400 3700
	-1   0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F81B2CD
P 7650 3700
AR Path="/5F2A50C6/5F81B2CD" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F81B2CD" Ref="C11"  Part="1" 
F 0 "C11" H 7450 3750 50  0000 L CNN
F 1 "220pF" H 7300 3650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7650 3700 50  0001 C CNN
F 3 "~" H 7650 3700 50  0001 C CNN
	1    7650 3700
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5F81B2D3
P 7400 3950
F 0 "#PWR08" H 7400 3700 50  0001 C CNN
F 1 "GND" H 7405 3777 50  0000 C CNN
F 2 "" H 7400 3950 50  0001 C CNN
F 3 "" H 7400 3950 50  0001 C CNN
	1    7400 3950
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5F81B2D9
P 7650 3950
F 0 "#PWR09" H 7650 3700 50  0001 C CNN
F 1 "GND" H 7655 3777 50  0000 C CNN
F 2 "" H 7650 3950 50  0001 C CNN
F 3 "" H 7650 3950 50  0001 C CNN
	1    7650 3950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7400 3950 7400 3800
Wire Wire Line
	7650 3950 7650 3800
$Comp
L Device:C_Small C?
U 1 1 5F82C841
P 8450 3700
AR Path="/5F2A50C6/5F82C841" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F82C841" Ref="C12"  Part="1" 
F 0 "C12" H 8650 3750 50  0000 L CNN
F 1 "220pF" H 8550 3650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8450 3700 50  0001 C CNN
F 3 "~" H 8450 3700 50  0001 C CNN
	1    8450 3700
	-1   0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F82C847
P 8650 3700
AR Path="/5F2A50C6/5F82C847" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5F82C847" Ref="C13"  Part="1" 
F 0 "C13" H 8400 3750 50  0000 L CNN
F 1 "220pF" H 8300 3650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8650 3700 50  0001 C CNN
F 3 "~" H 8650 3700 50  0001 C CNN
	1    8650 3700
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5F82C84D
P 8450 3950
F 0 "#PWR010" H 8450 3700 50  0001 C CNN
F 1 "GND" H 8455 3777 50  0000 C CNN
F 2 "" H 8450 3950 50  0001 C CNN
F 3 "" H 8450 3950 50  0001 C CNN
	1    8450 3950
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5F82C853
P 8650 3950
F 0 "#PWR011" H 8650 3700 50  0001 C CNN
F 1 "GND" H 8655 3777 50  0000 C CNN
F 2 "" H 8650 3950 50  0001 C CNN
F 3 "" H 8650 3950 50  0001 C CNN
	1    8650 3950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8450 3950 8450 3800
Wire Wire Line
	8650 3950 8650 3800
Wire Wire Line
	5750 3350 6150 3350
Wire Wire Line
	5750 3250 6150 3250
Wire Wire Line
	5750 2950 6150 2950
Wire Wire Line
	5750 3050 6150 3050
Wire Wire Line
	6650 2950 7400 2950
Wire Wire Line
	6650 3050 7650 3050
Wire Wire Line
	8850 3250 8450 3250
Wire Wire Line
	6650 3350 8650 3350
Wire Wire Line
	7400 3600 7400 2950
Connection ~ 7400 2950
Wire Wire Line
	7400 2950 8850 2950
Wire Wire Line
	7650 3600 7650 3050
Connection ~ 7650 3050
Wire Wire Line
	7650 3050 8850 3050
Wire Wire Line
	8450 3600 8450 3250
Connection ~ 8450 3250
Wire Wire Line
	8450 3250 6650 3250
Wire Wire Line
	8650 3600 8650 3350
Connection ~ 8650 3350
Wire Wire Line
	8650 3350 8850 3350
Wire Wire Line
	6300 2300 6600 2300
Wire Wire Line
	6300 2100 6600 2100
Wire Wire Line
	7500 1850 7500 2100
Connection ~ 7500 2100
Wire Wire Line
	7500 2100 8750 2100
Wire Wire Line
	7700 1850 7700 2300
Connection ~ 7700 2300
Wire Wire Line
	7700 2300 8750 2300
$Comp
L Device:R_US R?
U 1 1 5F8C07A8
P 3250 3150
AR Path="/5F2A50C6/5F8C07A8" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F8C07A8" Ref="R10"  Part="1" 
F 0 "R10" V 3200 2900 50  0000 L CNN
F 1 "33R" V 3200 3250 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 3140 50  0001 C CNN
F 3 "~" H 3250 3150 50  0001 C CNN
	1    3250 3150
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F8C09EA
P 3250 3450
AR Path="/5F2A50C6/5F8C09EA" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F8C09EA" Ref="R13"  Part="1" 
F 0 "R13" V 3200 3200 50  0000 L CNN
F 1 "33R" V 3200 3550 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 3440 50  0001 C CNN
F 3 "~" H 3250 3450 50  0001 C CNN
	1    3250 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 3450 3650 3450
Wire Wire Line
	3650 3150 3400 3150
Wire Wire Line
	3300 4050 3300 4150
$Comp
L Device:R_US R?
U 1 1 5F9D854B
P 9650 5300
AR Path="/5F2A50C6/5F9D854B" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5F9D854B" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5F9D854B" Ref="R?"  Part="1" 
AR Path="/5F2A50A6/5F9D854B" Ref="R15"  Part="1" 
F 0 "R15" V 9700 5450 50  0000 L CNN
F 1 "33R" V 9700 5000 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9690 5290 50  0001 C CNN
F 3 "~" H 9650 5300 50  0001 C CNN
	1    9650 5300
	0    -1   -1   0   
$EndComp
Connection ~ 8500 4850
Wire Wire Line
	9100 5700 8500 5700
Connection ~ 8500 5700
Wire Wire Line
	8500 5700 8500 5800
Wire Wire Line
	9400 5300 9500 5300
$Comp
L Connector:TestPoint_Alt TP?
U 1 1 5F9F9D8D
P 6200 2650
AR Path="/5F5976A1/5F9F9D8D" Ref="TP?"  Part="1" 
AR Path="/5F2A50A6/5F9F9D8D" Ref="TP1"  Part="1" 
F 0 "TP1" V 6200 2900 50  0000 C CNN
F 1 "OUT3" V 6150 2550 50  0000 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 6400 2650 50  0001 C CNN
F 3 "~" H 6400 2650 50  0001 C CNN
	1    6200 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 2650 6200 2650
Text Label 2400 2750 0    50   ~ 0
I2C_SDA
Text Label 2400 2650 0    50   ~ 0
I2C_SCL
Text Label 2400 2450 0    50   ~ 0
I2S_DOUT
Text Label 2400 2250 0    50   ~ 0
I2S_DIN
Text Label 2400 2150 0    50   ~ 0
I2S_LRCK
Text Label 2400 2050 0    50   ~ 0
I2S_SCLK
Wire Wire Line
	2450 3550 3650 3550
$Comp
L Connector:TestPoint_Alt TP?
U 1 1 5F9E3F61
P 2450 3550
AR Path="/5F5976A1/5F9E3F61" Ref="TP?"  Part="1" 
AR Path="/5F2A50A6/5F9E3F61" Ref="TP2"  Part="1" 
F 0 "TP2" V 2450 3800 50  0000 C CNN
F 1 "RINPUT3" V 2500 3450 50  0000 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 2650 3550 50  0001 C CNN
F 3 "~" H 2650 3550 50  0001 C CNN
	1    2450 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2850 3350 2400 3350
Connection ~ 2850 3350
Wire Wire Line
	2850 3450 2850 3350
Wire Wire Line
	3100 3450 2850 3450
Wire Wire Line
	2850 3250 2400 3250
Connection ~ 2850 3250
Wire Wire Line
	2850 3150 2850 3250
Wire Wire Line
	3100 3150 2850 3150
Wire Wire Line
	2350 2450 3100 2450
Wire Wire Line
	3100 2250 2350 2250
Text Label 2400 3350 0    50   ~ 0
RADIO_R
Text Label 2400 3250 0    50   ~ 0
RADIO_L
Wire Wire Line
	3100 3350 2850 3350
Wire Wire Line
	3100 3250 2850 3250
Text Label 2400 3050 0    50   ~ 0
HPDETECT
Wire Wire Line
	3100 3050 2400 3050
Text HLabel 2350 2750 0    50   Input ~ 0
I2C_SDA
Text HLabel 2350 2650 0    50   Input ~ 0
I2C_SCL
Wire Wire Line
	3100 2750 2350 2750
Wire Wire Line
	3100 2650 2350 2650
Text Label 2400 1950 0    50   ~ 0
I2S_MCLK
Text HLabel 2350 2250 0    50   Input ~ 0
I2S_DIN
Text HLabel 2350 2450 0    50   Input ~ 0
I2S_DOUT
Text HLabel 2350 2150 0    50   Input ~ 0
I2S_LRCK
Text HLabel 2350 2050 0    50   Input ~ 0
I2S_SCLK
Wire Wire Line
	3100 2150 2350 2150
Wire Wire Line
	3100 2050 2350 2050
Wire Wire Line
	3100 1950 2400 1950
Text Label 2250 6150 0    50   ~ 0
I2C_SDA
Text Label 2250 6250 0    50   ~ 0
I2C_SCL
Wire Wire Line
	2250 6550 2650 6550
Wire Wire Line
	3350 6850 3350 6550
$Comp
L power:PWR_FLAG #FLG01
U 1 1 605D9646
P 3350 6850
F 0 "#FLG01" H 3350 6925 50  0001 C CNN
F 1 "PWR_FLAG" H 3350 7023 50  0000 C CNN
F 2 "" H 3350 6850 50  0001 C CNN
F 3 "~" H 3350 6850 50  0001 C CNN
	1    3350 6850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5F3531EC
P 6050 4150
F 0 "#PWR014" H 6050 3900 50  0001 C CNN
F 1 "GND" H 6055 3977 50  0000 C CNN
F 2 "" H 6050 4150 50  0001 C CNN
F 3 "" H 6050 4150 50  0001 C CNN
	1    6050 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 4050 6050 4150
$Comp
L Device:C_Small C?
U 1 1 5FB0F2BC
P 5700 1500
AR Path="/5F2A50C6/5FB0F2BC" Ref="C?"  Part="1" 
AR Path="/5F2A50A6/5FB0F2BC" Ref="C5"  Part="1" 
F 0 "C5" H 5500 1450 50  0000 L CNN
F 1 "4.7uF" H 5400 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5700 1500 50  0001 C CNN
F 3 "~" H 5700 1500 50  0001 C CNN
	1    5700 1500
	-1   0    0    1   
$EndComp
$Comp
L FlightComputer_Library:SJ-43617-SMT J1
U 1 1 5FB13296
P 9000 2250
F 0 "J1" H 8670 2258 50  0000 R CNN
F 1 "SJ-43617-SMT" H 8670 2349 50  0000 R CNN
F 2 "FlightComputer_Library:SJ-43617-SMT" H 9050 2300 50  0001 C CNN
F 3 "" H 9050 2300 50  0001 C CNN
	1    9000 2250
	-1   0    0    1   
$EndComp
NoConn ~ 8750 2000
NoConn ~ 8750 2200
$Comp
L power:GND #PWR0231
U 1 1 5FB48519
P 8250 2650
F 0 "#PWR0231" H 8250 2400 50  0001 C CNN
F 1 "GND" H 8255 2477 50  0000 C CNN
F 2 "" H 8250 2650 50  0001 C CNN
F 3 "" H 8250 2650 50  0001 C CNN
	1    8250 2650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8750 2600 8250 2600
Wire Wire Line
	8250 2600 8250 2650
$EndSCHEMATC
