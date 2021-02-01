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

#define EPD_WIDTH			800
#define EPD_HEIGHT			600




/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperController

class EPaperController
{
public:
	EPaperController();

	enum EPD_Command
	{
		POWER_ON,
		POWER_OFF,
		REFRESH,
		CLEAR,
		GET_STATUS,
		SET_WINDOW,
		DATA_START,
		DATA_STOP
	};


	class SPIDriver : public SPIClassEx
	{
	public:
		SPIDriver(EPaperController* controller) : mControllerPtr(controller) { }

		void 			receive_IT();
		void			abort_IT();

	protected:
		virtual void 	IRQHandler();

		void			RxISR();
		void			TxISR();

	protected:
		EPaperController*	mControllerPtr;
	};

	friend class SPIDriver;


public:
	void			begin();
	void			end();

	void			run();

protected:
	virtual void	OnReceive(uint8_t data);
	virtual void	OnError(uint32_t error);


protected:
	static void 	SPI1_Init(SPIClassEx* spi);
	static void 	SPI1_Deinit(SPIClassEx* spi);

private:
	SPIDriver		mSPIDriver;
	EPaperDisplay	mDisp;

	// PIN_CS
	// PIN_BUSY
};


#endif /* LIBRARIES_EPD_EPAPERCONTROLLER_H_ */
