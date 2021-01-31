#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
 PC_15, // D0, EINK_BUSY
 PC_14, // D1, EINK_CMD

 PJ_8,	// D2, EPD_CKV
 PJ_9,	// D3, EPD_CL
 PD_2,	// D4, EPD_D0
 PD_3,	// D5, EPD_D1
 PD_4,	// D6, EPD_D2
 PD_5,	// D7, EPD_D3
 PD_6,	// D8, EPD_D4
 PD_7,	// D9, EPD_D5
 PD_11,	// D10, EPD_D6
 PD_12,	// D11, EPD_D7
 PJ_10,	// D12, EPD_GMODE
 PJ_11,	// D13, EPD_LE
 PK_0,	// D14, EPD_OE
 PK_1,	// D15, EPD_SPH
 PK_2,	// D16, EPD_SPV

 PB_0,	// D17, IMU_DRDY
 PB_1,	// D18, IMU_FSYNC
 PB_2,	// D19, IMU_nINT

 PC_7,	// D20, KEY_DOWN
 PA_0,	// D21, KEY_ENTER, PWR_WKUP0
 PC_13,	// D22, KEY_ESCAPE, PWR_WKUP2
 PC_8,	// D23, KEY_FUNC1
 PC_9,	// D24, KEY_FUNC2
 PC_4,	// D25, KEY_LEFT
 PA_1,	// D26, KEY_MENU
 PC_5,	// D27, KEY_RIGHT
 PC_6,	// D28, KEY_UP

 PC_1,	// D29, RPI_STATUS

 PG_11,	// D30, PMIC_PWRUP
 PG_9,	// D31, PMIC_VCOM
 PG_10,	// D32, PMIC_WAKEUP

 PB_9,	// D33, PWR_5V_EN
 PG_3,	// D34, PWR_EN_BAT+
 PG_7,	// D35, PWR_EN_PERIPH

 PG_14,	// D36, PWR_LED1
 PG_13,	// D37, PWR_LED2

 PC_12, // D38, USB_OTG_FS_VBUS
 PB_12, // D39, USB_OTG_HS_ID
 PA_8,  // D40, USB_OTG_HS_OVCR
 PD_13, // D41, USB_OTG_HS_PWR_EN
 PB_13, // D42, USB_OTG_HS_VBUS

 PB_7,	// D43, I2C1_SDA
 PB_8,	// D44, I2C1_SCL
 PB_11,	// D45, I2C2_SDA
 PB_10,	// D46, I2C2_SCL

 PA_7,	// D47, SPI1_MOSI
 PA_6,	// D48, SPI1_MISO
 PA_5,	// D49, SPI1_SCLK
 PA_4,	// D50, SPI1_CSEL

 PE_6,	// D51, SPI4_MOSI
 PE_5,	// D52, SPI4_MISO
 PE_2,	// D53, SPI4_SCLK

 PA_10,	// D54, UART1_RX
 PA_9,	// D55, UART1_TX
 PA_3,	// D56, UART2_RX
 PA_2,	// D57, UART2_TX
 PC_11,	// D58, UART3_RX
 PC_10,	// D59, UART3_TX
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif
