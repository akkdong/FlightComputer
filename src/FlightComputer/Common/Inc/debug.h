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



#if defined(DEBUG) && 1

int Trace(const char* fmt, ...);

#define TRACE(...)			Trace(__VA_ARGS__)

#else

#define TRACE(...)

#endif




#ifdef __cplusplus
}
#endif


#endif /* INC_DEBUG_H_ */
