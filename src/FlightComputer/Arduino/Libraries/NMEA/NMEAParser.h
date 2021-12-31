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

protected:
	HardwareSerial& gps;
};


#endif /* NMEA_NMEAPARSER_H_ */
