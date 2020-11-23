// SPI.h
//

#ifndef __SPI_H__
#define __SPI_H__

#include "stm32h7xx_hal.h"


/////////////////////////////////////////////////////////////////////////////
//

class SPIBase : public SPI_HandleTypeDef
{
public:
	SPIBase() = default;

	void Initialize(HAL_StatusTypeDef (* InitProc)(SPIBase* device)) {
		InitProc(this);
	}

#if 0
	// Initialization/de-initialization functions
	HAL_StatusTypeDef InitEx() {
		return HAL_SPI_Init(this);
	}
	HAL_StatusTypeDef DeInit() {
		return HAL_SPI_DeInit(this);
	}
	void MspInit() {
		return HAL_SPI_MspInit(this);
	}
	void MspDeInit() {
		return HAL_SPI_MspDeInit(this);
	}

	// I/O operation functions
	HAL_StatusTypeDef Transmit(uint8_t *pData, uint16_t Size, uint32_t Timeout) {
		return HAL_SPI_Transmit(this, pData, Size, Timeout);
	}
	HAL_StatusTypeDef Receive(uint8_t *pData, uint16_t Size, uint32_t Timeout) {
		return HAL_SPI_Receive(this, pData, Size, Timeout);
	}
	HAL_StatusTypeDef TransmitReceive(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout) {
		return HAL_SPI_TransmitReceive(this, pTxData, pRxData, Size, Timeout);
	}
	HAL_StatusTypeDef Transmit_IT(uint8_t *pData, uint16_t Size) {
		return HAL_SPI_Transmit_IT(this, pData, Size);
	}
	HAL_StatusTypeDef Receive_IT(uint8_t *pData, uint16_t Size) {
		return HAL_SPI_Receive_IT(this, pData, Size);
	}
	HAL_StatusTypeDef TransmitReceive_IT(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size) {
		return HAL_SPI_TransmitReceive_IT(this, pTxData, pRxData, Size);
	}
	HAL_StatusTypeDef Transmit_DMA(uint8_t *pData, uint16_t Size) {
		return HAL_SPI_Transmit_DMA(this, pData, Size);
	}
	HAL_StatusTypeDef Receive_DMA(uint8_t *pData, uint16_t Size) {
		return HAL_SPI_Receive_DMA(this, pData, Size);
	}
	HAL_StatusTypeDef TransmitReceive_DMA(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size) {
		return HAL_SPI_TransmitReceive_DMA(this, pTxData, pRxData, Size);
	}
	HAL_StatusTypeDef DMAPause() {
		return HAL_SPI_DMAPause(this);
	}
	HAL_StatusTypeDef DMAResume() {
		return HAL_SPI_DMAResume(this);
	}
	HAL_StatusTypeDef DMAStop() {
		return HAL_SPI_DMAStop(this);
	}

	// Transfer Abort functions
	HAL_StatusTypeDef Abort() {
		return HAL_SPI_Abort(this);
	}
	HAL_StatusTypeDef Abort_IT() {
		return HAL_SPI_Abort_IT(this);
	}

	// Peripheral State and Error functions
	HAL_SPI_StateTypeDef GetState() {
		return HAL_SPI_GetState(this);
	}
	uint32_t GetError() {
		return HAL_SPI_GetError(this);
	}
#endif
};


/////////////////////////////////////////////////////////////////////////////
//

extern "C" void SPI4_IRQHandler();


HAL_StatusTypeDef MX_SPI4_InitEx(SPIBase* device);


/////////////////////////////////////////////////////////////////////////////
//

class SPIEInk : public SPIBase
{
	friend void SPI4_IRQHandler();

public:
	SPIEInk();
	virtual ~SPIEInk();


	HAL_StatusTypeDef 	begin(HAL_StatusTypeDef (* InitProc)(SPIBase* device));
	void 				end();

	void				run();

protected:
	void 				IRQHandler();

	virtual void 		TxISR();
	virtual void 		RxISR();


	uint8_t tx_buf[64];
	int tx_front, tx_rear;

	uint8_t rx_buf[64];
	int rx_front, rx_rear;


	static SPIEInk* RunningRef;
};




#endif // __SPI_H__

