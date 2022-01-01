/*
 * vario_state.c
 *
 *  Created on: 2022. 1. 1.
 *      Author: akkdong
 */


#include "vario_state.h"
#include <memory.h>



void vario_reset(vario_t* state)
{
	memset(state, 0, sizeof(vario_t));
}
