/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main-cm7.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWR_WKUP0_KEY_ENTER_Pin GPIO_PIN_0
#define PWR_WKUP0_KEY_ENTER_GPIO_Port GPIOA
#define EINK_nCS_Pin GPIO_PIN_4
#define EINK_nCS_GPIO_Port GPIOA
#define EINK_SCLK_Pin GPIO_PIN_5
#define EINK_SCLK_GPIO_Port GPIOA
#define EINK_MISO_Pin GPIO_PIN_6
#define EINK_MISO_GPIO_Port GPIOA
#define EINK_MOSI_Pin GPIO_PIN_7
#define EINK_MOSI_GPIO_Port GPIOA
#define DEBUG_TX_Pin GPIO_PIN_9
#define DEBUG_TX_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_10
#define DEBUG_RX_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
#define PWR_EN_5V_PORT GPIOB
#define PWR_EN_5V_PIN GPIO_PIN_9
#define PWR_EN_BAT_PORT GPIOG
#define PWR_EN_BAT_PIN GPIO_PIN_3
#define PWR_EN_PERIPH_PORT GPIOG
#define PWR_EN_PERIPH_PIN GPIO_PIN_7
#define PWR_LED_PORT GPIOG
#define PWR_LED_PIN GPIO_PIN_14
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
