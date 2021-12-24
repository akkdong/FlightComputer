/*
 * sdram.c
 *
 *  Created on: 2021. 12. 24.
 *      Author: akkdong
 */


#include "main.h"
#include "sdram.h"
#include "is42s32800g.h"
#include <stdio.h>


extern SDRAM_HandleTypeDef hsdram1;


uint32_t aTable[1024];

__IO uint32_t uwTabAddr;
__IO uint32_t MSPValue = 0;



/**
  * @brief  Perform the SDRAM exernal memory inialization sequence
  * @param  hsdram: SDRAM handle
  * @param  &command: Pointer to SDRAM command structure
  * @retval None
  */
HAL_StatusTypeDef SDRAM_Do_InitializeSequence()
{
  FMC_SDRAM_CommandTypeDef command;
  HAL_StatusTypeDef result;
  __IO uint32_t tmpmrd =0;

  /* Step 3:  Configure a clock configuration enable command */
  command.CommandMode 			 = FMC_SDRAM_CMD_CLK_ENABLE;
  command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 1;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  result = HAL_SDRAM_SendCommand(&hsdram1, &command, 0x1000);
  if (result != HAL_OK)
	  return result;

  /* Step 4: Insert 100 ms delay */
  HAL_Delay(100);

  /* Step 5: Configure a PALL (precharge all) command */
  command.CommandMode 			 = FMC_SDRAM_CMD_PALL;
  command.CommandTarget 	     = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 1;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  result = HAL_SDRAM_SendCommand(&hsdram1, &command, 0x1000);
  if (result != HAL_OK)
	  return result;

  /* Step 6 : Configure a Auto-Refresh command */
  command.CommandMode 			 = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 4;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  result = HAL_SDRAM_SendCommand(&hsdram1, &command, 0x1000);
  if (result != HAL_OK)
	  return result;

  /* Step 7: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 1;
  command.ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  result = HAL_SDRAM_SendCommand(&hsdram1, &command, 0x1000);
  if (result != HAL_OK)
	  return result;

  /* Step 8: Set the refresh rate counter */
  /* (15.62 us x Freq) - 20 */
  /* Set the device refresh counter */
  result = HAL_SDRAM_ProgramRefreshRate(&hsdram1, REFRESH_COUNT);
  if (result != HAL_OK)
	  return result;

  return HAL_OK;
}

/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the buffer to fill
  * @param  uwBufferLenght: size of the buffer to fill
  * @param  uwOffset: first value to fill on the buffer
  * @retval None
  */
static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLength, uint16_t uwOffset)
{
  uint16_t tmpIndex = 0;

  /* Put in global buffer different values */
  for (tmpIndex = 0; tmpIndex < uwBufferLength; tmpIndex++ )
  {
    pBuffer[tmpIndex] = tmpIndex + uwOffset;
  }
}



void test_sdram()
{


	// initialize SDRAM
	HAL_Delay(1000);
	{
		//int32_t ret;
		static IS42S32800G_Context_t pRegMode;

		/* External memory mode register configuration */
		pRegMode.TargetBank      = FMC_SDRAM_CMD_TARGET_BANK2;
		pRegMode.RefreshMode     = IS42S32800G_AUTOREFRESH_MODE_CMD;
		pRegMode.RefreshRate     = REFRESH_COUNT;
		pRegMode.BurstLength     = IS42S32800G_BURST_LENGTH_1;
		pRegMode.BurstType       = IS42S32800G_BURST_TYPE_SEQUENTIAL;
		pRegMode.CASLatency      = IS42S32800G_CAS_LATENCY_3;
		pRegMode.OperationMode   = IS42S32800G_OPERATING_MODE_STANDARD;
		pRegMode.WriteBurstMode  = IS42S32800G_WRITEBURST_MODE_SINGLE;

		/* SDRAM initialization sequence */
		if(IS42S32800G_Init(&hsdram1, &pRegMode) != IS42S32800G_OK)
		{
			printf("SDRAM initialize failed!!\r\n");
		}
		else
		{
			printf("SDRAM initialized\r\n");

			volatile uint32_t* ptr = (volatile uint32_t *)0xD0000000;
			Fill_Buffer((uint32_t *)ptr, 1024, 0);

			uint32_t data1 = *((volatile uint32_t *)0xD0000010);
			uint32_t data2 = *((volatile uint32_t *)0xD0000014);
			uint8_t b1 = *((volatile uint8_t *)0xD0000018);
			uint8_t b2 = *((volatile uint8_t *)0xD0000019);
			uint8_t b3 = *((volatile uint8_t *)0xD000001A);
			uint8_t b4 = *((volatile uint8_t *)0xD000001B);
			printf("%lu, %lu, %u, %u, %u, %u\r\n", data1, data2, b1, b2, b3, b4);

			const char* str = (const char *)"SDRAM Test!!";
			volatile char* dst = (volatile char *)0xD0001000;
			while(*str)
			*dst++ = *str++;
			*dst = '\0';

			volatile char* src = (volatile char *)0xD0001000;
			for (int i = 0; i < 10; i++)
			printf("%X ", src[i]);
			printf("\r\n");

			printf("%s\r\n", src);
		}

	}
}

void test_sdram_alt()
{
	if (SDRAM_Do_InitializeSequence() == HAL_OK)
	{
		printf("SDRAM initialized\r\n");

		volatile uint32_t* ptr = (volatile uint32_t *)0xD0000000;
		Fill_Buffer((uint32_t *)ptr, 1024, 0);

		const char* str = (const char *)"SDRAM Test!!";
		volatile char* dst = (volatile char *)0xD0001000;
		while(*str)
			*dst++ = *str++;

		volatile char* src = (volatile char *)0xD0001000;
		for (int i = 0; i < 10; i++)
			printf("%X ", *src++);
		printf("\r\n");
	}
	else
	{
		printf("SDRAM initialize failed!!\r\n");
	}
}


void test_sdram_boot()
{
	/*##-1- Fill the buffer in the SDRAM device ##########################################*/
	Fill_Buffer(aTable, 1024, 0);

	/*##-2- Read address of the buffer and stack pointer address ########################*/
	uwTabAddr = (uint32_t)aTable; /* should be above 0xD0000000 */

	/* Get main stack pointer value */
	MSPValue = __get_MSP(); /* should be above 0xD0000000 */

	/*##-3- Activate LEDs pending on read values ########################################*/
	if ((uwTabAddr >= SDRAM_ADDRESS) && (MSPValue >= SDRAM_ADDRESS))
	{
	printf("SDRAM Test: PASSED!!\r\n");
	}
	else
	{
	  printf("SDRAM Test: FAILED!!\r\n");
	}

	printf("   uwTabAddr = 0X%x\r\n", (unsigned int)uwTabAddr);
	printf("   MSPValue = 0X%x\r\n", (unsigned int)MSPValue);
}
