/*
 * epd_drv.c
 *
 *  Created on: 2021. 1. 6.
 *      Author: akkdong
 */

#include <string.h>
#include "epd_drv.h"

#define EPD_WIDTH     		800
#define EPD_HEIGHT    		600
#define CLK_DELAY_US  		1
#define VCLK_DELAY_US 		1
#define OUTPUT_DELAY_US   	2
#define CLEAR_BYTE    		0b10101010
#define DARK_BYTE     		0b01010101

#define PIXEL2EPDCMD(x)		(((x) == 1) ? 0b00000010 : (((x) == 0) ? 0b00000001 : 0b00000011))

#define DWT_Delay_ms(x)		if ((x) > 0) HAL_Delay(x)



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

const uint8_t LUT2[16] =
{
	0xAA, 0x6A, 0x9A, 0x5A,
	0xA6, 0x66, 0x96, 0x56,
	0xA9, 0x69, 0x99, 0x59,
	0xA5, 0x65, 0x95, 0x55
};

const uint8_t LUTW[16] =
{
	0xFF, 0xBF, 0xEF, 0xAF,
	0xFB, 0xBB, 0xEB, 0xAB,
	0xFE, 0xBE, 0xEE, 0xAE,
	0xFA, 0xBA, 0xEA, 0xAA
};

const uint8_t LUTB[16] =
{
	0xFF, 0x7F, 0xDF, 0x5F,
	0xF7, 0x77, 0xD7, 0x57,
	0xFD, 0x7D, 0xDD, 0x5D,
	0xF5, 0x75, 0xD5, 0x55
};

#endif

uint32_t pinLUT[256];


/* Contrast cycles in order of contrast (Darkest first).  */
const uint8_t contrast_cycles[] = {4,4,4,4};
const uint8_t sz_contrast_cycles = sizeof(contrast_cycles)/sizeof(uint8_t);

/* Screen clearing state */
const uint8_t clear_cycles[] = {
  CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE,
  CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE,
  DARK_BYTE, DARK_BYTE, DARK_BYTE, DARK_BYTE, DARK_BYTE, DARK_BYTE,
  CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE,
  CLEAR_BYTE, CLEAR_BYTE, CLEAR_BYTE,
  CLEAR_BYTE,
};
const uint8_t sz_clear_cycles = sizeof(clear_cycles)/sizeof(uint8_t);



////////////////////////////////////////////////////////////////////////////////////////
//


/**
 * @brief  Initializes DWT_Clock_Cycle_Count for DWT_Delay_us function
 * @return Error DWT counter
 *         1: clock cycle counter not started
 *         0: clock cycle counter works
 */
uint32_t DWT_Delay_Init(void) {
	/* Disable TRC */
	CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
	/* Enable TRC */
	CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

	/* Disable clock cycle counter */
	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
	/* Enable  clock cycle counter */
	DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

	/* Reset the clock cycle counter value */
	DWT->CYCCNT = 0;

	/* 3 NO OPERATION instructions */
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");

	/* Check if clock cycle counter has started */
	if(DWT->CYCCNT)
	{
		return 0; /*clock cycle counter started*/
	}
	else
	{
		return 1; /*clock cycle counter not started*/
	}
}



/**
 * @brief  This function provides a delay (in microseconds)
 * @param  microseconds: delay in microseconds
 */
__STATIC_INLINE void DWT_Delay_us(volatile uint32_t microseconds)
{
	if (microseconds == 0)
		return;

	uint32_t clk_cycle_start = DWT->CYCCNT;

	/* Go to number of cycles for system */
	microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);

	/* Delay till end */
	while ((DWT->CYCCNT - clk_cycle_start) < microseconds);
}



void EPD_Init(void)
{
	// DATA Pin: GPIOD [12, 11, 7, 6, 5, 4, 3, 2]
	for (uint32_t i = 0; i < 256; i++)
	{
		uint32_t mask = ((i & 0b00111111) << 2) | (((i & 0b11000000) >> 6) << 11);
		pinLUT[i] = (((~mask) & 0b0001100011111100) << GPIO_NUMBER) | mask;
	}

	EPD_Reset_GMODE();
	EPD_Reset_CKV();
	EPD_Reset_CL();
	EPD_Set_SPH();
	EPD_Set_SPV();
	EPD_Reset_LE();
	EPD_Reset_OE();

	EPD_Set_DATA(0);

	DWT_Delay_Init();
}



void EPD_ClockPixel(void)
{
	EPD_Set_CL();
	//DWT_Delay_us(CLK_DELAY_US);
	EPD_Reset_CL();
	//DWT_Delay_us(CLK_DELAY_US);
}

void EPD_OutputRow(void)
{
    // OUTPUTROW
	DWT_Delay_us(OUTPUT_DELAY_US);
	EPD_Set_OE();
	EPD_Set_CKV();
	DWT_Delay_us(OUTPUT_DELAY_US);
    EPD_Reset_CKV();
    DWT_Delay_us(OUTPUT_DELAY_US);
    EPD_Reset_OE();
    // END OUTPUTROW

    // NEXTROW START
    EPD_Set_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Reset_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Set_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Reset_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Set_CKV();
    // END NEXTROW
}

void EPD_LatchRow(void)
{
	EPD_Set_LE();
	DWT_Delay_us(CLK_DELAY_US);
    EPD_Set_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Reset_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Set_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Reset_CL();
    DWT_Delay_us(CLK_DELAY_US);

    EPD_Reset_LE();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Set_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Reset_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Set_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Reset_CL();
    DWT_Delay_us(CLK_DELAY_US);
}

void EPD_VScanStart(void)
{
    // VSCANSTART
    EPD_Set_GMODE();
    //EPD_Set_OE();
    DWT_Delay_us(500);

    EPD_Set_SPV();
    DWT_Delay_us(VCLK_DELAY_US);
    EPD_Reset_CKV();
    DWT_Delay_us(VCLK_DELAY_US);
    EPD_Set_CKV();
    DWT_Delay_us(VCLK_DELAY_US);

    EPD_Reset_SPV();
    DWT_Delay_us(VCLK_DELAY_US);
    EPD_Reset_CKV();
    DWT_Delay_us(VCLK_DELAY_US);
    EPD_Set_CKV();
    DWT_Delay_us(VCLK_DELAY_US);

    EPD_Set_SPV();
    DWT_Delay_us(VCLK_DELAY_US);
    EPD_Reset_CKV();
    DWT_Delay_us(VCLK_DELAY_US);
    //EPD_Set_CKV();
    DWT_Delay_us(VCLK_DELAY_US);
    // END VSCANSTART
}

void EPD_VScanEnd(void)
{
#if 0
    // VSCANEND
	EPD_Set_DATA(0b00000000);
	EPD_HScanStart();
    for (int j = 0; j < 200; ++j)
    {
            EPD_Set_CL();
            //DWT_Delay_us(CLK_DELAY_US);
            EPD_Reset_CL();
            //DWT_Delay_us(CLK_DELAY_US);
    }
    EPD_HScanEnd();
    //noInterrupts();
    EPD_Set_OE();
    EPD_Set_CKV();
    DWT_Delay_us(1);
    EPD_Reset_CKV();
    DWT_Delay_us(1);
    EPD_Reset_OE();
    //interrupts();
    EPD_Set_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Reset_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Set_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Reset_CL();
    DWT_Delay_us(CLK_DELAY_US);
    DWT_Delay_us(1);
    EPD_Reset_CKV();
    EPD_Reset_OE();
    DWT_Delay_us(50);
    EPD_Set_CKV();
    DWT_Delay_us(50);
    EPD_Reset_CKV();
    DWT_Delay_us(1);
    EPD_Reset_GMODE();
    DWT_Delay_us(1);
    // END VSCANEND

#else

    EPD_Reset_CKV();
    DWT_Delay_us(1);
    EPD_Reset_GMODE();
    DWT_Delay_us(1);

#endif
}

void EPD_HScanStart(void)
{
    // HSCANSTART
    EPD_Set_OE();
    EPD_Reset_SPH();
    // END HSCANSTART
}

void EPD_HScanEnd(void)
{
    // HSCANEND
    EPD_Set_SPH();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Set_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Reset_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Set_CL();
    DWT_Delay_us(CLK_DELAY_US);
    EPD_Reset_CL();
    DWT_Delay_us(CLK_DELAY_US);
}



void EPD_ClearScreen(void)
{
	EPD_Set_DATA(CLEAR_BYTE);

    for (int k = 0; k < sz_clear_cycles; ++k)
    {
		EPD_VScanStart();
		EPD_Set_DATA(clear_cycles[k]);

		// Height of the display
		for (int i = 0; i < EPD_HEIGHT; ++i)
		{
			EPD_HScanStart();

			// Width of the display, 4 Pixels each.
			for (int j = 0; j < (EPD_WIDTH / 4); ++j)
			{
				EPD_ClockPixel();
			}

			EPD_HScanEnd();
			EPD_OutputRow();
			EPD_LatchRow();
		}

		EPD_VScanEnd();

    } // End loop of Refresh Cycles Size
}


void EPD_Draw16Gray(const uint8_t* img_bytes) // 800x600 16gray
{
	//for (int k = 0; k < 6; k++)
	for (int k = 0; k < sz_contrast_cycles; ++k)
	{
		for (int contrast_cnt = 0; contrast_cnt < contrast_cycles[k]; ++contrast_cnt)
		{
			EPD_VScanStart();

			// Height of the display
			for (int i = 0; i < EPD_HEIGHT; ++i)
			{
				const uint8_t *dp = img_bytes + ((EPD_HEIGHT - 1) - i) * (EPD_WIDTH / 2);

				EPD_HScanStart();

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
					EPD_ClockPixel();
				}

				EPD_HScanEnd();
				EPD_OutputRow();
				EPD_LatchRow();
			}

			EPD_VScanEnd();
		} // End contrast count

	} // End loop of Refresh Cycles Size
}

void EPD_DrawMono(const uint8_t* img_bytes)
{
    uint8_t data;
    uint8_t dram;

	for (int k = 0; k < 12; ++k)
	{
		const uint8_t* ptr = img_bytes + 59999;
		EPD_VScanStart();

		for (int i = 0; i < 600; ++i)
		{
			EPD_HScanStart();

			for (int j = 0; j < 800 / 8; ++j)
			{
				dram = *(ptr--);

				data = LUTB[dram & 0x0F];
				EPD_Set_DATA(data);
				EPD_ClockPixel();

				data = LUTB[dram >> 4];
				EPD_Set_DATA(data);
				EPD_ClockPixel();
			}

			EPD_HScanEnd();
			EPD_OutputRow();
			EPD_LatchRow();
		}

		EPD_VScanEnd();
	}

	//
	for (int k = 0; k < 12; ++k)
	{
		uint16_t _pos = 59999;

		EPD_VScanStart();

		for (int i = 0; i < 600; ++i)
		{
			EPD_HScanStart();

			for (int j = 0; j < 800 / 8; ++j)
			{
				dram = *(img_bytes + _pos);

				data = LUT2[dram & 0x0F];
				EPD_Set_DATA(data);
				EPD_ClockPixel();

				data = LUT2[dram >> 4];
				EPD_Set_DATA(data);
				EPD_ClockPixel();

				--_pos;
			}

			EPD_HScanEnd();
			EPD_OutputRow();
			EPD_LatchRow();
		}

		EPD_VScanEnd();
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
}

void EPD_DrawPartial(const uint8_t* img_bytes, const uint8_t* old_bytes)
{
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
}


//
//
//
//
//


void epd_vscan_start()
{
    EPD_Set_CKV(); //CKV_SET;
    DWT_Delay_us(7);
    EPD_Reset_SPV(); //SPV_CLEAR;
    DWT_Delay_us(10);
    EPD_Reset_CKV(); //CKV_CLEAR;
    DWT_Delay_us(0);
    EPD_Set_CKV(); //CKV_SET;
    DWT_Delay_us(8);
    EPD_Set_SPV(); //SPV_SET;
    DWT_Delay_us(10);
    EPD_Reset_CKV(); //CKV_CLEAR;
    DWT_Delay_us(0);
    EPD_Set_CKV(); //CKV_SET;
    DWT_Delay_us(18);
    EPD_Reset_CKV(); //CKV_CLEAR;
    DWT_Delay_us(0);
    EPD_Set_CKV(); //CKV_SET;
    DWT_Delay_us(18);
    EPD_Reset_CKV(); //CKV_CLEAR;
    DWT_Delay_us(0);
    EPD_Set_CKV(); //CKV_SET;
}

void epd_hscan_start(uint32_t _d)
{
    EPD_Reset_SPH(); //SPH_CLEAR;

    //GPIO.out_w1ts = (_d) | CL;
    //GPIO.out_w1tc = DATA | CL;
	EPD_Set_DATA(_d);
	EPD_Set_CL();
	EPD_Set_DATA(0);
	EPD_Reset_CL();

    EPD_Set_SPH(); //SPH_SET;
    EPD_Set_CKV(); //CKV_SET;
}

void epd_vscan_end()
{
    EPD_Reset_CKV(); //CKV_CLEAR;
    EPD_Set_LE(); //LE_SET;
    EPD_Reset_LE(); //LE_CLEAR;
    DWT_Delay_us(0);
}

#define DATA (0x00)

void epd_clearFast(uint8_t c, uint8_t rep)
{
	uint8_t data = 0;
	if (c == 0)
		data = 0b10101010;
	else if (c == 1)
		data = 0b01010101;
	else if (c == 2)
		data = 0b00000000;
	else if (c == 3)
		data = 0b11111111;

	//uint32_t _send = pinLUT[data];
	for (int k = 0; k < rep; ++k)
	{
		epd_vscan_start();

		for (int i = 0; i < 600; ++i)
		{
			epd_hscan_start(data);

			//GPIO.out_w1ts = (_send) | CL;
			//GPIO.out_w1tc = DATA | CL;
			EPD_Set_DATA(data);
			EPD_Set_CL();
			EPD_Set_DATA(0);
			EPD_Reset_CL();

			for (int j = 0; j < 99; ++j)
			{
				//GPIO.out_w1ts = (_send) | CL;
				//GPIO.out_w1tc = DATA | CL;
				//GPIO.out_w1ts = (_send) | CL;
				//GPIO.out_w1tc = DATA | CL;

				EPD_Set_DATA(data);
				EPD_Set_CL();
				EPD_Set_DATA(0);
				EPD_Reset_CL();

				EPD_Set_DATA(data);
				EPD_Set_CL();
				EPD_Set_DATA(0);
				EPD_Reset_CL();
			}

			//GPIO.out_w1ts = (_send) | CL;
			//GPIO.out_w1tc = DATA | CL;

			EPD_Set_DATA(data);
			EPD_Set_CL();
			EPD_Set_DATA(0);
			EPD_Reset_CL();

			epd_vscan_end();
		}
		DWT_Delay_us(230);
	}
}


void epd_init(void)
{
    EPD_Reset_LE(); // LE_CLEAR;
    EPD_Reset_OE(); // OE_CLEAR;
    EPD_Reset_CL(); // CL_CLEAR;
    EPD_Set_SPH(); // SPH_SET;
    EPD_Set_GMODE(); // GMOD_SET;
    EPD_Set_SPV(); // SPV_SET;
    EPD_Reset_CKV(); // CKV_CLEAR;
    EPD_Reset_OE(); // OE_CLEAR;

    EPD_Set_OE(); // OE_SET;
}

void epd_clearScreen(void)
{
	EPD_Set_GMODE();
	DWT_Delay_us(500);

    epd_clearFast(0, 1);
    epd_clearFast(1, 21);
    epd_clearFast(2, 1);
    epd_clearFast(0, 12);
    epd_clearFast(2, 1);
    epd_clearFast(1, 21);
    epd_clearFast(2, 1);
    epd_clearFast(0, 12);

    EPD_Reset_GMODE();
}
