#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Digtial pins alias
enum DigitalPins
{
EINK_BUSY, // D0
EINK_CMD, // D1
EPD_CKV, // D2
EPD_CL, // D3
EPD_D0, // D4
EPD_D1, // D5
EPD_D2, // D6
EPD_D3, // D7
EPD_D4, // D8
EPD_D5, // D9
EPD_D6, // D10
EPD_D7, // D11
EPD_GMODE, // D12
EPD_LE, // D13
EPD_OE, // D14
EPD_SPH, // D15
EPD_SPV, // D16

IMU_DRDY, // D17
IMU_FSYNC, // D18
IMU_nINT, // D19
KEY_DOWN, // D20
KEY_ENTER, // D21
KEY_ESCAPE, // D22
KEY_FUNC1, // D23
KEY_FUNC2, // D24
KEY_LEFT, // D25
KEY_MENU, // D26
KEY_RIGHT, // D27
KEY_UP, // D28
RPI_STATUS, // D29
PMIC_PWRUP, // D30
PMIC_VCOM, // D31
PMIC_WAKEUP, // D32
PWR_5V_EN, // D33
PWR_EN_BATp, // D34
PWR_EN_EXTRA = PWR_EN_BATp, // D34
PWR_EN_PMIC = PWR_EN_BATp, // D34
PWR_EN_PERIPH, // D35
PWR_LED1, // D36
PWR_LED2, // D37

USB_OTG_FS_VBUS, // D38
USB_OTG_HS_ID, // D39
USB_OTG_HS_OVCR, // D40
USB_OTG_HS_PWR_EN, // D41
USB_OTG_HS_VBUS, // D42
};


// This must be a literal with the same value as PEND
#define NUM_DIGITAL_PINS        43
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       1
#define NUM_ANALOG_FIRST        44

// On-board LED pin number
#define LED_RED					PWR_LED1
#define LED_BLUE				PWR_LED2

// On-board user button
#define USER_BTN                KEY_ENTER

// Timer Definitions
#define TIMER_TONE              TIM6

// UART Definitions
#define SERIAL_UART_INSTANCE    1 //Connected to ST-Link
#define ENABLE_HWSERIAL1
#define ENABLE_HWSERIAL2
#define ENABLE_HWSERIAL3

// Serial pin used for console
#define PIN_SERIAL_RX           PA_10
#define PIN_SERIAL_TX           PA_9

// SPI pin used for EPD controller
#define PIN_SPI_SS				PA_4
#define PIN_SPI_MOSI			PA_7
#define PIN_SPI_MISO			PA_6
#define PIN_SPI_SCK				PA_5

// I2C pin used for PMIC
#define PIN_WIRE_SDA			PB_7
#define PIN_WIRE_SCL			PB_8


// HSE default value is 25MHz in HAL
// HSE_BYPASS is 8MHz
#ifndef HSE_BYPASS_NOT_USED
#ifndef HSE_VALUE
#define HSE_VALUE 8000000
#endif
#endif

/* Extra HAL modules */
#define HAL_DAC_MODULE_ENABLED
#define HAL_ETH_MODULE_ENABLED

#ifdef __cplusplus
} // extern "C"
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
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_HARDWARE    Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
