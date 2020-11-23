// UART.h
//

#ifndef __UART_H__
#define __UART_H__

#include "stm32h7xx_hal.h"
#include "RingBuffer.h"

#define	MAX_RX_BUFFER			(64)
#define MAX_TX_BUFFER			(64)

#define SUPPORT_UART1			(1)
#define SUPPORT_UART2			(0)
#define SUPPORT_UART3			(0)
#define SUPPORT_UART4			(0)
#define SUPPORT_UART5			(0)
#define SUPPORT_UART6			(0)
#define SUPPORT_UART7			(0)
#define SUPPORT_UART8			(0)


/////////////////////////////////////////////////////////////////////////////
//

class UARTRepository;
class UARTDevice;

#if SUPPORT_UART1
extern "C" void USART1_IRQHandler();
#endif
#if SUPPORT_UART2
extern "C" void USART2_IRQHandler();
#endif
#if SUPPORT_UART3
extern "C" void USART3_IRQHandler();
#endif
#if SUPPORT_UART4
extern "C" void UART4_IRQHandler();
#endif
#if SUPPORT_UART5
extern "C" void UART5_IRQHandler();
#endif
#if SUPPORT_UART6
extern "C" void USART6_IRQHandler();
#endif
#if SUPPORT_UART7
extern "C" void UART7_IRQHandler();
#endif
#if SUPPORT_UART8
extern "C" void UART8_IRQHandler();
#endif


/////////////////////////////////////////////////////////////////////////////
//

HAL_StatusTypeDef MX_USART1_InitEx(UARTDevice* device);
HAL_StatusTypeDef MX_USART2_InitEx(UARTDevice* device);
HAL_StatusTypeDef MX_USART3_InitEx(UARTDevice* device);
HAL_StatusTypeDef MX_UART4_InitEx(UARTDevice* device);
HAL_StatusTypeDef MX_UART5_InitEx(UARTDevice* device);
HAL_StatusTypeDef MX_UART6_InitEx(UARTDevice* device);
HAL_StatusTypeDef MX_UART7_InitEx(UARTDevice* device);
HAL_StatusTypeDef MX_USART8_InitEx(UARTDevice* device);



/////////////////////////////////////////////////////////////////////////////
// class UARTDevice

class UARTDevice : public UART_HandleTypeDef
{
public:
	UARTDevice();

public:
	HAL_StatusTypeDef 	begin(HAL_StatusTypeDef (*InitProc)(UARTDevice* device));
	void 				end();

	int32_t 			available();
	int32_t 			peek();
	int32_t 			read();

	void 				write(int32_t data);
	void 				write(uint8_t * data, int32_t dataLen);
	void 				puts(const char * str);
	int 				printf(const char * fmt, ...);

	void 				flush();

protected:
#if SUPPORT_UART1
	friend void USART1_IRQHandler();
#endif
#if SUPPORT_UART2
	friend void USART2_IRQHandler();
#endif
#if SUPPORT_UART3
	friend void USART3_IRQHandler();
#endif
#if SUPPORT_UART4
	friend void UART4_IRQHandler();
#endif
#if SUPPORT_UART5
	friend void UART5_IRQHandler();
#endif
#if SUPPORT_UART6
	friend void UART6_IRQHandler();
#endif
#if SUPPORT_UART7
	friend void UART7_IRQHandler();
#endif
#if SUPPORT_UART8
	friend void USART8_IRQHandler();
#endif

	//
	void 				IRQHandler();

	//
	void 				_push(uint8_t ch);
	int32_t 			_pop();


	/*
	// IO operation functions
	HAL_StatusTypeDef Transmit(uint8_t *pData, uint16_t Size, uint32_t Timeout) {
		return HAL_UART_Transmit(this, pData, Size, Timeout);
	}
	HAL_StatusTypeDef Receive(uint8_t *pData, uint16_t Size, uint32_t Timeout) {
		return HAL_UART_Receive(this, pData, Size, Timeout);
	}
	HAL_StatusTypeDef Transmit_IT(uint8_t *pData, uint16_t Size) {
		return HAL_UART_Transmit_IT(this, pData, Size);
	}
	HAL_StatusTypeDef Receive_IT(uint8_t *pData, uint16_t Size) {
		return HAL_UART_Receive_IT(this, pData, Size);
	}
	HAL_StatusTypeDef Transmit_DMA(uint8_t *pData, uint16_t Size) {
		return HAL_UART_Transmit_DMA(this, pData, Size);
	}
	HAL_StatusTypeDef Receive_DMA(uint8_t *pData, uint16_t Size) {
		return HAL_UART_Receive_DMA(this, pData, Size);
	}
	HAL_StatusTypeDef DMAPause() {
		return HAL_UART_DMAPause(this);
	}
	HAL_StatusTypeDef DMAResume() {
		return HAL_UART_DMAResume(this);
	}
	HAL_StatusTypeDef DMAStop() {
		return HAL_UART_DMAStop(this);
	}

	// Transfer Abort functions
	HAL_StatusTypeDef Abort() {
		return HAL_UART_Abort(this);
	}
	HAL_StatusTypeDef AbortTransmit() {
		return HAL_UART_AbortTransmit(this);
	}
	HAL_StatusTypeDef AbortReceive() {
		return HAL_UART_AbortReceive(this);
	}
	HAL_StatusTypeDef Abort_IT() {
		return HAL_UART_Abort_IT(this);
	}
	HAL_StatusTypeDef AbortTransmit_IT() {
		return HAL_UART_AbortTransmit_IT(this);
	}
	HAL_StatusTypeDef AbortReceive_IT() {
		return HAL_UART_AbortReceive_IT(this);
	}

	// Peripheral Control functions
	HAL_StatusTypeDef SendBreak() {
		return HAL_LIN_SendBreak(this);
	}
	HAL_StatusTypeDef EnterMuteMode() {
		return HAL_MultiProcessor_EnterMuteMode(this);
	}
	HAL_StatusTypeDef ExitMuteMode() {
		return HAL_MultiProcessor_ExitMuteMode(this);
	}
	HAL_StatusTypeDef EnableTransmitter() {
		return HAL_HalfDuplex_EnableTransmitter(this);
	}
	HAL_StatusTypeDef EnableReceiver() {
		return HAL_HalfDuplex_EnableReceiver(this);
	}

	// Peripheral State functions
	HAL_UART_StateTypeDef GetState() {
		return HAL_UART_GetState(this);
	}
	uint32_t GetError() {
		return HAL_UART_GetError(this);
	}
	*/


protected:
	RingBuffer 		rx_rb;
	RingBuffer 		tx_rb;

	uint8_t			rx_buffer[MAX_RX_BUFFER];
	uint8_t			tx_buffer[MAX_TX_BUFFER];

	char			printBuf[256];
};


#endif // __UART_H__

