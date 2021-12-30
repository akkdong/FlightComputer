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
lwrb_t* rb_cm4_to_cm7 = (lwrb_t *)BUFF_CM4_TO_CM7_ADDR;
lwrb_t* rb_cm7_to_cm4 = (lwrb_t *)BUFF_CM7_TO_CM4_ADDR;

volatile int Notif_Sleep = 0;


///////////////////////////////////////////////////////////////////////////////
//

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
	/* Clear HSEM flag & Deativate HSEM notification*/
	__HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
	HAL_HSEM_DeactivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
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

	//pinMode(A26, INPUT_ANALOG);
	//pinMode(A27, INPUT_ANALOG);

	lwrb_write_string(rb_cm4_to_cm7, "CM4 Notify\r\n");

	HAL_NVIC_SetPriority(HSEM2_IRQn, 4, 0);
	HAL_NVIC_EnableIRQ(HSEM2_IRQn);

	Notif_Sleep = 0;
	HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_1));
	HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_2));


	// Sinewave PWM test code
#if 1
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

	HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_2);

	HAL_DMA_Start_IT(&hdma_tim4_ch1, (uint32_t)Wave_LUT, DestAddressCH3, NS);
	HAL_DMA_Start_IT(&hdma_tim4_ch2, (uint32_t)Wave_LUT, DestAddressCH4, NS);

	__HAL_TIM_ENABLE_DMA(&htim4, TIM_DMA_CC1);
	__HAL_TIM_ENABLE_DMA(&htim4, TIM_DMA_CC2);
#endif

#if 1
	// stop PWM
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);

	// disable DMA
	__HAL_TIM_DISABLE_DMA(&htim4, TIM_DMA_CC1);
	__HAL_TIM_DISABLE_DMA(&htim4, TIM_DMA_CC2);
	// abort DMA
	HAL_DMA_Abort_IT(&hdma_tim4_ch1);
	HAL_DMA_Abort_IT(&hdma_tim4_ch2);
	// stop timer
	HAL_TIM_OC_Stop(&htim4, TIM_CHANNEL_1);
	HAL_TIM_OC_Stop(&htim4, TIM_CHANNEL_2);
#endif
}


uint32_t lastTick = millis();
char buf[32];

void loop(void)
{
#if 0
	while (Serial2.available())
	{
		int ch = Serial2.read();
		lwrb_write(rb_cm4_to_cm7, &ch, 1);
	}
#endif

	if (Notif_Sleep)
	{
		char sz[64];
		sprintf(sz, "HSEM1 signaled: %d\r\n", Notif_Sleep);
		lwrb_write_string(rb_cm4_to_cm7, sz);

		if (Notif_Sleep & (1 << HSEM_ID_1))
		{
			  HAL_PWREx_ClearPendingEvent();
			  // Enter D3 to DStandby mode
			  HAL_PWREx_EnterSTANDBYMode(PWR_D3_DOMAIN);
			  // Enter D2 to DStandby mode
			  HAL_PWREx_EnterSTANDBYMode(PWR_D2_DOMAIN);
		}

		Notif_Sleep = 0;
	}

	if (0 && millis() - lastTick > 2000)
	{
		lastTick = millis();

		uint32_t adc1 = analogRead(A26);
		uint32_t adc2 = analogRead(A27);

		sprintf(buf, "adc1: %d\r\n", (unsigned int)adc1);
		lwrb_write_string(rb_cm4_to_cm7, buf);
		sprintf(buf, "adc2: %d\r\n", (unsigned int)adc2);
		lwrb_write_string(rb_cm4_to_cm7, buf);
	}
}


extern "C" void Error_Handler()
{
	//_Error_Handler(__FILE__, __LINE__);
}


extern "C" void HAL_HSEM_FreeCallback(uint32_t SemMask)
{
	Notif_Sleep |= SemMask;
}
