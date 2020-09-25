EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 10 11
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
L FlightComputer_Library:GY-86 M?
U 1 1 5F337ED0
P 3250 4350
F 0 "M?" H 3306 5465 50  0000 C CNN
F 1 "GY-86" H 3306 5374 50  0000 C CNN
F 2 "" H 3250 4350 50  0001 C CNN
F 3 "" H 3250 4350 50  0001 C CNN
	1    3250 4350
	-1   0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:GY-91 M?
U 1 1 5F337F74
P 3250 2800
F 0 "M?" H 3306 3915 50  0000 C CNN
F 1 "GY-91" H 3306 3824 50  0000 C CNN
F 2 "" H 3250 2800 50  0001 C CNN
F 3 "" H 3250 2800 50  0001 C CNN
	1    3250 2800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2600 3500 2600 3300
$Comp
L power:GND #PWR0137
U 1 1 5F426B3B
P 2400 3300
F 0 "#PWR0137" H 2400 3050 50  0001 C CNN
F 1 "GND" H 2405 3127 50  0000 C CNN
F 2 "" H 2400 3300 50  0001 C CNN
F 3 "" H 2400 3300 50  0001 C CNN
	1    2400 3300
	-1   0    0    1   
$EndComp
Wire Wire Line
	2400 3300 2400 3700
Wire Wire Line
	2400 3700 2900 3700
$Comp
L power:GND #PWR0138
U 1 1 5F426BC0
P 2400 1750
F 0 "#PWR0138" H 2400 1500 50  0001 C CNN
F 1 "GND" H 2405 1577 50  0000 C CNN
F 2 "" H 2400 1750 50  0001 C CNN
F 3 "" H 2400 1750 50  0001 C CNN
	1    2400 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	2600 3500 2900 3500
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 5F4ADBC1
P 3300 6600
F 0 "J?" H 3380 6592 50  0000 L CNN
F 1 "Conn_GPS" H 3380 6501 50  0000 L CNN
F 2 "" H 3300 6600 50  0001 C CNN
F 3 "~" H 3300 6600 50  0001 C CNN
	1    3300 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 1750 2600 1950
Wire Wire Line
	2600 1950 2900 1950
Wire Wire Line
	2400 2150 2900 2150
Wire Wire Line
	2400 1750 2400 2150
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 5F4D197A
P 3300 5350
F 0 "J?" H 3380 5342 50  0000 L CNN
F 1 "Conn_DEBUG" H 3380 5251 50  0000 L CNN
F 2 "" H 3300 5350 50  0001 C CNN
F 3 "~" H 3300 5350 50  0001 C CNN
	1    3300 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 5150 2800 5250
Wire Wire Line
	2800 5250 3100 5250
$Comp
L power:GND #PWR0255
U 1 1 5F4D748C
P 2800 5650
F 0 "#PWR0255" H 2800 5400 50  0001 C CNN
F 1 "GND" H 2805 5477 50  0000 C CNN
F 2 "" H 2800 5650 50  0001 C CNN
F 3 "" H 2800 5650 50  0001 C CNN
	1    2800 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 5550 2800 5550
Wire Wire Line
	2800 5550 2800 5650
$Comp
L power:GND #PWR0256
U 1 1 5F4DA344
P 2800 6900
F 0 "#PWR0256" H 2800 6650 50  0001 C CNN
F 1 "GND" H 2805 6727 50  0000 C CNN
F 2 "" H 2800 6900 50  0001 C CNN
F 3 "" H 2800 6900 50  0001 C CNN
	1    2800 6900
	1    0    0    -1  
$EndComp
Text Label 2200 2250 0    50   ~ 0
SPI_SCLK
Text Label 2200 2350 0    50   ~ 0
SPI_MOSI
Text Label 2200 2450 0    50   ~ 0
SPI_MISO
Text Label 2200 2550 0    50   ~ 0
SPI_CS1
Text Label 2200 2650 0    50   ~ 0
SPI_CS2
Text Label 2200 3800 0    50   ~ 0
I2C_SCL
Text Label 2200 3900 0    50   ~ 0
I2C_SDA
Wire Wire Line
	2800 6800 2800 6900
Wire Wire Line
	3100 6800 2800 6800
Wire Wire Line
	2800 6500 2800 6400
Wire Wire Line
	3100 6500 2800 6500
Text Label 2200 4000 0    50   ~ 0
IMU_FSYNC
Text Label 2200 4100 0    50   ~ 0
IMU_INT
Text Label 2200 4200 0    50   ~ 0
IMU_DRDY
$Comp
L FlightComputer_Library:VCC_BAT+ #PWR?
U 1 1 5FFA4D7C
P 2600 3300
F 0 "#PWR?" H 2600 3150 50  0001 C CNN
F 1 "VCC_BAT+" H 2617 3473 50  0000 C CNN
F 2 "" H 2600 3300 50  0001 C CNN
F 3 "" H 2600 3300 50  0001 C CNN
	1    2600 3300
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_BAT+ #PWR?
U 1 1 5FFA516C
P 2600 1750
F 0 "#PWR?" H 2600 1600 50  0001 C CNN
F 1 "VCC_BAT+" H 2617 1923 50  0000 C CNN
F 2 "" H 2600 1750 50  0001 C CNN
F 3 "" H 2600 1750 50  0001 C CNN
	1    2600 1750
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_PERIH #PWR?
U 1 1 5FFA5986
P 2800 6400
F 0 "#PWR?" H 2800 6250 50  0001 C CNN
F 1 "VCC_PERIH" H 2817 6573 50  0000 C CNN
F 2 "" H 2800 6400 50  0001 C CNN
F 3 "" H 2800 6400 50  0001 C CNN
	1    2800 6400
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:VCC_PERIH #PWR?
U 1 1 5FFA6026
P 2800 5150
F 0 "#PWR?" H 2800 5000 50  0001 C CNN
F 1 "VCC_PERIH" H 2817 5323 50  0000 C CNN
F 2 "" H 2800 5150 50  0001 C CNN
F 3 "" H 2800 5150 50  0001 C CNN
	1    2800 5150
	1    0    0    -1  
$EndComp
Text Label 2300 6600 0    50   ~ 0
UART_GPS_RX
Text Label 2300 6700 0    50   ~ 0
UART_GPS_TX
Text Label 2200 5350 0    50   ~ 0
UART_EXTERNAL_RX
Text Label 2200 5450 0    50   ~ 0
UART_EXTERNAL_TX
Wire Bus Line
	2550 1050 1950 1050
Wire Bus Line
	1950 1050 1800 1200
Text HLabel 2550 1050 2    50   Input ~ 0
VARIO
Entry Wire Line
	1800 2150 1900 2250
Entry Wire Line
	1800 2250 1900 2350
Entry Wire Line
	1800 2350 1900 2450
Entry Wire Line
	1800 2450 1900 2550
Entry Wire Line
	1800 2550 1900 2650
Entry Wire Line
	1800 3700 1900 3800
Entry Wire Line
	1800 3800 1900 3900
Entry Wire Line
	1800 3900 1900 4000
Entry Wire Line
	1800 4000 1900 4100
Entry Wire Line
	1800 4100 1900 4200
Entry Wire Line
	1800 6500 1900 6600
Entry Wire Line
	1800 6600 1900 6700
Entry Wire Line
	1800 5250 1900 5350
Entry Wire Line
	1800 5350 1900 5450
Wire Wire Line
	1900 2250 2900 2250
Wire Wire Line
	1900 2350 2900 2350
Wire Wire Line
	1900 2450 2900 2450
Wire Wire Line
	1900 2550 2900 2550
Wire Wire Line
	1900 2650 2900 2650
Wire Wire Line
	1900 5350 3100 5350
Wire Wire Line
	1900 5450 3100 5450
Wire Wire Line
	1900 3800 2900 3800
Wire Wire Line
	1900 3900 2900 3900
Wire Wire Line
	1900 4000 2900 4000
Wire Wire Line
	1900 4100 2900 4100
Wire Wire Line
	1900 4200 2900 4200
Wire Wire Line
	1900 6600 3100 6600
Wire Wire Line
	1900 6700 3100 6700
Wire Bus Line
	1800 1200 1800 7250
$EndSCHEMATC
