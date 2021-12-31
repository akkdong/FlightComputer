/*
 * debug_handler.c
 *
 *  Created on: 2021. 12. 31.
 *      Author: akkdong
 */

#include "main.h"
//#include "core_debug.h"
#include "debug.h"


void _Error_Handler(const char *msg, int val)
{
	/* User can add his own implementation to report the HAL error return state */
	//core_debug("Error: %s (%i)\n", msg, val);
	TRACE("Error: %s (%i)\n", msg, val);
}

void Error_Handler()
{
	_Error_Handler(__FILE__, __LINE__);
}
