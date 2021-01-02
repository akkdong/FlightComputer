// UART.c
//

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "UART.h"

#define MAX_PRINT_BUFFER		(128)


////////////////////////////////////////////////////////////////////////////////////////////////
// Static Variables

static UARTDriver* _DriverPool[] =
{
#if SUPPORT_UART1
	NULL,
#endif
#if SUPPORT_UART2
	NULL,
#endif
#if SUPPORT_UART3
	NULL,
#endif
#if SUPPORT_UART4
	NULL,
#endif
#if SUPPORT_UART5
	NULL,
#endif
#if SUPPORT_UART6
	NULL,
#endif
#if SUPPORT_UART7
	NULL,
#endif
#if SUPPORT_UART8
	NULL,
#endif
};


static char _PrintBuf[MAX_PRINT_BUFFER];



////////////////////////////////////////////////////////////////////////////////////////////////
// UARTDriver default IRQ Handler

static void UART__Push(UARTDriver* uart, uint8_t ch)
{
	RB_Push(&uart->rx_rb, ch);
}

static int32_t UART__Pop(UARTDriver* uart)
{
	return RB_Pop(&uart->tx_rb);
}


static void UART_IRQHandler(UARTDriver* uart)
{
	while ((uart->uartHandle->Instance->ISR & UART_FLAG_RXNE) /*&& (device->Instance->CR1 & USART_CR1_RXNEIE)*/)
	{
		int c = uart->uartHandle->Instance->RDR;
		UART__Push(uart, c);
	}

	if ((uart->uartHandle->Instance->ISR & UART_FLAG_TXE) /*&& (device->Instance->CR1 & USART_CR1_TXEIE)*/)
	{
		int32_t c = UART__Pop(uart);
		if (c < 0)
		{
			// Disable the UART Transmit Complete Interrupt
			__HAL_UART_DISABLE_IT(uart->uartHandle, UART_IT_TXE);
			// Enable the UART Transmit Complete Interrupt
			__HAL_UART_DISABLE_IT(uart->uartHandle, UART_IT_TC);
		}
		else
		{
			uart->uartHandle->Instance->TDR = c;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// UART IRQ Handlers

#if SUPPORT_UART1
void USART1_IRQHandler(void)
{
	if (!_DriverPool[UART_Driver1])
		return;

	UART_IRQHandler(_DriverPool[UART_Driver1]);
}
#endif

#if SUPPORT_UART2
void USART2_IRQHandler(void)
{
	if (!_DriverPool[UART_Driver2])
		return;

	UART_IRQHandler(_DriverPool[UART_Driver2]);
}
#endif

#if SUPPORT_UART3
void USART3_IRQHandler(void)
{
	if (!_DriverPool[UART_Driver3])
		return;

	UART_IRQHandler(_DriverPool[UART_Driver3]);
}
#endif



////////////////////////////////////////////////////////////////////////////////////////////////
// UARTDriver Implementation

void UART_Begin(UARTDriver* uart, UARTDriverIdentifier id, UART_HandleTypeDef* handle)
{
	//
	uart->id = id;
	uart->uartHandle = handle;

	_DriverPool[id] = uart;

	//
	RB_Init(&uart->rx_rb, uart->rx_buffer, MAX_RX_BUFFER);
	RB_Init(&uart->tx_rb, uart->tx_buffer, MAX_TX_BUFFER);

	__HAL_UART_ENABLE_IT(uart->uartHandle, UART_IT_RXNE);
}

void UART_End(UARTDriver* uart)
{
	_DriverPool[uart->id] = NULL;
}

int32_t UART_Available(UARTDriver* uart)
{
	return RB_IsEmpty(&uart->rx_rb) ? 0 : 1;
}

int32_t UART_Peek(UARTDriver* uart)
{
	return RB_Peek(&uart->rx_rb);
}

int32_t UART_Read(UARTDriver* uart)
{
	return RB_Pop(&uart->rx_rb);
}

void UART_Write(UARTDriver* uart, int32_t data)
{
	//
	RB_Push(&uart->tx_rb, data);

	// Enable TXE interrupt
	__HAL_UART_ENABLE_IT(uart->uartHandle, UART_IT_TXE);
}

void UART_WriteBuffer(UARTDriver* uart, uint8_t * data, int32_t dataLen)
{
	for (int32_t i = 0; i < dataLen; i++)
		RB_Push(&uart->tx_rb, data[i]);

	// Enable TXE interrupt
	__HAL_UART_ENABLE_IT(uart->uartHandle, UART_IT_TXE);
}

void UART_Puts(UARTDriver* uart, const char * str)
{
	while (*str)
		UART_Write(uart, *str++);
}

int UART_Printf(UARTDriver* uart, const char * fmt, ...)
{
	//
	va_list args;
	va_start(args,fmt);
	int ret = vsprintf(_PrintBuf, fmt, args);
	va_end(args);

	//
	UART_Puts(uart, _PrintBuf);

	return ret;
}

void UART_Flush(UARTDriver* uart)
{
	while (!(uart->uartHandle->Instance->ISR & USART_ISR_TXE_TXFNF)) // while(!empty())
	{
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}
