/*
 * EPaperController.cpp
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "EPaperController.h"





///////////////////////////////////////////////////////////////////////////////////
//

EPaperController::EPaperController()
	: mSPIDriver(this)
{
}



void EPaperController::begin()
{
	mSPIDriver.begin(SPI1_Init);
	mSPIDriver.receive_IT();
}

void EPaperController::end()
{
	mSPIDriver.abort_IT();
	mSPIDriver.end(SPI1_Deinit);
}

void EPaperController::run()
{

}


void EPaperController::OnReceive(uint8_t data)
{
	if (data == 0x55)
	{
		mSPIDriver.pTxBuffPtr = (uint8_t *)"hello";
		mSPIDriver.TxXferCount = 5;
	}
	else
	{
		Serial1.write(data);
	}
}

void EPaperController::OnError(uint32_t error)
{

}



void EPaperController::SPI1_Init(SPIClassEx* spi)
{
	spi->Instance = SPI1;
	spi->Init.Mode = SPI_MODE_SLAVE;
	spi->Init.Direction = SPI_DIRECTION_2LINES;
	spi->Init.DataSize = SPI_DATASIZE_8BIT;
	spi->Init.CLKPolarity = SPI_POLARITY_LOW;
	spi->Init.CLKPhase = SPI_PHASE_1EDGE;
	spi->Init.NSS = SPI_NSS_HARD_INPUT;
	spi->Init.FirstBit = SPI_FIRSTBIT_MSB;
	spi->Init.TIMode = SPI_TIMODE_DISABLE;
	spi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	spi->Init.CRCPolynomial = 0x0;
	spi->Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	spi->Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
	spi->Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
	spi->Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	spi->Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
	spi->Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
	spi->Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
	spi->Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
	spi->Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
	spi->Init.IOSwap = SPI_IO_SWAP_DISABLE;

	if (HAL_SPI_Init((SPI_HandleTypeDef *)spi) != HAL_OK)
	{
		Error_Handler();
	}
}

void EPaperController::SPI1_Deinit(SPIClassEx* spi)
{
}



void EPaperController::SPIDriver::receive_IT()
{
	SPI_HandleTypeDef* hspi = (SPI_HandleTypeDef *)this;

	hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
	hspi->ErrorCode = HAL_SPI_ERROR_NONE;
	hspi->pTxBuffPtr = nullptr;
	hspi->TxXferSize = 0;
	hspi->TxXferCount = 0;
	hspi->TxISR = nullptr;

	hspi->pRxBuffPtr = nullptr;
	hspi->RxXferSize = 0;
	hspi->RxXferCount = 0;
	hspi->RxISR = nullptr;

	MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TSIZE, 0);
	__HAL_SPI_ENABLE(hspi);
	// Transmit_IT
	//__HAL_SPI_ENABLE_IT(hspi, (SPI_IT_EOT | SPI_IT_TXP | SPI_IT_UDR | SPI_IT_FRE | SPI_IT_MODF | SPI_IT_TSERF));
	// Receive_IT
	//__HAL_SPI_ENABLE_IT(hspi, (SPI_IT_EOT | SPI_IT_RXP | SPI_IT_OVR | SPI_IT_FRE | SPI_IT_MODF | SPI_IT_TSERF));
	// TransmitReceive_IT
	__HAL_SPI_ENABLE_IT(hspi, (SPI_IT_EOT | SPI_IT_RXP | SPI_IT_TXP | SPI_IT_DXP | SPI_IT_UDR | SPI_IT_OVR | SPI_IT_FRE | SPI_IT_MODF | SPI_IT_TSERF));
}

void EPaperController::SPIDriver::abort_IT()
{
	SPI_HandleTypeDef* hspi = (SPI_HandleTypeDef *)this;

	hspi->State = HAL_SPI_STATE_ABORT;

	/* Disable SPI peripheral */
	__HAL_SPI_DISABLE(hspi);

	/* Disable ITs */
	__HAL_SPI_DISABLE_IT(hspi, (SPI_IT_EOT | SPI_IT_TXP | SPI_IT_RXP | SPI_IT_DXP | SPI_IT_UDR | SPI_IT_OVR | SPI_IT_FRE | SPI_IT_MODF));

	/* Clear the Status flags in the SR register */
	__HAL_SPI_CLEAR_EOTFLAG(hspi);
	__HAL_SPI_CLEAR_TXTFFLAG(hspi);

	/* Disable Tx DMA Request */
	CLEAR_BIT(hspi->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

	/* Clear the Error flags in the SR register */
	__HAL_SPI_CLEAR_OVRFLAG(hspi);
	__HAL_SPI_CLEAR_UDRFLAG(hspi);
	__HAL_SPI_CLEAR_FREFLAG(hspi);
	__HAL_SPI_CLEAR_MODFFLAG(hspi);
	__HAL_SPI_CLEAR_SUSPFLAG(hspi);

	#if (USE_SPI_CRC != 0U)
	__HAL_SPI_CLEAR_CRCERRFLAG(hspi);
	#endif /* USE_SPI_CRC */

	hspi->TxXferCount = (uint16_t)0UL;
	hspi->RxXferCount = (uint16_t)0UL;

	/* Check error during Abort procedure */
	if (hspi->ErrorCode == HAL_SPI_ERROR_ABORT)
	{
		/* return HAL_Error in case of error during Abort procedure */
		//uint32_t errorcode = HAL_ERROR;
	}
	else
	{
		/* Reset errorCode */
		hspi->ErrorCode = HAL_SPI_ERROR_NONE;
	}

    hspi->State = HAL_SPI_STATE_READY;
}

void EPaperController::SPIDriver::IRQHandler()
{
	SPI_HandleTypeDef* hspi = (SPI_HandleTypeDef *)this;

	uint32_t itsource = hspi->Instance->IER;
	uint32_t itflag   = hspi->Instance->SR;
	uint32_t trigger  = itsource & itflag;

	/* SPI in mode Transmitter and Receiver ------------------------------------*/
	if (HAL_IS_BIT_CLR(trigger, SPI_FLAG_OVR) && HAL_IS_BIT_CLR(trigger, SPI_FLAG_UDR) && HAL_IS_BIT_SET(trigger, SPI_FLAG_DXP))
	{
		this->TxISR();
		this->RxISR();
		return;
	}

	/* SPI in mode Receiver ----------------------------------------------------*/
	if (HAL_IS_BIT_CLR(trigger, SPI_FLAG_OVR) && HAL_IS_BIT_SET(trigger, SPI_FLAG_RXP) && HAL_IS_BIT_CLR(trigger, SPI_FLAG_DXP))
	{
		this->RxISR();
		return;
	}

	/* SPI in mode Transmitter -------------------------------------------------*/
	if (HAL_IS_BIT_CLR(trigger, SPI_FLAG_UDR) && HAL_IS_BIT_SET(trigger, SPI_FLAG_TXP) && HAL_IS_BIT_CLR(trigger, SPI_FLAG_DXP))
	{
		this->TxISR();
		return;
	}



	/* SPI in Error Treatment --------------------------------------------------*/
	if ((trigger & (SPI_FLAG_MODF | SPI_FLAG_OVR | SPI_FLAG_FRE | SPI_FLAG_UDR)) != 0UL)
	{
		/* SPI Overrun error interrupt occurred ----------------------------------*/
		if ((trigger & SPI_FLAG_OVR) != 0UL)
		{
			SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_OVR);
			__HAL_SPI_CLEAR_OVRFLAG(hspi);
		}

		/* SPI Mode Fault error interrupt occurred -------------------------------*/
		if ((trigger & SPI_FLAG_MODF) != 0UL)
		{
			SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_MODF);
			__HAL_SPI_CLEAR_MODFFLAG(hspi);
		}

		/* SPI Frame error interrupt occurred ------------------------------------*/
		if ((trigger & SPI_FLAG_FRE) != 0UL)
		{
			SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FRE);
			__HAL_SPI_CLEAR_FREFLAG(hspi);
		}

		/* SPI Underrun error interrupt occurred ------------------------------------*/
		if ((trigger & SPI_FLAG_UDR) != 0UL)
		{
			SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_UDR);
			__HAL_SPI_CLEAR_UDRFLAG(hspi);
		}

#if 0
		if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
		{
			/* Disable SPI peripheral */
			__HAL_SPI_DISABLE(hspi);

			/* Disable all interrupts */
			__HAL_SPI_DISABLE_IT(hspi, SPI_IT_EOT | SPI_IT_RXP | SPI_IT_TXP | SPI_IT_MODF | SPI_IT_OVR | SPI_IT_FRE | SPI_IT_UDR);

			/* Restore hspi->State to Ready */
			hspi->State = HAL_SPI_STATE_READY;

			/* Call user error callback */
			#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1UL)
				hspi->ErrorCallback(hspi);
			#else
				HAL_SPI_ErrorCallback(hspi);
			#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
		}
#endif
	}
}

void EPaperController::SPIDriver::RxISR()
{
	SPI_HandleTypeDef* hspi = (SPI_HandleTypeDef *)this;

	/* Receive data in 8 Bit mode */
	volatile uint8_t data = (*(__IO uint8_t *)&hspi->Instance->RXDR);
	mControllerPtr->OnReceive(data);
}

void EPaperController::SPIDriver::TxISR()
{
	SPI_HandleTypeDef* hspi = (SPI_HandleTypeDef *)this;

	if (hspi->TxXferCount > 0 && hspi->pTxBuffPtr)
	{
		*(__IO uint8_t *)&hspi->Instance->TXDR = *((uint8_t *)hspi->pTxBuffPtr);
		hspi->pTxBuffPtr += sizeof(uint8_t);
		hspi->TxXferCount--;

		if (hspi->TxXferCount == 0)
			hspi->pTxBuffPtr = nullptr;
	}
	else
	{
		// send emtpy-data
		*(__IO uint8_t *)&hspi->Instance->TXDR = 0x00;
	}
}
