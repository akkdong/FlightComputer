/*
 * EPaperController.h
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#ifndef LIBRARIES_EPD_EPAPERCONTROLLER_H_
#define LIBRARIES_EPD_EPAPERCONTROLLER_H_

#include "SPI/SPIClassEx.h"
#include "EPD/EPaperDisplay.h"



/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperController

class EPaperController
{
public:
	EPaperController();

	enum EPDC_Command
	{
		UNKNOWN = 0x00,

		POWER_ON = 0xA1,
		POWER_OFF = 0xA2,
		REFRESH = 0xB1,
		CLEAR = 0xB2,
		GET_DISPLAY = 0x21,
		SET_WINDOW = 0x22,
		START_DATA_TRANSMIT = 0x23,
		STOP_DATA_TRANSMIT = 0x24
	};

	enum EPDC_State
	{
		UNINIT,
		WAIT_COMMAND,
		PROCESSING,
		SENDING,
		RECEIVING
	};


	class SPIDriver : public SPIClassEx
	{
	public:
		SPIDriver(EPaperController* controller) : mControllerPtr(controller) { }

		void 			receive_IT();
		void			abort_IT();

		void			transmit_IT(uint8_t* bufPtr, uint16_t bufLen);
		void			stopTransmit();

	protected:
		virtual void 	IRQHandler();

		void			RxHandler();
		void			TxHandler();

	protected:
		EPaperController*	mControllerPtr;
	};

	friend class SPIDriver;


public:
	void					begin();
	void					end();

	void					run();

protected:
	virtual void			OnReceive(uint8_t data);
	virtual void			OnSendComplete();
	virtual void			OnError(uint32_t error);


protected:
	static void 			SPI1_Init(SPIClassEx* spi);
	static void 			SPI1_Deinit(SPIClassEx* spi);

private:
	SPIDriver				mSPIDriver;
	EPaperDisplay			mDisp;

	volatile EPDC_Command	mLastCommand;
	volatile EPDC_State		mState;
	uint32_t				mTimestamp;

	volatile uint8_t *		mRecvPtr;
	volatile uint32_t		mRecvLen;
	volatile uint32_t		mRecvExpect;

	volatile uint8_t *		mSendPtr;
	volatile uint32_t		mSendLen;

	// Display
	// WIDTH, HEIGHT, BPP

	// Window
	// sx, sy, ex, ey
	// addr, bytes
	uint8_t					mTemp[10];
};


#endif /* LIBRARIES_EPD_EPAPERCONTROLLER_H_ */
