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

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif


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
	EPaperController	epdc;

	uint8_t				data[64];
};

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

	Serial1.begin(115200);
	Serial2.begin(9600);
	Serial3.begin(115200);
	delay(100);
	Serial1.println("Hello world!\r\n");

	epdc.begin();



	//
	if (!QSPI_Driver_locked())
	{
		if(!QSPI_Driver_state())
		{
			if(QSPI_Driver_init() == QSPI_STATUS_OK)
			{
				Serial1.println("QSPI Driver initialized\r\n");
			}
			else
			{
				Serial1.println("QSPI Driver initialize failed!!\r\n");
			}
		}
		else
		{
			Serial1.println("QSPI Driver have been ready\r\n");
		}
	}
	else
	{
		Serial1.println("QSPI Driver locked\r\n");
	}


	if (SDRAM_Do_InitializeSequence() == HAL_OK)
	{
		Serial1.println("SDRAM initialized\r\n");
	}
	else
	{
		Serial1.println("SDRAM initialize failed!!\r\n");
	}
	delay(100);

	{
		volatile uint8_t* memPtr = (volatile uint8_t *)SDRAM_BANK_ADDR; // 0xD0000000
		Serial1.println("Test SDRAM ====\r\n");
		volatile uint8_t* tmpPtr = memPtr;
		uint32_t data = 0x55;
		{
			uint32_t tickStart = HAL_GetTick();
			for(uint32_t i = 0; i < 32 * 1024 * 1024; i++)
				*tmpPtr++ = data;
			Serial1.printf("Clear All: elapsed %d msec\r\n", HAL_GetTick() - tickStart);
		}

		Serial1.println("Write Data ");
		tmpPtr = memPtr;
		data = 0x55;
		for(uint32_t i = 0; i < 32 * 1024 * 1024; i++)
		{
			if ((i % (1024 * 1024)) == 0)
				Serial1.print(".");
			*tmpPtr++ = data++;
		}

		Serial1.println("\r\nCompare Data ");
		tmpPtr = memPtr;
		data = 0x55;
		uint8_t memOk = 1;
		for(uint32_t i = 0; i < 32 * 1024 * 1024; i++)
		{
			if ((i % (1024 * 1024)) == 0)
				Serial1.print(".");

			uint8_t a = *tmpPtr;
			uint8_t b = data;
			if (a != b)
			{
				Serial1.printf("\r\nMemory corrupt at %08X: %02X, %02X\r\n", (unsigned int)i, a, b);
				memOk = 0;
				break;
			}
			tmpPtr++;
			data++;
		}
		if (memOk)
			Serial1.println("\r\nMemory compare passed!!\r\n");
	}

	keyPad.begin();
}

void FlightComputer::loop()
{
	uint32_t tick = millis();
	while(1)
	{
		if (Serial1.available())
			Serial1.write(Serial1.read());
		//if (Serial2.available())
		//	Serial1.write(Serial2.read());
		if (Serial3.available())
		{
			int ch = Serial3.read();
			Serial1.write(ch);
			Serial3.write(ch);
		}

		if ((millis() - tick) > 1000)
		{
			digitalToggle(PWR_LED1);
			digitalToggle(PWR_LED2);

			tick = millis();
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

	MX_FMC_Init();
	MX_QUADSPI_Init();
	MX_USB_DEVICE_Init();
	MX_FATFS_Init();
	//MX_SPI1_Init();


	// turn-on powers
	digitalWrite(PWR_EN_EXTRA, LOW);
	digitalWrite(PWR_EN_PERIPH, LOW);
	pinMode(PWR_EN_EXTRA, OUTPUT);
	pinMode(PWR_EN_PERIPH, OUTPUT);
	//digitalWrite(PWR_EN_EXTRA, HIGH);
	digitalWrite(PWR_EN_PERIPH, HIGH);
	delay(10);


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

