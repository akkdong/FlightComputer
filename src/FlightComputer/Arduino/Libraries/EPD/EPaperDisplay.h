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

#include "Adafruit_GFX/Adafruit_GFX.h"


#define GPIO_NUMBER			(16U)

#define EPD_WIDTH     		(800)
#define EPD_HEIGHT    		(600)
#define BPP_MONO			(1)
#define BPP_16GRAY			(4)

#define COLOR_BLACK			(0xFF)
#define COLOR_WHITE			(0x00)


enum bm_mode //BM_ModeSet
{
	bm_normal = 0,
	bm_default = 1, // for use for BitmapExamples
	// these potentially can be combined
	bm_invert = (1 << 1),
	bm_flip_x = (1 << 2),
	bm_flip_y = (1 << 3),
	bm_r90 = (1 << 4),
	bm_r180 = (1 << 5),
	bm_r270 = bm_r90 | bm_r180,
	bm_partial_update = (1 << 6),
	bm_invert_red = (1 << 7),
	bm_transparent = (1 << 8)
};


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

#define EPD_Set_DATA(data)	do { GPIOD->BSRR = data; } while (0)
#define EPD_Reset_DATA()	do { GPIOD->BSRR = (0b0001100011111100 << GPIO_NUMBER); } while (0)


/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperDisplay

#if USE_MODEL_A

class EPaperDisplay : public Adafruit_GFX
{
public:
	EPaperDisplay();

public:
	int 					begin(void);
	void 					end();

	int						powerOn();
	void					powerOff();

	void 					clearScreen(void);

	void					drawBitmapBM(const uint8_t * bitmap, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, int16_t mode);


#if OBSOLETE
	void 					draw16Gray(const uint8_t* img_bytes);
	void 					drawMono(const uint8_t* img_bytes);
	void 					drawMono2(const uint8_t* img_bytes);
	void 					drawPartial(const uint8_t* new_bytes, const uint8_t* old_bytes);
#endif

	volatile uint8_t *		getCanvas() { return mCanvas.getPtr(); }
	int						getCanvasSize() { return EPD_WIDTH / 8 * EPD_HEIGHT; }


	void 					refresh(bool fast = false);


	///  virtual drawPixel() function to draw to the screen/framebuffer/etc.
	//   @param x X coordinate.
	//   @param y Y coordinate.
	//   @param color 16-bit pixel color.
	virtual void 			drawPixel(int16_t x, int16_t y, uint16_t color);


protected:
	void					clear(uint8_t c, uint8_t rep);
	void					display();
	void					fastUpdate();
	void					partialUpdate(bool forced = false);

	void 					clockPixel(void);
	void 					outputRow(void);
	void 					latchRow(void);
	void 					startVScan(void);
	void 					endVScan(void);
	void 					startHScan(void);
	void 					endHScan(void);


	template <typename T> static inline void _swap_(T & a, T & b) { T t = a; a = b; b = t;  }
	static inline uint16_t __max(uint16_t a, uint16_t b) { return (a > b ? a : b); }
	static inline uint16_t __min(uint16_t a, uint16_t b) { return (a < b ? a : b); }


protected:
	//
	EPaperFrameBuffer		mDisplay;
	EPaperFrameBuffer		mCanvas;
	EPaperFrameBuffer		mBuffer;

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
