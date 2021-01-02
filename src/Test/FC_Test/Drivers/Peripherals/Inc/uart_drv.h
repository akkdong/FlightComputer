// uart_drv.h
//

#ifndef __UART_DRV_H__
#define __UART_DRV_H__

#include "stm32h7xx_hal.h"
#include "RingBuffer.h"

#define	MAX_RX_BUFFER			(64)
#define MAX_TX_BUFFER			(128)

#include "UART_Conf.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//

typedef enum _UARTDriverIdentifier
{
#if SUPPORT_UART1
	UART_Driver1,
#endif
#if SUPPORT_UART2
	UART_Driver2,
#endif
#if SUPPORT_UART3
	UART_Driver3,
#endif
#if SUPPORT_UART4
	UART_Driver4,
#endif
#if SUPPORT_UART5
	UART_Driver5,
#endif
#if SUPPORT_UART6
	UART_Driver6,
#endif
#if SUPPORT_UART7
	UART_Driver7,
#endif
#if SUPPORT_UART8
	UART_Driver8,
#endif
	UART_DriverCount
} UARTDriverIdentifier;

typedef struct _UARTDriver
{
	UARTDriverIdentifier	id;
	UART_HandleTypeDef* 	uartHandle;

	RingBuffer 				rx_rb;
	RingBuffer 				tx_rb;

	uint8_t					rx_buffer[MAX_RX_BUFFER];
	uint8_t					tx_buffer[MAX_TX_BUFFER];

} UARTDriver;



////////////////////////////////////////////////////////////////////////////////////////////////
//

void 				UART_Begin(UARTDriver* uart, UARTDriverIdentifier id, UART_HandleTypeDef* handle);
void 				UART_End(UARTDriver* uart);

int32_t 			UART_Available(UARTDriver* uart);
int32_t 			UART_Peek(UARTDriver* uart);
int32_t 			UART_Read(UARTDriver* uart);

void 				UART_Write(UARTDriver* uart, int32_t data);
void 				UART_WriteBuffer(UARTDriver* uart, uint8_t * data, int32_t dataLen);
void 				UART_Puts(UARTDriver* uart, const char * str);
int 				UART_Printf(UARTDriver* uart, const char * fmt, ...);

void 				UART_Flush(UARTDriver* uart);


#endif // __UART_DRV_H__
