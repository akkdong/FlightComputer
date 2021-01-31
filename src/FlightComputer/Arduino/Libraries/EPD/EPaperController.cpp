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
	: mComm((ISPIClassInterface *)this)
{
}



void EPaperController::begin()
{
	mComm.begin(SPI1_Init);
}

void EPaperController::end()
{
	mComm.end(SPI1_Deinit);
}


void EPaperController::run()
{

}


void EPaperController::OnComplete(void* recvPtr, size_t recvLen, SPIClassEx::Error error)
{
	// controller state
	// error code
	//
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
