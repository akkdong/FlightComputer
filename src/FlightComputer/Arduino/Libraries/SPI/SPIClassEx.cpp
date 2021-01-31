/*
 * SPIClassEx.cpp
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "SPIClassEx.h"

#define SPI2_DISABLED
#define SPI3_DISABLED

class SPIClassEx;

volatile SPIClassEx * _SPIClasses[] =
{
#if defined(SPI1) && !defined(SPI1_DISABLED)
	nullptr,
#endif
#if defined(SPI2) && !defined(SPI2_DISABLED)
	nullptr,
#endif
#if defined(SPI3) && !defined(SPI3_DISABLED)
	nullptr,
#endif
#if defined(SPI4) && !defined(SPI4_DISABLED)
	nullptr,
#endif
};

enum SPIClassName
{
	SPI_NONE = -1,
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
};

#if defined(SPI1) && !defined(SPI1_DISABLED)
extern "C" void SPI1_IRQHandler(void)
{
	if (_SPIClasses[SPI_1])
		HAL_SPI_IRQHandler((SPI_HandleTypeDef *)_SPIClasses[SPI_1]);
}
#endif

#if defined(SPI2) && !defined(SPI2_DISABLED)
extern "C" void SPI2_IRQHandler(void)
{
	if (_SPIClasses[SPI_2])
		HAL_SPI_IRQHandler((SPI_HandleTypeDef *)_SPIClasses[SPI_2]);
}
#endif

#if defined(SPI3) && !defined(SPI3_DISABLED)
extern "C" void SPI3_IRQHandler(void)
{
	if (_SPIClasses[SPI_3])
		HAL_SPI_IRQHandler((SPI_HandleTypeDef *)_SPIClasses[SPI_3]);
}
#endif

#if defined(SPI4) && !defined(SPI4_DISABLED)
extern "C" void SPI4_IRQHandler(void)
{
	if (_SPIClasses[SPI_4])
		HAL_SPI_IRQHandler((SPI_HandleTypeDef *)_SPIClasses[SPI_4]);
}
#endif

static SPIClassName getClassName(SPI_TypeDef* spi)
{
#if defined(SPI1) && !defined(SPI1_DISABLED)
	if (spi == SPI1)
		return SPI_1;
#endif
#if defined(SPI2) && !defined(SPI2_DISABLED)
	if (spi == SPI2)
		return SPI_2;
#endif
#if defined(SPI3) && !defined(SPI3_DISABLED)
	if (spi == SPI3)
		return SPI_3;
#endif
#if defined(SPI4) && !defined(SPI4_DISABLED)
	if (spi == SPI4)
		return SPI_4;
#endif
	return SPI_NONE;
}

static void registerClass(SPIClassEx* spi)
{
	SPIClassName name = getClassName(spi->Instance);
	if (name != SPI_NONE)
		_SPIClasses[name] = spi;
}

static void unregisterClass(SPIClassEx* spi)
{
	SPIClassName name = getClassName(spi->Instance);
	if (name != SPI_NONE)
		_SPIClasses[name] = nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//

SPIClassEx::SPIClassEx(ISPIClassInterface* intf)
	: mRecvPtr(nullptr)
	, mRecvLen(0)
	, mState(UNDEF)
	, mIntf(intf)
{
}


void SPIClassEx::begin(void (* init)(SPIClassEx *))
{
	init(this);
	registerClass(this);
	setState(READY);
}

void SPIClassEx::end(void (* deinit)(SPIClassEx *))
{
	unregisterClass(this);
	deinit(this);
	setState(UNDEF);
}

uint8_t SPIClassEx::transfer(uint8_t data)
{
	uint8_t recv = 0x00;
	transfer(&data, &recv, sizeof(data));
	return recv;
}

uint16_t SPIClassEx::transfer(uint16_t data)
{
	uint16_t recv = 0x00;
	transfer(&data, &recv, sizeof(data));
	return recv;
}

uint32_t SPIClassEx::transfer(uint32_t data)
{
	uint32_t recv = 0x00;
	transfer(&data, &recv, sizeof(data));
	return recv;
}

void SPIClassEx::transfer(void* sendPtr, size_t count)
{
	HAL_SPI_Transmit(this, (uint8_t *)sendPtr, count, 1000);
}

void SPIClassEx::transfer(void* sendPtr, void* recvPtr, size_t count)
{
	HAL_SPI_TransmitReceive(this, (uint8_t *)sendPtr, (uint8_t *)recvPtr, count, 1000);
}


uint8_t SPIClassEx::receive(uint8_t data)
{
	receive(&data, sizeof(data));
	return data;
}

uint16_t SPIClassEx::receive(uint16_t data)
{
	receive(&data, sizeof(data));
	return data;
}

uint32_t SPIClassEx::receive(uint32_t data)
{
	receive(&data, sizeof(data));
	return data;
}

void SPIClassEx::receive(void* sendPtr, size_t count)
{
	HAL_SPI_Receive(this, (uint8_t *)sendPtr, count, 1000);
}


void SPIClassEx::transfer_IT(uint8_t data, uint32_t timeout)
{
	transfer_IT(&data, &mRecvData.data8, sizeof(data), timeout);
}

void SPIClassEx::transfer_IT(uint16_t data, uint32_t timeout)
{
	transfer_IT(&data, &mRecvData.data16, sizeof(data), timeout);
}

void SPIClassEx::transfer_IT(uint32_t data, uint32_t timeout)
{
	transfer_IT(&data, &mRecvData.data32, sizeof(data), timeout);
}

void SPIClassEx::transfer_IT(void* sendPtr, size_t count, uint32_t timeout)
{
	HAL_SPI_Transmit_IT(this, (uint8_t *)sendPtr, count);

	setState(SENDING);
	setTimeout(timeout);
}

void SPIClassEx::transfer_IT(void* sendPtr, void* recvPtr, size_t count, uint32_t timeout)
{
	HAL_SPI_TransmitReceive_IT(this, (uint8_t *)sendPtr, (uint8_t *)recvPtr, count);

	setState(TRANSFER, recvPtr, count);
	setTimeout(timeout);
}


void SPIClassEx::receive_IT(uint8_t data, uint32_t timeout)
{
	receive_IT(&data, sizeof(data), timeout);
}

void SPIClassEx::receive_IT(uint16_t data, uint32_t timeout)
{
	receive_IT(&data, sizeof(data), timeout);
}

void SPIClassEx::receive_IT(uint32_t data, uint32_t timeout)
{
	receive_IT(&data, sizeof(data));
}

void SPIClassEx::receive_IT(void* sendPtr, size_t count, uint32_t timeout)
{
	HAL_SPI_Receive_IT(this, (uint8_t *)sendPtr, count);

	setState(RECEIVING, sendPtr, count);
	setTimeout(timeout);
}


void SPIClassEx::setTimeout(uint32_t timeout)
{

}

void SPIClassEx::OnComplete(void* recvPtr, size_t recvLen, Error error)
{
	if (mIntf)
		mIntf->OnComplete(recvPtr, recvLen, error);
}

void SPIClassEx::CompleteCallback()
{
	if (mState == UNDEF)
		return;

	if (mState != READY)
	{
		OnComplete(mRecvPtr, mRecvLen, Error::OK);
		setState(READY);
	}
}

void SPIClassEx::ErrorCallback()
{
	if (mState == UNDEF)
		return;

	if (mState != READY)
	{
		OnComplete(mRecvPtr, mRecvLen, Error::INTERNAL);
		setState(READY);
	}
}

void SPIClassEx::AbortCpltCallback()
{
	if (mState == UNDEF)
		return;

	if (mState != READY)
	{
		OnComplete(mRecvPtr, mRecvLen, Error::ABORT);
		setState(READY);
	}
}




//
//
//
//

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->CompleteCallback();
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->CompleteCallback();
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->CompleteCallback();
}

void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->CompleteCallback();
}

void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->CompleteCallback();
}

void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->CompleteCallback();
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->ErrorCallback();
}

void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->AbortCpltCallback();
}


