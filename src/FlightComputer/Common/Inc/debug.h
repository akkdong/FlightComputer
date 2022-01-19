/*
 * debug.h
 *
 *  Created on: 2022. 1. 1.
 *      Author: akkdong
 */

#ifndef INC_DEBUG_H_
#define INC_DEBUG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ENABLE_TRACE		0


#if defined(DEBUG) && ENABLE_TRACE

void 	TraceInit();
int 	Trace(const char* fmt, ...);

#define TRACE_INIT()		TraceInit();
#define TRACE(...)			Trace(__VA_ARGS__)

#else

#define TRACE_INIT()
#define TRACE(...)

#endif




#ifdef __cplusplus
}
#endif


#endif /* INC_DEBUG_H_ */
