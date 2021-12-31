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


/////////////////////////////////////////////////////////////////////////////////////
// class FlightComputer

class FlightComputer
{
public:
	FlightComputer();

	void setup();
	void loop();

protected:
// 	FileSystem 	fs;
// 	EPapper		paper;
//  MonitorManager	mm;

	SPIClassEx			spi1;
	KeyPad				keyPad;
	//EPaperController	epdCont;
	EPaperDisplay		epdDisp;

	uint8_t				data[64];

public:
	static bool			flash_ok;
	static bool			sdram_ok;
};


#endif /* INC_FLIGHTCOMPUTER_H_ */
