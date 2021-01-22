EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 12
Title "Flight Computer"
Date ""
Rev "2"
Comp "Notirous Rascal Club"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L FlightComputer_Library:GY-86 M3
U 1 1 5F337ED0
P 4150 4700
F 0 "M3" H 4206 5815 50  0000 C CNN
F 1 "GY-86" H 4206 5724 50  0000 C CNN
F 2 "FlightComputer_Library:GY-86" H 4150 4700 50  0001 C CNN
F 3 "" H 4150 4700 50  0001 C CNN
	1    4150 4700
	-1   0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:GY-91 M2
U 1 1 5F337F74
P 4150 2750
AR Path="/5F337F74" Ref="M2"  Part="1" 
AR Path="/5F2A508D/5F337F74" Ref="M2"  Part="1" 
F 0 "M2" H 4206 3865 50  0000 C CNN
F 1 "GY-91" H 4206 3774 50  0000 C CNN
F 2 "FlightComputer_Library:GY-91" H 4150 2750 50  0001 C CNN
F 3 "" H 4150 2750 50  0001 C CNN
	1    4150 2750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3500 3850 3500 3400
Wire Wire Line
	3200 4050 3800 4050
$Comp
L power:GND #PWR0156
U 1 1 5F426BC0
P 3200 1700
F 0 "#PWR0156" H 3200 1450 50  0001 C CNN
F 1 "GND" H 3205 1527 50  0000 C CNN
F 2 "" H 3200 1700 50  0001 C CNN
F 3 "" H 3200 1700 50  0001 C CNN
	1    3200 1700
	-1   0    0    1   
$EndComp
Wire Wire Line
	3500 3850 3800 3850
Wire Wire Line
	3500 1700 3500 1900
Wire Wire Line
	3500 1900 3800 1900
Wire Wire Line
	3200 2100 3800 2100
Wire Wire Line
	3200 1700 3200 2100
Text Label 1850 2200 0    50   ~ 0
SPI_SCLK
Text Label 1850 2300 0    50   ~ 0
SPI_MOSI
Text Label 1850 2400 0    50   ~ 0
SPI_MISO
Text Label 1850 2500 0    50   ~ 0
SPI_nCS1
Text Label 1850 2600 0    50   ~ 0
SPI_nCS2
Text Label 1850 4150 0    50   ~ 0
I2C_SCL
Text Label 1850 4250 0    50   ~ 0
I2C_SDA
Text Label 1850 4350 0    50   ~ 0
FSYNC
Text Label 1850 4450 0    50   ~ 0
nINT
Text Label 1850 4550 0    50   ~ 0
DRDY
$Comp
L FlightComputer_Library:VCC_BAT+ #PWR0162
U 1 1 5FFA4D7C
P 3500 3400
F 0 "#PWR0162" H 3500 3250 50  0001 C CNN
F 1 "VCC_BAT+" H 3517 3573 50  0000 C CNN
F 2 "" H 3500 3400 50  0001 C CNN
F 3 "" H 3500 3400 50  0001 C CNN
	1    3500 3400
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_BAT+ #PWR0157
U 1 1 5FFA516C
P 3500 1700
F 0 "#PWR0157" H 3500 1550 50  0001 C CNN
F 1 "VCC_BAT+" H 3517 1873 50  0000 C CNN
F 2 "" H 3500 1700 50  0001 C CNN
F 3 "" H 3500 1700 50  0001 C CNN
	1    3500 1700
	1    0    0    -1  
$EndComp
Text HLabel 1800 2200 0    50   Input ~ 0
SPI_SCLK
Text HLabel 1800 2300 0    50   Input ~ 0
SPI_MOSI
Text HLabel 1800 2400 0    50   Input ~ 0
SPI_MISO
Text HLabel 1800 2500 0    50   Input ~ 0
SPI_nCS1
Text HLabel 1800 2600 0    50   Input ~ 0
SPI_nCS2
Text HLabel 1800 4150 0    50   Input ~ 0
I2C_SCL
Text HLabel 1800 4250 0    50   Input ~ 0
I2C_SDA
Text HLabel 1800 4350 0    50   Input ~ 0
FSYNC
Text HLabel 1800 4450 0    50   Input ~ 0
nINT
Text HLabel 1800 4550 0    50   Input ~ 0
DRDY
$Comp
L Device:R_US R?
U 1 1 60177C4B
P 2800 2200
AR Path="/5F2A50C6/60177C4B" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/60177C4B" Ref="R?"  Part="1" 
AR Path="/5F2A508D/60177C4B" Ref="R141"  Part="1" 
F 0 "R141" V 2750 1900 50  0000 L CNN
F 1 "33R" V 2750 2300 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2840 2190 50  0001 C CNN
F 3 "~" H 2800 2200 50  0001 C CNN
	1    2800 2200
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 60177C51
P 2800 2300
AR Path="/5F2A50C6/60177C51" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/60177C51" Ref="R?"  Part="1" 
AR Path="/5F2A508D/60177C51" Ref="R142"  Part="1" 
F 0 "R142" V 2750 2000 50  0000 L CNN
F 1 "33R" V 2750 2400 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2840 2290 50  0001 C CNN
F 3 "~" H 2800 2300 50  0001 C CNN
	1    2800 2300
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 60177C57
P 2800 2400
AR Path="/5F2A50C6/60177C57" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/60177C57" Ref="R?"  Part="1" 
AR Path="/5F2A508D/60177C57" Ref="R143"  Part="1" 
F 0 "R143" V 2750 2100 50  0000 L CNN
F 1 "33R" V 2750 2500 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2840 2390 50  0001 C CNN
F 3 "~" H 2800 2400 50  0001 C CNN
	1    2800 2400
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 601790F2
P 2800 2500
AR Path="/5F2A50C6/601790F2" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/601790F2" Ref="R?"  Part="1" 
AR Path="/5F2A508D/601790F2" Ref="R144"  Part="1" 
F 0 "R144" V 2750 2200 50  0000 L CNN
F 1 "33R" V 2750 2600 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2840 2490 50  0001 C CNN
F 3 "~" H 2800 2500 50  0001 C CNN
	1    2800 2500
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 60179316
P 2800 2600
AR Path="/5F2A50C6/60179316" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/60179316" Ref="R?"  Part="1" 
AR Path="/5F2A508D/60179316" Ref="R145"  Part="1" 
F 0 "R145" V 2750 2300 50  0000 L CNN
F 1 "33R" V 2750 2700 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2840 2590 50  0001 C CNN
F 3 "~" H 2800 2600 50  0001 C CNN
	1    2800 2600
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 6017AF34
P 3250 4150
AR Path="/5F2A50C6/6017AF34" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6017AF34" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6017AF34" Ref="R150"  Part="1" 
F 0 "R150" V 3200 3850 50  0000 L CNN
F 1 "33R" V 3200 4250 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 3290 4140 50  0001 C CNN
F 3 "~" H 3250 4150 50  0001 C CNN
	1    3250 4150
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 6017AF3A
P 3250 4250
AR Path="/5F2A50C6/6017AF3A" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6017AF3A" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6017AF3A" Ref="R151"  Part="1" 
F 0 "R151" V 3200 3950 50  0000 L CNN
F 1 "33R" V 3200 4350 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 3290 4240 50  0001 C CNN
F 3 "~" H 3250 4250 50  0001 C CNN
	1    3250 4250
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 6017AF40
P 3250 4350
AR Path="/5F2A50C6/6017AF40" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6017AF40" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6017AF40" Ref="R152"  Part="1" 
F 0 "R152" V 3200 4050 50  0000 L CNN
F 1 "33R" V 3200 4450 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 3290 4340 50  0001 C CNN
F 3 "~" H 3250 4350 50  0001 C CNN
	1    3250 4350
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 6017AF46
P 3250 4450
AR Path="/5F2A50C6/6017AF46" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6017AF46" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6017AF46" Ref="R153"  Part="1" 
F 0 "R153" V 3200 4150 50  0000 L CNN
F 1 "33R" V 3200 4550 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 3290 4440 50  0001 C CNN
F 3 "~" H 3250 4450 50  0001 C CNN
	1    3250 4450
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 6017AF4C
P 3250 4550
AR Path="/5F2A50C6/6017AF4C" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6017AF4C" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6017AF4C" Ref="R154"  Part="1" 
F 0 "R154" V 3200 4250 50  0000 L CNN
F 1 "33R" V 3200 4650 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 3290 4540 50  0001 C CNN
F 3 "~" H 3250 4550 50  0001 C CNN
	1    3250 4550
	0    1    1    0   
$EndComp
Wire Wire Line
	2950 2200 3250 2200
Wire Wire Line
	2950 2300 3400 2300
Wire Wire Line
	2950 2400 3800 2400
Wire Wire Line
	2950 2500 3800 2500
Wire Wire Line
	2950 2600 3800 2600
Wire Wire Line
	2650 2600 1800 2600
Wire Wire Line
	1800 2500 2650 2500
Wire Wire Line
	2650 2400 1800 2400
Wire Wire Line
	1800 2300 2650 2300
Wire Wire Line
	2650 2200 1800 2200
Wire Wire Line
	1800 4350 3100 4350
Wire Wire Line
	3100 4450 1800 4450
Wire Wire Line
	3400 4550 3800 4550
Wire Wire Line
	3800 4450 3400 4450
Wire Wire Line
	3400 4350 3800 4350
Wire Wire Line
	3800 4250 3400 4250
Wire Wire Line
	3400 4150 3800 4150
NoConn ~ 3800 2000
Wire Wire Line
	1800 4550 3100 4550
$Comp
L power:GND #PWR0161
U 1 1 5F426B3B
P 3200 3400
F 0 "#PWR0161" H 3200 3150 50  0001 C CNN
F 1 "GND" H 3205 3227 50  0000 C CNN
F 2 "" H 3200 3400 50  0001 C CNN
F 3 "" H 3200 3400 50  0001 C CNN
	1    3200 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 3400 3200 4050
Wire Wire Line
	1800 4250 2550 4250
Wire Wire Line
	1800 4150 2400 4150
NoConn ~ 3800 3950
$Comp
L Device:R_US R?
U 1 1 5F8FDF65
P 2400 3500
AR Path="/5F2A50C6/5F8FDF65" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/5F8FDF65" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5F8FDF65" Ref="R148"  Part="1" 
F 0 "R148" H 2500 3450 50  0000 L CNN
F 1 "N/C" H 2500 3550 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2440 3490 50  0001 C CNN
F 3 "~" H 2400 3500 50  0001 C CNN
	1    2400 3500
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F8FF165
P 2550 3500
AR Path="/5F2A50C6/5F8FF165" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/5F8FF165" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5F8FF165" Ref="R149"  Part="1" 
F 0 "R149" H 2650 3450 50  0000 L CNN
F 1 "N/C" H 2650 3550 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2590 3490 50  0001 C CNN
F 3 "~" H 2550 3500 50  0001 C CNN
	1    2550 3500
	1    0    0    1   
$EndComp
Wire Wire Line
	2400 3650 2400 4150
Connection ~ 2400 4150
Wire Wire Line
	2400 4150 3100 4150
Wire Wire Line
	2550 3650 2550 4250
Connection ~ 2550 4250
Wire Wire Line
	2550 4250 3100 4250
Wire Wire Line
	2400 3350 2400 2850
Wire Wire Line
	3250 2850 3250 2200
Wire Wire Line
	2400 2850 3250 2850
Connection ~ 3250 2200
Wire Wire Line
	3250 2200 3800 2200
Wire Wire Line
	2550 3350 2550 2950
Wire Wire Line
	2550 2950 3400 2950
Wire Wire Line
	3400 2950 3400 2300
Connection ~ 3400 2300
Wire Wire Line
	3400 2300 3800 2300
Text HLabel 6900 3450 0    50   Input ~ 0
DEBUG_TX
Text HLabel 6900 3350 0    50   Input ~ 0
DEBUG_RX
Text Label 6950 3450 0    50   ~ 0
DEBUG_TX
Text Label 6950 3350 0    50   ~ 0
DEBUG_RX
$Comp
L Device:R_US R?
U 1 1 5F85FE02
P 7900 3350
AR Path="/5F2A50C6/5F85FE02" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/5F85FE02" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5F85FE02" Ref="R147"  Part="1" 
F 0 "R147" V 7850 3050 50  0000 L CNN
F 1 "33R" V 7850 3450 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 7940 3340 50  0001 C CNN
F 3 "~" H 7900 3350 50  0001 C CNN
	1    7900 3350
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F85FDFC
P 7900 3450
AR Path="/5F2A50C6/5F85FDFC" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/5F85FDFC" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5F85FDFC" Ref="R146"  Part="1" 
F 0 "R146" V 7850 3150 50  0000 L CNN
F 1 "33R" V 7850 3550 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 7940 3440 50  0001 C CNN
F 3 "~" H 7900 3450 50  0001 C CNN
	1    7900 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 3450 6900 3450
Wire Wire Line
	6900 3350 7750 3350
Wire Wire Line
	8050 3450 8300 3450
Wire Wire Line
	8050 3350 8300 3350
Wire Wire Line
	7800 2650 7800 2750
Wire Wire Line
	7800 2750 8300 2750
Text HLabel 6900 3150 0    50   Input ~ 0
GPS_TX
Text HLabel 6900 3050 0    50   Input ~ 0
GPS_RX
Text Label 6950 3150 0    50   ~ 0
GPS_TX
Text Label 6950 3050 0    50   ~ 0
GPS_RX
$Comp
L Device:R_US R?
U 1 1 6018DFD2
P 7900 3050
AR Path="/5F2A50C6/6018DFD2" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6018DFD2" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6018DFD2" Ref="R155"  Part="1" 
F 0 "R155" V 7850 2750 50  0000 L CNN
F 1 "33R" V 7850 3150 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 7940 3040 50  0001 C CNN
F 3 "~" H 7900 3050 50  0001 C CNN
	1    7900 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 6018DFD8
P 7900 3150
AR Path="/5F2A50C6/6018DFD8" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6018DFD8" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6018DFD8" Ref="R156"  Part="1" 
F 0 "R156" V 7850 2850 50  0000 L CNN
F 1 "33R" V 7850 3250 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 7940 3140 50  0001 C CNN
F 3 "~" H 7900 3150 50  0001 C CNN
	1    7900 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 3150 6900 3150
Wire Wire Line
	6900 3050 7750 3050
Wire Wire Line
	8050 3150 8300 3150
Wire Wire Line
	8050 3050 8300 3050
$Comp
L FlightComputer_Library:VCC_PERIH #PWR0164
U 1 1 5FFA6026
P 7800 2650
F 0 "#PWR0164" H 7800 2500 50  0001 C CNN
F 1 "VCC_PERIH" H 7817 2823 50  0000 C CNN
F 2 "" H 7800 2650 50  0001 C CNN
F 3 "" H 7800 2650 50  0001 C CNN
	1    7800 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 3650 7800 3750
Wire Wire Line
	8300 3650 7800 3650
$Comp
L power:GND #PWR0165
U 1 1 5F4D748C
P 7800 3750
F 0 "#PWR0165" H 7800 3500 50  0001 C CNN
F 1 "GND" H 7805 3577 50  0000 C CNN
F 2 "" H 7800 3750 50  0001 C CNN
F 3 "" H 7800 3750 50  0001 C CNN
	1    7800 3750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x10 J?
U 1 1 5F952072
P 8500 3150
AR Path="/5F2A50A6/5F952072" Ref="J?"  Part="1" 
AR Path="/5F2A508D/5F952072" Ref="J2"  Part="1" 
F 0 "J2" H 8580 3142 50  0000 L CNN
F 1 "Conn_01x10" H 8580 3051 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 8500 3150 50  0001 C CNN
F 3 "~" H 8500 3150 50  0001 C CNN
	1    8500 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 2850 7800 2850
Wire Wire Line
	7800 2850 7800 2750
Connection ~ 7800 2750
NoConn ~ 8300 2950
NoConn ~ 8300 3250
NoConn ~ 8300 3550
$EndSCHEMATC
