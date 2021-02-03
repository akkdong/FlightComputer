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

#define SPI2_DISABLED
#define SPI3_DISABLED



///////////////////////////////////////////////////////////////////////////////////
//

extern "C" void SPI1_IRQHandler(void);
extern "C" void SPI2_IRQHandler(void);
extern "C" void SPI3_IRQHandler(void);
extern "C" void SPI4_IRQHandler(void);



//
enum SPIClassName
{
	SPI_INVALID = -1,
#if defined(SPI1) && !defined(SPI1_DISABLED)
	SPI_1,
#endif
#if defined(SPI2) && !defined(SPI2_DISABLED)
	SPI_2,
#endif
#if defined(SPI3) && !defined(SPI3_DISABLED)
	SPI_3,
#endif
#if defined(SPI4) && !defined(SPI4_DISABLED)
	SPI_4,
#endif
	SPI_COUNT
};

//
struct ISPIClassInterface;

//
class SPIClassEx;


///////////////////////////////////////////////////////////////////////////////////
// class SPIClassEx

class SPIClassEx : public SPI_HandleTypeDef
{
#if defined(SPI1) && !defined(SPI1_DISABLED)
	friend void SPI1_IRQHandler(void);
#endif
#if defined(SPI2) && !defined(SPI2_DISABLED)
	friend void SPI2_IRQHandler(void);
#endif
#if defined(SPI3) && !defined(SPI3_DISABLED)
	friend void SPI3_IRQHandler(void);
#endif
#if defined(SPI4) && !defined(SPI4_DISABLED)
	friend void SPI4_IRQHandler(void);
#endif

public:
	SPIClassEx(ISPIClassInterface* intf = nullptr);

	enum SPIState
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
	void				begin(void (* init)(SPIClassEx *));
	void 				end(void (* deinit)(SPIClassEx *));

	static void			run();

	uint8_t 			transfer(uint8_t data);
	uint16_t 			transfer(uint16_t data);
	uint32_t 			transfer(uint32_t data);

	HAL_StatusTypeDef	transfer(void* sendPtr, size_t count);
	HAL_StatusTypeDef	transfer(void* sendPtr, void* recvPtr, size_t count);

	uint8_t 			receive(uint8_t data);
	uint16_t 			receive(uint16_t data);
	uint32_t 			receive(uint32_t data);

	HAL_StatusTypeDef	receive(void* sendPtr, size_t count);

	HAL_StatusTypeDef	transfer_IT(uint8_t data, uint32_t timeout = 1000);
	HAL_StatusTypeDef	transfer_IT(uint16_t data, uint32_t timeout = 1000);
	HAL_StatusTypeDef	transfer_IT(uint32_t data, uint32_t timeout = 1000);

	HAL_StatusTypeDef	transfer_IT(void* sendPtr, size_t count, uint32_t timeout = 1000);
	HAL_StatusTypeDef	transfer_IT(void* sendPtr, void* recvPtr, size_t count, uint32_t timeout = 1000);

	HAL_StatusTypeDef	receive_IT(uint8_t data, uint32_t timeout = 1000);
	HAL_StatusTypeDef	receive_IT(uint16_t data, uint32_t timeout = 1000);
	HAL_StatusTypeDef	receive_IT(uint32_t data, uint32_t timeout = 1000);

	HAL_StatusTypeDef	receive_IT(void* sendPtr, size_t count, uint32_t timeout = 1000);

protected:
	virtual void 		IRQHandler();
	virtual void 		OnComplete(void* recvPtr, size_t recvLen, Error error);

protected:
	void 				Callback_Complete();
	void 				Callback_Error();
	void 				Callback_Abort();

	static void 		Callback_Complete(SPI_HandleTypeDef *hspi);
	static void 		Callback_Error(SPI_HandleTypeDef *hspi);
	static void 		Callback_Abort(SPI_HandleTypeDef *hspi);

	void				checkExpire();


private:
	static void 		registerInstance(SPIClassEx* spi);
	static void 		unregisterInstance(SPIClassEx* spi);

	void				setState(SPIState state, void* ptr = nullptr, size_t len = 0) { mState = state; mRecvPtr = ptr; mRecvLen = len; }
	void				setTimeout(uint32_t timeout); // ms
	void				setCallback();

private:
	void *				mRecvPtr;
	size_t				mRecvLen;

	SPIState			mState;		// UNDEF, READY, PENDING
	uint32_t			mTimestamp;
	uint32_t			mTimeout;

	union _Noname
	{
		uint8_t		data8;
		uint16_t 	data16;
		uint32_t	data32;
	} mRecvData;

	ISPIClassInterface*	mIntf;

	static SPIClassEx*	mInstanceMap[SPI_COUNT];
};


///////////////////////////////////////////////////////////////////////////////////
//

struct ISPIClassInterface
{
	virtual void	OnComplete(void* recvPtr, size_t recvLen, SPIClassEx::Error error) = 0;
};





#endif /* LIBRARIES_SPI_SPICLASSEX_H_ */
