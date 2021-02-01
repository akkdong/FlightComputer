/*
 * EPaperDisplay.h
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#ifndef LIBRARIES_EPD_EPAPERDISPLAY_H_
#define LIBRARIES_EPD_EPAPERDISPLAY_H_

/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperFrameBuffer

class EPaperFrameBuffer
{
public:
	EPaperFrameBuffer(int width, int height, int bpp = 1);

public:
	operator uint8_t *() { return (uint8_t *)mBuffPtr; }

private:
	void *			mBuffPtr;
	int				mBuffLen;

	int				mWidth;
	int				mHeight;
	int				mBitPerPixel;
};


/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperDisplay

class EPaperDisplay
{
public:
	EPaperDisplay();

	EPaperFrameBuffer&		getPrimary();
	EPaperFrameBuffer&		getSecondary();

protected:
	EPaperFrameBuffer		mPrimary;
	EPaperFrameBuffer		mSecondary;
};


#endif /* LIBRARIES_EPD_EPAPERDISPLAY_H_ */
