// sdram_drv.c
//

#include "sdram_drv.h"

/**
  * @brief  Perform the SDRAM exernal memory inialization sequence
  * @param  hsdram: SDRAM handle
  * @param  &command: Pointer to SDRAM command structure
  * @retval None
  */
void SDRAM_Do_InitializeSequence(SDRAM_HandleTypeDef *hsdram)
{
  FMC_SDRAM_CommandTypeDef command;
  __IO uint32_t tmpmrd =0;

  /* Step 3:  Configure a clock configuration enable command */
  command.CommandMode 			 = FMC_SDRAM_CMD_CLK_ENABLE;
  command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 1;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, &command, 0x1000);

  /* Step 4: Insert 100 ms delay */
  HAL_Delay(100);

  /* Step 5: Configure a PALL (precharge all) command */
  command.CommandMode 			 = FMC_SDRAM_CMD_PALL;
  command.CommandTarget 	     = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 1;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, &command, 0x1000);

  /* Step 6 : Configure a Auto-Refresh command */
  command.CommandMode 			 = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  command.CommandTarget 		 = FMC_SDRAM_CMD_TARGET_BANK2;
  command.AutoRefreshNumber 	 = 4;
  command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, &command, 0x1000);

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
  HAL_SDRAM_SendCommand(hsdram, &command, 0x1000);

  /* Step 8: Set the refresh rate counter */
  /* (15.62 us x Freq) - 20 */
  /* Set the device refresh counter */
  HAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT);
}
