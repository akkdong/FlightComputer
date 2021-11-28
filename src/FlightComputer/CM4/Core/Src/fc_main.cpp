/*
 * fc_main.cpp
 *
 *  Created on: 2021. 11. 25.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "main.h"
#include "common.h"

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

//
LWRB_VOLATILE lwrb_t* rb_cm4_to_cm7 = (LWRB_VOLATILE lwrb_t *)BUFF_CM4_TO_CM7_ADDR;
LWRB_VOLATILE lwrb_t* rb_cm7_to_cm4 = (LWRB_VOLATILE lwrb_t *)BUFF_CM7_TO_CM4_ADDR;


void init(void)
{
#if 1
	/*HW semaphore Clock enable*/
	__HAL_RCC_HSEM_CLK_ENABLE();
	/* Activate HSEM notification for Cortex-M4*/
	HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
	/*
	Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
	perform system initialization (system clock config, external memory configuration.. )
	*/
	HAL_PWREx_ClearPendingEvent();
	HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
	/* Clear HSEM flag */
	__HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
#endif

#if 0
    /* CPU2 goes to STOP mode and waits CPU1 to initialize all the steps first */
    /* CPU1 will wakeup CPU2 with semaphore take and release events */
    /* HW semaphore Clock enable */
    __HAL_RCC_HSEM_CLK_ENABLE();
    HAL_HSEM_ActivateNotification(HSEM_WAKEUP_CPU2_MASK);
    HAL_PWREx_ClearPendingEvent();
    HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
    __HAL_HSEM_CLEAR_FLAG(HSEM_WAKEUP_CPU2_MASK);
#endif

	/* MCU Configuration--------------------------------------------------------*/
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
}

void setup(void)
{
	Serial2.begin(9600);

	//pinMode(PWR_LED2, OUTPUT);
	//digitalWrite(PWR_LED2, HIGH);

	lwrb_write(rb_cm4_to_cm7, "Test\r\n", 6);
}


void loop(void)
{
	while (Serial2.available())
	{
		int ch = Serial2.read();
		lwrb_write(rb_cm4_to_cm7, &ch, 1);
	}
}


extern "C" void Error_Handler()
{
	//_Error_Handler(__FILE__, __LINE__);
}

