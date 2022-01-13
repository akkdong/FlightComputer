/*
 * BatteryPower.cpp
 *
 *  Created on: 2022. 1. 1.
 *      Author: akkdong
 */

#include "BatteryPower.h"



//////////////////////////////////////////////////////////////////////////////////////////
//

BatteryPower::BatteryPower()
{

}


int BatteryPower::begin()
{
#if 0
	  ADC_ChannelConfTypeDef sConfig = {0};

	  /* USER CODE BEGIN ADC3_Init 1 */

	  /* USER CODE END ADC3_Init 1 */
	  /** Common config
	  */
	  hadc3.Instance = ADC3;
	  hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;
	  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
	  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
	  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	  hadc3.Init.LowPowerAutoWait = DISABLE;
	  hadc3.Init.ContinuousConvMode = DISABLE;
	  hadc3.Init.NbrOfConversion = 1;
	  hadc3.Init.DiscontinuousConvMode = DISABLE;
	  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  hadc3.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DFSDM;
	  hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	  hadc3.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
	  hadc3.Init.OversamplingMode = ENABLE;
	  hadc3.Init.Oversampling.Ratio = 1;
	  hadc3.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_NONE;
	  hadc3.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
	  hadc3.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;
	  if (HAL_ADC_Init(&hadc3) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /** Configure Regular Channel
	  */
	  sConfig.Channel = ADC_CHANNEL_1;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_810CYCLES_5; // ADC_SAMPLETIME_8CYCLES_5;
	  sConfig.SingleDiff = ADC_SINGLE_ENDED;
	  sConfig.OffsetNumber = ADC_OFFSET_NONE;
	  sConfig.Offset = 0;
	  sConfig.OffsetSignedSaturation = DISABLE;
	  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
#endif

	  return 0;
}

void BatteryPower::end()
{

}

void BatteryPower::update()
{

}

float BatteryPower::getVoltage()
{
	return 0.0;
}

int BatteryPower::getPercentage()
{
	return 0;
}
