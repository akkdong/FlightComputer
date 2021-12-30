/*
 * EPaperDisplay.cpp
 *
 *  Created on: 2021. 2. 1.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "EPaperDisplay.h"


#if USE_MODEL_A


#define CLK_DELAY_US  		0
#define VCLK_DELAY_US 		1
#define OUTPUT_DELAY_US   	2
#define CLEAR_BYTE    		0b10101010
#define DARK_BYTE     		0b01010101

#define PIXEL2EPDCMD(x)		(((x) == 1) ? 0b00000010 : (((x) == 0) ? 0b00000001 : 0b00000011))

#define MAP2PIN(x)			(LUTpin[(x)])




////////////////////////////////////////////////////////////////////////////////////////
//

#if R2L || 1

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


//
#if R2L
const uint8_t _LUT2[16] = {0xAA, 0xA9, 0xA6, 0xA5, 0x9A, 0x99, 0x96, 0x95,
                          0x6A, 0x69, 0x66, 0x65, 0x5A, 0x59, 0x56, 0x55};
const uint8_t _LUTW[16] = {0xFF, 0xFE, 0xFB, 0xFA, 0xEF, 0xEE, 0xEB, 0xEA,
                          0xBF, 0xBE, 0xBB, 0xBA, 0xAF, 0xAE, 0xAB, 0xAA};
const uint8_t _LUTB[16] = {0xFF, 0xFD, 0xF7, 0xF5, 0xDF, 0xDD, 0xD7, 0xD5,
                          0x7F, 0x7D, 0x77, 0x75, 0x5F, 0x5D, 0x57, 0x55};
#else // L2R

// 0 -> W : 10
// 1 -> B : 01


const uint8_t _LUT2[16] =
{
#if 0
	0x55, 0x95, 0x65, 0xA5,	// 00h:BBBB: 01010101, 01h:BBBW: 10010101, 02h:BBWB: 01100101, 03h:BBWW: 10100101
	0x59, 0x99, 0x69, 0xA9, // 04h:BWBB: 01011001, 05h:BWBW: 10011001, 06h:BWWB: 01101001, 07h:BWWW: 10101001
	0x56, 0x96, 0x66, 0xA6, // 08h:WBBB: 01010110, 09h:WBBW: 10010110, 0Ah:WBWB: 01100110, 0Bh:WBWW: 10100110
	0x5A, 0x9A, 0x6A, 0xAA  // 0Ch:WWBB: 01011010, 0Dh:WWBW: 10011010, 0Eh:WWWB: 01101010, 0Fh:WWWW: 10101010
#else
	0xAA, 0x6A, 0x9A, 0x5A, // 00h:WWWW: 10101010, 01h:WWWB: 01101010, 02h:WWBW: 10011010, 03h:WWBB: 01011010
	0xA6, 0x66, 0x96, 0x56, // 04h:WBWW: 10100110, 05h:WBWB: 01100110, 06h:WBBW: 10010110, 07h:WBBB: 01010110
	0xA9, 0x69, 0x99, 0x59, // 08h:BWWW: 10101001, 09h:BWWB: 01101001, 0Ah:BWBW: 10011001, 0Bh:BWBB: 01011001
	0xA5, 0x65, 0x95, 0x55  // 0Ch:BBWW: 10100101, 0Dh:BBWB: 01100101, 0Eh:BBBW: 10010101, 0Fh:BBBB: 01010101
#endif
};

const uint8_t _LUTW[16] =
{
	0xFF, 0xBF, 0xEF, 0xAF,	// 00h:----: 11111111, 01h:---W: 10111111, 02h:--W-: 11101111, 03h:--WW: 10101111
	0xFB, 0xBB, 0xEB, 0xAB, // 04h:-W--: 11111011, 05h:-W-W: 10111011, 06h:-WW-: 11101011, 07h:-WWW: 10101011
	0xFE, 0xBE, 0xEE, 0xAE, // 08h:W---: 11111110, 09h:W--W: 10111110, 0Ah:W-W-: 11101110, 0Bh:W-WW: 10101110
	0xFA, 0xBA, 0xEA, 0xAA  // 0Ch:WW--: 11111010, 0Dh:WW-W: 10111010, 0Eh:WWW-: 11101010, 0Fh:WWWW: 10101010
};

const uint8_t _LUTB[16] =
{
	0xFF, 0x7F, 0xDF, 0x5F,	// 00h:----: 11111111, 01h:---B: 01111111, 02h:--B-: 11011111, 03h:--BB: 01011111
	0xF7, 0x77, 0xD7, 0x57, // 04h:-B--: 11110111, 05h:-B-B: 01110111, 06h:-BB-: 11010111, 07h:-BBB: 01010111
	0xFD, 0x7D, 0xDD, 0x5D, // 08h:B---: 11111101, 09h:B--B: 01111101, 0Ah:B-B-: 11011101, 0Bh:B-BB: 01011101
	0xF5, 0x75, 0xD5, 0x55  // 0Ch:BB--: 11110101, 0Dh:BB-B: 01110101, 0Eh:BBB-: 11010101, 0Fh:BBBB: 01010101
};
#endif

// data to pin mapping table
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
	: Adafruit_GFX(EPD_WIDTH, EPD_HEIGHT)
	, mDisplay(EPD_WIDTH, EPD_HEIGHT, BPP_MONO)
	, mCanvas(EPD_WIDTH, EPD_HEIGHT, BPP_MONO)
	, mBuffer(EPD_WIDTH, EPD_HEIGHT * 2, BPP_MONO)
{
	// DATA Pin: GPIOD [12, 11, 7, 6, 5, 4, 3, 2]
	for (uint32_t i = 0; i < 256; i++)
	{
		uint32_t mask = ((i & 0b00111111) << 2) | (((i & 0b11000000) >> 6) << 11);
		LUTpin[i] = (((~mask) & 0b0001100011111100) << GPIO_NUMBER) | mask;
	}
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
    	Serial.println("PMIC wakeup failed!");
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
    delayMicroseconds(16/*OUTPUT_DELAY_US*/);
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

void EPaperDisplay::startVScan(void)
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

void EPaperDisplay::endVScan(void)
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

void EPaperDisplay::startHScan(void)
{
    // HSCANSTART
    //EPD_Set_OE();
    EPD_Reset_SPH();
    // END HSCANSTART
}

void EPaperDisplay::endHScan(void)
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
#if 0
	memset(mCanvas.getPtr(), COLOR_WHITE, EPD_HEIGHT * EPD_WIDTH / 8);
#else
	volatile uint32_t* ptr = (volatile uint32_t *)mCanvas.getPtr();
	for (int i = 0; i < EPD_HEIGHT * EPD_WIDTH / 8 / 4; i++)
		*ptr++ = 0x00;
#endif
}

void EPaperDisplay::drawBitmapBM(const uint8_t *bitmap, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, int16_t mode)
{
  uint16_t inverse_color = (color != COLOR_WHITE) ? COLOR_WHITE : COLOR_BLACK;
  uint16_t fg_color = (mode & bm_invert) ? inverse_color : color;
  uint16_t bg_color = (mode & bm_invert) ? color : inverse_color;
  // taken from Adafruit_GFX.cpp, modified
  int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
  uint8_t byte = 0;
  if (mode & bm_transparent)
  {
    for (int16_t j = 0; j < h; j++)
    {
      for (int16_t i = 0; i < w; i++ )
      {
        if (i & 7) byte <<= 1;
        else
        {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
          byte = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
#else
          byte = bitmap[j * byteWidth + i / 8];
#endif
        }
        // transparent mode
        if (bool(mode & bm_invert) != bool(byte & 0x80))
        //if (!(byte & 0x80))
        {
          uint16_t xd = x + i;
          uint16_t yd = y + j;
          if (mode & bm_flip_x) xd = x + w - i;
          if (mode & bm_flip_y) yd = y + h - j;
          drawPixel(xd, yd, color);
        }
      }
    }
  }
  else
  {
    for (int16_t j = 0; j < h; j++)
    {
      for (int16_t i = 0; i < w; i++ )
      {
        if (i & 7) byte <<= 1;
        else
        {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
          byte = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
#else
          byte = bitmap[j * byteWidth + i / 8];
#endif
        }
        // keep using overwrite mode
        uint16_t pixelcolor = (byte & 0x80) ? fg_color  : bg_color;
        uint16_t xd = x + i;
        uint16_t yd = y + j;
        if (mode & bm_flip_x) xd = x + w - i;
        if (mode & bm_flip_y) yd = y + h - j;
        drawPixel(xd, yd, pixelcolor);
      }
    }
  }
}


#if OBSOLETE
void EPaperDisplay::draw16Gray(const uint8_t* img_bytes) // 800x600 16gray
{
	if (powerOn() < 0)
		return;

	//for (int k = 0; k < 6; k++)
	for (int k = 0; k < sz_contrast_cycles; ++k)
	{
		for (int contrast_cnt = 0; contrast_cnt < contrast_cycles[k]; ++contrast_cnt)
		{
			startVScan();

			// Height of the display
			for (int i = 0; i < EPD_HEIGHT; ++i)
			{
				const uint8_t *dp = img_bytes + ((EPD_HEIGHT - 1) - i) * (EPD_WIDTH / 2);

				startHScan();

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

				endHScan();
				latchRow();
				outputRow();
			}

			endVScan();
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
		startVScan();

		for (int i = 0; i < 600; ++i)
		{
			startHScan();

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

			endHScan();
			latchRow();
			outputRow();
		}

		endVScan();
	}

	//
	for (int k = 0; k < 10; ++k)
	{
		uint16_t _pos = 59999;

		startVScan();

		for (int i = 0; i < 600; ++i)
		{
			startHScan();

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

			endHScan();
			latchRow();
			outputRow();
		}

		endVScan();
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
    //memcpy(getOffline()->getPtr(), img_bytes, EPD_HEIGHT * EPD_WIDTH / 8);
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
		startVScan();

		for (int i = 0; i < 600; ++i)
		{
			startHScan();

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

			endHScan();
			latchRow();
			outputRow();
		}

		endVScan();
	}

	//
	for (int k = 0; k < 10; ++k)
	{
		uint16_t _pos = 59999;

		startVScan();

		for (int i = 0; i < 600; ++i)
		{
			startHScan();

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

			endHScan();
			latchRow();
			outputRow();
		}

		endVScan();
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
		startVScan();

		for (int i = 0; i < 600; ++i)
		{
			startHScan();

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

			endHScan();
			latchRow();
			outputRow();
		}

		endVScan();
	}

	powerOff();
}
#endif // OBSOLETE


void EPaperDisplay::refresh(bool fast)
{
	if (powerOn() < 0)
			return;

	if (fast)
		fastUpdate();
	else
		display();

	powerOff();
}


void EPaperDisplay::clear(uint8_t c, uint8_t rep)
{
    uint8_t cmd = 0;
    if (c == 0)  		// WHITE
    	cmd = B10101010;
    else if (c == 1) 	// BLACK
    	cmd = B01010101;
    else if (c == 2)	// SKIP
    	cmd = B00000000;
    else if (c == 3)	// UNCHARGE
    	cmd = B11111111;

    uint32_t data = LUTpin[cmd];
    for (int k = 0; k < rep; ++k)
    {
    	startVScan();
    	EPD_Set_DATA(data);

    	for (int i = 0; i < 600; ++i)
        {
    		startHScan();

            for (int j = 0; j < 800 / 8; ++j)
            {
            	clockPixel();
            	clockPixel();
            }

			endHScan();
			latchRow();
			outputRow();
        }

    	endVScan();
    }
}

void EPaperDisplay::display()
{
    clear(0, 1);
    clear(1, 16); // 21
    clear(2, 1);
    clear(0, 18); // 22
    clear(2, 1);
    clear(1, 16); // 21
    clear(2, 1);
    clear(0, 16);

	//
    volatile uint8_t* pDisplayPtr = mDisplay.getPtr();
    volatile uint8_t* pCanvasPtr = mCanvas.getPtr();
	uint8_t data;
	uint8_t dram;

#if 0
	memcpy(pDisplayPtr, pCanvasPtr, EPD_HEIGHT * EPD_WIDTH / 8);
#else
	volatile uint32_t* srcPtr = (volatile uint32_t *)pCanvasPtr;
	volatile uint32_t* dstPtr = (volatile uint32_t *)pDisplayPtr;
	for (int i = 0; i < EPD_HEIGHT * EPD_WIDTH / 8 / 4; i++)
		*dstPtr++ = *srcPtr++;
#endif

    for (int k = 0; k < 4; ++k)
    {
        volatile uint8_t* pDispPtr = pDisplayPtr + (EPD_WIDTH * EPD_HEIGHT / 8) - 1;
        startVScan();

        for (int i = 0; i < EPD_HEIGHT; ++i)
        {
        	startHScan();

            for (int j = 0; j < ((EPD_WIDTH / 8) - 0); ++j)
            {
            	dram = *(pDispPtr--);

            	data = _LUTB[dram & 0x0F];
                EPD_Set_DATA(MAP2PIN(data));
                clockPixel();

            	data = _LUTB[dram >> 4];
                EPD_Set_DATA(MAP2PIN(data));
                clockPixel();
            }

			endHScan();
			latchRow();
			outputRow();
        }

        endVScan();
    }

    {
    	volatile uint8_t* pDispPtr = pDisplayPtr + (EPD_WIDTH * EPD_HEIGHT / 8) - 1;
		startVScan();

		for (int i = 0; i < EPD_HEIGHT; ++i)
		{
			startHScan();

			for (int j = 0; j < ((EPD_WIDTH / 8) - 0); ++j)
			{
				dram = *(pDispPtr--);

				data = _LUT2[dram & 0x0F];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				data = _LUT2[dram >> 4];
				EPD_Set_DATA(MAP2PIN(data));
				clockPixel();
			}

			endHScan();
			latchRow();
			outputRow();
		}

		endVScan();
    }

#if 1
    {
		startVScan();

		for (int i = 0; i < EPD_HEIGHT; ++i)
		{
			startHScan();
			//data = 0;
			EPD_Set_DATA(MAP2PIN(0));

			for (int j = 0; j < ((EPD_WIDTH / 8) - 0); ++j)
			{
				//EPD_Set_DATA(MAP2PIN(data));
				clockPixel();

				//EPD_Set_DATA(MAP2PIN(data));
				clockPixel();
			}

			endHScan();
			latchRow();
			outputRow();
		}

		endVScan();
    }
#else
    clear(2, 1);
#endif
}

void EPaperDisplay::fastUpdate()
{
	volatile uint8_t* pDisplayPtr = mDisplay.getPtr();
	volatile uint8_t* pCanvasPtr = mCanvas.getPtr();

    for (int k = 0; k < 5; ++k)
    {
    	volatile uint8_t* pOldPtr = pDisplayPtr + (EPD_WIDTH * EPD_HEIGHT / 8) - 1;
    	volatile uint8_t* pNewPtr = pCanvasPtr + (EPD_WIDTH * EPD_HEIGHT / 8) - 1;
    	uint8_t data_o, data_n;
    	uint8_t diff_w, diff_b;
    	uint8_t output;

    	startVScan();

        for (int i = 0; i < EPD_HEIGHT; ++i)
        {
            startHScan();

            for (int j = 0; j < EPD_WIDTH / 8; ++j)
            {
            	data_o = *(pOldPtr--);
            	data_n = *(pNewPtr--);

                diff_w = data_o & (~data_n);
                diff_b = (~data_o) & data_n;

                output = _LUTW[diff_w & 0x0F] & _LUTB[diff_b & 0x0F];
				EPD_Set_DATA(MAP2PIN(output));
				clockPixel();

				output = _LUTW[diff_w >> 4] & _LUTB[diff_b >> 4];
				EPD_Set_DATA(MAP2PIN(output));
				clockPixel();
            }

			endHScan();
			latchRow();
			outputRow();
        }

        endVScan();
    }

    clear(2, 2);
    clear(3, 1);

#if 0
    memcpy(pDisplayPtr, pCanvasPtr, EPD_WIDTH * EPD_HEIGHT / 8);
#else
	volatile uint8_t* srcPtr = pCanvasPtr;
	volatile uint8_t* dstPtr = pDisplayPtr;
	for (int i = 0; i < EPD_HEIGHT * EPD_WIDTH / 8; i++)
		*dstPtr++ = *srcPtr++;
#endif
}

void EPaperDisplay::partialUpdate(bool forced)
{
    //if (getDisplayMode() == 1)
    //	return;

    //if (/*_blockPartial == 1 &&*/ !forced)
    //{
	//	display();
	//	return;
    //}

	volatile uint8_t* pDisplayPtr = mDisplay.getPtr();
	volatile uint8_t* pCanvasPtr = mCanvas.getPtr();
	volatile uint8_t* pBufferPtr = mBuffer.getPtr();

	uint32_t srcIndex = (EPD_WIDTH * EPD_HEIGHT / 8) - 1;
    uint32_t dstIndex = (EPD_WIDTH * EPD_HEIGHT / 4) - 1;
    uint8_t data_o, data_n, diff_w, diff_b;

    for (int i = 0; i < EPD_HEIGHT / 2; ++i)
    {
        for (int j = 0; j < EPD_WIDTH / 8; ++j)
        {
        	data_o = pDisplayPtr[srcIndex];
        	data_n = pCanvasPtr[srcIndex];
            diff_w = data_o & (~data_n);
            diff_b = (~data_o) & data_n;
            srcIndex--;

            pBufferPtr[dstIndex] = _LUTW[diff_w >> 4] & _LUTB[diff_b >> 4];
            dstIndex--;
            pBufferPtr[dstIndex] = _LUTW[diff_w & 0x0F] & _LUTB[diff_b & 0x0F];
            dstIndex--;
        }
    }

#if 0
	if (!einkOn())
	{
		return;
	}
#endif

    for (int k = 0; k < 5; ++k)
    {
    	dstIndex = (EPD_WIDTH * EPD_HEIGHT / 4) - 1;
    	startVScan();

        for (int i = 0; i < EPD_HEIGHT; ++i)
        {
            startHScan();

            for (int j = 0; j < EPD_WIDTH / 4; ++j)
            {
				EPD_Set_DATA(MAP2PIN(pBufferPtr[dstIndex]));
				dstIndex--;

				clockPixel();
            }

			endHScan();
			latchRow();
			outputRow();
        }

        endVScan();
    }

    clear(2, 2);
    clear(3, 1);

#if 0
    memcpy(pDisplayPtr, pCanvasPtr, EPD_WIDTH * EPD_HEIGHT / 8);
#else
	volatile uint32_t* srcPtr = (volatile uint32_t *)pCanvasPtr;
	volatile uint32_t* dstPtr = (volatile uint32_t *)pDisplayPtr;
	for (int i = 0; i < EPD_HEIGHT * EPD_WIDTH / 8 / 4; i++)
		*dstPtr++ = *srcPtr++;
#endif
}


void EPaperDisplay::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
		return;

//	if (_mirror)
//		x = _width - x - 1;

	// check rotation, move pixel around if necessary
	switch (getRotation())
	{
	case 1:
		_swap_(x, y);
		x = _width - x - 1;
		break;
	case 2:
		x = _width - x - 1;
		y = _height - y - 1;
		break;
	case 3:
		_swap_(x, y);
		y = _height - y - 1;
	break;
	}

	#if 0
	// transpose partial window to 0,0
	x -= _window_x;
	y -= _window_y;

	// clip to (partial) window
	if ((x < 0) || (x >= _window_w) || (y < 0) || (y >= _window_h))
		return;

	if (_reverse)
		y = _height - y - 1;

	if ((y < 0) || (y >= _height))
		return;

	uint16_t i = x / 8 + y * (_window_w / 8);
	#endif

	volatile uint8_t* _buffer = mCanvas.getPtr();
	uint16_t i = x / 8 + y * (_width / 8);

	if (color)
		_buffer[i] = (_buffer[i] | (1 << (7 - (x % 8))));
	else
		_buffer[i] = (_buffer[i] & (~(1 << (7 - (x % 8)))));
}


#endif // USE_MODEL_A

