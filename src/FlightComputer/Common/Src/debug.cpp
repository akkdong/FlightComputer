/*
 * debug.cpp
 *
 *  Created on: 2022. 1. 1.
 *      Author: akkdong
 */


#include "Arduino.h"
#include "debug.h"
#include <stdio.h>
#include <stdarg.h>

#if defined(DEBUG) && ENABLE_TRACE

static HardwareSerial& debug = Serial;
static char output_buf[1024];


void TraceInit()
{
	Serial.begin(115200);
}

int Trace(const char* format, ...)
{
	va_list args;

	va_start(args, format);
	int ret = vsprintf(output_buf, format, args);
	va_end(args);

	debug.write(output_buf);

	return ret;
}

#endif
