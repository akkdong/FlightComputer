// Util.cpp
//

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "UART.h"




/////////////////////////////////////////////////////////////////////////////
// class UARTRepository

class UARTRepository
{
protected:
	UARTRepository() {}

public:

#if SUPPORT_UART1
	static UARTDevice* Uart1Ref;
#endif
#if SUPPORT_UART2
	static UARTDevice* Uart2Ref;
#endif
#if SUPPORT_UART3
	static UARTDevice* Uart3Ref;
#endif
#if SUPPORT_UART4
	static UARTDevice* Uart4Ref;
#endif
#if SUPPORT_UART5
	static UARTDevice* Uart5Ref;
#endif
#if SUPPORT_UART6
	static UARTDevice* Uart6Ref;
#endif
};

#if SUPPORT_UART1
UARTDevice* UARTRepository::Uart1Ref = nullptr;
#endif
#if SUPPORT_UART2
UARTDevice* UARTRepository::Uart2Ref = nullptr;
#endif
#if SUPPORT_UART3
UARTDevice* UARTRepository::Uart3Ref = nullptr;
#endif
#if SUPPORT_UART4
UARTDevice* UARTRepository::Uart4Ref = nullptr;
#endif
#if SUPPORT_UART5
UARTDevice* UARTRepository::Uart5Ref = nullptr;
#endif
#if SUPPORT_UART6
UARTDevice* UARTRepository::Uart6Ref = nullptr;
#endif




/////////////////////////////////////////////////////////////////////////////
// class UARTDevice


UARTDevice::UARTDevice() : rx_rb(rx_buffer, MAX_RX_BUFFER) , tx_rb(tx_buffer, MAX_TX_BUFFER)
{
}

HAL_StatusTypeDef UARTDevice::begin(HAL_StatusTypeDef (*InitProc)(UARTDevice* device))
{
	if (InitProc(this) != HAL_OK)
		return HAL_ERROR;

#if 0
	__HAL_LOCK(this);
	{
		this->pRxBuffPtr = rx_buffer;
		this->RxXferSize = MAX_RX_BUFFER;
		this->RxXferCount = MAX_RX_BUFFER;

		this->ErrorCode = HAL_UART_ERROR_NONE;
		this->RxState = HAL_UART_STATE_BUSY_RX;
	}
	__HAL_UNLOCK(this);
#endif

	// Enable the UART Parity Error Interrupt
	//__HAL_UART_ENABLE_IT(this, UART_IT_PE);

	// Enable the UART Error Interrupt: (Frame error, noise error, overrun error)
	//__HAL_UART_ENABLE_IT(this, UART_IT_ERR);

	// Enable the UART Data Register not empty Interrupt
	__HAL_UART_ENABLE_IT(this, UART_IT_RXNE);

	return HAL_OK;
}

void end()
{

}

int32_t UARTDevice::available()
{
	return rx_rb.isEmpty() ? 0 : 1;
}


int32_t UARTDevice::read()
{
	return rx_rb.pop();
}

int32_t UARTDevice::peek()
{
	return rx_rb.peek();
}

void UARTDevice::write(int32_t data)
{
	//
	tx_rb.push(data);

	// Enable TXE interrupt
	__HAL_UART_ENABLE_IT(this, UART_IT_TXE);
}

void UARTDevice::write(uint8_t * data, int32_t dataLen)
{
	for (int32_t i = 0; i < dataLen; i++)
		tx_rb.push(data[i]);

	// Enable TXE interrupt
	__HAL_UART_ENABLE_IT(this, UART_IT_TXE);
}

void UARTDevice::puts(const char * str)
{
	while (*str)
		write(*str++);
}

int UARTDevice::printf(const char * fmt, ...)
{
	//
	va_list args;
	va_start(args,fmt);
	int ret = vsprintf(printBuf, fmt, args);
	va_end(args);

	//
	puts(printBuf);

	return ret;
}

void UARTDevice::flush()
{
	while (!(this->Instance->ISR & USART_ISR_TXE_TXFNF)) // while(!empty())
	{
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}

//
void UARTDevice::IRQHandler()
{
	while ((this->Instance->ISR & UART_FLAG_RXNE) /*&& (device->Instance->CR1 & USART_CR1_RXNEIE)*/)
	{
		int c = this->Instance->RDR;
		this->_push(c);
	}

	if ((this->Instance->ISR & UART_FLAG_TXE) /*&& (device->Instance->CR1 & USART_CR1_TXEIE)*/)
	{
		int32_t c = this->_pop();
		if (c < 0)
		{
			// Disable the UART Transmit Complete Interrupt
			__HAL_UART_DISABLE_IT(this, UART_IT_TXE);
			// Enable the UART Transmit Complete Interrupt
			__HAL_UART_DISABLE_IT(this, UART_IT_TC);
		}
		else
		{
			this->Instance->TDR = c;
		}
	}
}

//
void UARTDevice::_push(uint8_t ch)
{
	rx_rb.push(ch);
}

int32_t UARTDevice::_pop()
{
	return tx_rb.pop();
}






/////////////////////////////////////////////////////////////////////////////
//

#if SUPPORT_UART1
extern "C" void USART1_IRQHandler(void)
{
	if (!UARTRepository::Uart1Ref)
		return;

	UARTRepository::Uart1Ref->IRQHandler();
}
#endif


#if SUPPORT_UART5
extern "C" void UART5_IRQHandler(void)
{
	if (!UARTRepository::Uart5Ref)
		return;

	UARTRepository::Uart5Ref->IRQHandler();
}
#endif






/////////////////////////////////////////////////////////////////////////////
//

HAL_StatusTypeDef MX_USART1_InitEx(UARTDevice* device)
{
	if (UARTRepository::Uart1Ref)
		return HAL_BUSY; // FALSE

	UARTRepository::Uart1Ref = device;

	//
	device->Instance = USART1;
	//
	device->Init.BaudRate = 115200;
	device->Init.WordLength = UART_WORDLENGTH_8B;
	device->Init.StopBits = UART_STOPBITS_1;
	device->Init.Parity = UART_PARITY_NONE;
	device->Init.Mode = UART_MODE_TX_RX;
	device->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	device->Init.OverSampling = UART_OVERSAMPLING_16;
	device->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	device->Init.ClockPrescaler = UART_PRESCALER_DIV1;
	device->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	//
	if (HAL_UART_Init(device) != HAL_OK)
		return HAL_ERROR;
	if (HAL_UARTEx_SetTxFifoThreshold(device, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
		return HAL_ERROR;
	if (HAL_UARTEx_SetRxFifoThreshold(device, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
		return HAL_ERROR;
	if (HAL_UARTEx_DisableFifoMode(device) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

#if UNUSE
HAL_StatusTypeDef MX_UART5_InitEx(UARTDevice* device)
{
	if (UARTRepository::Uart5Ref)
		return HAL_BUSY; // FALSE

	UARTRepository::Uart5Ref = device;

	//
	device->Instance = UART5;
	//
	device->Init.BaudRate = 115200;
	device->Init.WordLength = UART_WORDLENGTH_8B;
	device->Init.StopBits = UART_STOPBITS_1;
	device->Init.Parity = UART_PARITY_NONE;
	device->Init.Mode = UART_MODE_TX_RX;
	device->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	device->Init.OverSampling = UART_OVERSAMPLING_16;

	//
	if (HAL_UART_Init(device) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}
#endif
