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

class EPaperController : public ISPIClassInterface
{
public:
	EPaperController();

public:
	void			begin();
	void			end();

	void			run();

protected:
	virtual void	OnComplete(void* recvPtr, size_t recvLen, SPIClassEx::Error error);


protected:
	static void 	SPI1_Init(SPIClassEx* spi);
	static void 	SPI1_Deinit(SPIClassEx* spi);

private:
	SPIClassEx		mComm;

//	EPaperDisplay&	mDisp;
//	EPaperFrameBuffer	mPrimary;
//	EPaperFrameBuffer	mSecondary;
};


#endif /* LIBRARIES_EPD_EPAPERCONTROLLER_H_ */
