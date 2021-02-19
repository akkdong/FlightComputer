/*
 * EPaperFrameBuffer.h
 *
 *  Created on: 2021. 2. 5.
 *      Author: akkdong
 */

#ifndef LIBRARIES_EPD_EPAPERFRAMEBUFFER_H_
#define LIBRARIES_EPD_EPAPERFRAMEBUFFER_H_

#include <stddef.h>
#include <stdint.h>


/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperFrameBuffer

class EPaperFrameBuffer
{
public:
	EPaperFrameBuffer(size_t width, size_t height, size_t bpp = 1);

public:
	uint8_t * getPtr() { return mBuffPtr; }
	int	getSize() { return mBuffLen; }

	operator uint8_t *() { return getPtr(); }

protected:
	static uint8_t *	alloc(size_t size);
	static size_t		capacity();

private:
	uint8_t *			mBuffPtr;
	size_t				mBuffLen;

	size_t				mWidth;
	size_t				mHeight;
	size_t				mBitPerPixel;

	//
protected:
	static uint8_t *	mBaseAddrPtr;
	static uint8_t *	mNextAddrPtr;
	static size_t		mMemTotalSize;
};



#endif /* LIBRARIES_EPD_EPAPERFRAMEBUFFER_H_ */
