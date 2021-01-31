/*
 * SPIClassEx.h
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#ifndef LIBRARIES_SPI_SPICLASSEX_H_
#define LIBRARIES_SPI_SPICLASSEX_H_

#include "Timer.h"
#include "SPI/SPI.h"


///////////////////////////////////////////////////////////////////////////////////
// HAL_SPI Callbacks

extern "C"
{
	void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
	void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);
	void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
	void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi);
	void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi);
	void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi);
	void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);
	void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef *hspi);
}


///////////////////////////////////////////////////////////////////////////////////
//

struct ISPIClassInterface;
class SPIClassEx;


///////////////////////////////////////////////////////////////////////////////////
// class SPIClassEx

class SPIClassEx : public SPI_HandleTypeDef
{
	// SPI Callbacks are my friends
	friend void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
	friend void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);
	friend void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
	friend void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi);
	friend void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi);
	friend void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi);
	friend void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);
	friend void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef *hspi);

public:
	SPIClassEx(ISPIClassInterface* intf = nullptr);

	enum State
	{
		UNDEF = -1,
		READY,
		SENDING,
		RECEIVING,
		TRANSFER
	};

	enum Error
	{
		OK,
		INTERNAL,
		ABORT,
		TIMEOUT,
	};

public:
	void			begin(void (* init)(SPIClassEx *));
	void 			end(void (* deinit)(SPIClassEx *));

	uint8_t 		transfer(uint8_t data);
	uint16_t 		transfer(uint16_t data);
	uint32_t 		transfer(uint32_t data);

	void 			transfer(void* sendPtr, size_t count);
	void 			transfer(void* sendPtr, void* recvPtr, size_t count);

	uint8_t 		receive(uint8_t data);
	uint16_t 		receive(uint16_t data);
	uint32_t 		receive(uint32_t data);

	void 			receive(void* sendPtr, size_t count);

	void 			transfer_IT(uint8_t data, uint32_t timeout = 1000);
	void 			transfer_IT(uint16_t data, uint32_t timeout = 1000);
	void 			transfer_IT(uint32_t data, uint32_t timeout = 1000);

	void 			transfer_IT(void* sendPtr, size_t count, uint32_t timeout = 1000);
	void 			transfer_IT(void* sendPtr, void* recvPtr, size_t count, uint32_t timeout = 1000);

	void 			receive_IT(uint8_t data, uint32_t timeout = 1000);
	void 			receive_IT(uint16_t data, uint32_t timeout = 1000);
	void 			receive_IT(uint32_t data, uint32_t timeout = 1000);

	void 			receive_IT(void* sendPtr, size_t count, uint32_t timeout = 1000);

protected:
	virtual void	OnComplete(void* recvPtr, size_t recvLen, Error error);
protected:
	void 			CompleteCallback();
	void 			ErrorCallback();
	void 			AbortCpltCallback();

private:
	void			setState(State state, void* ptr = nullptr, size_t len = 0) { mState = state; mRecvPtr = ptr; mRecvLen = len; }
	void			setTimeout(uint32_t timeout); // ms

private:
	void *			mRecvPtr;
	size_t			mRecvLen;
	State			mState;		// UNDEF, READY, PENDING

	union _Noname
	{
		uint8_t		data8;
		uint16_t 	data16;
		uint32_t	data32;
	} mRecvData;

	ISPIClassInterface*	mIntf;
};


///////////////////////////////////////////////////////////////////////////////////
//

struct ISPIClassInterface
{
	virtual void	OnComplete(void* recvPtr, size_t recvLen, SPIClassEx::Error error) = 0;
};





#endif /* LIBRARIES_SPI_SPICLASSEX_H_ */
