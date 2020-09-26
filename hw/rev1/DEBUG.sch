EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 12 12
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
L Connector_Generic:Conn_02x10_Odd_Even J?
U 1 1 5FAE6220
P 5200 2300
F 0 "J?" H 5250 2917 50  0000 C CNN
F 1 "Conn_02x10_Odd_Even" H 5250 2826 50  0000 C CNN
F 2 "" H 5200 2300 50  0001 C CNN
F 3 "~" H 5200 2300 50  0001 C CNN
	1    5200 2300
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_MCU #PWR?
U 1 1 5FAE6C5A
P 6000 1450
F 0 "#PWR?" H 6000 1300 50  0001 C CNN
F 1 "VCC_MCU" H 6017 1623 50  0000 C CNN
F 2 "" H 6000 1450 50  0001 C CNN
F 3 "" H 6000 1450 50  0001 C CNN
	1    6000 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 1900 6000 1900
Wire Wire Line
	6000 1900 6000 1450
$Comp
L power:GND #PWR?
U 1 1 5FAE727B
P 6000 2900
F 0 "#PWR?" H 6000 2650 50  0001 C CNN
F 1 "GND" H 6005 2727 50  0000 C CNN
F 2 "" H 6000 2900 50  0001 C CNN
F 3 "" H 6000 2900 50  0001 C CNN
	1    6000 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2000 6000 2000
Wire Wire Line
	6000 2000 6000 2100
Wire Wire Line
	5500 2100 6000 2100
Connection ~ 6000 2100
Wire Wire Line
	6000 2100 6000 2200
Wire Wire Line
	5500 2200 6000 2200
Connection ~ 6000 2200
Wire Wire Line
	6000 2200 6000 2300
Wire Wire Line
	5500 2300 6000 2300
Connection ~ 6000 2300
Wire Wire Line
	6000 2300 6000 2400
Wire Wire Line
	5500 2400 6000 2400
Connection ~ 6000 2400
Wire Wire Line
	6000 2400 6000 2500
Wire Wire Line
	5500 2500 6000 2500
Connection ~ 6000 2500
Wire Wire Line
	6000 2500 6000 2600
Wire Wire Line
	5500 2600 6000 2600
Connection ~ 6000 2600
Wire Wire Line
	6000 2600 6000 2700
Wire Wire Line
	5500 2700 6000 2700
Connection ~ 6000 2700
Wire Wire Line
	6000 2700 6000 2800
Wire Wire Line
	5500 2800 6000 2800
Connection ~ 6000 2800
Wire Wire Line
	6000 2800 6000 2900
Wire Wire Line
	5000 2000 3950 2000
Wire Wire Line
	5000 2100 3550 2100
Wire Wire Line
	5000 2200 3250 2200
Wire Wire Line
	5000 2300 3550 2300
Wire Wire Line
	5000 2500 3250 2500
Wire Wire Line
	5000 2600 3250 2600
NoConn ~ 5000 2700
NoConn ~ 5000 2800
Text Label 4150 2600 0    50   ~ 0
nRESET
Text Label 4150 2500 0    50   ~ 0
TDO
Text Label 4150 2300 0    50   ~ 0
TCLK
Text Label 4150 2200 0    50   ~ 0
TMS
Text Label 4150 2100 0    50   ~ 0
TDI
Text Label 4150 2000 0    50   ~ 0
TRST
$Comp
L FlightComputer_Library:VCC_MCU #PWR?
U 1 1 5FAEA3A4
P 4500 1450
F 0 "#PWR?" H 4500 1300 50  0001 C CNN
F 1 "VCC_MCU" H 4517 1623 50  0000 C CNN
F 2 "" H 4500 1450 50  0001 C CNN
F 3 "" H 4500 1450 50  0001 C CNN
	1    4500 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 1450 4500 1900
Wire Wire Line
	4500 1900 5000 1900
Text HLabel 3250 2000 0    50   Input ~ 0
DEBUG_JTRST
Text HLabel 3250 2100 0    50   Input ~ 0
DEBUG_JTDI
Text HLabel 3250 2300 0    50   Input ~ 0
DEBUG_JTCK-SWCLK
Text HLabel 3250 2600 0    50   Input ~ 0
nRST
Text HLabel 3250 2500 0    50   Input ~ 0
DEBUG_JTDO-TRACESWO
Text HLabel 3250 2200 0    50   Input ~ 0
DEBUG_JMS-SWDIO
NoConn ~ 5000 2400
$Comp
L Device:R_US R?
U 1 1 5FAF8AFB
P 3550 2950
AR Path="/5F2A50C6/5FAF8AFB" Ref="R?"  Part="1" 
AR Path="/5F7BC0DD/5FAF8AFB" Ref="R?"  Part="1" 
F 0 "R?" H 3618 2996 50  0000 L CNN
F 1 "100K" H 3618 2905 50  0000 L CNN
F 2 "" V 3590 2940 50  0001 C CNN
F 3 "~" H 3550 2950 50  0001 C CNN
	1    3550 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2800 3550 2300
Connection ~ 3550 2300
Wire Wire Line
	3550 2300 3250 2300
$Comp
L Device:R_US R?
U 1 1 5FAF930C
P 3550 1700
AR Path="/5F2A50C6/5FAF930C" Ref="R?"  Part="1" 
AR Path="/5F7BC0DD/5FAF930C" Ref="R?"  Part="1" 
F 0 "R?" H 3618 1746 50  0000 L CNN
F 1 "100K" H 3618 1655 50  0000 L CNN
F 2 "" V 3590 1690 50  0001 C CNN
F 3 "~" H 3550 1700 50  0001 C CNN
	1    3550 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FAF95E4
P 3950 1700
AR Path="/5F2A50C6/5FAF95E4" Ref="R?"  Part="1" 
AR Path="/5F7BC0DD/5FAF95E4" Ref="R?"  Part="1" 
F 0 "R?" H 4018 1746 50  0000 L CNN
F 1 "100K" H 4018 1655 50  0000 L CNN
F 2 "" V 3990 1690 50  0001 C CNN
F 3 "~" H 3950 1700 50  0001 C CNN
	1    3950 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1850 3550 2100
Connection ~ 3550 2100
Wire Wire Line
	3550 2100 3250 2100
Wire Wire Line
	3950 1850 3950 2000
Connection ~ 3950 2000
Wire Wire Line
	3950 2000 3250 2000
$Comp
L FlightComputer_Library:VCC_MCU #PWR?
U 1 1 5FAFB12A
P 3950 1450
F 0 "#PWR?" H 3950 1300 50  0001 C CNN
F 1 "VCC_MCU" H 3967 1623 50  0000 C CNN
F 2 "" H 3950 1450 50  0001 C CNN
F 3 "" H 3950 1450 50  0001 C CNN
	1    3950 1450
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_MCU #PWR?
U 1 1 5FAFB33E
P 3550 1450
F 0 "#PWR?" H 3550 1300 50  0001 C CNN
F 1 "VCC_MCU" H 3567 1623 50  0000 C CNN
F 2 "" H 3550 1450 50  0001 C CNN
F 3 "" H 3550 1450 50  0001 C CNN
	1    3550 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1450 3550 1550
Wire Wire Line
	3950 1450 3950 1550
$Comp
L power:GND #PWR?
U 1 1 5FAFC51E
P 3550 3200
F 0 "#PWR?" H 3550 2950 50  0001 C CNN
F 1 "GND" H 3555 3027 50  0000 C CNN
F 2 "" H 3550 3200 50  0001 C CNN
F 3 "" H 3550 3200 50  0001 C CNN
	1    3550 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 3100 3550 3200
$EndSCHEMATC
