/*
 * NMEAParser.cpp
 *
 *  Created on: 2021. 1. 28.
 *      Author: akkdong
 */


#include "NMEAParser.h"



NMEAParser::NMEAParser(HardwareSerial& serial)
	: gps(serial)
	, front(0)
	, rear(0)
	, has_line(0)
{

}


int NMEAParser::begin()
{
	lwgps_init(this);

	front = rear = 0;
	has_line = 0;

	return 0;
}

void NMEAParser::update()
{
	while (gps.available())
	{
		int ch = gps.read();
		lwgps_process(this, &ch, 1);

		// save gps-data
		nmea_buf[front] = ch;
		front = (front + 1) % MAX_BUFSIZE;
		if (rear == front)
			rear = (rear + 1) % MAX_BUFSIZE;

		if (ch == '\n')
			has_line += 1;
	}
}

void NMEAParser::end()
{
}


void NMEAParser::fetchData(lwrb_t* rb)
{
	while (has_line > 0 && front != rear)
	{
		int ch = nmea_buf[rear];
		lwrb_write(rb, &ch, 1);

		rear = (rear + 1) % MAX_BUFSIZE;
		if (ch == '\n')
			has_line -= 1;
	}
}
