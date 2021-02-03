/*
 * EPaperDisplay.h
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#ifndef LIBRARIES_EPD_EPAPERDISPLAY_H_
#define LIBRARIES_EPD_EPAPERDISPLAY_H_


#include "stm32h7xx_hal.h"

#define GPIO_NUMBER           (16U)


////////////////////////////////////////////////////////////////////////////////////////
//


//                                      Bits:     5432109876543210
#define EPD_Set_CKV()		do { GPIOJ->BSRR = (0b0000000100000000); } while (0)
#define EPD_Set_SPH()		do { GPIOK->BSRR = (0b0000000000000010); } while (0)
#define EPD_Set_SPV()		do { GPIOK->BSRR = (0b0000000000000100); } while (0)
#define EPD_Set_LE()		do { GPIOJ->BSRR = (0b0000100000000000); } while (0)
#define EPD_Set_CL()		do { GPIOJ->BSRR = (0b0000001000000000); } while (0)
#define EPD_Set_OE()		do { GPIOK->BSRR = (0b0000000000000001); } while (0)
#define EPD_Set_GMODE()		do { GPIOJ->BSRR = (0b0000010000000000); } while (0)

//                                      Bits:     5432109876543210
#define EPD_Reset_CKV()		do { GPIOJ->BSRR = (0b0000000100000000 << GPIO_NUMBER); } while (0)
#define EPD_Reset_SPH()		do { GPIOK->BSRR = (0b0000000000000010 << GPIO_NUMBER); } while (0)
#define EPD_Reset_SPV()		do { GPIOK->BSRR = (0b0000000000000100 << GPIO_NUMBER); } while (0)
#define EPD_Reset_LE()		do { GPIOJ->BSRR = (0b0000100000000000 << GPIO_NUMBER); } while (0)
#define EPD_Reset_CL()		do { GPIOJ->BSRR = (0b0000001000000000 << GPIO_NUMBER); } while (0)
#define EPD_Reset_OE()		do { GPIOK->BSRR = (0b0000000000000001 << GPIO_NUMBER); } while (0)
#define EPD_Reset_GMODE() 	do { GPIOJ->BSRR = (0b0000010000000000 << GPIO_NUMBER); } while (0)

#define EPD_Set_DATA(data)	do { GPIOD->BSRR = pinLUT[(data)]; } while (0)



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

public:
	void 					begin(void);
	void 					end();

	void					powerOn();
	void					powerOff();

	void 					clearScreen(void);
	void 					draw16Gray(const uint8_t* img_bytes);
	void 					drawMono(const uint8_t* img_bytes);
	void 					drawMono2(const uint8_t* img_bytes);
	void 					drawPartial(const uint8_t* new_bytes, const uint8_t* old_bytes);

	EPaperFrameBuffer&		getPrimary();
	EPaperFrameBuffer&		getSecondary();


protected:

	void 					clockPixel(void);
	void 					outputRow(void);
	void 					latchRow(void);
	void 					scanVStart(void);
	void 					scanVEnd(void);
	void 					scanHStart(void);
	void 					scanHEnd(void);


protected:
	EPaperFrameBuffer		mPrimary;
	EPaperFrameBuffer		mSecondary;
};


#endif /* LIBRARIES_EPD_EPAPERDISPLAY_H_ */
