/*
 * EPaperFrameBuffer.cpp
 *
 *  Created on: 2021. 2. 5.
 *      Author: akkdong
 */

#include "EPaperFrameBuffer.h"


#define BASE_DISPBUFFER				0x24000000
#define SIZE_DISPBUFFER				0x00080000;


/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperFrameBuffer

EPaperFrameBuffer::EPaperFrameBuffer(size_t width, size_t height, size_t bpp)
{
	size_t scanLine = (width * bpp) / 8;
	size_t bufSize = (((scanLine + 3) / 4) * 4) * height;

	mBuffPtr = alloc(bufSize);
	mBuffLen = bufSize;

	mWidth = width;
	mHeight = height;
	mBitPerPixel = bpp;
}

volatile uint8_t * EPaperFrameBuffer::mBaseAddrPtr	= (volatile uint8_t *)BASE_DISPBUFFER;
volatile uint8_t * EPaperFrameBuffer::mNextAddrPtr 	= (volatile uint8_t *)BASE_DISPBUFFER;

size_t EPaperFrameBuffer::mMemTotalSize		= SIZE_DISPBUFFER;

volatile uint8_t * EPaperFrameBuffer::alloc(size_t size)
{
	size = ((size + 3) / 4) * 4; // alignment
	if (size > capacity())
		return nullptr;

	volatile uint8_t * allocPtr = mNextAddrPtr;
	mNextAddrPtr += size;

	return allocPtr;
}

size_t EPaperFrameBuffer::capacity()
{
	return mMemTotalSize - (mNextAddrPtr - mBaseAddrPtr);
}
