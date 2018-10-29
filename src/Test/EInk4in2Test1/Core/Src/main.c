
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "spi.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "epd4in2.h"
#include "epdif.h"
#include "epdpaint.h"
#include "imagedata.h"
#include <stdlib.h>
#include <math.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define COLORED      1
#define UNCOLORED    0

unsigned char frame[EPD_WIDTH * EPD_HEIGHT / 8];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	unsigned char* frame_buffer = frame; // (unsigned char*)malloc(EPD_WIDTH * EPD_HEIGHT / 8);
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USB_DEVICE_Init();
  MX_SPI1_Init();

  /* USER CODE BEGIN 2 */
  EPD epd;
  if (EPD_Init(&epd) != 0) {
    printf("e-Paper init failed\n");
    return -1;
  }

  //
  EPD_ClearFrame(&epd);
  EPD_DisplayFrame(&epd);

  //
  Paint paint;
  Paint_Init(&paint, frame_buffer, epd.width, epd.height);
  Paint_Clear(&paint, UNCOLORED);

#if 1

	Paint_DrawFilledCircle(&paint, 32, 32, 8, COLORED);
	EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
	EPD_DisplayFrameQuick(&epd);
	EPD_WaitUntilIdle(&epd);

	Paint_DrawFilledCircle(&paint, 16, 16, 8, COLORED);
	EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
	EPD_DisplayFrameQuick(&epd);
	EPD_WaitUntilIdle(&epd);

	Paint_DrawFilledCircle(&paint, 40, 32, 18, COLORED);
	EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
	EPD_DisplayFrameQuick(&epd);
	EPD_WaitUntilIdle(&epd);

	Paint_DrawFilledCircle(&paint, 64, 64, 24, COLORED);
	EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
	EPD_DisplayFrameQuick(&epd);
	EPD_WaitUntilIdle(&epd);

	Paint_DrawFilledCircle(&paint, 200, 150, 50, COLORED);
	EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
	EPD_DisplayFrameQuick(&epd);
	EPD_WaitUntilIdle(&epd);

	Paint_DrawFilledCircle(&paint, 250, 75, 80, COLORED);
	EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
	EPD_DisplayFrameQuick(&epd);
	EPD_WaitUntilIdle(&epd);

	Paint_DrawFilledCircle(&paint, 100, 250, 80, COLORED);
	EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
	EPD_DisplayFrameQuick(&epd);
	EPD_WaitUntilIdle(&epd);

	Paint_DrawFilledCircle(&paint, 100, 250, 50, UNCOLORED);
	EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
	EPD_DisplayFrameQuick(&epd);
	EPD_WaitUntilIdle(&epd);
	Paint_DrawFilledCircle(&paint, 250, 75, 50, UNCOLORED);
	EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
	EPD_DisplayFrameQuick(&epd);
	EPD_WaitUntilIdle(&epd);

	Paint_DrawFilledCircle(&paint, 200, 150, 20, UNCOLORED);
	EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
	EPD_DisplayFrameQuick(&epd);
	EPD_WaitUntilIdle(&epd);
	EPD_DelayMs(&epd, 3000);

	Paint_Clear(&paint, UNCOLORED);
	EPD_DisplayFrame(&epd);

	//
	float phase = 0.0;
	float twopi = 3.14159 * 2;

	static char outstr[15];
	while(phase < 8)
	{
		Paint_Clear(&paint, UNCOLORED);
		Paint_DrawStringAt(&paint, (int)30+phase*10, 30, itoa(phase * 10, outstr, 10), &Font24, COLORED);
		Paint_DrawFilledCircle(&paint, 200+80*sin(phase), 150+80*cos(phase), 20, COLORED);
		EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
		EPD_DisplayFrameQuick(&epd);
		EPD_WaitUntilIdle(&epd);
		phase = phase + 0.2;
	}

	for(int i = 0; i<2;i++)
	{
		Paint_Clear(&paint, UNCOLORED);
		EPD_SetPartialWindow(&epd, Paint_GetImage(&paint), 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint),2);
		EPD_DisplayFrame(&epd);
		EPD_DelayMs(&epd, 10);
	}

	/* This displays an image */
	EPD_DisplayFrameEx(&epd, IMAGE_BUTTERFLY);
	EPD_DelayMs(&epd, 4000);
	EPD_DisplayFrameEx(&epd, IMAGE_ASCIENCE);
	EPD_DelayMs(&epd, 4000);
	EPD_DisplayFrameEx(&epd, IMAGE_PLAYBUTTON);
	/* Deep sleep */
	EPD_Sleep(&epd);

#else
  /* Draw something to the frame_buffer */
  /* For simplicity, the arguments are explicit numerical coordinates */
  Paint_DrawRectangle(&paint, 20, 80, 180, 280, COLORED);
  Paint_DrawLine(&paint, 20, 80, 180, 280, COLORED);
  Paint_DrawLine(&paint, 180, 80, 20, 280, COLORED);
  Paint_DrawFilledRectangle(&paint, 200, 80, 360, 280, COLORED);
  Paint_DrawCircle(&paint, 300, 160, 60, UNCOLORED);
  Paint_DrawFilledCircle(&paint, 90, 210, 30, COLORED);

  /*Write strings to the buffer */
  Paint_DrawFilledRectangle(&paint, 0, 6, 400, 30, COLORED);
  Paint_DrawStringAt(&paint, 100, 10, "Hello world!", &Font24, UNCOLORED);
  Paint_DrawStringAt(&paint, 100, 40, "e-Paper Demo", &Font24, COLORED);

  /* Display the frame_buffer */
  EPD_DisplayFrameEx(&epd, frame_buffer);

  /* Display the image buffer */
  EPD_DisplayFrameEx(&epd, IMAGE_BUTTERFLY);
#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
