/*
 * EPaperDisplay.cpp
 *
 *  Created on: 2021. 11. 18.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "EPaperDisplay.h"


#if !MODEL_A  // MODEL_B(InkPlate)

#define EPD_WIDTH     		800
#define EPD_HEIGHT    		600
#define BPP_MONO			1
#define BPP_16GRAY			4

#define CLK_DELAY_US  		0
#define VCLK_DELAY_US 		1
#define OUTPUT_DELAY_US   	2
#define CLEAR_BYTE    		0b10101010
#define DARK_BYTE     		0b01010101



#define E_INK_WIDTH			EPD_WIDTH
#define E_INK_HEIGHT		EPD_HEIGHT

#define CL_SET				EPD_Set_CL()
#define CL_CLEAR			EPD_Reset_CL()

#define CKV_SET				EPD_Set_CKV()
#define CKV_CLEAR			EPD_Reset_CKV()

#define SPH_SET				EPD_Set_SPH()
#define SPH_CLEAR			EPD_Reset_SPH()

#define LE_SET				EPD_Set_LE()
#define LE_CLEAR			EPD_Reset_LE()

#define OE_SET				EPD_Set_OE()
#define OE_CLEAR			EPD_Reset_OE()

#define GMOD_SET			EPD_Set_GMODE()
#define GMOD_CLEAR			EPD_Reset_GMODE()

#define SPV_SET				EPD_Set_SPV()
#define SPV_CLEAR			EPD_Reset_SPV()



////////////////////////////////////////////////////////////////////////////////////////
//

const uint8_t LUT2[16] =
{
	0xAA, 0xA9, 0xA6, 0xA5, 0x9A, 0x99, 0x96, 0x95,
	0x6A, 0x69, 0x66, 0x65, 0x5A, 0x59, 0x56, 0x55
};

const uint8_t LUTW[16] =
{
	0xFF, 0xFE, 0xFB, 0xFA, 0xEF, 0xEE, 0xEB, 0xEA,
	0xBF, 0xBE, 0xBB, 0xBA, 0xAF, 0xAE, 0xAB, 0xAA
};

const uint8_t LUTB[16] =
{
	0xFF, 0xFD, 0xF7, 0xF5, 0xDF, 0xDD, 0xD7, 0xD5,
	0x7F, 0x7D, 0x77, 0x75, 0x5F, 0x5D, 0x57, 0x55
};




/////////////////////////////////////////////////////////////////////////////////////////////////
// class EPaperDisplay

EPaperDisplay::EPaperDisplay()
	: mDispBuffer(EPD_WIDTH, EPD_HEIGHT, BPP_MONO)
	, mBackBuffer(EPD_WIDTH, EPD_HEIGHT, BPP_MONO)
{
	// DATA Pin: GPIOD [12, 11, 7, 6, 5, 4, 3, 2]
	for (uint32_t i = 0; i < 256; i++)
	{
		uint32_t mask = ((i & 0b00111111) << 2) | (((i & 0b11000000) >> 6) << 11);
		mPinLUT[i] = (((~mask) & 0b0001100011111100) << GPIO_NUMBER) | mask;
	}

	//
}


void EPaperDisplay::begin(void)
{
	//
	mEPaperPMIC.init();

	//
	// ...
}

void EPaperDisplay::end()
{
}

void EPaperDisplay::clearDisplay()
{
	memset(mBackBuffer.getPtr(), 0, mBackBuffer.getSize());
}

void EPaperDisplay::display(bool leaveOn)
{
	//
	if (!leaveOn && !einkOn())
	{
		return;
	}

	//
	clean(0, 1);
	clean(1, 21);
	clean(2, 1);
	clean(0, 12);
	clean(2, 1);
	clean(1, 21);
	clean(2, 1);
	clean(0, 12);

	//
	uint8_t* pDispBufferPtr = mDispBuffer.getPtr();
	uint8_t* pBackBufferPtr = mBackBuffer.getPtr();
	uint32_t _send;
	uint8_t data;
	uint8_t dram;

	memcpy(pDispBufferPtr, pBackBufferPtr, mBackBuffer.getSize());


	//
	for (int k = 0; k < 4; ++k)
	{
		uint8_t *DMemoryNewPtr = pDispBufferPtr + (E_INK_WIDTH * E_INK_HEIGHT / 8) - 1;
		vscan_start();
		for (int i = 0; i < E_INK_HEIGHT; ++i)
		{
			dram = *(DMemoryNewPtr--);

			data = LUTB[dram >> 4];
			_send = mPinLUT[data];
			hscan_start(_send);

			data = LUTB[dram & 0x0F];
			_send = mPinLUT[data];
			//GPIO.out_w1ts = (_send) | CL;
			//GPIO.out_w1tc = DATA | CL;
			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();

			for (int j = 0; j < ((E_INK_WIDTH / 8) - 1); ++j)
			{
				dram = *(DMemoryNewPtr--);

				data = LUTB[dram >> 4];
				_send = mPinLUT[data];
				//GPIO.out_w1ts = (_send) | CL;
				//GPIO.out_w1tc = DATA | CL;
				EPD_Set_DATA(_send);
				EPD_Set_CL();
				EPD_Reset_CL();
				EPD_Reset_DATA();

				data = LUTB[dram & 0x0F];
				_send = mPinLUT[data];
				//GPIO.out_w1ts = (_send) | CL;
				//GPIO.out_w1tc = DATA | CL;
				EPD_Set_DATA(_send);
				EPD_Set_CL();
				EPD_Reset_CL();
				EPD_Reset_DATA();
			}
			//GPIO.out_w1ts = (_send) | CL;
			//GPIO.out_w1tc = DATA | CL;
			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();

			vscan_end();
		}
		delayMicroseconds(230);
	}

	//
	uint16_t _pos = (E_INK_WIDTH * E_INK_HEIGHT / 8) - 1;
	vscan_start();
	for (int i = 0; i < E_INK_HEIGHT; ++i)
	{
		dram = *(pDispBufferPtr + _pos);

		data = LUT2[dram >> 4];
		_send = mPinLUT[data];
		hscan_start(_send);

		data = LUT2[dram & 0x0F];
		_send = mPinLUT[data];
		//GPIO.out_w1ts = (_send) | CL;
		//GPIO.out_w1tc = DATA | CL;
		EPD_Set_DATA(_send);
		EPD_Set_CL();
		EPD_Reset_CL();
		EPD_Reset_DATA();

		_pos--;
		for (int j = 0; j < ((E_INK_WIDTH / 8) - 1); ++j)
		{
			dram = *(pDispBufferPtr + _pos);

			data = LUT2[dram >> 4];
			_send = mPinLUT[data];
			//GPIO.out_w1ts = (_send) | CL;
			//GPIO.out_w1tc = DATA | CL;
			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();

			data = LUT2[dram & 0x0F];
			_send = mPinLUT[data];
			//GPIO.out_w1ts = (_send) | CL;
			//GPIO.out_w1tc = DATA | CL;
			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();

			_pos--;
		}
		//GPIO.out_w1ts = (_send) | CL;
		//GPIO.out_w1tc = DATA | CL;
		EPD_Set_DATA(_send);
		EPD_Set_CL();
		EPD_Reset_CL();
		EPD_Reset_DATA();

		vscan_end();
	}
	delayMicroseconds(230);

	//
	vscan_start();
	for (int i = 0; i < E_INK_HEIGHT; ++i)
	{
		dram = *(pDispBufferPtr + _pos);

		data = 0;
		_send = mPinLUT[data];
		hscan_start(_send);

		data = 0;
		//GPIO.out_w1ts = (_send) | CL;
		//GPIO.out_w1tc = DATA | CL;
		EPD_Set_DATA(_send);
		EPD_Set_CL();
		EPD_Reset_CL();
		EPD_Reset_DATA();

		for (int j = 0; j < ((E_INK_WIDTH / 8) - 1); ++j)
		{
			//GPIO.out_w1ts = (_send) | CL;
			//GPIO.out_w1tc = DATA | CL;
			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();

			//GPIO.out_w1ts = (_send) | CL;
			//GPIO.out_w1tc = DATA | CL;
			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();
		}
		//GPIO.out_w1ts = (_send) | CL;
		//GPIO.out_w1tc = DATA | CL;
		EPD_Set_DATA(_send);
		EPD_Set_CL();
		EPD_Reset_CL();
		EPD_Reset_DATA();

		vscan_end();
	}
	delayMicroseconds(230);

	//
	vscan_start();

	if (!leaveOn)
		einkOff();

	//_blockPartial = 0;
}

void EPaperDisplay::partialUpdate(bool forced, bool leaveOn)
{
}


int EPaperDisplay::einkOn()
{
//	if (getPanelState() == 1)
//	   return 1;

	mEPaperPMIC.turnOnPower();

	pinsAsOutputs();
	LE_CLEAR;
	OE_CLEAR;
	CL_CLEAR;
	SPH_SET;
	GMOD_SET;
	SPV_SET;
	CKV_CLEAR;
	OE_CLEAR;
	mEPaperPMIC.turnOnVCOM(); // VCOM_SET

	unsigned long timer = millis();
	do
	{
		delay(1);
	} while (!mEPaperPMIC.isPowerGood() && (millis() - timer) < 250);

	if ((millis() - timer) >= 250)
	{
		mEPaperPMIC.turnOffVCOM();
		mEPaperPMIC.turnOffPower();

		return 0;
	}

	OE_SET;
//	setPanelState(1);

	return 1;
}

void EPaperDisplay::einkOff()
{
//	if (getPanelState() == 0)
//		return;

	OE_CLEAR;
	GMOD_CLEAR;
	// GPIO.out &= ~(DATA | LE | CL);
	EPD_Reset_LE();
	EPD_Reset_CL();
	EPD_Reset_DATA();
	CKV_CLEAR;
	SPH_CLEAR;
	SPV_CLEAR;

	// VCOM_CLEAR;
	mEPaperPMIC.turnOffVCOM();
	delay(6);

	//PWRUP_CLEAR;
	// WAKEUP_CLEAR
	mEPaperPMIC.turnOffPower();

	unsigned long timer = millis();
	do
	{
		delay(1);
	} while (mEPaperPMIC.isPowerGood() && (millis() - timer) < 250);

	pinsZstate();
//	setPanelState(0);
}

void EPaperDisplay::preloadScreen()
{
}

uint8_t EPaperDisplay::readPowerGood()
{
	return 0;
}

void EPaperDisplay::clean(uint8_t c, uint8_t rep)
{
	einkOn();
	uint8_t data = 0;
	if (c == 0)
		data = B10101010; // draw white
	else if (c == 1)
		data = B01010101; // draw black
	else if (c == 2)
		data = B00000000; // discharge
	else if (c == 3)
		data = B11111111; // skip(no action)

	uint32_t _send = mPinLUT[data];

	for (int k = 0; k < rep; ++k)
	{
		vscan_start();

		for (int i = 0; i < E_INK_HEIGHT; ++i)
		{
			hscan_start(_send);

			EPD_Set_DATA(data);
			EPD_Set_CL();
			EPD_Reset_CL();

			for (int j = 0; j < ((E_INK_WIDTH / 8) - 1); ++j)
			{
				EPD_Set_CL();
				EPD_Reset_CL();

				EPD_Set_CL();
				EPD_Reset_CL();
			}

			EPD_Set_CL();
			EPD_Reset_CL();

			vscan_end();
		}

		delayMicroseconds(230);
	}
}


void EPaperDisplay::display1b(bool leaveOn)
{
}

void EPaperDisplay::display3b(bool leaveOn)
{
}


void EPaperDisplay::vscan_start()
{
	CKV_SET;
	delayMicroseconds(7);
	SPV_CLEAR;
	delayMicroseconds(10);
	CKV_CLEAR;
	delayMicroseconds(0);
	CKV_SET;
	delayMicroseconds(8);
	SPV_SET;
	delayMicroseconds(10);
	CKV_CLEAR;
	delayMicroseconds(0);
	CKV_SET;
	delayMicroseconds(18);
	CKV_CLEAR;
	delayMicroseconds(0);
	CKV_SET;
	delayMicroseconds(18);
	CKV_CLEAR;
	delayMicroseconds(0);
	CKV_SET;
}

void EPaperDisplay::vscan_end()
{
	CKV_CLEAR;
	LE_SET;
	LE_CLEAR;
	delayMicroseconds(0);
}

void EPaperDisplay::hscan_start(uint32_t data)
{
    SPH_CLEAR;
    EPD_Set_DATA(data);
    EPD_Set_CL();
    EPD_Reset_CL();
    EPD_Reset_DATA();
    SPH_SET;
    CKV_SET;
}

void EPaperDisplay::pinsZstate()
{
	// nop
}

void EPaperDisplay::pinsAsOutputs()
{
	// nop
}





#endif // !MODEL_A

