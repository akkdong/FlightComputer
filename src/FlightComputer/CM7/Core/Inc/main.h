/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#define IMU1_SCLK_Pin GPIO_PIN_2
#define IMU1_SCLK_GPIO_Port GPIOE
#define IMU1_nCS1_Pin GPIO_PIN_3
#define IMU1_nCS1_GPIO_Port GPIOE
#define IMU1_nCS2_Pin GPIO_PIN_4
#define IMU1_nCS2_GPIO_Port GPIOE
#define IMU1_MISO_Pin GPIO_PIN_5
#define IMU1_MISO_GPIO_Port GPIOE
#define IMU1_MOSI_Pin GPIO_PIN_6
#define IMU1_MOSI_GPIO_Port GPIOE
#define KEY_ESCAPE_Pin GPIO_PIN_13
#define KEY_ESCAPE_GPIO_Port GPIOC
#define EINK_CMD_Pin GPIO_PIN_14
#define EINK_CMD_GPIO_Port GPIOC
#define EINK_BUSY_Pin GPIO_PIN_15
#define EINK_BUSY_GPIO_Port GPIOC
#define RPI_STATUS_Pin GPIO_PIN_1
#define RPI_STATUS_GPIO_Port GPIOC
#define PWR_WKUP0_KEY_ENTER_Pin GPIO_PIN_0
#define PWR_WKUP0_KEY_ENTER_GPIO_Port GPIOA
#define KEY_MENU_Pin GPIO_PIN_1
#define KEY_MENU_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_2
#define GPS_TX_GPIO_Port GPIOA
#define GPS_RX_Pin GPIO_PIN_3
#define GPS_RX_GPIO_Port GPIOA
#define EINK_nCS_Pin GPIO_PIN_4
#define EINK_nCS_GPIO_Port GPIOA
#define EINK_SCLK_Pin GPIO_PIN_5
#define EINK_SCLK_GPIO_Port GPIOA
#define EINK_MISO_Pin GPIO_PIN_6
#define EINK_MISO_GPIO_Port GPIOA
#define EINK_MOSI_Pin GPIO_PIN_7
#define EINK_MOSI_GPIO_Port GPIOA
#define KEY_LEFT_Pin GPIO_PIN_4
#define KEY_LEFT_GPIO_Port GPIOC
#define KEY_RIGHT_Pin GPIO_PIN_5
#define KEY_RIGHT_GPIO_Port GPIOC
#define IMU_DRDY_Pin GPIO_PIN_0
#define IMU_DRDY_GPIO_Port GPIOB
#define IMU_FSYNC_Pin GPIO_PIN_1
#define IMU_FSYNC_GPIO_Port GPIOB
#define IMU_nINT_Pin GPIO_PIN_2
#define IMU_nINT_GPIO_Port GPIOB
#define USB_OTG_HS_ID_Pin GPIO_PIN_12
#define USB_OTG_HS_ID_GPIO_Port GPIOB
#define EPD_D6_Pin GPIO_PIN_11
#define EPD_D6_GPIO_Port GPIOD
#define EPD_D7_Pin GPIO_PIN_12
#define EPD_D7_GPIO_Port GPIOD
#define USB_OTG_HS_PWR_EN_Pin GPIO_PIN_13
#define USB_OTG_HS_PWR_EN_GPIO_Port GPIOD
#define EPD_CKV_Pin GPIO_PIN_8
#define EPD_CKV_GPIO_Port GPIOJ
#define EPD_CL_Pin GPIO_PIN_9
#define EPD_CL_GPIO_Port GPIOJ
#define EPD_GMODE_Pin GPIO_PIN_10
#define EPD_GMODE_GPIO_Port GPIOJ
#define EPD_LE_Pin GPIO_PIN_11
#define EPD_LE_GPIO_Port GPIOJ
#define EPD_OE_Pin GPIO_PIN_0
#define EPD_OE_GPIO_Port GPIOK
#define EPD_SPH_Pin GPIO_PIN_1
#define EPD_SPH_GPIO_Port GPIOK
#define EPD_SPV_Pin GPIO_PIN_2
#define EPD_SPV_GPIO_Port GPIOK
#define PWR_EN_PMIC_Pin GPIO_PIN_3
#define PWR_EN_PMIC_GPIO_Port GPIOG
#define PWR_EN_PERIPH_Pin GPIO_PIN_7
#define PWR_EN_PERIPH_GPIO_Port GPIOG
#define KEY_UP_Pin GPIO_PIN_6
#define KEY_UP_GPIO_Port GPIOC
#define KEY_DOWN_Pin GPIO_PIN_7
#define KEY_DOWN_GPIO_Port GPIOC
#define KEY_FUNC1_Pin GPIO_PIN_8
#define KEY_FUNC1_GPIO_Port GPIOC
#define KEY_FUNC2_Pin GPIO_PIN_9
#define KEY_FUNC2_GPIO_Port GPIOC
#define USB_OTG_HS_OVCR_Pin GPIO_PIN_8
#define USB_OTG_HS_OVCR_GPIO_Port GPIOA
#define DEBUG_TX_Pin GPIO_PIN_9
#define DEBUG_TX_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_10
#define DEBUG_RX_GPIO_Port GPIOA
#define VARIO_TX_Pin GPIO_PIN_10
#define VARIO_TX_GPIO_Port GPIOC
#define VARIO_RX_Pin GPIO_PIN_11
#define VARIO_RX_GPIO_Port GPIOC
#define USB_OTG_FS_VBUS_Pin GPIO_PIN_12
#define USB_OTG_FS_VBUS_GPIO_Port GPIOC
#define EPD_D0_Pin GPIO_PIN_2
#define EPD_D0_GPIO_Port GPIOD
#define EPD_D1_Pin GPIO_PIN_3
#define EPD_D1_GPIO_Port GPIOD
#define EPD_D2_Pin GPIO_PIN_4
#define EPD_D2_GPIO_Port GPIOD
#define EPD_D3_Pin GPIO_PIN_5
#define EPD_D3_GPIO_Port GPIOD
#define EPD_D4_Pin GPIO_PIN_6
#define EPD_D4_GPIO_Port GPIOD
#define EPD_D5_Pin GPIO_PIN_7
#define EPD_D5_GPIO_Port GPIOD
#define PMIC_VCOM_Pin GPIO_PIN_9
#define PMIC_VCOM_GPIO_Port GPIOG
#define PMIC_WAKEUP_Pin GPIO_PIN_10
#define PMIC_WAKEUP_GPIO_Port GPIOG
#define PMIC_PWRUP_Pin GPIO_PIN_11
#define PMIC_PWRUP_GPIO_Port GPIOG
#define PWR_LED2_Pin GPIO_PIN_13
#define PWR_LED2_GPIO_Port GPIOG
#define PWR_LED1_Pin GPIO_PIN_14
#define PWR_LED1_GPIO_Port GPIOG
#define PWR_5V_EN_Pin GPIO_PIN_9
#define PWR_5V_EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
