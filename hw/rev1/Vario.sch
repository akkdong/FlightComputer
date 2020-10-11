EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 12
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
$Comp
L Connector_Generic:Conn_01x04 J10
U 1 1 5F4D197A
P 4200 5700
F 0 "J10" H 4280 5692 50  0000 L CNN
F 1 "Conn_DEBUG" H 4280 5601 50  0000 L CNN
F 2 "Connector_Molex:Molex_SPOX_5268-04A_1x04_P2.50mm_Horizontal" H 4200 5700 50  0001 C CNN
F 3 "~" H 4200 5700 50  0001 C CNN
	1    4200 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0165
U 1 1 5F4D748C
P 3700 6000
F 0 "#PWR0165" H 3700 5750 50  0001 C CNN
F 1 "GND" H 3705 5827 50  0000 C CNN
F 2 "" H 3700 6000 50  0001 C CNN
F 3 "" H 3700 6000 50  0001 C CNN
	1    3700 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5900 3700 5900
Wire Wire Line
	3700 5900 3700 6000
$Comp
L power:GND #PWR0163
U 1 1 5F4DA344
P 5950 3750
F 0 "#PWR0163" H 5950 3500 50  0001 C CNN
F 1 "GND" H 5955 3577 50  0000 C CNN
F 2 "" H 5950 3750 50  0001 C CNN
F 3 "" H 5950 3750 50  0001 C CNN
	1    5950 3750
	1    0    0    -1  
$EndComp
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
$Comp
L FlightComputer_Library:VCC_PERIH #PWR0159
U 1 1 5FFA5986
P 5950 2050
F 0 "#PWR0159" H 5950 1900 50  0001 C CNN
F 1 "VCC_PERIH" H 5967 2223 50  0000 C CNN
F 2 "" H 5950 2050 50  0001 C CNN
F 3 "" H 5950 2050 50  0001 C CNN
	1    5950 2050
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_PERIH #PWR0164
U 1 1 5FFA6026
P 3700 5500
F 0 "#PWR0164" H 3700 5350 50  0001 C CNN
F 1 "VCC_PERIH" H 3717 5673 50  0000 C CNN
F 2 "" H 3700 5500 50  0001 C CNN
F 3 "" H 3700 5500 50  0001 C CNN
	1    3700 5500
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
L FlightComputer_Library:Teseo-LIV3F U12
U 1 1 60164E3E
P 7700 2900
AR Path="/60164E3E" Ref="U12"  Part="1" 
AR Path="/5F2A508D/60164E3E" Ref="U12"  Part="1" 
F 0 "U12" H 7700 3915 50  0000 C CNN
F 1 "Teseo-LIV3F" H 7700 3824 50  0000 C CNN
F 2 "FlightComputer_Library:Teseo-LIV3F" H 7700 2900 50  0001 C CNN
F 3 "" H 7700 2900 50  0001 C CNN
	1    7700 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2050 5950 2200
Wire Wire Line
	7100 2450 5950 2450
Wire Wire Line
	7100 2350 5950 2350
Connection ~ 5950 2350
Wire Wire Line
	5950 2350 5950 2450
Wire Wire Line
	7100 2200 5950 2200
Connection ~ 5950 2200
Wire Wire Line
	5950 2200 5950 2350
Wire Wire Line
	5950 3750 5950 3650
Wire Wire Line
	5950 3400 7100 3400
Wire Wire Line
	7100 3550 5950 3550
Connection ~ 5950 3550
Wire Wire Line
	5950 3550 5950 3400
Wire Wire Line
	7100 3650 5950 3650
Connection ~ 5950 3650
Wire Wire Line
	5950 3650 5950 3550
$Comp
L Device:R_US R?
U 1 1 60177C4B
P 2800 2200
AR Path="/5F2A50C6/60177C4B" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/60177C4B" Ref="R?"  Part="1" 
AR Path="/5F2A508D/60177C4B" Ref="R141"  Part="1" 
F 0 "R141" V 2750 1900 50  0000 L CNN
F 1 "33R" V 2750 2300 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 2840 2190 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 2840 2290 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 2840 2390 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 2840 2490 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 2840 2590 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 4140 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 4240 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 4340 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 4440 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 3290 4540 50  0001 C CNN
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
Wire Wire Line
	3850 5700 4000 5700
Wire Wire Line
	3850 5800 4000 5800
Wire Wire Line
	2800 5700 3550 5700
Wire Wire Line
	3550 5800 2800 5800
$Comp
L Device:R_US R?
U 1 1 6018DFD8
P 3700 5800
AR Path="/5F2A50C6/6018DFD8" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6018DFD8" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6018DFD8" Ref="R156"  Part="1" 
F 0 "R156" V 3650 5500 50  0000 L CNN
F 1 "33R" V 3650 5900 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3740 5790 50  0001 C CNN
F 3 "~" H 3700 5800 50  0001 C CNN
	1    3700 5800
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 6018DFD2
P 3700 5700
AR Path="/5F2A50C6/6018DFD2" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6018DFD2" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6018DFD2" Ref="R155"  Part="1" 
F 0 "R155" V 3650 5400 50  0000 L CNN
F 1 "33R" V 3650 5800 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3740 5690 50  0001 C CNN
F 3 "~" H 3700 5700 50  0001 C CNN
	1    3700 5700
	0    1    1    0   
$EndComp
Text Label 2850 5700 0    50   ~ 0
UART_EXT_RX
Text Label 2850 5800 0    50   ~ 0
UART_EXT_TX
Text HLabel 2800 5700 0    50   Input ~ 0
EXTERNAL_RX
Text HLabel 2800 5800 0    50   Input ~ 0
EXTERNAL_TX
Wire Wire Line
	3700 5600 4000 5600
Wire Wire Line
	3700 5500 3700 5600
$Comp
L Device:R_US R?
U 1 1 6019B350
P 8650 3250
AR Path="/5F2A50C6/6019B350" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6019B350" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6019B350" Ref="R147"  Part="1" 
F 0 "R147" V 8600 2950 50  0000 L CNN
F 1 "33R" V 8600 3350 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8690 3240 50  0001 C CNN
F 3 "~" H 8650 3250 50  0001 C CNN
	1    8650 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 6019B356
P 8650 3150
AR Path="/5F2A50C6/6019B356" Ref="R?"  Part="1" 
AR Path="/5F2A50D8/6019B356" Ref="R?"  Part="1" 
AR Path="/5F2A508D/6019B356" Ref="R146"  Part="1" 
F 0 "R146" V 8600 2850 50  0000 L CNN
F 1 "33R" V 8600 3250 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8690 3140 50  0001 C CNN
F 3 "~" H 8650 3150 50  0001 C CNN
	1    8650 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	8300 3150 8500 3150
Wire Wire Line
	8300 3250 8500 3250
Text HLabel 9350 3250 2    50   Input ~ 0
GPS_RX
Text HLabel 9350 3150 2    50   Input ~ 0
GPS_TX
Text Label 9300 3250 2    50   ~ 0
GPS_RX
Text Label 9300 3150 2    50   ~ 0
GPS_TX
Wire Wire Line
	8800 3250 9350 3250
Wire Wire Line
	9350 3150 8800 3150
$Comp
L Device:L L11
U 1 1 601CE65C
P 8950 2150
F 0 "L11" V 9000 2350 50  0000 C CNN
F 1 "33nH" V 9000 1900 50  0000 C CNN
F 2 "Inductor_SMD:L_0402_1005Metric" H 8950 2150 50  0001 C CNN
F 3 "~" H 8950 2150 50  0001 C CNN
	1    8950 2150
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C72
U 1 1 601D02A1
P 8950 2000
F 0 "C72" V 8900 1850 50  0000 C CNN
F 1 "22pF" V 8900 2200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8950 2000 50  0001 C CNN
F 3 "~" H 8950 2000 50  0001 C CNN
	1    8950 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	9100 2150 9550 2150
Wire Wire Line
	9550 2150 9550 2300
Connection ~ 9550 2300
Wire Wire Line
	8800 2150 8500 2150
Wire Wire Line
	8500 2150 8500 2000
Wire Wire Line
	8500 2000 8850 2000
Connection ~ 8500 2150
Wire Wire Line
	8500 2150 8300 2150
$Comp
L power:GND #PWR0158
U 1 1 601DCE57
P 9450 2000
F 0 "#PWR0158" H 9450 1750 50  0001 C CNN
F 1 "GND" H 9455 1827 50  0000 C CNN
F 2 "" H 9450 2000 50  0001 C CNN
F 3 "" H 9450 2000 50  0001 C CNN
	1    9450 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9050 2000 9450 2000
Wire Wire Line
	9550 2300 8300 2300
Wire Wire Line
	9650 2300 9550 2300
Connection ~ 9550 2500
Wire Wire Line
	9550 2400 9550 2500
Wire Wire Line
	9650 2400 9550 2400
Wire Wire Line
	9550 2500 9550 2600
Wire Wire Line
	9650 2500 9550 2500
$Comp
L power:GND #PWR0160
U 1 1 601D2BAC
P 9550 2600
F 0 "#PWR0160" H 9550 2350 50  0001 C CNN
F 1 "GND" H 9555 2427 50  0000 C CNN
F 2 "" H 9550 2600 50  0001 C CNN
F 3 "" H 9550 2600 50  0001 C CNN
	1    9550 2600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J9
U 1 1 601C9A85
P 9850 2400
F 0 "J9" H 9930 2442 50  0000 L CNN
F 1 "IPEX_IPX" H 9930 2351 50  0000 L CNN
F 2 "FlightComputer_Library:IPEX-IPX" H 9850 2400 50  0001 C CNN
F 3 "~" H 9850 2400 50  0001 C CNN
	1    9850 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C73
U 1 1 601FCF35
P 5950 2900
F 0 "C73" H 6150 2850 50  0000 C CNN
F 1 "0.1uF" H 6150 2950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5950 2900 50  0001 C CNN
F 3 "~" H 5950 2900 50  0001 C CNN
	1    5950 2900
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 3000 5950 3400
Connection ~ 5950 3400
Wire Wire Line
	5950 2800 5950 2450
Connection ~ 5950 2450
NoConn ~ 3800 2000
NoConn ~ 8300 2400
$Comp
L Connector:TestPoint_Alt TP?
U 1 1 6007C088
P 7000 2800
AR Path="/5F5976A1/6007C088" Ref="TP?"  Part="1" 
AR Path="/5F2A508D/6007C088" Ref="TP8"  Part="1" 
F 0 "TP8" V 7000 3000 50  0000 L CNN
F 1 "GPS_nRST" V 7000 3200 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 7200 2800 50  0001 C CNN
F 3 "~" H 7200 2800 50  0001 C CNN
	1    7000 2800
	0    -1   -1   0   
$EndComp
$Comp
L Connector:TestPoint_Alt TP?
U 1 1 6007C55B
P 7000 2950
AR Path="/5F5976A1/6007C55B" Ref="TP?"  Part="1" 
AR Path="/5F2A508D/6007C55B" Ref="TP10"  Part="1" 
F 0 "TP10" V 7000 3150 50  0000 L CNN
F 1 "GPS_WAKEUP" V 7000 3350 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 7200 2950 50  0001 C CNN
F 3 "~" H 7200 2950 50  0001 C CNN
	1    7000 2950
	0    -1   -1   0   
$EndComp
$Comp
L Connector:TestPoint_Alt TP?
U 1 1 6007C6B4
P 7000 3050
AR Path="/5F5976A1/6007C6B4" Ref="TP?"  Part="1" 
AR Path="/5F2A508D/6007C6B4" Ref="TP11"  Part="1" 
F 0 "TP11" V 7000 3250 50  0000 L CNN
F 1 "1PPS" V 7000 3450 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 7200 3050 50  0001 C CNN
F 3 "~" H 7200 3050 50  0001 C CNN
	1    7000 3050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7000 3050 7100 3050
Wire Wire Line
	7100 2950 7000 2950
Wire Wire Line
	7000 2800 7100 2800
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 2440 3490 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0402_1005Metric" V 2590 3490 50  0001 C CNN
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
NoConn ~ 8300 3550
NoConn ~ 8300 3650
$Comp
L Connector:TestPoint_Alt TP7
U 1 1 5F903577
P 8500 2650
F 0 "TP7" H 8558 2768 50  0000 L CNN
F 1 "GPS_SCL" H 8550 2700 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 8700 2650 50  0001 C CNN
F 3 "~" H 8700 2650 50  0001 C CNN
	1    8500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 2750 8500 2750
Wire Wire Line
	8500 2750 8500 2650
Wire Wire Line
	8300 2850 8900 2850
Wire Wire Line
	8900 2850 8900 2650
$Comp
L Connector:TestPoint_Alt TP9
U 1 1 5F905F86
P 8900 2650
F 0 "TP9" H 8958 2768 50  0000 L CNN
F 1 "GPS_SDA" H 8950 2700 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 9100 2650 50  0001 C CNN
F 3 "~" H 9100 2650 50  0001 C CNN
	1    8900 2650
	1    0    0    -1  
$EndComp
$EndSCHEMATC
