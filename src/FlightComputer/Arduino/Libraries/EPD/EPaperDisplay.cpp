/*
 * EPaperDisplay.cpp
 *
 *  Created on: 2021. 2. 1.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "EPaperDisplay.h"


#if MODEL_A

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


#endif

uint32_t pinLUT[256];


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
		pinLUT[i] = (((~mask) & 0b0001100011111100) << GPIO_NUMBER) | mask;
	}

	mActivePtr = &mPrimary;
}


void EPaperDisplay::begin(void)
{
	//
	mEPaperPMIC.init();

	//
	EPD_Reset_GMODE();
	EPD_Reset_CKV();
	EPD_Reset_CL();
	EPD_Set_SPH();
	EPD_Set_SPV();
	EPD_Reset_LE();
	EPD_Reset_OE();

	EPD_Set_DATA(0);
}

void EPaperDisplay::end()
{
}


void EPaperDisplay::powerOn(void)
{
    EPD_Set_GMODE();
    //EPD_Set_OE();
    delayMicroseconds(0);
}

void EPaperDisplay::powerOff(void)
{
	EPD_Reset_GMODE();
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
    delayMicroseconds(200/*OUTPUT_DELAY_US*/);
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
	EPD_Set_DATA(0b00000000);
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
	powerOn();

    for (int k = 0; k < sz_clear_cycles; ++k)
    {
		scanVStart();
		EPD_Set_DATA(clear_cycles[k]);

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

    powerOff();
}


void EPaperDisplay::draw16Gray(const uint8_t* img_bytes) // 800x600 16gray
{
	powerOn();

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

					EPD_Set_DATA(pixel);
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
	powerOn();

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
				EPD_Set_DATA(data);
				clockPixel();

				data = LUT_B[dram >> 4];
				EPD_Set_DATA(data);
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
				EPD_Set_DATA(data);
				clockPixel();

				data = LUT_W[dram >> 4];
				EPD_Set_DATA(data);
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
			EPD_Set_DATA(data);
			EPD_ClockPixel();

			data = 0;
			EPD_Set_DATA(data);
			EPD_ClockPixel();

			//--_pos;
		}

		EPD_HScanEnd();
		EPD_OutputRow();
		EPD_LatchRow();
	}

	EPD_VScanEnd();
	*/

	powerOff();
}


void EPaperDisplay::drawMono2(const uint8_t* img_bytes)
{
	powerOn();

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
				EPD_Set_DATA(data);
				clockPixel();

				data = LUT_W[dram >> 4];
				EPD_Set_DATA(data);
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
				EPD_Set_DATA(data);
				clockPixel();

				data = LUT_B[dram >> 4];
				EPD_Set_DATA(data);
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
				EPD_Set_DATA(data);
				EPD_ClockPixel();

				data = *(tempPtr + n);
				n--;
				EPD_Set_DATA(data);
				EPD_ClockPixel();
			}

			EPD_HScanEnd();
			EPD_OutputRow();
			EPD_LatchRow();
		}

		EPD_VScanEnd();
	}
	*/

	powerOn();

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
				EPD_Set_DATA(data);
				clockPixel();

				data = LUT_BW[dram >> 4];
				EPD_Set_DATA(data);
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


#endif // MODEL_A

