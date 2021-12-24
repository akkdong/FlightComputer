/*
 * nor.c
 *
 *  Created on: 2021. 12. 24.
 *      Author: akkdong
 */


#include "main.h"
#include "nor.h"
#include <stdio.h>

extern NOR_HandleTypeDef hnor1;


static void NOR_MspWait(NOR_HandleTypeDef *hnor, uint32_t Timeout);
static int32_t NOR_GetStatus(uint32_t Instance, uint32_t Address, uint32_t Timeout, uint32_t ProgramTimeout);




/**
  * @brief  Erases the specified block of the NOR device.
  * @param  Instance  NOR Instance
  * @param  BlockAddress  Block address to erase
  * @retval BSP status
  */
int32_t BSP_NOR_EraseBlock(uint32_t Instance, uint32_t BlockAddress)
{
  int32_t ret = BSP_ERROR_NONE;

  /* Send NOR erase block operation */
  if(HAL_NOR_Erase_Block(&hnor1, BlockAddress, NOR_DEVICE_ADDR) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else
  {
    if(NOR_GetStatus(Instance, NOR_DEVICE_ADDR, PROGRAM_TIMEOUT, BLOCKERASE_TIMEOUT) != BSP_ERROR_NONE)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
  * @brief  Reads an amount of data from the NOR device.
  * @param  Instance  NOR Instance
  * @param  uwStartAddress  Read start address
  * @param  pData  Pointer to data to be read
  * @param  uwDataSize  Size of data to read
  * @retval BSP status
  */
int32_t BSP_NOR_ReadData(uint32_t Instance, uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize)
{
  int32_t ret;

  if(HAL_NOR_ReadBuffer(&hnor1, NOR_DEVICE_ADDR + uwStartAddress, pData, uwDataSize) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Writes an amount of data to the NOR device.
  * @param  Instance  NOR Instance
  * @param  uwStartAddress  Write start address
  * @param  pData  Pointer to data to be written
  * @param  uwDataSize  Size of data to write
  * @retval BSP status
  */
int32_t BSP_NOR_WriteData(uint32_t Instance, uint32_t uwStartAddress, uint16_t* pData, uint32_t uwDataSize)
{
  int32_t ret = BSP_ERROR_NONE;
  uint32_t index = uwDataSize;
  uint32_t write_addr;
  uint16_t* write_data;

	write_data = pData;
	write_addr = uwStartAddress;
	while((index > 0UL) && (ret == BSP_ERROR_NONE))
	{
	  /* Write data to NOR */
	  if(HAL_NOR_Program(&hnor1, (uint32_t *)(NOR_DEVICE_ADDR + write_addr), write_data) != HAL_OK)
	  {
		ret = BSP_ERROR_PERIPH_FAILURE;
	  }
	  else if(NOR_GetStatus(Instance, NOR_DEVICE_ADDR, PROGRAM_TIMEOUT, PROGRAM_TIMEOUT) != BSP_ERROR_NONE)
	  {
		ret = BSP_ERROR_PERIPH_FAILURE;
	  }
	  else
	  {
		/* Update the counters */
		index--;
		write_addr += 2UL;
		write_data++;
	  }
	}

  return ret;
}


/**
  * @brief  NOR BSP Wait for Ready/Busy signal.
  * @param  hnor     Pointer to NOR handle
  * @param  Timeout  Timeout duration
  * @retval None
  */
static void NOR_MspWait(NOR_HandleTypeDef *hnor, uint32_t Timeout)
{
  uint32_t timeout = Timeout;
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hnor);

  /* Polling on Ready/Busy signal */
  while((HAL_GPIO_ReadPin(NOR_READY_BUSY_GPIO, NOR_READY_BUSY_PIN) != NOR_BUSY_STATE) && (timeout > 0U))
  {
    timeout--;
  }

  timeout = Timeout;

  /* Polling on Ready/Busy signal */
  while((HAL_GPIO_ReadPin(NOR_READY_BUSY_GPIO, NOR_READY_BUSY_PIN) != NOR_READY_STATE) && (timeout > 0U))
  {
    timeout--;
  }
}

/**
  * @brief  Returns the NOR operation status.
  * @param  Instance  NOR Instance
  * @param  Address Device address
  * @param  Timeout NOR Timeout for Ready/Busy signal
  * @param  ProgramTimeout NOR programming Timeout
  * @retval BSP status
  */
static int32_t NOR_GetStatus(uint32_t Instance, uint32_t Address, uint32_t Timeout, uint32_t ProgramTimeout)
{
  int32_t ret = BSP_ERROR_NONE;


    /* NOR BSP Wait for Ready/Busy signal */
    NOR_MspWait(&hnor1, Timeout);

    /* Return the NOR memory status */
    if(HAL_NOR_GetStatus(&hnor1, Address, ProgramTimeout) != HAL_NOR_STATUS_SUCCESS)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }

  return ret;
}




#define NOR_BUFFER_SIZE     	((uint32_t)0x0100)
#define NOR_WRITE_READ_ADDR     ((uint32_t)0x0800)



void test_nor()
{
	NOR_IDTypeDef pNOR_ID;

	if(HAL_NOR_Read_ID(&hnor1, &pNOR_ID) != HAL_OK)
	{
		printf("NOR Test FAILED!!!\r\n");
	}
	else
	{
		printf("NOR Test.....\r\n");
		printf("  Manufacturer_Code: %04X\r\n", pNOR_ID.Manufacturer_Code);
		printf("  Device_Code1: %04X\r\n", pNOR_ID.Device_Code1);
		printf("  Device_Code2: %04X\r\n", pNOR_ID.Device_Code2);
		printf("  Device_Code3: %04X\r\n", pNOR_ID.Device_Code3);

		volatile uint16_t* nor_aRxBuffer = (volatile uint16_t *)0xD0000100;
		volatile uint16_t* nor_aTxBuffer = (volatile uint16_t *)0xD0000800;

		/*##-3- Erase NOR memory ###################################################*/
		/* Return to read mode */
		if(HAL_NOR_ReturnToReadMode(&hnor1) != HAL_OK)
		{
			printf("NOR Test: Failed HAL_NOR_ReturnToReadMode\r\n");
			Error_Handler();
		}

		if(BSP_NOR_EraseBlock(0, NOR_WRITE_READ_ADDR) != BSP_ERROR_NONE)
		{
			printf("NOR Test: Failed BSP_NOR_EraseBlock\r\n");
			Error_Handler();
		}

		/* Read back data from the NOR memory */
		if(BSP_NOR_ReadData(0, NOR_WRITE_READ_ADDR, (uint16_t *)nor_aRxBuffer, NOR_BUFFER_SIZE) != BSP_ERROR_NONE)
		{
			printf("NOR Test: Failed BSP_NOR_ReadData #1\r\n");
			Error_Handler();
		}
		/*##-4- NOR memory read/write access  ######################################*/
		/* Fill the buffer to write */
		//Fill_Buffer((uint16_t *)nor_aTxBuffer, NOR_BUFFER_SIZE, 0xD20F);
		{
			uint32_t tmpIndex = 0;

			/* Put in global buffer different values */
			for (tmpIndex = 0; tmpIndex < NOR_BUFFER_SIZE; tmpIndex++ )
			{
				nor_aTxBuffer[tmpIndex] = tmpIndex + 0xD20F;
			}
		}

		/* Write data to the NOR memory */
		if(BSP_NOR_WriteData(0, NOR_WRITE_READ_ADDR, (uint16_t *)nor_aTxBuffer, NOR_BUFFER_SIZE) != BSP_ERROR_NONE)
		{
			printf("NOR Test: Failed BSP_NOR_WriteData\r\n");
			Error_Handler();
		}

		/* Read back data from the NOR memory */
		if(BSP_NOR_ReadData(0, NOR_WRITE_READ_ADDR, (uint16_t *)nor_aRxBuffer, NOR_BUFFER_SIZE) != BSP_ERROR_NONE)
		{
			printf("NOR Test: Failed BSP_NOR_ReadData #2\r\n");
			Error_Handler();
		}
		else
		{
			int mismatch = -1;
			for (int i = 0; i < NOR_BUFFER_SIZE; i++)
			{
				printf("compare: %04X, %04X\r\n", nor_aTxBuffer[i], nor_aRxBuffer[i]);

				if (nor_aTxBuffer[i] != nor_aRxBuffer[i])
				{
					mismatch = i;
				}

				if (i > 50)
					break;
			}

			if (mismatch >= 0)
			{
				printf("NOR Test: memory compare failed at %d\r\n", mismatch);
				Error_Handler();
			}

			printf("NOR Test: SUCCESS!!\r\n");
		}
	}
}
