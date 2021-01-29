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
#include "hw_config.h"
#include "Wire/Wire.h"
#include "SPI/SPI.h"

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

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
	hw_config_init();

	//
	MX_FMC_Init();
	MX_QUADSPI_Init();

	//SDRAM_Do_InitializeSequence(&hsdram1);

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

void setup(void)
{
	pinMode(PWR_LED1, OUTPUT);
	pinMode(PWR_LED2, OUTPUT);
	digitalWrite(PWR_LED1, LOW);
	digitalWrite(PWR_LED2, HIGH);

	Serial1.begin(115200);
	Serial2.begin(9600);
	delay(100);
	Serial1.println("Hello world!\n");

	uint32_t tick = millis();
	while(1)
	{
		if (Serial2.available())
			Serial1.write(Serial2.read());

		if ((millis() - tick) > 1000)
		{
			digitalToggle(PWR_LED1);
			digitalToggle(PWR_LED2);

			tick = millis();
		}
	}
}

void loop()
{
	//
	uint32_t lastTick = HAL_GetTick();
	//main_loop_begin();

	while (1)
	{
		//main_loop();

		if (HAL_GetTick() - lastTick > 1000)
		{
			HAL_GPIO_TogglePin(PWR_LED1_GPIO_Port, PWR_LED1_Pin);
			lastTick = HAL_GetTick();
		}
	}
}


extern "C" void Error_Handler()
{
	_Error_Handler(__FILE__, __LINE__);
}

