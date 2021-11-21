/*
 * EPaperDisplay.cpp
 *
 *  Created on: 2021. 2. 1.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "EPaperDisplay.h"


#if USE_MODEL_A

#define EPD_WIDTH     		800
#define EPD_HEIGHT    		600
#define BPP_MONO			1
#define BPP_16GRAY			4

#define CLK_DELAY_US  		0
#define VCLK_DELAY_US 		1
#define OUTPUT_DELAY_US   	2
#define CLEAR_BYTE    		0b10101010
#define DARK_BYTE     		0b01010101

#define PIXEL2EPDCMD(x)		(((x) == 1) ? 0b00000010 : (((x) == 0) ? 0b00000001 : 0b00000011))

#define MAP2PIN(x)			(LUTpin[(x)])



////////////////////////////////////////////////////////////////////////////////////////
//

#if R2L

const uint8_t LUT2[16] =
{
	0xAA, 0xA9, 0xA6, 0xA5,
	0x9A, 0x99, 0x96, 0x95,
	0x6A, 0x69, 0x66, 0x65,
	0x5A, 0x59, 0x56, 0x55
};

const uint8_t LUTW[16] =
{
	0xFF, 0xFE, 0xFB, 0xFA,
	0xEF, 0xEE, 0xEB, 0xEA,
	0xBF, 0xBE, 0xBB, 0xBA,
	0xAF, 0xAE, 0xAB, 0xAA
};

const uint8_t LUTB[16] =
{
	0xFF, 0xFD, 0xF7, 0xF5,
	0xDF, 0xDD, 0xD7, 0xD5,
	0x7F, 0x7D, 0x77, 0x75,
	0x5F, 0x5D, 0x57, 0x55
};

#else // L2R

// 1 -> W : 10
// 0 -> B : 01

const uint8_t LUT2[16] =
{
	0xAA, 0x6A, 0x9A, 0x5A,
	0xA6, 0x66, 0x96, 0x56,
	0xA9, 0x69, 0x99, 0x59,
	0xA5, 0x65, 0x95, 0x55
};

const uint8_t LUT_W[16] =
{
	0xFF, 0xBF, 0xEF, 0xAF,	// 0000:WWWW:11111111, 0001:---W:10111111, 0010:--W-:11101111, --WW: 10101111
	0xFB, 0xBB, 0xEB, 0xAB, // -W--: 11111011, ...
	0xFE, 0xBE, 0xEE, 0xAE,
	0xFA, 0xBA, 0xEA, 0xAA
};

const uint8_t LUT_B[16] =
{
	0x55, 0xD5, 0x75, 0xF5,	// ----: 11111111, ---B: 10111111, --B-: 11101111, --BB: 01011111
	0x5D, 0xDD, 0x7D, 0xFD, // -B--: 11111011, ...
	0x57, 0xD7, 0x77, 0xF7,
	0x5F, 0xDF, 0x7F, 0xFF
};

const uint8_t LUT_BW[16] =
{
	0x55, 0x95, 0x65, 0xA5,
	0x59, 0x99, 0x69, 0xA9,
	0x56, 0x96, 0x66, 0xA6,
	0x5A, 0x9A, 0x6A, 0xAA
};


const uint8_t _LUT2[16] = {0xAA, 0xA9, 0xA6, 0xA5, 0x9A, 0x99, 0x96, 0x95,
                          0x6A, 0x69, 0x66, 0x65, 0x5A, 0x59, 0x56, 0x55};
const uint8_t _LUTW[16] = {0xFF, 0xFE, 0xFB, 0xFA, 0xEF, 0xEE, 0xEB, 0xEA,
                          0xBF, 0xBE, 0xBB, 0xBA, 0xAF, 0xAE, 0xAB, 0xAA};
const uint8_t _LUTB[16] = {0xFF, 0xFD, 0xF7, 0xF5, 0xDF, 0xDD, 0xD7, 0xD5,
                          0x7F, 0x7D, 0x77, 0x75, 0x5F, 0x5D, 0x57, 0x55};

#endif

uint32_t LUTpin[256];


/* Contrast cycles in order of contrast (Darkest first).  */
const uint8_t contrast_cycles[] = {4,4,2,1};
const uint8_t sz_contrast_cycles = sizeof(contrast_cycles)/sizeof(uint8_t);

/* Screen clearing state */
const uint8_t clear_cycles[] = {
  CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE,
  CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE,
  DARK_BYTE, DARK_BYTE, DARK_BYTE, DARK_BYTE, DARK_BYTE, DARK_BYTE,
  DARK_BYTE, DARK_BYTE, DARK_BYTE, DARK_BYTE, DARK_BYTE, DARK_BYTE,
  CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE,
  CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE,
  CLEAR_BYTE,
};
const uint8_t sz_clear_cycles = sizeof(clear_cycles)/sizeof(uint8_t);



/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperDisplay

EPaperDisplay::EPaperDisplay()
	: mPrimary(EPD_WIDTH, EPD_HEIGHT, BPP_MONO)
	, mSecondary(EPD_WIDTH, EPD_HEIGHT, BPP_MONO)
	, mGrayscale(EPD_WIDTH, EPD_HEIGHT, BPP_16GRAY)
{
	// DATA Pin: GPIOD [12, 11, 7, 6, 5, 4, 3, 2]
	for (uint32_t i = 0; i < 256; i++)
	{
		uint32_t mask = ((i & 0b00111111) << 2) | (((i & 0b11000000) >> 6) << 11);
		LUTpin[i] = (((~mask) & 0b0001100011111100) << GPIO_NUMBER) | mask;
	}

	mActivePtr = &mPrimary;
}


int EPaperDisplay::begin(void)
{
	//
	mEPaperPMIC.init();

	// set all pins to low
    digitalWrite(EPD_CKV, LOW);
    digitalWrite(EPD_CL, LOW);
    digitalWrite(EPD_GMODE, LOW);
    digitalWrite(EPD_LE, LOW);
    digitalWrite(EPD_OE, LOW);
    digitalWrite(EPD_SPH, LOW);
    digitalWrite(EPD_SPV, LOW);
    digitalWrite(EPD_D0, LOW);
    digitalWrite(EPD_D1, LOW);
    digitalWrite(EPD_D2, LOW);
    digitalWrite(EPD_D3, LOW);
    digitalWrite(EPD_D4, LOW);
    digitalWrite(EPD_D5, LOW);
    digitalWrite(EPD_D6, LOW);
    digitalWrite(EPD_D7, LOW);

    // set all pins as output
    pinMode(EPD_CKV, OUTPUT);
    pinMode(EPD_CL, OUTPUT);
    pinMode(EPD_GMODE, OUTPUT);
    pinMode(EPD_LE, OUTPUT);
    pinMode(EPD_OE, OUTPUT);
    pinMode(EPD_SPH, OUTPUT);
    pinMode(EPD_SPV, OUTPUT);
    pinMode(EPD_D0, OUTPUT);
    pinMode(EPD_D1, OUTPUT);
    pinMode(EPD_D2, OUTPUT);
    pinMode(EPD_D3, OUTPUT);
    pinMode(EPD_D4, OUTPUT);
    pinMode(EPD_D5, OUTPUT);
    pinMode(EPD_D6, OUTPUT);
    pinMode(EPD_D7, OUTPUT);

    if (mEPaperPMIC.wakeup() < 0)
    {
#ifdef DEBUG
    	Serial1.println("PMIC wakeup failed!");
#endif
    	return -1;
    }

	// set default state
	EPD_Reset_GMODE();
	EPD_Reset_CKV();
	EPD_Reset_CL();
	EPD_Set_SPH();
	EPD_Set_SPV();
	EPD_Reset_LE();
	EPD_Reset_OE();
	EPD_Reset_DATA();

    return 0;
}

void EPaperDisplay::end()
{
    // set to high-z state: set all pins as input
    pinMode(EPD_CKV, INPUT);
    pinMode(EPD_CL, INPUT);
    pinMode(EPD_GMODE, INPUT);
    pinMode(EPD_LE, INPUT);
    pinMode(EPD_OE, INPUT);
    pinMode(EPD_SPH, INPUT);
    pinMode(EPD_SPV, INPUT);
    pinMode(EPD_D0, INPUT);
    pinMode(EPD_D1, INPUT);
    pinMode(EPD_D2, INPUT);
    pinMode(EPD_D3, INPUT);
    pinMode(EPD_D4, INPUT);
    pinMode(EPD_D5, INPUT);
    pinMode(EPD_D6, INPUT);
    pinMode(EPD_D7, INPUT);

    // sleep PMIC
	mEPaperPMIC.sleep();
}


int EPaperDisplay::powerOn(void)
{
	//
	if (mEPaperPMIC.wakeup() < 0 || mEPaperPMIC.powerOn() < 0)
		return -1;

	//
    EPD_Set_GMODE();
    //EPD_Set_OE();
    delayMicroseconds(0);

    return 0;
}

void EPaperDisplay::powerOff(void)
{
	EPD_Reset_GMODE();

	//
	mEPaperPMIC.powerOff();
	//mEPaperPMIC.sleep();
}

void EPaperDisplay::clockPixel(void)
{
	EPD_Set_CL();
	//delayMicroseconds(CLK_DELAY_US);
	EPD_Reset_CL();
	//delayMicroseconds(CLK_DELAY_US);
}

void EPaperDisplay::outputRow(void)
{
    // OUTPUTROW
	//delayMicroseconds(OUTPUT_DELAY_US);
	EPD_Set_OE();
	EPD_Set_CKV();
	delayMicroseconds(5/*OUTPUT_DELAY_US*/);
    EPD_Reset_CKV();
    EPD_Reset_OE();
    delayMicroseconds(20/*OUTPUT_DELAY_US*/);
    // END OUTPUTROW

#if 0
    // NEXTROW START
    EPD_Set_CL();
    delayMicroseconds(1/*CLK_DELAY_US*/);
    EPD_Reset_CL();
    delayMicroseconds(1/*CLK_DELAY_US*/);
    EPD_Set_CL();
    delayMicroseconds(1/*CLK_DELAY_US*/);
    EPD_Reset_CL();
    delayMicroseconds(1/*CLK_DELAY_US*/);
    //EPD_Set_CKV();
#endif
    // END NEXTROW
}

void EPaperDisplay::latchRow(void)
{
	EPD_Set_LE();
	//delayMicroseconds(CLK_DELAY_US);
    EPD_Set_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Reset_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Set_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Reset_CL();
    //delayMicroseconds(CLK_DELAY_US);

    EPD_Reset_LE();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Set_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Reset_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Set_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Reset_CL();
    //delayMicroseconds(CLK_DELAY_US);
}

void EPaperDisplay::scanVStart(void)
{
    // VSCANSTART
    //EPD_Set_GMODE();
    ////EPD_Set_OE();
    //delayMicroseconds(100);

    EPD_Set_SPV();
    delayMicroseconds(VCLK_DELAY_US);
    EPD_Reset_CKV();
    delayMicroseconds(VCLK_DELAY_US);

    EPD_Set_CKV();
    delayMicroseconds(VCLK_DELAY_US);
    EPD_Reset_SPV();
    delayMicroseconds(VCLK_DELAY_US);
    EPD_Reset_CKV();
    delayMicroseconds(VCLK_DELAY_US);

    EPD_Set_CKV();
    delayMicroseconds(VCLK_DELAY_US);
    EPD_Set_SPV();
    delayMicroseconds(VCLK_DELAY_US);
    EPD_Reset_CKV();
    delayMicroseconds(VCLK_DELAY_US);

    //EPD_Set_CKV();
    //delayMicroseconds(VCLK_DELAY_US);
    // END VSCANSTART
}

void EPaperDisplay::scanVEnd(void)
{
#if 0
    // VSCANEND
	EPD_Set_DATA(MAP2PINS0b00000000));
	EPD_HScanStart();
    for (int j = 0; j < 200; ++j)
    {
            EPD_Set_CL();
            //delayMicroseconds(CLK_DELAY_US);
            EPD_Reset_CL();
            //delayMicroseconds(CLK_DELAY_US);
    }
    EPD_HScanEnd();
    //noInterrupts();
    EPD_Set_OE();
    EPD_Set_CKV();
    delayMicroseconds(1);
    EPD_Reset_CKV();
    delayMicroseconds(1);
    EPD_Reset_OE();
    //interrupts();
    EPD_Set_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Reset_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Set_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Reset_CL();
    //delayMicroseconds(CLK_DELAY_US);
    delayMicroseconds(1);
    EPD_Reset_CKV();
    EPD_Reset_OE();
    delayMicroseconds(50);
    EPD_Set_CKV();
    delayMicroseconds(50);
    EPD_Reset_CKV();
    delayMicroseconds(1);
    EPD_Reset_GMODE();
    delayMicroseconds(1);
    // END VSCANEND

#else

    EPD_Reset_CKV();
    delayMicroseconds(1);
    //EPD_Reset_GMODE();
    //delayMicroseconds(1);

#endif
}

void EPaperDisplay::scanHStart(void)
{
    // HSCANSTART
    //EPD_Set_OE();
    EPD_Reset_SPH();
    // END HSCANSTART
}

void EPaperDisplay::scanHEnd(void)
{
    // HSCANEND
    EPD_Set_SPH();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Set_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Reset_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Set_CL();
    //delayMicroseconds(CLK_DELAY_US);
    EPD_Reset_CL();
    //delayMicroseconds(CLK_DELAY_US);
}


void EPaperDisplay::clearScreen(void)
{
	if (powerOn() < 0)
		return;

#if 0
    for (int k = 0; k < sz_clear_cycles; ++k)
    {
		scanVStart();
		EPD_Set_DATA(MAP2PIN(clear_cycles[k]));

		// Height of the display
		for (int i = 0; i < EPD_HEIGHT; ++i)
		{
			scanHStart();

			// Width of the display, 4 Pixels each.
			for (int j = 0; j < (EPD_WIDTH / 4); ++j)
			{
				clockPixel();
			}

			scanHEnd();
			latchRow();
			outputRow();
		}

		scanVEnd();

    } // End loop of Refresh Cycles Size
#else
    memset(getOffline()->getPtr(), 0, EPD_HEIGHT * EPD_WIDTH / 8);
    display();
#endif

    powerOff();
}


void EPaperDisplay::draw16Gray(const uint8_t* img_bytes) // 800x600 16gray
{
	if (powerOn() < 0)
		return;

	//for (int k = 0; k < 6; k++)
	for (int k = 0; k < sz_contrast_cycles; ++k)
	{
		for (int contrast_cnt = 0; contrast_cnt < contrast_cycles[k]; ++contrast_cnt)
		{
			scanVStart();

			// Height of the display
			for (int i = 0; i < EPD_HEIGHT; ++i)
			{
				const uint8_t *dp = img_bytes + ((EPD_HEIGHT - 1) - i) * (EPD_WIDTH / 2);

				scanHStart();

				// Width of the display, 4 Pixels each.
				for (int j = 0; j < (EPD_WIDTH / 4); ++j)
				{
					uint8_t pixel = 0b00000000;
					uint8_t pix1 = (*(dp) >> (7 - k)) & 1;
					uint8_t pix2 = (*(dp++) >> (3 - k)) & 1;
					uint8_t pix3 = (*(dp) >> (7 - k)) & 1;
					uint8_t pix4 = (*(dp++) >> (3 - k)) & 1;

					pixel |= (PIXEL2EPDCMD(pix1) << 6);
					pixel |= (PIXEL2EPDCMD(pix2) << 4);
					pixel |= (PIXEL2EPDCMD(pix3) << 2);
					pixel |= (PIXEL2EPDCMD(pix4) << 0);

					EPD_Set_DATA(MAP2PIN(pixel));
					clockPixel();
				}

				scanHEnd();
				latchRow();
				outputRow();
			}

			scanVEnd();
		} // End contrast count

	} // End loop of Refresh Cycles Size

	powerOff();
}

void EPaperDisplay::drawMono(const uint8_t* img_bytes)
{
	if (powerOn() < 0)
		return;

#if 0
    uint8_t data;
    uint8_t dram;

	for (int k = 0; k < 10; ++k)
	{
		const uint8_t* ptr = img_bytes + 59999;
		scanVStart();

		for (int i = 0; i < 600; ++i)
		{
			scanHStart();

			for (int j = 0; j < 800 / 8; ++j)
			{
				dram = *(ptr--);

				data = LUT_B[dram & 0x0F];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				data = LUT_B[dram >> 4];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();
			}

			scanHEnd();
			latchRow();
			outputRow();
		}

		scanVEnd();
	}

	//
	for (int k = 0; k < 10; ++k)
	{
		uint16_t _pos = 59999;

		scanVStart();

		for (int i = 0; i < 600; ++i)
		{
			scanHStart();

			for (int j = 0; j < 800 / 8; ++j)
			{
				dram = *(img_bytes + _pos);

				data = LUT_W[dram & 0x0F];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				data = LUT_W[dram >> 4];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				--_pos;
			}

			scanHEnd();
			latchRow();
			outputRow();
		}

		scanVEnd();
	}

	//
	/*
	EPD_VScanStart();

	for (int i = 0; i < 600; ++i)
	{
		EPD_HScanStart();

		for (int j = 0; j < 800 / 8; ++j)
		{
			//dram = *(img_bytes + _pos);

			data = 0;
			EPD_Set_DATA(MAP2PIN(data));
			EPD_ClockPixel();

			data = 0;
			EPD_Set_DATA(MAP2PIN(data));
			EPD_ClockPixel();

			//--_pos;
		}

		EPD_HScanEnd();
		EPD_OutputRow();
		EPD_LatchRow();
	}

	EPD_VScanEnd();
	*/
#else
    memcpy(getOffline()->getPtr(), img_bytes, EPD_HEIGHT * EPD_WIDTH / 8);
    display();
#endif

	powerOff();
}


void EPaperDisplay::drawMono2(const uint8_t* img_bytes)
{
	if (powerOn() < 0)
		return;

    uint8_t data;
    uint8_t dram;

	for (int k = 0; k < 10; ++k)
	{
		const uint8_t* ptr = img_bytes + 59999;
		scanVStart();

		for (int i = 0; i < 600; ++i)
		{
			scanHStart();

			for (int j = 0; j < 800 / 8; ++j)
			{
				dram = *(ptr--);

				data = LUT_W[dram & 0x0F];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				data = LUT_W[dram >> 4];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();
			}

			scanHEnd();
			latchRow();
			outputRow();
		}

		scanVEnd();
	}

	//
	for (int k = 0; k < 10; ++k)
	{
		uint16_t _pos = 59999;

		scanVStart();

		for (int i = 0; i < 600; ++i)
		{
			scanHStart();

			for (int j = 0; j < 800 / 8; ++j)
			{
				dram = *(img_bytes + _pos);

				data = LUT_B[dram & 0x0F];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				data = LUT_B[dram >> 4];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				--_pos;
			}

			scanHEnd();
			latchRow();
			outputRow();
		}

		scanVEnd();
	}

	powerOff();
}

void EPaperDisplay::drawPartial(const uint8_t* img_bytes, const uint8_t* old_bytes)
{
	/*
	uint8_t* tempPtr = (uint8_t *)(0xD0000000 + 800 / 8 * 600 * 3);

    uint8_t data;
    uint8_t dram;

    uint8_t diffw, diffb;
    uint32_t n = 119999;
    uint16_t _pos = 59999;

    for (int i = 0; i < 600; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            diffw = *(old_bytes + _pos) & ~*(img_bytes + _pos);
            diffb = ~*(old_bytes + _pos) & *(img_bytes + _pos);
            _pos--;
            *(tempPtr + n) = LUTW[diffw >> 4] & (LUTB[diffb >> 4]);
            n--;
            *(tempPtr + n) = LUTW[diffw & 0x0F] & (LUTB[diffb & 0x0F]);
            n--;
        }
    }

	for (int k = 0; k < 16; ++k)
	{
		n = 119999;
		EPD_VScanStart();

		for (int i = 0; i < 600; ++i)
		{
			EPD_HScanStart();

			for (int j = 0; j < 800 / 8; ++j)
			{
				data = *(tempPtr + n);
				n--;
				EPD_Set_DATA(MAP2PIN(data));
				EPD_ClockPixel();

				data = *(tempPtr + n);
				n--;
				EPD_Set_DATA(MAP2PIN(data));
				EPD_ClockPixel();
			}

			EPD_HScanEnd();
			EPD_OutputRow();
			EPD_LatchRow();
		}

		EPD_VScanEnd();
	}
	*/

	if (powerOn() < 0)
		return;

	uint8_t data;
	uint8_t dram;

	for (int k = 0; k < 16; ++k)
	{
		const uint8_t* ptr = img_bytes + 59999;
		scanVStart();

		for (int i = 0; i < 600; ++i)
		{
			scanHStart();

			for (int j = 0; j < 800 / 8; ++j)
			{
				dram = *(ptr--);

				data = LUT_BW[dram & 0x0F];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				data = LUT_BW[dram >> 4];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();
			}

			scanHEnd();
			latchRow();
			outputRow();
		}

		scanVEnd();
	}

	powerOff();
}

void EPaperDisplay::clear(uint8_t c, uint8_t rep)
{
    uint8_t cmd = 0;
    if (c == 0)
    	cmd = B10101010;
    else if (c == 1)
    	cmd = B01010101;
    else if (c == 2)
    	cmd = B00000000;
    else if (c == 3)
    	cmd = B11111111;

    uint32_t data = LUTpin[cmd];
    for (int k = 0; k < rep; ++k)
    {
    	scanVStart();
    	EPD_Set_DATA(data);

    	for (int i = 0; i < 600; ++i)
        {
    		scanHStart();

            for (int j = 0; j < 800 / 8; ++j)
            {
            	clockPixel();
            	clockPixel();
            }

			scanHEnd();
			latchRow();
			outputRow();
        }

    	scanVEnd();
    }
}

void EPaperDisplay::display()
{
    clear(0, 1);
    clear(1, 11); // 21
    clear(2, 1);
    clear(0, 12); // 22
    clear(2, 1);
    clear(1, 21);
    clear(2, 1);
    clear(0, 12);

	//
	uint8_t* pDispBufferPtr = getOnline()->getPtr();
	uint8_t* pBackBufferPtr = getOffline()->getPtr();
	uint8_t data;
	uint8_t dram;

	memcpy(pDispBufferPtr, pBackBufferPtr, EPD_HEIGHT * EPD_WIDTH / 8);

    for (int k = 0; k < 4; ++k)
    {
        uint8_t *DMemoryNewPtr = pDispBufferPtr + (EPD_WIDTH * EPD_HEIGHT / 8) - 1;
        scanVStart();

        for (int i = 0; i < EPD_HEIGHT; ++i)
        {
        	scanHStart();

            for (int j = 0; j < ((EPD_WIDTH / 8) - 0); ++j)
            {
            	dram = *(DMemoryNewPtr--);

            	data = _LUTB[dram >> 4];
                EPD_Set_DATA(MAP2PIN(data));
                clockPixel();

            	data = _LUTB[dram & 0x0F];
                EPD_Set_DATA(MAP2PIN(data));
                clockPixel();
            }

			scanHEnd();
			latchRow();
			outputRow();
        }

        scanVEnd();
    }

    uint16_t _pos = (EPD_WIDTH * EPD_HEIGHT / 8) - 1;
    {
		scanVStart();

		for (int i = 0; i < EPD_HEIGHT; ++i)
		{
			scanHStart();

			for (int j = 0; j < ((EPD_WIDTH / 8) - 0); ++j)
			{
				dram = *(pDispBufferPtr + _pos);
				_pos--;

				data = _LUT2[dram >> 4];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				data = _LUT2[dram & 0x0F];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();
			}

			scanHEnd();
			latchRow();
			outputRow();
		}

		scanVEnd();
    }

    {
		scanVStart();

		for (int i = 0; i < EPD_HEIGHT; ++i)
		{
			scanHStart();
			data = 0;

			for (int j = 0; j < ((EPD_WIDTH / 8) - 0); ++j)
			{
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();
			}

			scanHEnd();
			latchRow();
			outputRow();
		}

		scanVEnd();
    }
}

#endif // USE_MODEL_A

