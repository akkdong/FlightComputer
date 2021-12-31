/*
 * NMEAParser.cpp
 *
 *  Created on: 2021. 1. 28.
 *      Author: akkdong
 */


#include "NMEAParser.h"



NMEAParser::NMEAParser(HardwareSerial& serial)
	: gps(serial)
{

}


int NMEAParser::begin()
{
	lwgps_init(this);

	return 0;
}

void NMEAParser::update()
{
	while (gps.available())
	{
		int ch = gps.read();
		lwgps_process(this, &ch, 1);
	}
}

void NMEAParser::end()
{
}

