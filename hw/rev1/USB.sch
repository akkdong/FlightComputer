EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 11
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
L Connector:USB_A J?
U 1 1 5F70D663
P 7300 4550
F 0 "J?" H 7357 5017 50  0000 C CNN
F 1 "USB_A" H 7357 4926 50  0000 C CNN
F 2 "" H 7450 4500 50  0001 C CNN
F 3 " ~" H 7450 4500 50  0001 C CNN
	1    7300 4550
	-1   0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J?
U 1 1 5F70E376
P 7250 1650
F 0 "J?" H 7307 2117 50  0000 C CNN
F 1 "USB_B_Micro" H 7307 2026 50  0000 C CNN
F 2 "" H 7400 1600 50  0001 C CNN
F 3 "~" H 7400 1600 50  0001 C CNN
	1    7250 1650
	-1   0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_USB #PWR0244
U 1 1 5F71CCE7
P 5600 1350
F 0 "#PWR0244" H 5600 1200 50  0001 C CNN
F 1 "VCC_USB" H 5617 1523 50  0000 C CNN
F 2 "" H 5600 1350 50  0001 C CNN
F 3 "" H 5600 1350 50  0001 C CNN
	1    5600 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F71EB4C
P 5600 1650
AR Path="/5F2A50C6/5F71EB4C" Ref="C?"  Part="1" 
AR Path="/5F742A7D/5F71EB4C" Ref="C?"  Part="1" 
F 0 "C?" H 5700 1700 50  0000 L CNN
F 1 "4.7uF" H 5700 1600 50  0000 L CNN
F 2 "" H 5600 1650 50  0001 C CNN
F 3 "~" H 5600 1650 50  0001 C CNN
	1    5600 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0245
U 1 1 5F7263CC
P 5600 1900
F 0 "#PWR0245" H 5600 1650 50  0001 C CNN
F 1 "GND" H 5605 1727 50  0000 C CNN
F 2 "" H 5600 1900 50  0001 C CNN
F 3 "" H 5600 1900 50  0001 C CNN
	1    5600 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1350 5600 1450
Connection ~ 5600 1450
Wire Wire Line
	5600 1450 6950 1450
Wire Wire Line
	5600 1450 5600 1550
Wire Wire Line
	5600 1900 5600 1750
Wire Wire Line
	3300 2800 2050 2800
Wire Wire Line
	3300 2900 2050 2900
Wire Wire Line
	3300 3000 2050 3000
Text HLabel 2050 2800 0    50   Input ~ 0
USB_FS_DP
Text HLabel 2050 2900 0    50   Input ~ 0
USB_FS_DN
Text HLabel 2050 3000 0    50   Input ~ 0
USB_FS_ID
Text HLabel 2050 2700 0    50   Input ~ 0
USB_FS_VBUS
$Comp
L Device:R_US R?
U 1 1 5F72C5E8
P 3450 2700
AR Path="/5F2A50C6/5F72C5E8" Ref="R?"  Part="1" 
AR Path="/5F742A7D/5F72C5E8" Ref="R?"  Part="1" 
F 0 "R?" V 3500 2900 50  0000 L CNN
F 1 "33R" V 3500 2400 50  0000 L CNN
F 2 "" V 3490 2690 50  0001 C CNN
F 3 "~" H 3450 2700 50  0001 C CNN
	1    3450 2700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F729C4B
P 3450 3000
AR Path="/5F2A50C6/5F729C4B" Ref="R?"  Part="1" 
AR Path="/5F742A7D/5F729C4B" Ref="R?"  Part="1" 
F 0 "R?" V 3500 3200 50  0000 L CNN
F 1 "33R" V 3500 2700 50  0000 L CNN
F 2 "" V 3490 2990 50  0001 C CNN
F 3 "~" H 3450 3000 50  0001 C CNN
	1    3450 3000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F729A83
P 3450 2900
AR Path="/5F2A50C6/5F729A83" Ref="R?"  Part="1" 
AR Path="/5F742A7D/5F729A83" Ref="R?"  Part="1" 
F 0 "R?" V 3500 3100 50  0000 L CNN
F 1 "33R" V 3500 2600 50  0000 L CNN
F 2 "" V 3490 2890 50  0001 C CNN
F 3 "~" H 3450 2900 50  0001 C CNN
	1    3450 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F728EBC
P 3450 2800
AR Path="/5F2A50C6/5F728EBC" Ref="R?"  Part="1" 
AR Path="/5F742A7D/5F728EBC" Ref="R?"  Part="1" 
F 0 "R?" V 3500 3000 50  0000 L CNN
F 1 "33R" V 3500 2500 50  0000 L CNN
F 2 "" V 3490 2790 50  0001 C CNN
F 3 "~" H 3450 2800 50  0001 C CNN
	1    3450 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2050 2700 3300 2700
Wire Wire Line
	3600 2700 4900 2700
Wire Wire Line
	4900 2700 4900 1450
Wire Wire Line
	4900 1450 5600 1450
Wire Wire Line
	3600 2800 6150 2800
Wire Wire Line
	6150 2800 6150 1650
Wire Wire Line
	6150 1650 6950 1650
Wire Wire Line
	3600 2900 6250 2900
Wire Wire Line
	6250 2900 6250 1750
Wire Wire Line
	6250 1750 6950 1750
Wire Wire Line
	3600 3000 6350 3000
Wire Wire Line
	6350 3000 6350 1850
Wire Wire Line
	6350 1850 6950 1850
$Comp
L power:GND #PWR0246
U 1 1 5F736FF8
P 7250 2250
F 0 "#PWR0246" H 7250 2000 50  0001 C CNN
F 1 "GND" H 7255 2077 50  0000 C CNN
F 2 "" H 7250 2250 50  0001 C CNN
F 3 "" H 7250 2250 50  0001 C CNN
	1    7250 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2050 7250 2150
Wire Wire Line
	7250 2150 7350 2150
Wire Wire Line
	7350 2150 7350 2050
Connection ~ 7250 2150
Wire Wire Line
	7250 2150 7250 2250
$Comp
L FlightComputer_Library:STMPS2141STR U?
U 1 1 5F73EA11
P 4050 4450
F 0 "U?" H 4050 4815 50  0000 C CNN
F 1 "STMPS2141STR" H 4050 4724 50  0000 C CNN
F 2 "" H 4050 4450 50  0001 C CNN
F 3 "" H 4050 4450 50  0001 C CNN
	1    4050 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0247
U 1 1 5F73EA1D
P 4050 4900
F 0 "#PWR0247" H 4050 4650 50  0001 C CNN
F 1 "GND" H 4055 4727 50  0000 C CNN
F 2 "" H 4050 4900 50  0001 C CNN
F 3 "" H 4050 4900 50  0001 C CNN
	1    4050 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F73EA23
P 2800 5150
AR Path="/5F2A50C6/5F73EA23" Ref="R?"  Part="1" 
AR Path="/5F742A7D/5F73EA23" Ref="R?"  Part="1" 
F 0 "R?" H 2600 5100 50  0000 L CNN
F 1 "47k" H 2600 5200 50  0000 L CNN
F 2 "" V 2840 5140 50  0001 C CNN
F 3 "~" H 2800 5150 50  0001 C CNN
	1    2800 5150
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F73EA29
P 5650 4550
AR Path="/5F2A50C6/5F73EA29" Ref="C?"  Part="1" 
AR Path="/5F742A7D/5F73EA29" Ref="C?"  Part="1" 
F 0 "C?" H 5750 4600 50  0000 L CNN
F 1 "4.7uF" H 5750 4500 50  0000 L CNN
F 2 "" H 5650 4550 50  0001 C CNN
F 3 "~" H 5650 4550 50  0001 C CNN
	1    5650 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 4350 4950 4350
$Comp
L FlightComputer_Library:VCC_MCU #PWR0248
U 1 1 5F73EA30
P 2800 4900
F 0 "#PWR0248" H 2800 4750 50  0001 C CNN
F 1 "VCC_MCU" H 2817 5073 50  0000 C CNN
F 2 "" H 2800 4900 50  0001 C CNN
F 3 "" H 2800 4900 50  0001 C CNN
	1    2800 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 4550 4700 4550
Wire Wire Line
	4700 4550 4700 5400
Wire Wire Line
	4700 5400 2800 5400
Text HLabel 2100 5400 0    50   Input ~ 0
USB_HS_OVCR
Wire Wire Line
	4050 4750 4050 4900
Wire Wire Line
	2800 4250 2800 4350
Wire Wire Line
	2800 4350 3600 4350
Wire Wire Line
	3600 4550 2100 4550
Text HLabel 2100 4550 0    50   Input ~ 0
USB_HS_PWR_EN
Wire Wire Line
	2800 4900 2800 5000
Wire Wire Line
	2800 5300 2800 5400
Connection ~ 2800 5400
Wire Wire Line
	2800 5400 2100 5400
$Comp
L FlightComputer_Library:VCC_5V #PWR0249
U 1 1 5F73EA43
P 2800 4250
F 0 "#PWR0249" H 2800 4100 50  0001 C CNN
F 1 "VCC_5V" H 2817 4423 50  0000 C CNN
F 2 "" H 2800 4250 50  0001 C CNN
F 3 "" H 2800 4250 50  0001 C CNN
	1    2800 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0250
U 1 1 5F73EA49
P 5650 4800
F 0 "#PWR0250" H 5650 4550 50  0001 C CNN
F 1 "GND" H 5655 4627 50  0000 C CNN
F 2 "" H 5650 4800 50  0001 C CNN
F 3 "" H 5650 4800 50  0001 C CNN
	1    5650 4800
	1    0    0    -1  
$EndComp
Connection ~ 5650 4350
Wire Wire Line
	5650 4350 7000 4350
Wire Wire Line
	5650 4350 5650 4450
Wire Wire Line
	5650 4800 5650 4650
Wire Wire Line
	3350 5700 2100 5700
Wire Wire Line
	3350 5800 2100 5800
Text HLabel 2100 5700 0    50   Input ~ 0
USB_HS_DP
Text HLabel 2100 5800 0    50   Input ~ 0
USB_HS_DN
Text HLabel 2100 5600 0    50   Input ~ 0
USB_HS_VBUS
$Comp
L Device:R_US R?
U 1 1 5F73EA5B
P 3500 5600
AR Path="/5F2A50C6/5F73EA5B" Ref="R?"  Part="1" 
AR Path="/5F742A7D/5F73EA5B" Ref="R?"  Part="1" 
F 0 "R?" V 3550 5800 50  0000 L CNN
F 1 "33R" V 3550 5300 50  0000 L CNN
F 2 "" V 3540 5590 50  0001 C CNN
F 3 "~" H 3500 5600 50  0001 C CNN
	1    3500 5600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F73EA67
P 3500 5800
AR Path="/5F2A50C6/5F73EA67" Ref="R?"  Part="1" 
AR Path="/5F742A7D/5F73EA67" Ref="R?"  Part="1" 
F 0 "R?" V 3550 6000 50  0000 L CNN
F 1 "33R" V 3550 5500 50  0000 L CNN
F 2 "" V 3540 5790 50  0001 C CNN
F 3 "~" H 3500 5800 50  0001 C CNN
	1    3500 5800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F73EA6D
P 3500 5700
AR Path="/5F2A50C6/5F73EA6D" Ref="R?"  Part="1" 
AR Path="/5F742A7D/5F73EA6D" Ref="R?"  Part="1" 
F 0 "R?" V 3550 5900 50  0000 L CNN
F 1 "33R" V 3550 5400 50  0000 L CNN
F 2 "" V 3540 5690 50  0001 C CNN
F 3 "~" H 3500 5700 50  0001 C CNN
	1    3500 5700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2100 5600 3350 5600
Wire Wire Line
	3650 5600 4950 5600
Wire Wire Line
	4950 5600 4950 4350
Connection ~ 4950 4350
Wire Wire Line
	4950 4350 5650 4350
Wire Wire Line
	3650 5700 6200 5700
Wire Wire Line
	6200 5700 6200 4550
Wire Wire Line
	6200 4550 7000 4550
Wire Wire Line
	3650 5800 6300 5800
Wire Wire Line
	6300 5800 6300 4650
Wire Wire Line
	6300 4650 7000 4650
$Comp
L power:GND #PWR0251
U 1 1 5F747F22
P 7300 5150
F 0 "#PWR0251" H 7300 4900 50  0001 C CNN
F 1 "GND" H 7305 4977 50  0000 C CNN
F 2 "" H 7300 5150 50  0001 C CNN
F 3 "" H 7300 5150 50  0001 C CNN
	1    7300 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 4950 7300 5050
Wire Wire Line
	7300 5050 7400 5050
Wire Wire Line
	7400 5050 7400 4950
Connection ~ 7300 5050
Wire Wire Line
	7300 5050 7300 5150
$EndSCHEMATC
