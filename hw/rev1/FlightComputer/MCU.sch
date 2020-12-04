EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 11 12
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
L FlightComputer_Library:STM32H745IIT U?
U 2 1 5F78B5B6
P 3900 2900
AR Path="/5F78B5B6" Ref="U?"  Part="2" 
AR Path="/5F741CFB/5F78B5B6" Ref="U13"  Part="2" 
F 0 "U13" H 3900 5067 50  0000 C CNN
F 1 "STM32H745IIT" H 3900 4976 50  0000 C CNN
F 2 "Package_QFP:LQFP-176_24x24mm_P0.5mm" H 3900 2900 50  0001 C CNN
F 3 "" H 3900 2900 50  0001 C CNN
	2    3900 2900
	1    0    0    -1  
$EndComp
$Comp
L FlightComputer_Library:STM32H745IIT U?
U 3 1 5F78E522
P 8800 2900
AR Path="/5F78E522" Ref="U?"  Part="3" 
AR Path="/5F741CFB/5F78E522" Ref="U13"  Part="3" 
F 0 "U13" H 8800 5067 50  0000 C CNN
F 1 "STM32H745IIT" H 8800 4976 50  0000 C CNN
F 2 "Package_QFP:LQFP-176_24x24mm_P0.5mm" H 8800 2900 50  0001 C CNN
F 3 "" H 8800 2900 50  0001 C CNN
	3    8800 2900
	1    0    0    -1  
$EndComp
$Sheet
S 5500 7250 950  250 
U 5F7A3EBB
F0 "MCU_POWER" 50
F1 "MCU_POWER.sch" 50
$EndSheet
$Comp
L Switch:SW_Push SW10
U 1 1 5FD06459
P 4900 5850
F 0 "SW10" H 4900 6135 50  0000 C CNN
F 1 "SW_Push" H 4900 6044 50  0000 C CNN
F 2 "FlightComputer_Library:SW-TACT-436351045816" H 4900 6050 50  0001 C CNN
F 3 "" H 4900 6050 50  0001 C CNN
	1    4900 5850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW11
U 1 1 5FD0645F
P 6950 5850
F 0 "SW11" H 6950 6135 50  0000 C CNN
F 1 "SW_Push" H 6950 6044 50  0000 C CNN
F 2 "FlightComputer_Library:SW-TACT-436351045816" H 6950 6050 50  0001 C CNN
F 3 "" H 6950 6050 50  0001 C CNN
	1    6950 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FD06465
P 4500 5600
AR Path="/5F2A50C6/5FD06465" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FD06465" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FD06465" Ref="R186"  Part="1" 
F 0 "R186" H 4600 5550 50  0000 L CNN
F 1 "100K" H 4600 5650 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 4540 5590 50  0001 C CNN
F 3 "~" H 4500 5600 50  0001 C CNN
	1    4500 5600
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5FD0646B
P 4500 6050
AR Path="/5F2A50C6/5FD0646B" Ref="C?"  Part="1" 
AR Path="/5F2A508D/5FD0646B" Ref="C?"  Part="1" 
AR Path="/5F741CFB/5FD0646B" Ref="C85"  Part="1" 
F 0 "C85" H 4300 6100 50  0000 L CNN
F 1 "0.1uF" H 4200 6000 50  0000 L CNN
F 2 "FlightComputer_Library:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 4500 6050 50  0001 C CNN
F 3 "~" H 4500 6050 50  0001 C CNN
	1    4500 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5FD06471
P 6600 6100
AR Path="/5F2A50C6/5FD06471" Ref="C?"  Part="1" 
AR Path="/5F2A508D/5FD06471" Ref="C?"  Part="1" 
AR Path="/5F741CFB/5FD06471" Ref="C86"  Part="1" 
F 0 "C86" H 6692 6146 50  0000 L CNN
F 1 "0.1uF" H 6692 6055 50  0000 L CNN
F 2 "FlightComputer_Library:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 6600 6100 50  0001 C CNN
F 3 "~" H 6600 6100 50  0001 C CNN
	1    6600 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 5750 4500 5850
Wire Wire Line
	4700 5850 4500 5850
Connection ~ 4500 5850
Wire Wire Line
	4500 5850 4500 5950
Wire Wire Line
	4000 5850 4500 5850
$Comp
L power:GND #PWR0196
U 1 1 5FD0647C
P 4500 6250
F 0 "#PWR0196" H 4500 6000 50  0001 C CNN
F 1 "GND" H 4505 6077 50  0000 C CNN
F 2 "" H 4500 6250 50  0001 C CNN
F 3 "" H 4500 6250 50  0001 C CNN
	1    4500 6250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0197
U 1 1 5FD06482
P 5300 6250
F 0 "#PWR0197" H 5300 6000 50  0001 C CNN
F 1 "GND" H 5305 6077 50  0000 C CNN
F 2 "" H 5300 6250 50  0001 C CNN
F 3 "" H 5300 6250 50  0001 C CNN
	1    5300 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 6150 4500 6250
Wire Wire Line
	5100 5850 5300 5850
Wire Wire Line
	5300 5850 5300 6250
$Comp
L FlightComputer_Library:VCC_MCU #PWR0194
U 1 1 5FD0648B
P 4500 5350
F 0 "#PWR0194" H 4500 5200 50  0001 C CNN
F 1 "VCC_MCU" H 4517 5523 50  0000 C CNN
F 2 "" H 4500 5350 50  0001 C CNN
F 3 "" H 4500 5350 50  0001 C CNN
	1    4500 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 5350 4500 5450
Text Label 5700 5850 0    50   ~ 0
BOOT0
Wire Wire Line
	5700 5850 6300 5850
Connection ~ 6600 5850
Wire Wire Line
	6600 5850 6750 5850
$Comp
L power:GND #PWR0199
U 1 1 5FD06496
P 6600 6250
F 0 "#PWR0199" H 6600 6000 50  0001 C CNN
F 1 "GND" H 6605 6077 50  0000 C CNN
F 2 "" H 6600 6250 50  0001 C CNN
F 3 "" H 6600 6250 50  0001 C CNN
	1    6600 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 6200 6600 6250
$Comp
L Device:R_US R?
U 1 1 5FD0649D
P 7300 5650
AR Path="/5F2A50C6/5FD0649D" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FD0649D" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FD0649D" Ref="R187"  Part="1" 
F 0 "R187" H 7150 5600 50  0000 L CNN
F 1 "1K" H 7100 5700 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 7340 5640 50  0001 C CNN
F 3 "~" H 7300 5650 50  0001 C CNN
	1    7300 5650
	-1   0    0    1   
$EndComp
Wire Wire Line
	7150 5850 7300 5850
Wire Wire Line
	7300 5850 7300 5800
$Comp
L FlightComputer_Library:VCC_MCU #PWR0195
U 1 1 5FD064A5
P 7300 5450
F 0 "#PWR0195" H 7300 5300 50  0001 C CNN
F 1 "VCC_MCU" H 7317 5623 50  0000 C CNN
F 2 "" H 7300 5450 50  0001 C CNN
F 3 "" H 7300 5450 50  0001 C CNN
	1    7300 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 5450 7300 5500
Wire Wire Line
	6600 5850 6600 6000
Text Label 4000 5850 0    50   ~ 0
~RESET~
$Comp
L Device:R_US R?
U 1 1 5FD064AE
P 6300 6100
AR Path="/5F2A50C6/5FD064AE" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FD064AE" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FD064AE" Ref="R188"  Part="1" 
F 0 "R188" H 6400 6050 50  0000 L CNN
F 1 "100K" H 6400 6150 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 6340 6090 50  0001 C CNN
F 3 "~" H 6300 6100 50  0001 C CNN
	1    6300 6100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0198
U 1 1 5FD064B4
P 6300 6250
F 0 "#PWR0198" H 6300 6000 50  0001 C CNN
F 1 "GND" H 6305 6077 50  0000 C CNN
F 2 "" H 6300 6250 50  0001 C CNN
F 3 "" H 6300 6250 50  0001 C CNN
	1    6300 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 5950 6300 5850
Connection ~ 6300 5850
Wire Wire Line
	6300 5850 6600 5850
$Comp
L Device:R_US R?
U 1 1 5F6E167B
P 2300 4700
AR Path="/5F2A50C6/5F6E167B" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5F6E167B" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5F6E167B" Ref="R184"  Part="1" 
F 0 "R184" V 2350 4850 50  0000 L CNN
F 1 "10K" V 2350 4400 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2340 4690 50  0001 C CNN
F 3 "~" H 2300 4700 50  0001 C CNN
	1    2300 4700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5F6E2C8F
P 2300 4800
AR Path="/5F2A50C6/5F6E2C8F" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5F6E2C8F" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5F6E2C8F" Ref="R185"  Part="1" 
F 0 "R185" V 2350 4950 50  0000 L CNN
F 1 "N/C" V 2350 4500 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2340 4790 50  0001 C CNN
F 3 "~" H 2300 4800 50  0001 C CNN
	1    2300 4800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 4700 2700 4700
Wire Wire Line
	2450 4800 2700 4800
Wire Wire Line
	2700 4800 2700 4700
Connection ~ 2700 4700
Wire Wire Line
	2700 4700 3100 4700
$Comp
L FlightComputer_Library:VCC_MCU #PWR0192
U 1 1 5F6E41F3
P 1950 4700
F 0 "#PWR0192" H 1950 4550 50  0001 C CNN
F 1 "VCC_MCU" V 1950 5050 50  0000 C CNN
F 2 "" H 1950 4700 50  0001 C CNN
F 3 "" H 1950 4700 50  0001 C CNN
	1    1950 4700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1950 4700 2150 4700
$Comp
L power:GND #PWR0193
U 1 1 5F6E4E63
P 1950 4800
F 0 "#PWR0193" H 1950 4550 50  0001 C CNN
F 1 "GND" V 1950 4550 50  0000 C CNN
F 2 "" H 1950 4800 50  0001 C CNN
F 3 "" H 1950 4800 50  0001 C CNN
	1    1950 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 4800 2150 4800
Wire Wire Line
	3100 4200 2150 4200
Text Label 2200 4200 0    50   ~ 0
~RESET~
Wire Wire Line
	3100 2600 2150 2600
Wire Wire Line
	3100 2500 2150 2500
Wire Wire Line
	3100 2400 2150 2400
Wire Wire Line
	4700 1400 5600 1400
Wire Wire Line
	4700 1500 5600 1500
Text Label 2200 2400 0    50   ~ 0
DEBUG_JMS_SWDIO
Text Label 2200 2500 0    50   ~ 0
DEBUG_JTCK_SWCLK
Text Label 2200 2600 0    50   ~ 0
DEBUG_JTDI
Text Label 5550 1400 2    50   ~ 0
DEBUG_JTDO-SWO
Text Label 5550 1500 2    50   ~ 0
DEBUG_nJTRST
Wire Wire Line
	8000 3200 7350 3200
Wire Wire Line
	8000 3300 7350 3300
Wire Wire Line
	9600 3200 10300 3200
Wire Wire Line
	9600 3300 10300 3300
Wire Wire Line
	9600 3400 10300 3400
Wire Wire Line
	8000 3500 7350 3500
Wire Wire Line
	8000 3600 7350 3600
Wire Wire Line
	8000 3700 7350 3700
Wire Wire Line
	8000 4400 7350 4400
Wire Wire Line
	8000 4500 7350 4500
Wire Wire Line
	8000 4600 7350 4600
Wire Wire Line
	8000 4700 7350 4700
Wire Wire Line
	9600 3600 10350 3600
Text Label 7350 3200 0    50   ~ 0
FMC_A0
Text Label 7350 3300 0    50   ~ 0
FMC_A1
Wire Wire Line
	8000 3400 7350 3400
Text Label 7350 3400 0    50   ~ 0
FMC_A2
Text Label 7350 3500 0    50   ~ 0
FMC_A3
Text Label 7350 3600 0    50   ~ 0
FMC_A4
Text Label 7350 3700 0    50   ~ 0
FMC_A5
Text Label 7350 4400 0    50   ~ 0
FMC_A6
Text Label 7350 4500 0    50   ~ 0
FMC_A7
Text Label 7350 4600 0    50   ~ 0
FMC_A8
Text Label 7350 4700 0    50   ~ 0
FMC_A9
Text Label 10300 3200 2    50   ~ 0
FMC_A10
Text Label 10300 3300 2    50   ~ 0
FMC_A11
Wire Wire Line
	9600 3700 10350 3700
Text Label 10300 3600 2    50   ~ 0
FMC_BA0
Text Label 10300 3700 2    50   ~ 0
FMC_BA1
Wire Wire Line
	8000 2500 7350 2500
Wire Wire Line
	8000 2600 7350 2600
Text Label 7350 2500 0    50   ~ 0
FMC_D0
Text Label 7350 2600 0    50   ~ 0
FMC_D1
Wire Wire Line
	9600 2400 10300 2400
Wire Wire Line
	9600 2500 10300 2500
Wire Wire Line
	9600 2600 10300 2600
Text Label 10300 2400 2    50   ~ 0
FMC_D10
Text Label 10300 2500 2    50   ~ 0
FMC_D11
Text Label 10300 2600 2    50   ~ 0
FMC_D12
Wire Wire Line
	8000 1100 7350 1100
Wire Wire Line
	8000 1200 7350 1200
Text Label 7350 1100 0    50   ~ 0
FMC_D2
Text Label 7350 1200 0    50   ~ 0
FMC_D3
Wire Wire Line
	9600 1800 10300 1800
Wire Wire Line
	9600 1900 10300 1900
Wire Wire Line
	9600 2000 10300 2000
Wire Wire Line
	9600 2100 10300 2100
Wire Wire Line
	9600 2200 10300 2200
Wire Wire Line
	9600 2300 10300 2300
Text Label 10300 1800 2    50   ~ 0
FMC_D4
Text Label 10300 1900 2    50   ~ 0
FMC_D5
Text Label 10300 2000 2    50   ~ 0
FMC_D6
Text Label 10300 2100 2    50   ~ 0
FMC_D7
Text Label 10300 2200 2    50   ~ 0
FMC_D8
Text Label 10300 2300 2    50   ~ 0
FMC_D9
Wire Wire Line
	9600 1100 10350 1100
Wire Wire Line
	9600 1200 10350 1200
Text Label 10300 1100 2    50   ~ 0
FMC_nBL0
Text Label 10300 1200 2    50   ~ 0
FMC_nBL1
Wire Wire Line
	8000 2000 7350 2000
Wire Wire Line
	8000 1900 7350 1900
Wire Wire Line
	8000 2100 7350 2100
Text Label 7350 1900 0    50   ~ 0
FMC_D13
Text Label 7350 2000 0    50   ~ 0
FMC_D14
Text Label 7350 2100 0    50   ~ 0
FMC_D15
Wire Wire Line
	4700 1600 5600 1600
Text Label 5550 1600 2    50   ~ 0
FMC_SDCKE1
Wire Wire Line
	9600 4000 10350 4000
Wire Wire Line
	9600 4700 10350 4700
Wire Wire Line
	4700 1700 5600 1700
Wire Wire Line
	8000 4300 7300 4300
Wire Wire Line
	4700 3200 5600 3200
Text Label 5550 3200 2    50   ~ 0
FMC_SDNWE
Text Label 5550 1700 2    50   ~ 0
FMC_SDNE1
Text Label 10300 4000 2    50   ~ 0
FMC_SDCLK
Text Label 10300 4700 2    50   ~ 0
FMC_SDNCAS
Text Label 5550 1800 2    50   ~ 0
I2C1_SDA
Text Label 5550 1900 2    50   ~ 0
I2C1_SCL
Wire Wire Line
	8000 4000 7350 4000
Wire Wire Line
	8000 3800 7350 3800
Wire Wire Line
	8000 3900 7350 3900
Wire Wire Line
	8000 4100 7350 4100
Text Label 7350 4000 0    50   ~ 0
QUADSPI_BK1_IO0
Text Label 7350 4100 0    50   ~ 0
QUADSPI_BK1_IO1
Text Label 7350 3900 0    50   ~ 0
QUADSPI_BK1_IO2
Text Label 7350 3800 0    50   ~ 0
QUADSPI_BK1_IO3
Wire Wire Line
	8000 4200 7300 4200
Text Label 7350 4200 0    50   ~ 0
QUADSPI_CLK
Text Label 7350 4300 0    50   ~ 0
FMC_SDNRAS
Wire Wire Line
	3100 1700 2150 1700
Wire Wire Line
	3100 1800 2150 1800
Text Label 2200 1700 0    50   ~ 0
SPI1_MISO
Text Label 2200 1800 0    50   ~ 0
SPI1_MOSI
Wire Wire Line
	3100 1500 2150 1500
Wire Wire Line
	3100 1600 2150 1600
Text Label 2200 1500 0    50   ~ 0
SPI1_NSS
Text Label 2200 1600 0    50   ~ 0
SPI1_SCK
Wire Wire Line
	4700 3400 5500 3400
Wire Wire Line
	4700 2400 5600 2400
Text Label 5550 2400 2    50   ~ 0
USB_OTG_HS_VBUS
Wire Wire Line
	3100 1300 2150 1300
Wire Wire Line
	3100 1400 2150 1400
Wire Wire Line
	4700 4200 5600 4200
Text Label 5550 4200 2    50   ~ 0
USART3_TX
Text Label 5550 2200 2    50   ~ 0
I2C2_SDA
Text Label 2200 1300 0    50   ~ 0
USART2_TX
Text Label 2200 1400 0    50   ~ 0
USART2_RX
Wire Wire Line
	3100 2200 2150 2200
Wire Wire Line
	3100 2300 2150 2300
Text Label 2200 2200 0    50   ~ 0
USB_OTG_FS_DM
Text Label 2200 2300 0    50   ~ 0
USB_OTG_FS_DP
Wire Wire Line
	4700 2500 5600 2500
Wire Wire Line
	4700 2600 5600 2600
Text Label 5550 2500 2    50   ~ 0
USB_OTG_HS_DM
Text Label 5550 2600 2    50   ~ 0
USB_OTG_HS_DP
Wire Wire Line
	8000 1300 7350 1300
Wire Wire Line
	8000 1400 7350 1400
Wire Wire Line
	8000 1500 7350 1500
Wire Wire Line
	8000 1600 7350 1600
Wire Wire Line
	8000 1700 7350 1700
Wire Wire Line
	9600 4100 10350 4100
Wire Wire Line
	9600 4200 10350 4200
Wire Wire Line
	9600 4300 10350 4300
Wire Wire Line
	9600 4500 10350 4500
Wire Wire Line
	9600 4600 10350 4600
Wire Wire Line
	9600 1300 10350 1300
Wire Wire Line
	9600 1400 10350 1400
Wire Wire Line
	9600 1500 10350 1500
Wire Wire Line
	9600 1600 10350 1600
Wire Wire Line
	9600 1700 10350 1700
Wire Wire Line
	8000 2200 7350 2200
Wire Wire Line
	8000 2300 7350 2300
Wire Wire Line
	8000 2400 7300 2400
Text Label 7350 2200 0    50   ~ 0
EPD_D6
Text Label 7350 2300 0    50   ~ 0
EPD_D7
Text Label 7350 2400 0    50   ~ 0
USB_HS_PWR_EN
Wire Wire Line
	3100 3300 2150 3300
Wire Wire Line
	3100 3400 2150 3400
Wire Wire Line
	3100 3500 2150 3500
Wire Wire Line
	3100 3600 2150 3600
Wire Wire Line
	4700 4500 5600 4500
Wire Wire Line
	4700 1100 5600 1100
Text Label 5550 3600 2    50   ~ 0
KEY_LEFT
Text Label 5550 3700 2    50   ~ 0
KEY_RIGHT
Text Label 5550 2100 2    50   ~ 0
I2C2_SCL
Wire Wire Line
	9600 3800 10350 3800
Text Label 10300 3800 2    50   ~ 0
QUADSPI_BK1_nCS
Wire Wire Line
	4700 3800 5600 3800
Wire Wire Line
	4700 3900 5600 3900
Text Label 5550 3800 2    50   ~ 0
KEY_UP
Text Label 5550 3900 2    50   ~ 0
KEY_DOWN
Wire Wire Line
	4700 4300 5600 4300
Text Label 5550 4300 2    50   ~ 0
USART3_RX
Text Label 7350 1400 0    50   ~ 0
EPD_D1
Wire Wire Line
	3100 4500 2200 4500
Text Label 2200 4500 0    50   ~ 0
BOOT0
Text Label 2200 2100 0    50   ~ 0
USART1_RX
Text Label 2200 2000 0    50   ~ 0
USART1_TX
Wire Wire Line
	3100 1900 2150 1900
Text Label 2200 1900 0    50   ~ 0
USB_OTG_HS_OVCR
Text Label 5550 1100 2    50   ~ 0
IMU_DRDY
Wire Wire Line
	4700 2000 5600 2000
Wire Wire Line
	4700 2300 5600 2300
Text Label 5550 2300 2    50   ~ 0
USB_OTG_HS_ID
Text Label 5550 2000 2    50   ~ 0
PWR_5V_EN
Wire Wire Line
	4700 4000 5600 4000
Wire Wire Line
	4700 4400 5600 4400
Text Label 5550 4400 2    50   ~ 0
USB_OTG_FS_VBUS
Text Label 5550 4500 2    50   ~ 0
KEY_ESCAPE
Wire Wire Line
	4700 4100 5600 4100
Text Label 5550 4000 2    50   ~ 0
KEY_FUNC1
Text Label 5550 4100 2    50   ~ 0
KEY_FUNC2
Text Label 7350 1300 0    50   ~ 0
EPD_D0
Text Label 7350 1500 0    50   ~ 0
EPD_D2
Text Label 7350 1600 0    50   ~ 0
EPD_D3
Text Label 7350 1700 0    50   ~ 0
EPD_D4
Text Label 10300 1300 2    50   ~ 0
SPI4_SCLK
Text Label 10300 1400 2    50   ~ 0
SPI4_nCS1
Text Label 10300 1500 2    50   ~ 0
SPI4_nCS2
Text Label 10300 1600 2    50   ~ 0
SPI4_MISO
Text Label 10300 1700 2    50   ~ 0
SPI4_MOSI
Text Label 10300 4200 2    50   ~ 0
PMIC_WAKEUP
Text Label 10300 4300 2    50   ~ 0
PMIC_PWRUP
Text Label 10300 4500 2    50   ~ 0
PWR_LED2
Text Label 10300 4600 2    50   ~ 0
PWR_LED1
Text Label 10300 3400 2    50   ~ 0
FMC_A12
Wire Wire Line
	9600 3900 10350 3900
Text Label 10300 3900 2    50   ~ 0
PWR_PERIPH_EN
Text Label 10300 4100 2    50   ~ 0
PMIC_VCOM
Text Label 2200 3300 0    50   ~ 0
EPD_CKV
Text Label 2200 3400 0    50   ~ 0
EPD_CL
Text Label 2200 3500 0    50   ~ 0
EPD_GMODE
Text Label 2200 3600 0    50   ~ 0
EPD_LE
Wire Wire Line
	2150 2000 3100 2000
Wire Wire Line
	2150 2100 3100 2100
Text HLabel 2150 1300 0    50   Input ~ 0
USART2_TX
Text HLabel 2150 1400 0    50   Input ~ 0
USART2_RX
Text HLabel 2150 1500 0    50   Input ~ 0
SPI1_nCS
Text HLabel 2150 1600 0    50   Input ~ 0
SPI1_SCLK
Text HLabel 2150 1700 0    50   Input ~ 0
SPI1_MISO
Text HLabel 2150 1800 0    50   Input ~ 0
SPI1_MOSI
Text HLabel 2150 1900 0    50   Input ~ 0
USB_HS_OVCR
Text HLabel 2150 2200 0    50   Input ~ 0
USB_FS_DN
Text HLabel 2150 2300 0    50   Input ~ 0
USB_FS_DP
Text HLabel 2150 2400 0    50   Input ~ 0
DEBUG_JMS-SWDIO
Text HLabel 2150 2600 0    50   Input ~ 0
DEBUG_JTDI
Entry Wire Line
	2050 6800 2150 6900
Entry Wire Line
	1950 6800 2050 6900
Entry Wire Line
	1850 6800 1950 6900
Entry Wire Line
	1750 6800 1850 6900
Entry Wire Line
	2150 6800 2250 6900
Entry Wire Line
	2250 6800 2350 6900
Entry Wire Line
	2350 6800 2450 6900
Entry Wire Line
	2450 6800 2550 6900
Text HLabel 1600 6900 0    50   Input ~ 0
EPD_D[0..7]
Text HLabel 2150 4200 0    50   Input ~ 0
nRST
Text HLabel 5600 1100 2    50   Input ~ 0
IMU_DRDY
Text HLabel 5600 1400 2    50   Input ~ 0
DEBUG_JTDO-SWO
Text HLabel 5600 1500 2    50   Input ~ 0
DEBUG_nJTRST
Text HLabel 5600 1600 2    50   Input ~ 0
FMC_CKE1
Text HLabel 5600 1700 2    50   Input ~ 0
FMC_nE1
Text HLabel 5600 2000 2    50   Input ~ 0
PWR_5V_EN
Text HLabel 5600 2300 2    50   Input ~ 0
USB_HS_ID
Text HLabel 5600 2400 2    50   Input ~ 0
USB_HS_VBUS
Text HLabel 5600 2500 2    50   Input ~ 0
USB_HS_DN
Text HLabel 5600 2600 2    50   Input ~ 0
USB_HS_DP
Text HLabel 5600 3200 2    50   Input ~ 0
FMC_nWE
Text HLabel 5600 3600 2    50   Input ~ 0
KEY_LEFT
Text HLabel 5600 3700 2    50   Input ~ 0
KEY_RIGHT
Text HLabel 5600 3800 2    50   Input ~ 0
KEY_UP
Text HLabel 5600 3900 2    50   Input ~ 0
KEY_DOWN
Text HLabel 5600 4000 2    50   Input ~ 0
KEY_FUNC1
Text HLabel 5600 4100 2    50   Input ~ 0
KEY_FUNC2
Text HLabel 5600 4200 2    50   Input ~ 0
USART3_TX
Text HLabel 5600 4300 2    50   Input ~ 0
USART3_RX
Text HLabel 5600 4400 2    50   Input ~ 0
USB_FS_VBUS
Text HLabel 5600 4500 2    50   Input ~ 0
KEY_ESCAPE
Text HLabel 7300 2400 0    50   Input ~ 0
USB_HS_PWR_EN
Text HLabel 7300 4200 0    50   Input ~ 0
QUADSPI_CLK
Text HLabel 7300 4300 0    50   Input ~ 0
FMC_nRAS
Text HLabel 1600 7200 0    50   Input ~ 0
QUADSPI_BK1_IO[0..3]
Entry Wire Line
	1900 7250 1800 7350
Entry Wire Line
	1900 7350 1800 7450
Entry Wire Line
	1900 7450 1800 7550
Entry Wire Line
	1900 7550 1800 7650
Wire Wire Line
	1900 7250 2650 7250
Wire Wire Line
	1900 7350 2650 7350
Wire Wire Line
	1900 7450 2650 7450
Wire Wire Line
	1900 7550 2650 7550
Text Label 2650 7250 2    50   ~ 0
QUADSPI_BK1_IO1
Text Label 2650 7350 2    50   ~ 0
QUADSPI_BK1_IO2
Text Label 2650 7450 2    50   ~ 0
QUADSPI_BK1_IO3
Text Label 2650 7550 2    50   ~ 0
QUADSPI_BK1_IO4
Text HLabel 10350 4700 2    50   Input ~ 0
FMC_nCAS
Text HLabel 10350 4300 2    50   Input ~ 0
PMIC_PWRUP
Text HLabel 10350 4200 2    50   Input ~ 0
PMIC_WAKEUP
Text HLabel 10350 4100 2    50   Input ~ 0
PMIC_VCOM
Text HLabel 10350 4000 2    50   Input ~ 0
FMC_CLK
Text HLabel 10350 3900 2    50   Input ~ 0
PWR_PERIPH_EN
Text HLabel 10350 3800 2    50   Input ~ 0
QUADSPI_BK1_nCS
Text HLabel 10350 3700 2    50   Input ~ 0
FMC_BA1
Text HLabel 10350 3600 2    50   Input ~ 0
FMC_BA0
Text HLabel 10350 1700 2    50   Input ~ 0
SPI4_MOSI
Text HLabel 10350 1600 2    50   Input ~ 0
SPI4_MISO
Text HLabel 10350 1500 2    50   Input ~ 0
SPI4_nCS2
Text HLabel 10350 1400 2    50   Input ~ 0
SPI4_nCS1
Text HLabel 10350 1300 2    50   Input ~ 0
SPI4_SCLK
Text HLabel 10350 1200 2    50   Input ~ 0
FMC_nBL1
Text HLabel 10350 1100 2    50   Input ~ 0
FMC_nBL0
Wire Bus Line
	1800 7250 1750 7200
Wire Bus Line
	1750 7200 1600 7200
$Comp
L Device:R_US R?
U 1 1 5FD241CA
P 3800 7350
AR Path="/5F2A50C6/5FD241CA" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FD241CA" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FD241CA" Ref="R189"  Part="1" 
F 0 "R189" V 3750 7550 50  0000 L CNN
F 1 "10K" V 3750 7050 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 3840 7340 50  0001 C CNN
F 3 "~" H 3800 7350 50  0001 C CNN
	1    3800 7350
	0    -1   1    0   
$EndComp
$Comp
L FlightComputer_Library:VCC_MCU #PWR0200
U 1 1 5FD31656
P 3300 7200
F 0 "#PWR0200" H 3300 7050 50  0001 C CNN
F 1 "VCC_MCU" H 3317 7373 50  0000 C CNN
F 2 "" H 3300 7200 50  0001 C CNN
F 3 "" H 3300 7200 50  0001 C CNN
	1    3300 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3600 5600 3600
Wire Wire Line
	4700 3700 5600 3700
Wire Wire Line
	4700 1900 5600 1900
Wire Wire Line
	4700 1800 5600 1800
Text HLabel 5600 1900 2    50   Input ~ 0
I2C1_SCL
Text HLabel 5600 1800 2    50   Input ~ 0
I2C1_SDA
Wire Wire Line
	4700 2200 5600 2200
Wire Wire Line
	4700 2100 5600 2100
Text HLabel 5600 2200 2    50   Input ~ 0
I2C2_SDA
Text HLabel 5600 2100 2    50   Input ~ 0
I2C2_SCL
Text Label 2950 5850 3    50   ~ 0
FMC_A12
Text Label 2850 5850 3    50   ~ 0
FMC_A11
Text Label 2750 5850 3    50   ~ 0
FMC_A10
Text Label 2650 5850 3    50   ~ 0
FMC_A9
Text Label 2550 5850 3    50   ~ 0
FMC_A8
Text Label 2450 5850 3    50   ~ 0
FMC_A7
Text Label 2350 5850 3    50   ~ 0
FMC_A6
Text Label 2250 5850 3    50   ~ 0
FMC_A5
Text Label 2150 5850 3    50   ~ 0
FMC_A4
Text Label 2050 5850 3    50   ~ 0
FMC_A3
Text Label 1950 5850 3    50   ~ 0
FMC_A2
Text Label 1850 5850 3    50   ~ 0
FMC_A1
Text Label 1750 5850 3    50   ~ 0
FMC_A0
Wire Wire Line
	2950 6200 2950 5850
Wire Wire Line
	2850 6200 2850 5850
Wire Wire Line
	2750 6200 2750 5850
Wire Wire Line
	2650 6200 2650 5850
Wire Wire Line
	2550 6200 2550 5850
Wire Wire Line
	2450 6200 2450 5850
Wire Wire Line
	2350 6200 2350 5850
Wire Wire Line
	2250 6200 2250 5850
Wire Wire Line
	2150 6200 2150 5850
Wire Wire Line
	2050 6200 2050 5850
Wire Wire Line
	1950 6200 1950 5850
Wire Wire Line
	1850 6200 1850 5850
Wire Wire Line
	1750 6200 1750 5850
Entry Wire Line
	2950 6200 3050 6300
Entry Wire Line
	2850 6200 2950 6300
Entry Wire Line
	2750 6200 2850 6300
Entry Wire Line
	2650 6200 2750 6300
Entry Wire Line
	2550 6200 2650 6300
Entry Wire Line
	2450 6200 2550 6300
Entry Wire Line
	2350 6200 2450 6300
Entry Wire Line
	2250 6200 2350 6300
Entry Wire Line
	2150 6200 2250 6300
Entry Wire Line
	2050 6200 2150 6300
Entry Wire Line
	1950 6200 2050 6300
Entry Wire Line
	1850 6200 1950 6300
Entry Wire Line
	1750 6200 1850 6300
Text HLabel 1600 6300 0    50   Input ~ 0
FMC_A[0..12]
Text Label 2450 6450 3    50   ~ 0
EPD_D7
Text Label 2350 6450 3    50   ~ 0
EPD_D6
Text Label 2250 6450 3    50   ~ 0
EPD_D5
Text Label 2150 6450 3    50   ~ 0
EPD_D4
Text Label 2050 6450 3    50   ~ 0
EPD_D3
Text Label 1950 6450 3    50   ~ 0
EPD_D2
Text Label 1850 6450 3    50   ~ 0
EPD_D1
Text Label 1750 6450 3    50   ~ 0
EDP_D0
Wire Wire Line
	2450 6800 2450 6450
Wire Wire Line
	2350 6800 2350 6450
Wire Wire Line
	2250 6800 2250 6450
Wire Wire Line
	2150 6800 2150 6450
Wire Wire Line
	2050 6800 2050 6450
Wire Wire Line
	1950 6800 1950 6450
Wire Wire Line
	1850 6800 1850 6450
Wire Wire Line
	1750 6800 1750 6450
Text Label 3250 5250 3    50   ~ 0
FMC_D15
Text Label 3150 5250 3    50   ~ 0
FMC_D14
Text Label 3050 5250 3    50   ~ 0
FMC_D13
Text Label 2950 5250 3    50   ~ 0
FMC_D12
Text Label 2850 5250 3    50   ~ 0
FMC_D11
Text Label 2750 5250 3    50   ~ 0
FMC_D10
Text Label 2650 5250 3    50   ~ 0
FMC_D9
Text Label 2550 5250 3    50   ~ 0
FMC_D8
Text Label 2450 5250 3    50   ~ 0
FMC_D7
Text Label 2350 5250 3    50   ~ 0
FMC_D6
Text Label 2250 5250 3    50   ~ 0
FMC_D5
Text Label 2150 5250 3    50   ~ 0
FMC_D4
Text Label 2050 5250 3    50   ~ 0
FMC_D3
Text Label 1950 5250 3    50   ~ 0
FMC_D2
Text Label 1850 5250 3    50   ~ 0
FMC_D1
Text Label 1750 5250 3    50   ~ 0
FMC_D0
Wire Wire Line
	3250 5600 3250 5250
Wire Wire Line
	3150 5600 3150 5250
Wire Wire Line
	3050 5600 3050 5250
Wire Wire Line
	2950 5600 2950 5250
Wire Wire Line
	2850 5600 2850 5250
Wire Wire Line
	2750 5600 2750 5250
Wire Wire Line
	2650 5600 2650 5250
Wire Wire Line
	2550 5600 2550 5250
Wire Wire Line
	2450 5600 2450 5250
Wire Wire Line
	2350 5600 2350 5250
Wire Wire Line
	2250 5600 2250 5250
Wire Wire Line
	2150 5600 2150 5250
Wire Wire Line
	2050 5600 2050 5250
Wire Wire Line
	1950 5600 1950 5250
Wire Wire Line
	1850 5600 1850 5250
Wire Wire Line
	1750 5600 1750 5250
Entry Wire Line
	3250 5600 3350 5700
Entry Wire Line
	3150 5600 3250 5700
Entry Wire Line
	3050 5600 3150 5700
Entry Wire Line
	2950 5600 3050 5700
Entry Wire Line
	2850 5600 2950 5700
Entry Wire Line
	2750 5600 2850 5700
Entry Wire Line
	2650 5600 2750 5700
Entry Wire Line
	2550 5600 2650 5700
Entry Wire Line
	2450 5600 2550 5700
Entry Wire Line
	2350 5600 2450 5700
Entry Wire Line
	2250 5600 2350 5700
Entry Wire Line
	2150 5600 2250 5700
Entry Wire Line
	2050 5600 2150 5700
Entry Wire Line
	1950 5600 2050 5700
Entry Wire Line
	1850 5600 1950 5700
Entry Wire Line
	1750 5600 1850 5700
Text HLabel 1600 5700 0    50   Input ~ 0
FMC_D[0..15]
$Comp
L Device:R_US R?
U 1 1 5FF918D9
P 3800 7450
AR Path="/5F2A50C6/5FF918D9" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FF918D9" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FF918D9" Ref="R190"  Part="1" 
F 0 "R190" V 3750 7650 50  0000 L CNN
F 1 "10K" V 3750 7150 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 3840 7440 50  0001 C CNN
F 3 "~" H 3800 7450 50  0001 C CNN
	1    3800 7450
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FF91C07
P 3800 7550
AR Path="/5F2A50C6/5FF91C07" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FF91C07" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FF91C07" Ref="R191"  Part="1" 
F 0 "R191" V 3750 7750 50  0000 L CNN
F 1 "10K" V 3750 7250 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 3840 7540 50  0001 C CNN
F 3 "~" H 3800 7550 50  0001 C CNN
	1    3800 7550
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FF91D51
P 3800 7650
AR Path="/5F2A50C6/5FF91D51" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FF91D51" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FF91D51" Ref="R192"  Part="1" 
F 0 "R192" V 3750 7850 50  0000 L CNN
F 1 "10K" V 3750 7350 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 3840 7640 50  0001 C CNN
F 3 "~" H 3800 7650 50  0001 C CNN
	1    3800 7650
	0    -1   1    0   
$EndComp
Wire Wire Line
	3950 7350 4800 7350
Wire Wire Line
	3950 7450 4800 7450
Wire Wire Line
	3950 7550 4800 7550
Wire Wire Line
	3950 7650 4800 7650
Text Label 4800 7350 2    50   ~ 0
I2C1_SCL
Text Label 4800 7450 2    50   ~ 0
I2C1_SDA
Text Label 4800 7550 2    50   ~ 0
I2C2_SCL
Text Label 4800 7650 2    50   ~ 0
I2C2_SDA
Wire Wire Line
	3300 7650 3650 7650
Wire Wire Line
	3300 7200 3300 7350
Wire Wire Line
	3650 7550 3300 7550
Connection ~ 3300 7550
Wire Wire Line
	3300 7550 3300 7650
Wire Wire Line
	3650 7450 3300 7450
Connection ~ 3300 7450
Wire Wire Line
	3300 7450 3300 7550
Wire Wire Line
	3650 7350 3300 7350
Connection ~ 3300 7350
Wire Wire Line
	3300 7350 3300 7450
Wire Wire Line
	4700 1200 5600 1200
Wire Wire Line
	4700 1300 5600 1300
Text Label 5550 1200 2    50   ~ 0
IMU_FSYNC
Text Label 5550 1300 2    50   ~ 0
IMU_nINT
Wire Wire Line
	3100 3750 2150 3750
Wire Wire Line
	3100 3850 2150 3850
Text Label 2200 3750 0    50   ~ 0
EPD_OE
Text Label 2200 3850 0    50   ~ 0
EPD_SPH
Wire Wire Line
	3100 3950 2150 3950
Text Label 2200 3950 0    50   ~ 0
EPD_SPV
Text HLabel 2150 3950 0    50   Input ~ 0
EPD_SPV
Wire Wire Line
	3100 1100 2150 1100
Wire Wire Line
	3100 1200 2150 1200
Text Label 2200 1100 0    50   ~ 0
KEY_ENTER
Text HLabel 2150 1100 0    50   Input ~ 0
KEY_ENTER
Text HLabel 5600 1200 2    50   Input ~ 0
IMU_FSYNC
Text HLabel 5600 1300 2    50   Input ~ 0
IMU_nINT
Wire Wire Line
	4700 3500 5600 3500
$Comp
L Connector:TestPoint_Alt TP?
U 1 1 5F8B8AB0
P 5500 3400
AR Path="/5F5976A1/5F8B8AB0" Ref="TP?"  Part="1" 
AR Path="/5F741CFB/5F8B8AB0" Ref="TP13"  Part="1" 
F 0 "TP13" V 5500 3600 50  0000 L CNN
F 1 "PC2" V 5450 3200 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 5700 3400 50  0001 C CNN
F 3 "~" H 5700 3400 50  0001 C CNN
	1    5500 3400
	0    1    1    0   
$EndComp
Text HLabel 5600 3500 2    50   Input ~ 0
BAT_SENSING
Text Label 5550 3500 2    50   ~ 0
PWR_BAT_SENSING
Wire Wire Line
	8000 1800 7350 1800
Text Label 7350 1800 0    50   ~ 0
EPD_D5
Wire Wire Line
	9600 3500 10350 3500
Text Label 10300 3500 2    50   ~ 0
PWR_BAT+_EN
Text HLabel 10350 3500 2    50   Input ~ 0
PWR_BAT+_EN
Text HLabel 2150 3850 0    50   Input ~ 0
EPD_SPH
Text HLabel 2150 3750 0    50   Input ~ 0
EPD_OE
Text HLabel 2150 3600 0    50   Input ~ 0
EPD_LE
Text HLabel 2150 3500 0    50   Input ~ 0
EPD_GMODE
Text HLabel 2150 3400 0    50   Input ~ 0
EPD_CL
Text HLabel 2150 3300 0    50   Input ~ 0
EPD_CKV
Text HLabel 2150 2000 0    50   Input ~ 0
USART1_TX
Text HLabel 2150 2100 0    50   Input ~ 0
USART1_RX
$Comp
L Device:Crystal_GND24_Small Y1
U 1 1 5F80DD1B
P 950 3200
F 0 "Y1" H 1000 2850 50  0000 R CNN
F 1 "25MHz" H 1050 2950 50  0000 R CNN
F 2 "Crystal:Crystal_SMD_5032-4Pin_5.0x3.2mm" H 950 3200 50  0001 C CNN
F 3 "~" H 950 3200 50  0001 C CNN
	1    950  3200
	-1   0    0    1   
$EndComp
Text HLabel 2150 2500 0    50   Input ~ 0
DEBUG_JTCK-SWCLK
$Comp
L Device:C_Small C?
U 1 1 5F8517AC
P 650 3450
AR Path="/5F2A50C6/5F8517AC" Ref="C?"  Part="1" 
AR Path="/5F2A508D/5F8517AC" Ref="C?"  Part="1" 
AR Path="/5F741CFB/5F8517AC" Ref="C83"  Part="1" 
F 0 "C83" H 750 3500 50  0000 L CNN
F 1 "18pF" H 750 3400 50  0000 L CNN
F 2 "FlightComputer_Library:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 650 3450 50  0001 C CNN
F 3 "~" H 650 3450 50  0001 C CNN
	1    650  3450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F851ABA
P 1200 3450
AR Path="/5F2A50C6/5F851ABA" Ref="C?"  Part="1" 
AR Path="/5F2A508D/5F851ABA" Ref="C?"  Part="1" 
AR Path="/5F741CFB/5F851ABA" Ref="C84"  Part="1" 
F 0 "C84" H 1300 3500 50  0000 L CNN
F 1 "18pF" H 1300 3400 50  0000 L CNN
F 2 "FlightComputer_Library:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 1200 3450 50  0001 C CNN
F 3 "~" H 1200 3450 50  0001 C CNN
	1    1200 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  3000 650  3200
Wire Wire Line
	1050 3200 1200 3200
Wire Wire Line
	1200 3350 1200 3200
Connection ~ 1200 3200
Wire Wire Line
	1200 3200 1200 3100
$Comp
L power:GND #PWR0190
U 1 1 5F8A6EF9
P 650 3650
F 0 "#PWR0190" H 650 3400 50  0001 C CNN
F 1 "GND" H 655 3477 50  0000 C CNN
F 2 "" H 650 3650 50  0001 C CNN
F 3 "" H 650 3650 50  0001 C CNN
	1    650  3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0191
U 1 1 5F8A717D
P 1200 3650
F 0 "#PWR0191" H 1200 3400 50  0001 C CNN
F 1 "GND" H 1205 3477 50  0000 C CNN
F 2 "" H 1200 3650 50  0001 C CNN
F 3 "" H 1200 3650 50  0001 C CNN
	1    1200 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 3550 1200 3650
Wire Wire Line
	650  3550 650  3650
Wire Wire Line
	850  3200 650  3200
Connection ~ 650  3200
Wire Wire Line
	650  3200 650  3350
Text Label 5500 3300 2    50   ~ 0
LOW_BATTERY
Text HLabel 5600 3300 2    50   Input ~ 0
LOW_BATTERY
Wire Wire Line
	4700 3300 5600 3300
NoConn ~ 950  3100
NoConn ~ 950  3300
Text Label 2200 1200 0    50   ~ 0
KEY_MENU
Text HLabel 2150 1200 0    50   Input ~ 0
KEY_MENU
$Comp
L Device:R_US R?
U 1 1 5FA3ACF5
P 2000 3000
AR Path="/5F2A50C6/5FA3ACF5" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FA3ACF5" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FA3ACF5" Ref="R174"  Part="1" 
F 0 "R174" V 2050 3150 50  0000 L CNN
F 1 "0R" V 2050 2700 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2040 2990 50  0001 C CNN
F 3 "~" H 2000 3000 50  0001 C CNN
	1    2000 3000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 5FA3B77C
P 2000 3100
AR Path="/5F2A50C6/5FA3B77C" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FA3B77C" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FA3B77C" Ref="R175"  Part="1" 
F 0 "R175" V 2050 3250 50  0000 L CNN
F 1 "0R" V 2050 2800 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 2040 3090 50  0001 C CNN
F 3 "~" H 2000 3100 50  0001 C CNN
	1    2000 3100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2150 3100 3100 3100
Wire Wire Line
	3100 3000 2150 3000
Wire Wire Line
	650  3000 1850 3000
Wire Wire Line
	1200 3100 1850 3100
Text HLabel 5600 4600 2    50   Input ~ 0
EINK_CMD
Text HLabel 5600 4700 2    50   Input ~ 0
EINK_BUSY
$Comp
L Device:R_US R?
U 1 1 5FCE8457
P 8550 6150
AR Path="/5F2A50C6/5FCE8457" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5F371147/5FCE8457" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FCE8457" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FCE8457" Ref="R30"  Part="1" 
F 0 "R30" V 8650 6150 50  0000 L CNN
F 1 "1K" V 8650 5950 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 8590 6140 50  0001 C CNN
F 3 "~" H 8550 6150 50  0001 C CNN
	1    8550 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7950 6150 8400 6150
$Comp
L Device:LED D?
U 1 1 5FCE8466
P 8950 5850
AR Path="/5F2A50C6/5FCE8466" Ref="D?"  Part="1" 
AR Path="/5F741CFB/5FCE8466" Ref="D12"  Part="1" 
F 0 "D12" V 8988 5733 50  0000 R CNN
F 1 "LED_R" V 8897 5733 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8950 5850 50  0001 C CNN
F 3 "~" H 8950 5850 50  0001 C CNN
	1    8950 5850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8950 6000 8950 6150
Wire Wire Line
	8950 6150 8700 6150
$Comp
L FlightComputer_Library:VCC_MCU #PWR?
U 1 1 5FCE846F
P 8950 5600
AR Path="/5F2A50C6/5FCE846F" Ref="#PWR?"  Part="1" 
AR Path="/5F741CFB/5FCE846F" Ref="#PWR0129"  Part="1" 
F 0 "#PWR0129" H 8950 5450 50  0001 C CNN
F 1 "VCC_MCU" H 8967 5773 50  0000 C CNN
F 2 "" H 8950 5600 50  0001 C CNN
F 3 "" H 8950 5600 50  0001 C CNN
	1    8950 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 5600 8950 5700
$Comp
L Device:R_US R?
U 1 1 5FD1DDD7
P 10350 6150
AR Path="/5F2A50C6/5FD1DDD7" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5F371147/5FD1DDD7" Ref="R?"  Part="1" 
AR Path="/5F2A508D/5FD1DDD7" Ref="R?"  Part="1" 
AR Path="/5F741CFB/5FD1DDD7" Ref="R31"  Part="1" 
F 0 "R31" V 10450 6150 50  0000 L CNN
F 1 "1K" V 10450 5950 50  0000 L CNN
F 2 "FlightComputer_Library:R_0402_1005Metric_Pad0.72x0.64mm_HandSolder" V 10390 6140 50  0001 C CNN
F 3 "~" H 10350 6150 50  0001 C CNN
	1    10350 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9700 6150 10200 6150
$Comp
L Device:LED D?
U 1 1 5FD1DDDF
P 10750 5850
AR Path="/5F2A50C6/5FD1DDDF" Ref="D?"  Part="1" 
AR Path="/5F741CFB/5FD1DDDF" Ref="D13"  Part="1" 
F 0 "D13" V 10788 5733 50  0000 R CNN
F 1 "LED_G" V 10697 5733 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 10750 5850 50  0001 C CNN
F 3 "~" H 10750 5850 50  0001 C CNN
	1    10750 5850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10750 6000 10750 6150
Wire Wire Line
	10750 6150 10500 6150
$Comp
L FlightComputer_Library:VCC_MCU #PWR?
U 1 1 5FD1DDE7
P 10750 5600
AR Path="/5F2A50C6/5FD1DDE7" Ref="#PWR?"  Part="1" 
AR Path="/5F741CFB/5FD1DDE7" Ref="#PWR0130"  Part="1" 
F 0 "#PWR0130" H 10750 5450 50  0001 C CNN
F 1 "VCC_MCU" H 10767 5773 50  0000 C CNN
F 2 "" H 10750 5600 50  0001 C CNN
F 3 "" H 10750 5600 50  0001 C CNN
	1    10750 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10750 5600 10750 5700
Text Label 7950 6150 0    50   ~ 0
PWR_LED1
Text Label 9700 6150 0    50   ~ 0
PWR_LED2
$Comp
L Connector:TestPoint_Alt TP?
U 1 1 5FCA08F9
P 10250 4400
AR Path="/5F5976A1/5FCA08F9" Ref="TP?"  Part="1" 
AR Path="/5F741CFB/5FCA08F9" Ref="TP25"  Part="1" 
F 0 "TP25" V 10250 4600 50  0000 L CNN
F 1 "PG12" V 10200 4200 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 10450 4400 50  0001 C CNN
F 3 "~" H 10450 4400 50  0001 C CNN
	1    10250 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	10250 4400 9600 4400
Wire Wire Line
	4700 4600 5600 4600
Wire Wire Line
	4700 4700 5600 4700
Wire Bus Line
	1800 7250 1800 7700
Wire Bus Line
	1600 6900 2600 6900
Wire Bus Line
	1600 6300 3200 6300
Wire Bus Line
	1600 5700 3500 5700
$EndSCHEMATC
