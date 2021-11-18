/*
 * EPaperController.cpp
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "EPaperController.h"

#define EPD_SET_BUSY()			do { GPIOC->BSRR = (0b1000000000000000); } while (0)
#define EPD_RESET_BUSY()		do { GPIOC->BSRR = (0b1000000000000000 << 16); } while (0)

#define EPD_IS_COMMAND()		(GPIOC->IDR & 0b0100000000000000)
#define EPD_IS_BUSY()			(GPIOC->IDR & 0b1000000000000000)



///////////////////////////////////////////////////////////////////////////////////
//

EPaperController::EPaperController()
	: mSPIDriver(this)
//	, mDisp(DISPLAY_1BPP)
	, mLastCommand(UNKNOWN)
	, mState(UNINIT)
	, mTimestamp(0)
{
}



void EPaperController::begin()
{
	EPD_SET_BUSY();
	pinMode(EINK_BUSY, OUTPUT);
	pinMode(EINK_CMD, INPUT);

	mLastCommand = UNKNOWN;
	mState = WAIT_COMMAND;

	mSPIDriver.begin(SPI1_Init);
	mSPIDriver.receive_IT();

	EPD_RESET_BUSY();
}

void EPaperController::end()
{
	EPD_SET_BUSY();
	mSPIDriver.abort_IT();
	mSPIDriver.end(SPI1_Deinit);

	mState = UNINIT;
}

void EPaperController::run()
{
	if (mState == WAIT_COMMAND)
	{
		// NOP
	}
	else if (mState == PROCESSING)
	{
		switch (mLastCommand)
		{
		case POWER_ON : 			// 0xA1
			// mDisp.powerOn();
			mState = WAIT_COMMAND;
			EPD_RESET_BUSY();
			break;
		case POWER_OFF : 			// 0xA2
			// mDisp.powerOff();
			mState = WAIT_COMMAND;
			EPD_RESET_BUSY();
			break;
		case REFRESH : 				// 0xB1
			// mDisp.refresh();
			mState = WAIT_COMMAND;
			EPD_RESET_BUSY();
			break;
		case CLEAR : 				// 0xB2
			// mDisp.clear();
			mState = WAIT_COMMAND;
			EPD_RESET_BUSY();
			break;
		case GET_DISPLAY : 			// 0x21
			// Fill display info to buffer
			// set send buffer
			mTimestamp = millis();
			mState = SENDING;
			mSPIDriver.transmit_IT((uint8_t *)"\x80\x70\x71\x72\x73", 5);
			EPD_RESET_BUSY();
			Serial1.println("start sending...");
			break;
		case SET_WINDOW : 			// 0x22
			mRecvPtr = &mTemp[0];
			mRecvLen = 0;
			mRecvExpect = 5;
			mTimestamp = millis();
			mState = RECEIVING;
			EPD_RESET_BUSY();
			Serial1.println("start receiving...");
			break;
		case START_DATA_TRANSMIT : 	// 0x23
			//mRecvPtr = (volatile uint8_t *)mDisp.getOffline()->getPtr();
			//mRecvLen = mDisp.getOffline()->getSize();
			mRecvExpect = mRecvLen;
			mTimestamp = millis();
			mState = RECEIVING;
			EPD_RESET_BUSY();
			break;
		case STOP_DATA_TRANSMIT : 	// 0x24
			if (mState == RECEIVING)
			{
				// update display
				// ...
			}

			mState = WAIT_COMMAND;
			EPD_RESET_BUSY();
			break;
		default:
			break;
		}
	}
	else if (mState == RECEIVING)
	{
		if (mRecvLen < mRecvExpect)
		{
			// check timeout
			if ((millis() - mTimestamp) > 1000)
			{
				mState = WAIT_COMMAND;
				EPD_RESET_BUSY();
				Serial1.println("receiving timeout!");
			}
		}
		else // receive complete
		{
			//
			switch (mLastCommand)
			{
			case SET_WINDOW:
				// update window-info
				for (uint32_t i = 0; i < mRecvLen; i++)
					Serial1.printf("RX[%02x]\r\n", mTemp[i]);
				break;
			case START_DATA_TRANSMIT:
				//mDisp.swap(); // swap on/offline buffer & refresh
				//mDisp.refresh();
				break;
			default:
				break;
			}

			mState = WAIT_COMMAND;
			EPD_RESET_BUSY();
		}
	}
	else if (mState == SENDING)
	{
		// check timeout
		if ((millis() - mTimestamp) > 1000)
		{
			mState = WAIT_COMMAND;
			mSPIDriver.stopTransmit();
			EPD_RESET_BUSY();
			Serial1.println("sending timeout!");
		}
	}
}


void EPaperController::OnReceive(uint8_t data)
{
	if (EPD_IS_BUSY())
		return; // IGNORE ALL

	if (EPD_IS_COMMAND())
	{
		switch (data)
		{
		case POWER_ON : 			// 0xA1
		case POWER_OFF : 			// 0xA2
		case REFRESH : 				// 0xB1
		case CLEAR : 				// 0xB2
		case GET_DISPLAY : 			// 0x21
		case SET_WINDOW : 			// 0x22
		case START_DATA_TRANSMIT : 	// 0x23
		case STOP_DATA_TRANSMIT : 	// 0x24
			EPD_SET_BUSY();
			mState = PROCESSING;
			mLastCommand = static_cast<EPDC_Command>(data);
			break;
		default:
			// NOP
			break;
		}
	}
	else
	{
		if (mState == RECEIVING && mRecvLen < mRecvExpect && mRecvPtr)
		{
			*mRecvPtr++ = data;
			mRecvLen++;

			if (mRecvLen == mRecvExpect)
				EPD_SET_BUSY();
		}
	}
}

void EPaperController::OnSendComplete()
{
	if (mState == SENDING)
	{
		mState = WAIT_COMMAND;
		EPD_RESET_BUSY();
		Serial1.println("sending complete!");
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
	this->State = HAL_SPI_STATE_BUSY_RX;
	this->ErrorCode = HAL_SPI_ERROR_NONE;
	this->pTxBuffPtr = nullptr;
	this->TxXferSize = 0;
	this->TxXferCount = 0;
	this->TxISR = nullptr;

	this->pRxBuffPtr = nullptr;
	this->RxXferSize = 0;
	this->RxXferCount = 0;
	this->RxISR = nullptr;

	MODIFY_REG(this->Instance->CR2, SPI_CR2_TSIZE, 0);
	__HAL_SPI_ENABLE(this);
	__HAL_SPI_ENABLE_IT(this, (SPI_IT_RXP | SPI_IT_OVR));

	// Transmit_IT
	//__HAL_SPI_ENABLE_IT(this, (SPI_IT_EOT | SPI_IT_TXP | SPI_IT_UDR | SPI_IT_FRE | SPI_IT_MODF | SPI_IT_TSERF));
	// Receive_IT
	//__HAL_SPI_ENABLE_IT(this, (SPI_IT_EOT | SPI_IT_RXP | SPI_IT_OVR | SPI_IT_FRE | SPI_IT_MODF | SPI_IT_TSERF));
	// TransmitReceive_IT
	//__HAL_SPI_ENABLE_IT(this, (SPI_IT_EOT | SPI_IT_RXP | SPI_IT_TXP | SPI_IT_DXP | SPI_IT_UDR | SPI_IT_OVR | SPI_IT_FRE | SPI_IT_MODF | SPI_IT_TSERF));
}

void EPaperController::SPIDriver::abort_IT()
{
	this->State = HAL_SPI_STATE_ABORT;

	/* Disable SPI peripheral */
	__HAL_SPI_DISABLE(this);

	/* Disable ITs */
	__HAL_SPI_DISABLE_IT(this, (SPI_IT_EOT | SPI_IT_TXP | SPI_IT_RXP | SPI_IT_DXP | SPI_IT_UDR | SPI_IT_OVR | SPI_IT_FRE | SPI_IT_MODF));

	/* Clear the Status flags in the SR register */
	__HAL_SPI_CLEAR_EOTFLAG(this);
	__HAL_SPI_CLEAR_TXTFFLAG(this);

	/* Disable Tx DMA Request */
	CLEAR_BIT(this->Instance->CFG1, SPI_CFG1_TXDMAEN | SPI_CFG1_RXDMAEN);

	/* Clear the Error flags in the SR register */
	__HAL_SPI_CLEAR_OVRFLAG(this);
	__HAL_SPI_CLEAR_UDRFLAG(this);
	__HAL_SPI_CLEAR_FREFLAG(this);
	__HAL_SPI_CLEAR_MODFFLAG(this);
	__HAL_SPI_CLEAR_SUSPFLAG(this);

	#if (USE_SPI_CRC != 0U)
	__HAL_SPI_CLEAR_CRCERRFLAG(this);
	#endif /* USE_SPI_CRC */

	this->TxXferCount = (uint16_t)0UL;
	this->RxXferCount = (uint16_t)0UL;

	/* Check error during Abort procedure */
	if (this->ErrorCode == HAL_SPI_ERROR_ABORT)
	{
		/* return HAL_Error in case of error during Abort procedure */
		//uint32_t errorcode = HAL_ERROR;
	}
	else
	{
		/* Reset errorCode */
		this->ErrorCode = HAL_SPI_ERROR_NONE;
	}

	this->State = HAL_SPI_STATE_READY;
}

void EPaperController::SPIDriver::transmit_IT(uint8_t* bufPtr, uint16_t bufLen)
{
	this->pTxBuffPtr = bufPtr;
	this->TxXferSize = bufLen;
	this->TxXferCount = bufLen;

	__HAL_SPI_ENABLE_IT(this, (SPI_IT_TXP | SPI_IT_UDR));
}

void EPaperController::SPIDriver::stopTransmit()
{
	__HAL_SPI_DISABLE_IT(this, (SPI_IT_TXP | SPI_IT_UDR));

	this->pTxBuffPtr = nullptr;
	this->TxXferSize = 0;
	this->TxXferCount = 0;
}

void EPaperController::SPIDriver::IRQHandler()
{
	uint32_t itsource = this->Instance->IER;
	uint32_t itflag   = this->Instance->SR;
	uint32_t trigger  = itsource & itflag;

#if 0
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
#else
	if (HAL_IS_BIT_SET(trigger, SPI_FLAG_RXP))
	{
		this->RxHandler();
	}
	if (HAL_IS_BIT_SET(trigger, SPI_FLAG_TXP))
	{
		this->TxHandler();
	}
#endif


	/* SPI in Error Treatment --------------------------------------------------*/
	if ((trigger & (SPI_FLAG_MODF | SPI_FLAG_OVR | SPI_FLAG_FRE | SPI_FLAG_UDR)) != 0UL)
	{
		/* SPI Overrun error interrupt occurred ----------------------------------*/
		if ((trigger & SPI_FLAG_OVR) != 0UL)
		{
			SET_BIT(this->ErrorCode, HAL_SPI_ERROR_OVR);
			__HAL_SPI_CLEAR_OVRFLAG(this);
		}

		/* SPI Mode Fault error interrupt occurred -------------------------------*/
		if ((trigger & SPI_FLAG_MODF) != 0UL)
		{
			SET_BIT(this->ErrorCode, HAL_SPI_ERROR_MODF);
			__HAL_SPI_CLEAR_MODFFLAG(this);
		}

		/* SPI Frame error interrupt occurred ------------------------------------*/
		if ((trigger & SPI_FLAG_FRE) != 0UL)
		{
			SET_BIT(this->ErrorCode, HAL_SPI_ERROR_FRE);
			__HAL_SPI_CLEAR_FREFLAG(this);
		}

		/* SPI Underrun error interrupt occurred ------------------------------------*/
		if ((trigger & SPI_FLAG_UDR) != 0UL)
		{
			SET_BIT(this->ErrorCode, HAL_SPI_ERROR_UDR);
			__HAL_SPI_CLEAR_UDRFLAG(this);
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

void EPaperController::SPIDriver::RxHandler()
{
	/* Receive data in 8 Bit mode */
	volatile uint8_t data = *((__IO uint8_t *)&this->Instance->RXDR);
	mControllerPtr->OnReceive(data);
}

void EPaperController::SPIDriver::TxHandler()
{
	if (/*!EPD_IS_BUSY() &&*/ this->TxXferCount > 0 && this->pTxBuffPtr)
	{
		uint8_t data = *((uint8_t *)this->pTxBuffPtr++);
		*((__IO uint8_t *)&this->Instance->TXDR) = data;
		Serial1.printf("<%d>: %02X\r\n", this->TxXferCount, data);
		this->TxXferCount--;

		if (this->TxXferCount == 0)
		{
			this->stopTransmit();
			mControllerPtr->OnSendComplete();
		}
	}
	else
	{
		// send dummy-data
		uint8_t data = 0x00;
		*((__IO uint8_t *)&this->Instance->TXDR) = data;
		Serial1.printf("[%02X]\r\n", data);
	}
}
