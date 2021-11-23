// flight_computer.cpp
//

#include "Arduino.h"
#include "main.h"
#include "adc.h"
#include "fatfs.h"
#include "i2c.h"
#include "quadspi.h"
#include "spi.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"
#include "fmc.h"
#include "sdram_drv.h"
#include "qspi_drv.h"
#include "hw_config.h"
#include "Wire/Wire.h"
#include "SPI/SPIClassEx.h"
#include "KeyPad/KeyPad.h"
#include "EPD/EPaperController.h"
#include "EPD/EPaperDisplay.h"
#include "lv_port.h"

#include "../../../../Test/FC_Test/CM7/Core/Inc/image_mono.h"
#include "../../../../Test/FC_Test/CM7/Core/Inc/landscape.h"
#include "Adafruit_GFX/Fonts/FreeSans24pt7b.h"

int image_type = 0;


#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

HardwareSerial& Debug = Serial1;
HardwareSerial& GPS = Serial2;
HardwareSerial& RPI = Serial3;


class FlightComputer
{
public:
	FlightComputer();

	void setup();
	void loop();

protected:
// 	FileSystem 	fs;
// 	EPapper		paper;
//  MonitorManager	mm;

	SPIClassEx			spi1;
	KeyPad				keyPad;
	EPaperController	epdCont;
	EPaperDisplay		epdDisp;

	uint8_t				data[64];

public:
	static bool			flash_ok;
	static bool			sdram_ok;
};


bool FlightComputer::flash_ok = false;
bool FlightComputer::sdram_ok = false;


FlightComputer::FlightComputer()
{
	// mm.registerClient(&debug);
}

void FlightComputer::setup(void)
{
	//
	pinMode(PWR_LED1, OUTPUT);
	pinMode(PWR_LED2, OUTPUT);
	digitalWrite(PWR_LED1, LOW);
	digitalWrite(PWR_LED2, HIGH);

	Debug.begin(115200);
	GPS.begin(9600);
	Serial3.begin(115200);
	delay(100);
	Debug.println("Start Flight computer");

	// device check
	if (!flash_ok)
		Debug.println("[DEBUG] Flash initialization failed.");
	if (!sdram_ok)
		Debug.println("[DEBUG] SDRAM initialization failed.");

	//
	lv_init();
	hal_init();
	app_init();

	//
	//epdCont.begin();
	epdDisp.begin();
	keyPad.begin();
}

void FlightComputer::loop()
{
	while(1)
	{
		// [TEST] echo Debug console
		if (Debug.available())
			Debug.write(Debug.read());
		// [TEST] forward GPS to Debug console
		//if (GPS.available())
		//	Debug.write(GPS.read());
		// [TEST] echo RPI & forward to Debug console
		if (RPI.available())
		{
			int ch = RPI.read();
			Debug.write(ch);
			RPI.write(ch);
		}

		// console
		// CommandConsole console;
		//
		// console.SetInterface(Debug);
		// console.SetClient(SerialShell);

		// lvgl timer handler
		{
			static uint32_t tick = millis();
			if ((millis() - tick) > 5)
			{
				lv_timer_handler();
				tick = millis();
			}
		}

		// debug purpose
		{
			static uint32_t tick = millis();
			if ((millis() - tick) > 1000)
			{
				digitalToggle(PWR_LED1);
				digitalToggle(PWR_LED2);

				tick = millis();
			}
		}

		//
		//epdCont.run();


		//
		int event = Key.getEvent();
		if (event != EVENT_NOKEY)
		{
#ifdef DEBUG
			Debug.printf("Key event: %X\r\n", event);
#endif

			if ((event & EVENT_MASK_STATE) == EVENT_KEYUP)
			{
				if ((event & EVENT_MASK_KEY) == KeyPad::ENTER)
				{
					if (image_type == 0)
					{
						epdDisp.drawBitmapBM(alien_bytes,  0,  0,  EPD_WIDTH, EPD_HEIGHT, COLOR_WHITE, bm_invert);
					}
					else if (image_type == 1)
					{
						epdDisp.drawBitmapBM(landscape_bytes,  0,  0,  EPD_WIDTH, EPD_HEIGHT, COLOR_WHITE, bm_invert);
					}
					else if (image_type == 2)
					{
						uint8_t* ptr = epdDisp.getCanvas();

						// draw check-pattern
						for (int y = 0; y < 600; y++)
							{
								for (int x = 0; x < 100 /*800/8*/; x++)
								{
									int iy = y / 60; // 0 ~ 9
									int ix = x / 10; // 0 ~ 9

									*ptr++ = ((iy % 2) == (ix % 2)) ? 0xFF : 0x00;
								}
						}
					}

					image_type = (image_type + 1) % 3;

					uint32_t lastTick = millis();
					epdDisp.refresh();
					Serial1.printf("clear done!: %u ms\r\n", millis() - lastTick);
				}
				else if ((event & EVENT_MASK_KEY) == KeyPad::ESCAPE)
				{
					uint32_t lastTick = millis();
					epdDisp.clearScreen();
					epdDisp.refresh();
					Serial1.printf("clear mono image!: %u ms\r\n", millis() - lastTick);
				}
				else if ((event & EVENT_MASK_KEY) == KeyPad::FUNC1)
				{
					epdDisp.setFont(&FreeSans24pt7b);
					epdDisp.setCursor(100, 100);
					epdDisp.setTextColor(COLOR_BLACK);
					epdDisp.print("Hello everyone!");
					epdDisp.refresh();
				}
			}
		}
	}

	/*
	SPIClass spi(SPI4_MOSI, SPI4_MISO, SPI4_SCLK);

	spi.begin();
	spi.transfer(data);
	spi.transfer(ptr, size);
	spi.end();

	SPIClassEx spiEx;

	spiEx.begin(init_function);
	spiEx.transfer(sendPtr, sendLen, recvPtr, recvLen);

	spiEx.receive(dataPtr, dataLen, timeout, callback);


	Timer aaa;
	aaa.Expire(1000, class::callback);
	spiEx.end();
	*/
}


FlightComputer	fc;





extern "C" void init(void);
extern "C" void setup(void);
extern "C" void loop(void);


void init(void)
{
	// Wait until CPU2 boots and enters in stop mode or timeout
	int32_t timeout = 0xFFFF;
	while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
	if ( timeout < 0 )
	{
		Error_Handler();
	}

	//
	/* Init DWT if present */
	#ifdef DWT_BASE
	dwt_init();
	#endif

	/* Initialize the HAL */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();


	#if defined (USBCON) && defined(USBD_USE_CDC)
	USBD_CDC_init();
	#endif

	// enable all gpio clock
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOJ_CLK_ENABLE();
	__HAL_RCC_GPIOK_CLK_ENABLE();

	// initialize each peripherals
	MX_FMC_Init();
	MX_QUADSPI_Init();
	MX_USB_DEVICE_Init();
	MX_FATFS_Init();

	// set default power state
	digitalWrite(PWR_EN_EXTRA, LOW);
	digitalWrite(PWR_EN_PERIPH, LOW);
	// set power-pin as output
	pinMode(PWR_EN_EXTRA, OUTPUT);
	pinMode(PWR_EN_PERIPH, OUTPUT);
	// turn-on peripheral power
	digitalWrite(PWR_EN_EXTRA, HIGH);
	digitalWrite(PWR_EN_PERIPH, HIGH);
	delay(100);

	//Serial1.begin(115200);

	// initialize Flash
	if (!QSPI_Driver_locked())
	{
		if(!QSPI_Driver_state())
		{
			if(QSPI_Driver_init() == QSPI_STATUS_OK)
			{
				//Serial1.println("QSPI Driver initialized");
				FlightComputer::flash_ok = true;
			}
			else
			{
				//Serial1.println("QSPI Driver initialize failed!!");
			}
		}
		else
		{
			//Serial1.println("QSPI Driver have been ready");
		}
	}
	else
	{
		//Serial1.println("QSPI Driver locked");
	}

	// initialize SDRAM
	if (SDRAM_Do_InitializeSequence() == HAL_OK)
	{
		//Serial1.println("SDRAM initialized");
		FlightComputer::sdram_ok = true;
	}
	else
	{
		//Serial1.println("SDRAM initialize failed!!");
	}
	delay(100);

	// When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of HSEM notification HW semaphore Clock enable
	/*
	__HAL_RCC_HSEM_CLK_ENABLE();
	// Take HSEM
	HAL_HSEM_FastTake(HSEM_ID_0);
	// Release HSEM in order to notify the CPU2(CM4)
	HAL_HSEM_Release(HSEM_ID_0,0);
	// Wait until CPU2 wakes up from stop mode
	timeout = 0xFFFF;
	while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
	if ( timeout < 0 )
	{
		Error_Handler();
	}
	*/
}


void setup()
{
	fc.setup();
}

void loop()
{
	fc.loop();
}


extern "C" void Error_Handler()
{
	_Error_Handler(__FILE__, __LINE__);
}

