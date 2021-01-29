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
 PA_8, // D40, USB_OTG_HS_OVCR
 PD_13, // D41, USB_OTG_HS_PWR_EN
 PB_13, // D42, USB_OTG_HS_VBUS
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
