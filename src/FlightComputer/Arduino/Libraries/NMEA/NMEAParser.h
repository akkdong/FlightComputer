/*
 * NMEAParser.h
 *
 *  Created on: 2021. 1. 28.
 *      Author: akkdong
 */

#ifndef NMEA_NMEAPARSER_H_
#define NMEA_NMEAPARSER_H_

#include "Arduino.h"
#include "lwgps/lwgps.h"
#include "lwrb/lwrb.h"

#define MAX_BUFSIZE		(4095)	// 0x0FFFF


/////////////////////////////////////////////////////////////////////////////////////////////
//

class NMEAParser : public lwgps_t
{
public:
	NMEAParser(HardwareSerial& serial);

public:
	int			begin();
	void		update();
	void		end();

	void		fetchData(lwrb_t* rb);

protected:
	HardwareSerial& gps;

	char		nmea_buf[MAX_BUFSIZE];
	int			front, rear;
	int			has_line;
};


#endif /* NMEA_NMEAPARSER_H_ */
