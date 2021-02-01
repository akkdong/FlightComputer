/*
 * EPaperDisplay.cpp
 *
 *  Created on: 2021. 2. 1.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "EPaperDisplay.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperFrameBuffer

EPaperFrameBuffer::EPaperFrameBuffer(int width, int height, int bpp)
{

}



/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperDisplay

EPaperDisplay::EPaperDisplay()
	: mPrimary(800, 600, 1)
	, mSecondary(800, 600, 1)
{
	uint8_t* ptr = mPrimary;
	if (ptr)
		ptr[0] = 0;
}
