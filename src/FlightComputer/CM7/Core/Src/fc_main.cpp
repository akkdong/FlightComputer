// flight_computer.cpp
//

#if 0
#include "adc.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "hw_config.h"
#include "Wire/Wire.h"
#endif

#include "main.h"
#include "quadspi.h"
#include "fmc.h"
#include "fatfs.h"
#include "sdram_drv.h"
#include "qspi_drv.h"
#include "usb_device.h"
#include "common.h"
#include "debug.h"
#include "FlightComputer.h"



/////////////////////////////////////////////////////////////////////////////////////
//

// CM4 notify
volatile int notify_cm4 = 0;

lwrb_t* rb_cm4_to_cm7 = (lwrb_t *)BUFF_CM4_TO_CM7_ADDR;
lwrb_t* rb_cm7_to_cm4 = (lwrb_t *)BUFF_CM7_TO_CM4_ADDR;


//
FlightComputer	fc;



/////////////////////////////////////////////////////////////////////////////////////
//

extern "C" void init(void)
{
	// enable HSEM clock
	__HAL_RCC_HSEM_CLK_ENABLE();

	// Wait until CPU2 boots and enters in stop mode or timeout
	//
	int32_t timeout = 0xFFFF;
	while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
	if ( timeout < 0 )
	{
		Error_Handler();
	}

	//
	/*
    HAL_RCCEx_EnableBootCore(RCC_BOOT_C2);
    WAIT_COND_WITH_TIMEOUT(__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET, 0xFFFF);
    */

	//
	/* Init DWT if present */
	#ifdef DWT_BASE
	dwt_init();
	#endif

	/* Initialize the HAL */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	// Check and handle if the system was resumed from StandBy mode
	if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
	{
		// Clear system Standby flag
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
		TRACE("Wakeup from standby mode\r\n");
	}

	/* Disable all used wakeup sources*/
	HAL_PWREx_DisableWakeUpPin(PWR_WAKEUP_PIN1);


	#if defined (USBCON) && defined(USBD_USE_CDC)
	USBD_CDC_init();
	#endif

	// enable all gpio clock
	//__HAL_RCC_GPIOA_CLK_ENABLE();
	//__HAL_RCC_GPIOB_CLK_ENABLE();
	//__HAL_RCC_GPIOC_CLK_ENABLE();
	//__HAL_RCC_GPIOD_CLK_ENABLE();
	//__HAL_RCC_GPIOE_CLK_ENABLE();
	//__HAL_RCC_GPIOF_CLK_ENABLE();
	//__HAL_RCC_GPIOG_CLK_ENABLE();
	//__HAL_RCC_GPIOH_CLK_ENABLE();
	//__HAL_RCC_GPIOJ_CLK_ENABLE();
	//__HAL_RCC_GPIOK_CLK_ENABLE();

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

	Serial.begin(115200);
	TRACE("Start Flight computer!\r\n");

	// initialize Flash
	if (!QSPI_Driver_locked())
	{
		if(!QSPI_Driver_state())
		{
			if(QSPI_Driver_init() == QSPI_STATUS_OK)
			{
				TRACE("QSPI Driver initialized\r\n");
				FlightComputer::flash_ok = true;
			}
			else
			{
				//TRACE("QSPI Driver initialize failed!!\r\n");
			}
		}
		else
		{
			//TRACE("QSPI Driver have been ready\r\n");
		}
	}
	else
	{
		//TRACE("QSPI Driver locked\r\n");
	}

	// initialize SDRAM
	if (SDRAM_Do_InitializeSequence() == HAL_OK)
	{
		TRACE("SDRAM initialized\r\n");
		FlightComputer::sdram_ok = true;
	}
	else
	{
		//TRACE("SDRAM initialize failed!!\r\n");
	}
	delay(100);


    /* Initialize buffers that are used as shared memory */
    lwrb_init(rb_cm7_to_cm4, (void *)BUFFDATA_CM7_TO_CM4_ADDR, BUFFDATA_CM7_TO_CM4_LEN);
    lwrb_init(rb_cm4_to_cm7, (void *)BUFFDATA_CM4_TO_CM7_ADDR, BUFFDATA_CM4_TO_CM7_LEN);

	// When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of HSEM notification HW semaphore Clock enable
	//__HAL_RCC_HSEM_CLK_ENABLE();
	// Take HSEM
	HAL_HSEM_FastTake(HSEM_WAKEUP_CPU2);
	// Release HSEM in order to notify the CPU2(CM4)
	HAL_HSEM_Release(HSEM_WAKEUP_CPU2, 0);
	// Wait until CPU2 wakes up from stop mode
	timeout = 0xFFFFF;
	while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
	if ( timeout < 0 )
	{
		TRACE("CM4 is not READY!!\r\n");
		while(1);
	}

#if 0
    HAL_RCCEx_EnableBootCore(RCC_BOOT_C2);
#endif

    HAL_HSEM_ActivateNotification(HSEM_VAIO_UPDATE_MASK);
}


extern "C" void setup()
{
	fc.setup();
}

extern "C" void loop()
{
	fc.loop();

	if (notify_cm4 & HSEM_VAIO_UPDATE_MASK)
	{
		notify_cm4 &= ~HSEM_VAIO_UPDATE_MASK;

		// fc.updateVario();
		HAL_HSEM_ActivateNotification(HSEM_VAIO_UPDATE_MASK);
	}
}



extern "C" void HAL_HSEM_FreeCallback(uint32_t SemMask)
{
	notify_cm4 |= SemMask;
}
