/*
 * FlightComputer.h
 *
 *  Created on: 2021. 12. 31.
 *      Author: akkdong
 */

#ifndef INC_FLIGHTCOMPUTER_H_
#define INC_FLIGHTCOMPUTER_H_

#include "Arduino.h"
#include "SPI/SPIClassEx.h"
#include "EPD/EPaperController.h"
#include "EPD/EPaperDisplay.h"
#include "KeyPad/KeyPad.h"

#include "common.h"



/////////////////////////////////////////////////////////////////////////////////////
// class FlightComputer

class FlightComputer
{
public:
	FlightComputer();

	enum Event {
		VARIO_UPDATED,
		GPS_UPDATED
	};

public:
	void 				setup();
	void 				loop();

	void				setEvent(Event event);
	void				updateVario();
	void				updateGPS();

protected:
	void				standby();

	void				procDebugShell();
	void				procInterProcess();
	void				procKeyboard();
#if SUPPORT_LVGL
	void				procLVGL();
#endif

	void				updateScreen(bool fast = true);


public:
	static bool			flash_ok;
	static bool			sdram_ok;

protected:
// 	FileSystem 			fs;
// 	EPapper				paper;
//  MonitorManager		mm;

	SPIClassEx			spi1;
	KeyPad				keyPad;
	//EPaperController	epdCont;
	EPaperDisplay		epdDisp;

	uint8_t				data[64];

	//
	lwrb_t* 			rb_cm4_to_cm7;
	lwrb_t* 			rb_cm7_to_cm4;

	vario_t*			varioState;

	//
	int					displayUpdateCount;
	int					enterStandby;

	// test-only
	int					imageType;
};


#endif /* INC_FLIGHTCOMPUTER_H_ */