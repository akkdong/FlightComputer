/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
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
#define PWR_WKUP0_KEY_ENTER_Pin GPIO_PIN_0
#define PWR_WKUP0_KEY_ENTER_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_2
#define GPS_TX_GPIO_Port GPIOA
#define GPS_RX_Pin GPIO_PIN_3
#define GPS_RX_GPIO_Port GPIOA
#define IMU_DRDY_Pin GPIO_PIN_0
#define IMU_DRDY_GPIO_Port GPIOB
#define IMU_FSYNC_Pin GPIO_PIN_1
#define IMU_FSYNC_GPIO_Port GPIOB
#define IMU_nINT_Pin GPIO_PIN_2
#define IMU_nINT_GPIO_Port GPIOB
#define DEBUG_TX_Pin GPIO_PIN_9
#define DEBUG_TX_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_10
#define DEBUG_RX_GPIO_Port GPIOA
#define VARIO_TX_Pin GPIO_PIN_10
#define VARIO_TX_GPIO_Port GPIOC
#define VARIO_RX_Pin GPIO_PIN_11
#define VARIO_RX_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */
#define KEY_ESCAPE_Pin GPIO_PIN_13
#define KEY_ESCAPE_GPIO_Port GPIOC
#define EINK_CMD_Pin GPIO_PIN_14
#define EINK_CMD_GPIO_Port GPIOC
#define EINK_BUSY_Pin GPIO_PIN_15
#define EINK_BUSY_GPIO_Port GPIOC
#define LOW_BATTERY_Pin GPIO_PIN_1
#define LOW_BATTERY_GPIO_Port GPIOC
#define PWR_WKUP0_KEY_ENTER_Pin GPIO_PIN_0
#define PWR_WKUP0_KEY_ENTER_GPIO_Port GPIOA
#define KEY_MENU_Pin GPIO_PIN_1
#define KEY_MENU_GPIO_Port GPIOA
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
#define PWR_EN_BAT_Pin GPIO_PIN_3
#define PWR_EN_BAT_GPIO_Port GPIOG
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
#define PMIC_PWR_GOOD_Pin GPIO_PIN_12
#define PMIC_PWR_GOOD_GPIO_Port GPIOG
#define PMIC_nINT_Pin GPIO_PIN_13
#define PMIC_nINT_GPIO_Port GPIOG
#define PWR_LED_Pin GPIO_PIN_14
#define PWR_LED_GPIO_Port GPIOG
#define PWR_EN_5V_Pin GPIO_PIN_9
#define PWR_EN_5V_GPIO_Port GPIOB


/* MT25QL512ABB Micron memory */
/* Size of the flash */
#define QSPI_FLASH_SIZE                      25
#define QSPI_PAGE_SIZE                       256

/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

/* Identification Operations */
#define READ_ID_CMD                          0x9E
#define READ_ID_CMD2                         0x9F
#define MULTIPLE_IO_READ_ID_CMD              0xAF
#define READ_SERIAL_FLASH_DISCO_PARAM_CMD    0x5A

/* Read Operations */
#define READ_CMD                             0x03
#define READ_4_BYTE_ADDR_CMD                 0x13

#define FAST_READ_CMD                        0x0B
#define FAST_READ_DTR_CMD                    0x0D
#define FAST_READ_4_BYTE_ADDR_CMD            0x0C

#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_OUT_FAST_READ_DTR_CMD           0x3D
#define DUAL_OUT_FAST_READ_4_BYTE_ADDR_CMD   0x3C

#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define DUAL_INOUT_FAST_READ_DTR_CMD         0xBD
#define DUAL_INOUT_FAST_READ_4_BYTE_ADDR_CMD 0xBC

#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_OUT_FAST_READ_DTR_CMD           0x6D
#define QUAD_OUT_FAST_READ_4_BYTE_ADDR_CMD   0x6C

#define QUAD_INOUT_FAST_READ_CMD             0xEB
#define QUAD_INOUT_FAST_READ_DTR_CMD         0xED
#define QUAD_INOUT_FAST_READ_4_BYTE_ADDR_CMD 0xEC

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05
#define WRITE_STATUS_REG_CMD                 0x01

#define READ_LOCK_REG_CMD                    0xE8
#define WRITE_LOCK_REG_CMD                   0xE5

#define READ_FLAG_STATUS_REG_CMD             0x70
#define CLEAR_FLAG_STATUS_REG_CMD            0x50

#define READ_NONVOL_CFG_REG_CMD              0xB5
#define WRITE_NONVOL_CFG_REG_CMD             0xB1

#define READ_VOL_CFG_REG_CMD                 0x85
#define WRITE_VOL_CFG_REG_CMD                0x81

#define READ_ENHANCED_VOL_CFG_REG_CMD        0x65
#define WRITE_ENHANCED_VOL_CFG_REG_CMD       0x61

#define READ_EXT_ADDR_REG_CMD                0xC8
#define WRITE_EXT_ADDR_REG_CMD               0xC5

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define PAGE_PROG_4_BYTE_ADDR_CMD            0x12

#define DUAL_IN_FAST_PROG_CMD                0xA2
#define EXT_DUAL_IN_FAST_PROG_CMD            0xD2

#define QUAD_IN_FAST_PROG_CMD                0x32
#define EXT_QUAD_IN_FAST_PROG_CMD            0x12 /*0x38*/
#define QUAD_IN_FAST_PROG_4_BYTE_ADDR_CMD    0x34

/* Erase Operations */
#define SUBSECTOR_ERASE_CMD                  0x20
#define SUBSECTOR_ERASE_4_BYTE_ADDR_CMD      0x21

#define SECTOR_ERASE_CMD                     0xD8
#define SECTOR_ERASE_4_BYTE_ADDR_CMD         0xDC

#define BULK_ERASE_CMD                       0xC7

#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75

/* One-Time Programmable Operations */
#define READ_OTP_ARRAY_CMD                   0x4B
#define PROG_OTP_ARRAY_CMD                   0x42

/* 4-byte Address Mode Operations */
#define ENTER_4_BYTE_ADDR_MODE_CMD           0xB7
#define EXIT_4_BYTE_ADDR_MODE_CMD            0xE9

/* Quad Operations */
#define ENTER_QUAD_CMD                       0x35
#define EXIT_QUAD_CMD                        0xF5

/* Default dummy clocks cycles */
#define DUMMY_CLOCK_CYCLES_READ              8
#define DUMMY_CLOCK_CYCLES_READ_QUAD         10

#define DUMMY_CLOCK_CYCLES_READ_DTR          6
#define DUMMY_CLOCK_CYCLES_READ_QUAD_DTR     8

/* End address of the QSPI memory */
#define QSPI_END_ADDR              (1 << QSPI_FLASH_SIZE)

/* Size of buffers */
#define BUFFERSIZE                 (COUNTOF(aTxBuffer) - 1)

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)        (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
