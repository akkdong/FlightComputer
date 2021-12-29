/*
 *******************************************************************************
 * Copyright (c) 2020-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#pragma once

/*----------------------------------------------------------------------------
 *        STM32 pins number
 *----------------------------------------------------------------------------*/

#define PA0                     0 // PIN_A0
#define PA1                     1 // PIN_A1
#define PA2                     2 // PIN_A2
#define PA3                     3 // PIN_A3
#define PA4                     4 // PIN_A4
#define PA5                     5 // PIN_A5
#define PA6                     6 // PIN_A6
#define PA7                     7 // PIN_A7
#define PA8                     8
#define PA9                     9
#define PA10                    10
#define PA11                    11
#define PA12                    12
#define PA13                    13
#define PA14                    14
#define PA15                    15
#define PB0                     16 // PIN_A8
#define PB1                     17 // PIN_A9
#define PB2                     18
#define PB3                     19
#define PB4                     20
#define PB5                     21
#define PB6                     22
#define PB7                     23
#define PB8                     24
#define PB9                     25
#define PB10                    26
#define PB11                    27
#define PB12                    28
#define PB13                    29
#define PB14                    30
#define PB15                    31
#define PC0                     32 // PIN_A10
#define PC1                     33 // PIN_A11
#define PC4                     34 // PIN_A12
#define PC5                     35 // PIN_A13
#define PC6                     36
#define PC7                     37
#define PC8                     38
#define PC9                     39
#define PC10                    40
#define PC11                    41
#define PC12                    42
#define PC13                    43
#define PC14                    44
#define PC15                    45
#define PD0                     46
#define PD1                     47
#define PD2                     48
#define PD3                     49
#define PD4                     50
#define PD5                     51
#define PD6                     52
#define PD7                     53
#define PD8                     54
#define PD9                     55
#define PD10                    56
#define PD11                    57
#define PD12                    58
#define PD13                    59
#define PD14                    60
#define PD15                    61
#define PE0                     62
#define PE1                     63
#define PE2                     64
#define PE3                     65
#define PE4                     66
#define PE5                     67
#define PE6                     68
#define PE7                     69
#define PE8                     70
#define PE9                     71
#define PE10                    72
#define PE11                    73
#define PE12                    74
#define PE13                    75
#define PE14                    76
#define PE15                    77
#define PF0                     78
#define PF1                     79
#define PF2                     80
#define PF3                     81 // PIN_A14
#define PF4                     82 // PIN_A15
#define PF5                     83 // PIN_A16
#define PF6                     84 // PIN_A17
#define PF7                     85 // PIN_A18
#define PF8                     86 // PIN_A19
#define PF9                     87 // PIN_A20
#define PF10                    88 // PIN_A21
#define PF11                    89 // PIN_A22
#define PF12                    90 // PIN_A23
#define PF13                    91 // PIN_A24
#define PF14                    92 // PIN_A25
#define PF15                    93
#define PG0                     94
#define PG1                     95
#define PG2                     96
#define PG3                     97
#define PG4                     98
#define PG5                     99
#define PG6                     100
#define PG7                     101
#define PG8                     102
#define PG9                     103
#define PG10                    104
#define PG11                    105
#define PG12                    106
#define PG13                    107
#define PG14                    108
#define PG15                    109
#define PH0                     110
#define PH1                     111
#define PJ8                     112
#define PJ9                     113
#define PJ10                    114
#define PJ11                    115
#define PK0                     116
#define PK1                     117
#define PK2                     118
#define PC2_C                   119 // PIN_A26
#define PC3_C                   120 // PIN_A27


#define NUM_DIGITAL_PINS        121
#define NUM_DUALPAD_PINS        2
#define NUM_ANALOG_INPUTS       28


// Timer Definitions
#ifndef TIMER_TONE
#define TIMER_TONE              TIM6
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
  #define SERIAL_UART_INSTANCE  1
#endif

#define ENABLE_HWSERIAL1
#define ENABLE_HWSERIAL2
#define ENABLE_HWSERIAL3

// Serial pin used for console
#ifndef PIN_SERIAL_RX
#define PIN_SERIAL_RX           PA10
#endif
#ifndef PIN_SERIAL_TX
#define PIN_SERIAL_TX           PA9
#endif

// SPI pin used for EPD controller
#ifndef PIN_SPI_SS
#define PIN_SPI_SS				PA4
#endif
#ifndef PIN_SPI_MOSI
#define PIN_SPI_MOSI			PA7
#endif
#ifndef PIN_SPI_MISO
#define PIN_SPI_MISO			PA6
#endif
#ifndef PIN_SPI_SCK
#define PIN_SPI_SCK				PA5
#endif

// I2C pin used for PMIC
#ifndef PIN_WIRE_SDA
#define PIN_WIRE_SDA			PB7
#endif
#ifndef PIN_WIRE_SCL
#define PIN_WIRE_SCL			PB8
#endif


// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
  #define HAL_DAC_MODULE_ENABLED
#endif
#if !defined(HAL_ETH_MODULE_DISABLED)
  #define HAL_ETH_MODULE_ENABLED
#endif
#if !defined(HAL_QSPI_MODULE_DISABLED)
  #define HAL_QSPI_MODULE_ENABLED
#endif
#if !defined(HAL_SD_MODULE_DISABLED)
  #define HAL_SD_MODULE_ENABLED
#endif


/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
  // These serial port names are intended to allow libraries and architecture-neutral
  // sketches to automatically default to the correct port name for a particular type
  // of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
  // the first hardware serial port whose RX/TX pins are not dedicated to another use.
  //
  // SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
  //
  // SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
  //
  // SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
  //
  // SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
  //
  // SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
  //                            pins are NOT connected to anything by default.
  #ifndef SERIAL_PORT_MONITOR
    #define SERIAL_PORT_MONITOR   Serial
  #endif
  #ifndef SERIAL_PORT_HARDWARE
    #define SERIAL_PORT_HARDWARE  Serial
  #endif
#endif




//
// pin-alias
//
enum PinNumberAlias
{
	EINK_BUSY = PC15, 			// PC_15
	EINK_CMD = PC14, 			// PC_14

	EPD_CKV = PJ8, 				// PJ_8
	EPD_CL = PJ9, 				// PJ_9
	EPD_D0 = PD2, 				// PD_2
	EPD_D1 = PD3, 				// PD_3
	EPD_D2 = PD4, 				// PD_4
	EPD_D3 = PD5, 				// PD_5
	EPD_D4 = PD6, 				// PD_6
	EPD_D5 = PD7, 				// PD_7
	EPD_D6 = PD11, 				// PD_11
	EPD_D7 = PD12, 				// PD_12
	EPD_GMODE = PJ10, 			// PJ_10
	EPD_LE = PJ11, 				// PJ_11
	EPD_OE = PK0, 				// PK_0
	EPD_SPH = PK1, 				// PK_1
	EPD_SPV = PK2, 				// PK_2

	IMU_DRDY = PB0, 			// PB_0
	IMU_FSYNC = PB1, 			// PB_1
	IMU_nINT = PB2, 			// PB_2

	KEY_DOWN = PC7, 			// PC_7
	KEY_ENTER = PA0, 			// PA_0
	KEY_ESCAPE = PC13, 			// PC_13
	KEY_FUNC1 = PC8, 			// PC_8
	KEY_FUNC2 = PC9, 			// PC_9
	KEY_LEFT = PC4, 			// PC_4
	KEY_MENU = PA1, 			// PA_1
	KEY_RIGHT = PC5, 			// PC_5
	KEY_UP = PC6, 				// PC_6

	RPI_STATUS = PC1, 			// PC_1

	PMIC_PWRUP = PG11, 			// PG_11
	PMIC_WAKEUP = PG10, 		// PG_10
	PMIC_VCOM = PG9, 			// PG_9

	PWR_5V_EN = PB9, 			// PB_9
	PWR_EN_BPLUS = PG3, 		// PG_3
	PWR_EN_EXTRA = PWR_EN_BPLUS,
	PWR_EN_PMIC = PWR_EN_BPLUS,
	PWR_EN_PERIPH = PG7, 		// PG_7

	PWR_LED1 = PG14, 			// PG_14
	PWR_LED2 = PG13, 			// PG_13

	USB_OTG_FS_VBUS = PC12, 	// PC_12
	USB_OTG_HS_ID = PB12, 		// PB_12
	USB_OTG_HS_OVCR = PA8, 		// PA_8
	USB_OTG_HS_PWR_EN = PD13, 	// PD_13
	USB_OTG_HS_VBUS = PB13, 	// PB_13

	I2C1_SDA = PB7,				// PB_7
	I2C1_SCL = PB8,				// PB_8
	I2C2_SDA = PB11,			// PB_11
	I2C2_SCL = PB10,			// PB_10

	SPI1_MOSI = PA7,			// PA_7
	SPI1_MISO = PA6,			// PA_6
	SPI1_SCLK = PA5,			// PA_5
	SPI1_CSEL = PA4,			// PA_4

	SPI4_MOSI = PE6,			// PE_6
	SPI4_MISO = PE5,			// PE_5
	SPI4_SCLK = PE2,			// PE_2

	UART1_RX = PA10,			// PA_10
	UART1_TX = PA9,				// PA_9
	UART2_RX = PA3,				// PA_3
	UART2_TX = PA2,				// PA_2
	UART3_RX = PC11,			// PC_11
	UART3_TX = PC10,			// PC_10

	BAT_POWER = PC2_C			// PC_2C
};
