/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_storage_if.c
  * @version        : v1.0_Cube
  * @brief          : Memory management layer.
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_storage_if.h"

/* USER CODE BEGIN INCLUDE */
#include "qspi_drv.h"
#include <stdio.h>
/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @defgroup USBD_STORAGE
  * @brief Usb mass storage device module
  * @{
  */

/** @defgroup USBD_STORAGE_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Defines
  * @brief Private defines.
  * @{
  */

#define STORAGE_TOTAL_SIZE				 (64 * 1024 * 1024)
#define STORAGE_LUN_NBR                  (1)
#define STORAGE_BLK_SIZ                  (0x1000)
#define STORAGE_BLK_NBR                  ((STORAGE_TOTAL_SIZE) / (STORAGE_BLK_SIZ))


/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Variables
  * @brief Private variables.
  * @{
  */

/* USER CODE BEGIN INQUIRY_DATA_HS */
/** USB Mass storage Standard Inquiry Data. */
const int8_t STORAGE_Inquirydata_HS[] = {/* 36 */

  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,
  0x00,
  'R', 'a', 's', 'c', 'a', 'l', ' ', ' ', /* Manufacturer : 8 bytes */
  'F', 'l', 'i', 'g', 'h', 't', ' ', 'C', /* Product      : 16 Bytes */
  'o', 'm', 'p', 't', 'e', 'r', ' ', ' ',
  '0', '.', '0' ,'1'                      /* Version      : 4 Bytes */
};
/* USER CODE END INQUIRY_DATA_HS */

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceHS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t STORAGE_Init_HS(uint8_t lun);
static int8_t STORAGE_GetCapacity_HS(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
static int8_t STORAGE_IsReady_HS(uint8_t lun);
static int8_t STORAGE_IsWriteProtected_HS(uint8_t lun);
static int8_t STORAGE_Read_HS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_Write_HS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_GetMaxLun_HS(void);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_StorageTypeDef USBD_Storage_Interface_fops_HS =
{
  STORAGE_Init_HS,
  STORAGE_GetCapacity_HS,
  STORAGE_IsReady_HS,
  STORAGE_IsWriteProtected_HS,
  STORAGE_Read_HS,
  STORAGE_Write_HS,
  STORAGE_GetMaxLun_HS,
  (int8_t *)STORAGE_Inquirydata_HS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes over USB HS IP
  * @param  lun:
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Init_HS(uint8_t lun)
{
  /* USER CODE BEGIN 2 */
	if (QSPI_Driver_locked())
	{
		//printf( "Locked\n");
		return USBD_FAIL;
	}
	if(QSPI_Driver_state() == 1)
	{
		//printf( "OK\n");
		return USBD_OK;
	}
	//init qspi
	if(  QSPI_Driver_init() == QSPI_STATUS_OK)
	{
		//printf( "INIT OK\n");
		return USBD_OK;
	}

	//printf( "N/A\n");
	return USBD_FAIL;
  /* USER CODE END 2 */
}

/**
  * @brief  .
  * @param  lun: .
  * @param  block_num: .
  * @param  block_size: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_GetCapacity_HS(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  /* USER CODE BEGIN 3 */
  *block_num  = STORAGE_BLK_NBR;
  *block_size = STORAGE_BLK_SIZ;
  return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsReady_HS(uint8_t lun)
{
  /* USER CODE BEGIN 4 */
	if(!QSPI_Driver_state())
	{
		if(  QSPI_Driver_init() == QSPI_STATUS_OK)
		{
			//printf("OK\n");
			return USBD_OK;
		}

		//printf("INIT FAILED\n");
		return USBD_FAIL;
	}
	if(QSPI_Driver_locked())
	{
		//printf("LOCKED\n");
		return USBD_FAIL;
	}

	//printf("OK\n");
	return USBD_OK;
  /* USER CODE END 4 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsWriteProtected_HS(uint8_t lun)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Read_HS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  /* USER CODE BEGIN 6 */
	 if(QSPI_Driver_locked())
	 {
		 printf("QSPI LOCKED!!\n");
		 return USBD_FAIL;
	 }
	 uint32_t bufferSize = (BLOCK_SIZE * blk_len);
	 uint32_t address =  (blk_addr * BLOCK_SIZE);
	 uint32_t data_read = 0;
	 //printf("Reading sector 0x%X, %d sectors\n",(unsigned int)blk_addr,(unsigned int)blk_len);
	 while(data_read < bufferSize)
	 {
		 uint32_t incr = bufferSize < MAX_READ_SIZE ? bufferSize : MAX_READ_SIZE;
		 if(QSPI_Driver_read(&buf[data_read], address, incr) != QSPI_STATUS_OK)
		 {
			 printf("READ FAILED: 0x%X\n", (unsigned int)address);
			 return USBD_FAIL;
		 }
		 data_read += incr;
		 address += incr;
	 }
	 return USBD_OK;
  /* USER CODE END 6 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Write_HS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  /* USER CODE BEGIN 7 */
	 if(QSPI_Driver_locked())
	 {
		 printf("QSPI LOCKED!!\n");
		 return USBD_FAIL;
	 }
	 //erase subsectors
	 uint32_t subsector_addr = blk_addr * BLOCK_SIZE;
	 int i=0;
	 for(i=0;i<blk_len;i++)
	 {
		 if(QSPI_Driver_erase_subsector(subsector_addr) != QSPI_STATUS_OK)
		 {
			 printf("ERASE FAILED: 0x%X\n", (unsigned int)subsector_addr);
			 return USBD_FAIL;
		 }
		 subsector_addr += BLOCK_SIZE;
	 }
	 //write data
	 uint32_t bufferSize = (BLOCK_SIZE * blk_len);
	 uint32_t address =  (blk_addr * BLOCK_SIZE);
	 if(QSPI_Driver_write(buf, address, bufferSize) != QSPI_STATUS_OK)
	 {
		 printf("WRITE FAILED: 0x%X\n", (unsigned int)address);
		 return USBD_FAIL;
	 }
	 return USBD_OK;
  /* USER CODE END 7 */
}

/**
  * @brief  .
  * @param  None
  * @retval .
  */
int8_t STORAGE_GetMaxLun_HS(void)
{
  /* USER CODE BEGIN 8 */
  return (STORAGE_LUN_NBR - 1);
  /* USER CODE END 8 */
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
