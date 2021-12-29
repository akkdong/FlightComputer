/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define ARDUINO_MAIN
#include "Arduino.h"

/**
  * @brief  Configure the MPU attributes as Not cacheable for D3 SRAM.
  * @note   The Base Address is D3_SRAM_BASE.
  *         The Region Size is 64KB.
  * @param  None
  * @retval None
  */

extern "C" {

#if (__CORTEX_M == 0x07U)
	static void MPU_Config(void)
	{
	  MPU_Region_InitTypeDef MPU_InitStruct;

	  /* Disable the MPU */
	  HAL_MPU_Disable();

	  /* Configure the MPU attributes as WT for SDRAM */
	  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	  MPU_InitStruct.BaseAddress = D3_SRAM_BASE;
	  MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
	  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	  MPU_InitStruct.SubRegionDisable = 0x00;
	  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);

	  /* Enable the MPU */
	  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
	}
#endif
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need HAL may fail.
__attribute__((constructor(101))) void premain()
{

  // Required by FreeRTOS, see http://www.freertos.org/RTOS-Cortex-M3-M4.html
#ifdef NVIC_PRIORITYGROUP_4
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
#endif
#if (__CORTEX_M == 0x07U)

  MPU_Config();

  // Defined in CMSIS core_cm7.h
#ifndef I_CACHE_DISABLED
  SCB_EnableICache();
#endif
#ifndef D_CACHE_DISABLED
  SCB_EnableDCache();
#endif
#endif

  //init();
}

/*
 * \brief Main entry point of Arduino application
 */
int main(void)
{
  init();
  initVariant();

  setup();

  for (;;) {
#if defined(CORE_CALLBACK)
    CoreCallback();
#endif
    loop();
    serialEventRun();
  }

  return 0;
}
