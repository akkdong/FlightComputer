/*
 * EPaperDisplay.h
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#ifndef LIBRARIES_EPD_EPAPERDISPLAY_H_
#define LIBRARIES_EPD_EPAPERDISPLAY_H_

#include "stm32h7xx_hal.h"
#include "EPaperFrameBuffer.h"
#include "EPaperPMIC.h"


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

//#define EPD_Set_DATA(data)	do { GPIOD->BSRR = pinLUT[(data)]; } while (0)

#define EPD_Set_DATA(data)	do { GPIOD->BSRR = data; } while (0)
#define EPD_Reset_DATA()	do { GPIOD->BSRR = (0b0001100011111100 << GPIO_NUMBER); } while (0)


/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperDisplay

#if USE_MODEL_A

class EPaperDisplay
{
public:
	EPaperDisplay();

public:
	int 					begin(void);
	void 					end();

	int						powerOn();
	void					powerOff();

	void 					clearScreen(void);
	void 					draw16Gray(const uint8_t* img_bytes);
	void 					drawMono(const uint8_t* img_bytes);
	void 					drawMono2(const uint8_t* img_bytes);
	void 					drawPartial(const uint8_t* new_bytes, const uint8_t* old_bytes);

	EPaperFrameBuffer &		getPrimary() { return mPrimary; }
	EPaperFrameBuffer &		getSecondary() { return mSecondary; }
	EPaperFrameBuffer &		getGrayscale() { return mGrayscale; }

	EPaperFrameBuffer *		getOnline() { return mActivePtr; }
	EPaperFrameBuffer *		getOffline() { return mActivePtr == &mPrimary ? &mSecondary : &mPrimary; }

	void					swap() {}
	void					refresh(bool fast = true) {}

protected:
	void					clear(uint8_t c, uint8_t rep);
	void					display();

	void 					clockPixel(void);
	void 					outputRow(void);
	void 					latchRow(void);
	void 					scanVStart(void);
	void 					scanVEnd(void);
	void 					scanHStart(void);
	void 					scanHEnd(void);


protected:
	//
	EPaperFrameBuffer		mPrimary;
	EPaperFrameBuffer		mSecondary;
	EPaperFrameBuffer		mGrayscale;

	EPaperFrameBuffer *		mActivePtr;

	//
	EPaperPMIC				mEPaperPMIC;
};

#else // MODEL_B

class EPaperDisplay
{
public:
	EPaperDisplay();

public:
	void 					begin(void);
	void 					end();

	void					clearDisplay();
	void					display(bool leaveOn = false);
	void					partialUpdate(bool forced = false, bool leaveOn = false);

	int						einkOn();
	void					einkOff();
	void					preloadScreen();
	uint8_t					readPowerGood();
	void					clean(uint8_t c, uint8_t rep);

	void					display1b(bool leaveOn = false);
	void					display3b(bool leaveOn = false);

	void					vscan_start();
	void					vscan_end();
	void					hscan_start(uint32_t d = 0);
	void					pinsZstate();
	void					pinsAsOutputs();


	uint8_t*				getDisplayBuffer() { return mBackBuffer.getPtr(); }

protected:
	int 					getPanelState() { return mPanelState; }
	void 					setPanelState(int state) { mPanelState = state; }

#ifdef DEBUG
	void					DumpRegister();
	void					DumpPort();
#endif

protected:
	//
	EPaperFrameBuffer		mDispBuffer;
	EPaperFrameBuffer		mBackBuffer;

	//
	EPaperPMIC				mEPaperPMIC;

	//
	uint32_t				mPinLUT[256];
	uint32_t * 				mGlobalLUT;
	uint32_t * 				mGlobalLUT2;

    //uint8_t *				DMemoryNew;
    //uint8_t *				_partial;
    //uint8_t *				DMemory4Bit;
    //uint8_t *				_pBuffer;

    int						mPanelState;
};

#endif


#endif /* LIBRARIES_EPD_EPAPERDISPLAY_H_ */
