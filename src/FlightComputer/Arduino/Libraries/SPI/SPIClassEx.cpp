/*
 * SPIClassEx.cpp
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "SPIClassEx.h"


///////////////////////////////////////////////////////////////////////////////
//

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
	return SPI_INVALID;
}


///////////////////////////////////////////////////////////////////////////////
//

SPIClassEx * SPIClassEx::mInstanceMap[SPI_COUNT] =
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


#if defined(SPI1) && !defined(SPI1_DISABLED)
extern "C" void SPI1_IRQHandler(void)
{
	if (SPIClassEx::mInstanceMap[SPI_1])
		SPIClassEx::mInstanceMap[SPI_1]->IRQHandler();
}
#endif

#if defined(SPI2) && !defined(SPI2_DISABLED)
extern "C" void SPI2_IRQHandler(void)
{
	if (SPIClassEx::mInstanceMap[SPI_2])
		SPIClassEx::mInstanceMap[SPI_2]->IRQHandler();
}
#endif

#if defined(SPI3) && !defined(SPI3_DISABLED)
extern "C" void SPI3_IRQHandler(void)
{
	if (SPIClassEx::mInstanceMap[SPI_3])
		SPIClassEx::mInstanceMap[SPI_3]->IRQHandler();
}
#endif

#if defined(SPI4) && !defined(SPI4_DISABLED)
extern "C" void SPI4_IRQHandler(void)
{
	if (SPIClassEx::mInstanceMap[SPI_4])
		SPIClassEx::mInstanceMap[SPI_4]->IRQHandler();
}
#endif


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
	registerInstance(this);
	setState(READY);
	setCallback();
}

void SPIClassEx::end(void (* deinit)(SPIClassEx *))
{
	unregisterInstance(this);
	deinit(this);
	setState(UNDEF);
}

void SPIClassEx::run()
{
	for (size_t i = 0; i < sizeof(mInstanceMap) / sizeof(mInstanceMap[0]); i++)
	{
		if (mInstanceMap[i])
			mInstanceMap[i]->checkExpire();
	}
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

HAL_StatusTypeDef SPIClassEx::transfer(void* sendPtr, size_t count)
{
	return HAL_SPI_Transmit(this, (uint8_t *)sendPtr, count, 1000);
}

HAL_StatusTypeDef SPIClassEx::transfer(void* sendPtr, void* recvPtr, size_t count)
{
	return HAL_SPI_TransmitReceive(this, (uint8_t *)sendPtr, (uint8_t *)recvPtr, count, 1000);
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

HAL_StatusTypeDef SPIClassEx::receive(void* sendPtr, size_t count)
{
	return HAL_SPI_Receive(this, (uint8_t *)sendPtr, count, 1000);
}


HAL_StatusTypeDef SPIClassEx::transfer_IT(uint8_t data, uint32_t timeout)
{
	return transfer_IT(&data, &mRecvData.data8, sizeof(data), timeout);
}

HAL_StatusTypeDef SPIClassEx::transfer_IT(uint16_t data, uint32_t timeout)
{
	return transfer_IT(&data, &mRecvData.data16, sizeof(data), timeout);
}

HAL_StatusTypeDef SPIClassEx::transfer_IT(uint32_t data, uint32_t timeout)
{
	return transfer_IT(&data, &mRecvData.data32, sizeof(data), timeout);
}

HAL_StatusTypeDef SPIClassEx::transfer_IT(void* sendPtr, size_t count, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_SPI_Transmit_IT(this, (uint8_t *)sendPtr, count);
	if (status == HAL_OK)
	{
		setState(SENDING);
		setTimeout(timeout);
	}

	return status;
}

HAL_StatusTypeDef SPIClassEx::transfer_IT(void* sendPtr, void* recvPtr, size_t count, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(this, (uint8_t *)sendPtr, (uint8_t *)recvPtr, count);
	if (status == HAL_OK)
	{
		setState(TRANSFER, recvPtr, count);
		setTimeout(timeout);
	}

	return status;
}


HAL_StatusTypeDef SPIClassEx::receive_IT(uint8_t data, uint32_t timeout)
{
	return receive_IT(&data, sizeof(data), timeout);
}

HAL_StatusTypeDef SPIClassEx::receive_IT(uint16_t data, uint32_t timeout)
{
	return receive_IT(&data, sizeof(data), timeout);
}

HAL_StatusTypeDef SPIClassEx::receive_IT(uint32_t data, uint32_t timeout)
{
	return receive_IT(&data, sizeof(data));
}

HAL_StatusTypeDef SPIClassEx::receive_IT(void* sendPtr, size_t count, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_SPI_Receive_IT(this, (uint8_t *)sendPtr, count);
	if (status == HAL_OK)
	{
		setState(RECEIVING, sendPtr, count);
		setTimeout(timeout);
	}

	return status;
}

void SPIClassEx::IRQHandler()
{
	HAL_SPI_IRQHandler((SPI_HandleTypeDef *)this);
}

void SPIClassEx::OnComplete(void* recvPtr, size_t recvLen, Error error)
{
	if (mIntf)
		mIntf->OnComplete(recvPtr, recvLen, error);
}


void SPIClassEx::registerInstance(SPIClassEx* spi)
{
	SPIClassName name = getClassName(spi->Instance);
	if (name != SPI_INVALID)
		SPIClassEx::mInstanceMap[name] = spi;
}

void SPIClassEx::unregisterInstance(SPIClassEx* spi)
{
	SPIClassName name = getClassName(spi->Instance);
	if (name != SPI_INVALID)
		mInstanceMap[name] = nullptr;
}

void SPIClassEx::setTimeout(uint32_t timeout)
{
	mTimestamp = millis();
	mTimeout = timeout;
}

void SPIClassEx::setCallback()
{
    this->TxCpltCallback       = Callback_Complete;
    this->RxCpltCallback       = Callback_Complete;
    this->TxRxCpltCallback     = Callback_Complete;
    this->TxHalfCpltCallback   = Callback_Complete;
    this->RxHalfCpltCallback   = Callback_Complete;
    this->TxRxHalfCpltCallback = Callback_Complete;
    this->ErrorCallback        = Callback_Error;
    this->AbortCpltCallback    = Callback_Abort;
}


void SPIClassEx::Callback_Complete()
{
	if (mState == UNDEF)
		return;

	if (mState != READY)
	{
		OnComplete(mRecvPtr, mRecvLen, Error::OK);
		setState(READY);
	}
}

void SPIClassEx::Callback_Error()
{
	if (mState == UNDEF)
		return;

	if (mState != READY)
	{
		OnComplete(mRecvPtr, mRecvLen, Error::INTERNAL);
		setState(READY);
	}
}

void SPIClassEx::Callback_Abort()
{
	if (mState == UNDEF)
		return;

	if (mState != READY)
	{
		OnComplete(mRecvPtr, mRecvLen, Error::ABORT);
		setState(READY);
	}
}

void SPIClassEx::Callback_Complete(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->Callback_Complete();
}

void SPIClassEx::Callback_Error(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->Callback_Error();
}

void SPIClassEx::Callback_Abort(SPI_HandleTypeDef *hspi)
{
	((SPIClassEx *)hspi)->Callback_Abort();
}

void SPIClassEx::checkExpire()
{
	if (mState == UNDEF)
		return;

	if (mState != READY)
	{
		if (millis() - mTimestamp > mTimeout)
		{
			OnComplete(mRecvPtr, mRecvLen, Error::ABORT);
			setState(READY);

			HAL_SPI_Abort_IT(this);
		}
	}
}
