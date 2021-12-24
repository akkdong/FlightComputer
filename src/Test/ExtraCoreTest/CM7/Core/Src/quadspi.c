/*
 * quadspi.c
 *
 *  Created on: 2021. 12. 24.
 *      Author: akkdong
 */


#include "main.h"
#include "quadspi.h"
#include <stdio.h>


#define BUFFERSIZE                 			(COUNTOF(aTxBuffer) - 1)
#define COUNTOF(__BUFFER__)        			(sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))


extern QSPI_HandleTypeDef hqspi;


__IO uint8_t CmdCplt, RxCplt, TxCplt, StatusMatch, TimeOut;
/* Buffer used for transmission */
uint8_t aTxBuffer[] = " ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT****  ****QSPI communication based on IT**** ";

/* Buffer used for reception */
uint8_t aRxBuffer[BUFFERSIZE];



/**
  * @brief  Command completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_CmdCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  CmdCplt++;
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  RxCplt++;
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
  TxCplt++;
}

/**
  * @brief  Status Match callbacks
  * @param  hqspi: QSPI handle
  * @retval None
  */
void HAL_QSPI_StatusMatchCallback(QSPI_HandleTypeDef *hqspi)
{
  StatusMatch++;
}


/**
  * @brief  This function send a Write Enable and wait it is effective.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef     sCommand;
  QSPI_AutoPollingTypeDef sConfig;

  /* Enable write operations ------------------------------------------ */
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = WRITE_ENABLE_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_NONE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }

  /* Configure automatic polling mode to wait for write enabling ---- */
  sConfig.Match           = 0x02;
  sConfig.Mask            = 0x02;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  sCommand.Instruction    = READ_STATUS_REG_CMD;
  sCommand.DataMode       = QSPI_DATA_1_LINE;

  if (HAL_QSPI_AutoPolling(hqspi, &sCommand, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function read the SR of the memory and wait the EOP.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void QSPI_AutoPollingMemReady(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef     sCommand;
  QSPI_AutoPollingTypeDef sConfig;

  /* Configure automatic polling mode to wait for memory ready ------ */
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = READ_STATUS_REG_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_1_LINE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  sConfig.Match           = 0x00;
  sConfig.Mask            = 0x01;
  sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
  sConfig.StatusBytesSize = 1;
  sConfig.Interval        = 0x10;
  sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_QSPI_AutoPolling_IT(hqspi, &sCommand, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function configure the dummy cycles on memory side.
  * @param  hqspi: QSPI handle
  * @retval None
  */
void QSPI_DummyCyclesCfg(QSPI_HandleTypeDef *hqspi)
{
  QSPI_CommandTypeDef sCommand;
  uint8_t reg;

  /* Read Volatile Configuration register --------------------------- */
  sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
  sCommand.Instruction       = READ_VOL_CFG_REG_CMD;
  sCommand.AddressMode       = QSPI_ADDRESS_NONE;
  sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  sCommand.DataMode          = QSPI_DATA_1_LINE;
  sCommand.DummyCycles       = 0;
  sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
  sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
  sCommand.NbData            = 1;

  if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_QSPI_Receive(hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }

  /* Enable write operations ---------------------------------------- */
  QSPI_WriteEnable(hqspi);

  /* Write Volatile Configuration register (with new dummy cycles) -- */
  sCommand.Instruction = WRITE_VOL_CFG_REG_CMD;
  MODIFY_REG(reg, 0xF0, (DUMMY_CLOCK_CYCLES_READ_QUAD << POSITION_VAL(0xF0)));

  if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_QSPI_Transmit(hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
}




void test_quadspi()
{
	QSPI_CommandTypeDef sCommand;
	uint32_t address = 0;
	uint16_t index;
	__IO uint8_t step = 0;

	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	while (1)
	{
		switch(step)
		{
		case 0:
			printf("Start QSPI Flash Test....\r\n");
			CmdCplt = 0;

			/* Initialize Reception buffer --------------------------------------- */
			for (index = 0; index < BUFFERSIZE; index++)
			{
				aRxBuffer[index] = 0;
			}

			/* Enable write operations ------------------------------------------- */
			QSPI_WriteEnable(&hqspi);

			/* Erasing Sequence -------------------------------------------------- */
			sCommand.Instruction = SECTOR_ERASE_CMD;
			sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
			sCommand.Address     = address;
			sCommand.DataMode    = QSPI_DATA_NONE;
			sCommand.DummyCycles = 0;

			if (HAL_QSPI_Command_IT(&hqspi, &sCommand) != HAL_OK)
			{
				Error_Handler();
			}

			step++;
			printf("Pass Step #%d\r\n", step);
			break;

		case 1:
			if(CmdCplt != 0)
			{
				CmdCplt = 0;
				StatusMatch = 0;

				/* Configure automatic polling mode to wait for end of erase ------- */
				QSPI_AutoPollingMemReady(&hqspi);

				step++;
				printf("Pass Step #%d\r\n", step);
			}
			break;

		case 2:
			if(StatusMatch != 0)
			{
				StatusMatch = 0;
				TxCplt = 0;

				/* Enable write operations ----------------------------------------- */
				QSPI_WriteEnable(&hqspi);

				/* Writing Sequence ------------------------------------------------ */
				sCommand.Instruction = QUAD_IN_FAST_PROG_CMD;
				sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
				sCommand.DataMode    = QSPI_DATA_4_LINES;
				sCommand.NbData      = BUFFERSIZE;

				if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
				{
					Error_Handler();
				}

				if (HAL_QSPI_Transmit_IT(&hqspi, aTxBuffer) != HAL_OK)
				{
					Error_Handler();
				}

				step++;
				printf("Pass Step #%d\r\n", step);
			}
			break;

		case 3:
			if(TxCplt != 0)
			{
				TxCplt = 0;
				StatusMatch = 0;

				/* Configure automatic polling mode to wait for end of program ----- */
				QSPI_AutoPollingMemReady(&hqspi);

				step++;
				printf("Pass Step #%d\r\n", step);
			}
			break;

		case 4:
			if(StatusMatch != 0)
			{
				StatusMatch = 0;
				RxCplt = 0;

				/* Configure Volatile Configuration register (with new dummy cycles) */
				QSPI_DummyCyclesCfg(&hqspi);

				/* Reading Sequence ------------------------------------------------ */
				sCommand.Instruction = QUAD_OUT_FAST_READ_CMD;
				sCommand.DummyCycles = DUMMY_CLOCK_CYCLES_READ_QUAD;

				if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
				{
					printf("FAILED on Step #%d: FAST_READ_CMD\r\n", step);
					Error_Handler();
				}

				if (HAL_QSPI_Receive_IT(&hqspi, aRxBuffer) != HAL_OK)
					{
					printf("FAILED on Step #%d: Receive_IT\r\n", step);
					Error_Handler();
				}
				step++;
			}
			break;

		case 5:
			if (RxCplt != 0)
			{
				RxCplt = 0;

				/* Result comparison ----------------------------------------------- */
				for (index = 0; index < BUFFERSIZE; index++)
				{
					if (aRxBuffer[index] != aTxBuffer[index])
					{
						printf("FAILED on Step #%d: Mismatch reading data\r\n", step);
						while (1)
						{
							HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
							HAL_Delay(100);
						}
					}
				}

				address += QSPI_PAGE_SIZE;
				if(address >= QSPI_END_ADDR)
				{
					address = 0;
				}
				printf("Finished QSPI Flash Test: SUCCESS!!\r\n");
				step = 0;
				while (1)
				{
					HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
					HAL_Delay(400);
				}
			}
			break;

		default :
			Error_Handler();
			break;
		}
	}
}
