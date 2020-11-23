// SPI.cpp
//

#include "SPI.h"




/////////////////////////////////////////////////////////////////////////////
//

SPIEInk* SPIEInk::RunningRef = nullptr;


extern "C" void SPI4_IRQHandler(void)
{
	if (!SPIEInk::RunningRef)
		return;

	SPIEInk::RunningRef->IRQHandler();
}


HAL_StatusTypeDef MX_SPI4_InitEx(SPIBase* device)
{
	//
	device->Instance = SPI4;

	//
	device->Init.Mode = SPI_MODE_SLAVE;
	device->Init.Direction = SPI_DIRECTION_2LINES;
	device->Init.DataSize = SPI_DATASIZE_8BIT;
	device->Init.CLKPolarity = SPI_POLARITY_LOW;
	device->Init.CLKPhase = SPI_PHASE_1EDGE;
	device->Init.NSS = SPI_NSS_HARD_INPUT;
	device->Init.FirstBit = SPI_FIRSTBIT_MSB;
	device->Init.TIMode = SPI_TIMODE_DISABLE;
	device->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	device->Init.CRCPolynomial = 10;

	if (HAL_SPI_Init(device) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}



/////////////////////////////////////////////////////////////////////////////
//

SPIEInk::SPIEInk()
{
	tx_front = tx_rear = 0;
	rx_front = rx_rear = 0;
}

SPIEInk::~SPIEInk()
{
}

HAL_StatusTypeDef SPIEInk::begin(HAL_StatusTypeDef (* InitProc)(SPIBase* device))
{
	if (SPIEInk::RunningRef != nullptr)
		return HAL_BUSY;

	if (InitProc(this) != HAL_OK)
		return HAL_ERROR;

	// initialize DC, BUSY GPIO
	// __HAL_RCC_GPIOX_CLK_ENABLE()
	//
	// GPIO_InitStruct.xxx = yyy;
	// HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

	SPIEInk::RunningRef = this;

	// Enable TXE, RXNE and ERR interrupt
	__HAL_SPI_ENABLE_IT(this, (/*SPI_IT_TXE |*/ SPI_IT_RXNE /*| SPI_IT_ERR*/));

	// Check if the SPI is already enabled
	if ((this->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
	{
		// Enable SPI peripheral
		__HAL_SPI_ENABLE(this);
	}

	return HAL_OK;
}

void SPIEInk::end()
{
}

void SPIEInk::run()
{
}


void SPIEInk::IRQHandler()
{
	uint32_t itsource = this->Instance->CR2;
	uint32_t itflag   = this->Instance->SR;

	// SPI in mode Receiver
	//if ((SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) == RESET) &&
	//	(SPI_CHECK_FLAG(itflag, SPI_FLAG_RXNE) != RESET) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_RXNE) != RESET))
	if ((itsource & SPI_IT_RXNE))
	{
		RxISR();
		return;
	}

	// SPI in mode Transmitter
	//if ((SPI_CHECK_FLAG(itflag, SPI_FLAG_TXE) != RESET) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_TXE) != RESET))
	if ((SPI_CHECK_FLAG(itflag, SPI_FLAG_TXE) != RESET))
	{
		TxISR();
		return;
	}

	// SPI in Error Treatment
	if (((SPI_CHECK_FLAG(itflag, SPI_FLAG_MODF) != RESET) || (SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) != RESET) ||
		(SPI_CHECK_FLAG(itflag, SPI_FLAG_FRE) != RESET)) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_ERR) != RESET))
	{
		// SPI Overrun error interrupt occurred
		if (SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) != RESET)
		{
			__HAL_SPI_CLEAR_OVRFLAG(this);
		}

		// SPI Mode Fault error interrupt occurred
		if (SPI_CHECK_FLAG(itflag, SPI_FLAG_MODF) != RESET)
		{
			__HAL_SPI_CLEAR_MODFFLAG(this);
		}

		/* SPI Frame error interrupt occurred ------------------------------------*/
		if (SPI_CHECK_FLAG(itflag, SPI_FLAG_FRE) != RESET)
		{
			__HAL_SPI_CLEAR_FREFLAG(this);
		}
	}
}

extern UART_HandleTypeDef huart1;
#include "UART.h"
extern UARTDevice huart5;

void SPIEInk::TxISR()
{
	__HAL_SPI_DISABLE_IT(this, (SPI_IT_TXE | SPI_IT_ERR));
}

void SPIEInk::RxISR()
{
	uint8_t data = this->Instance->DR;
	//HAL_UART_Transmit(&huart1, &data, 1, 1000);
	huart5.write(data);
}
