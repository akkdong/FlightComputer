/*
 * EPaperDisplay.cpp
 *
 *  Created on: 2021. 11. 18.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "EPaperDisplay.h"


#if !USE_MODEL_A  // MODEL_B(InkPlate)

#define EPD_WIDTH     			800
#define EPD_HEIGHT    			600
#define BPP_MONO				1
#define BPP_16GRAY				4

#define CLK_DELAY_US  			0
#define VCLK_DELAY_US 			1
#define OUTPUT_DELAY_US   		2
#define CLEAR_BYTE    			0b10101010
#define DARK_BYTE     			0b01010101



#define PMIC_ADDR				(0x48)

#define PMIC_REG_TMST_VALUE		(0x00)
#define PMIC_REG_ENABLE			(0x01)
#define PMIC_REG_VADJ			(0x02)
#define PMIC_REG_VCOM1			(0x03)
#define PMIC_REG_VCOM2			(0x04)
#define PMIC_REG_INT_EN1		(0x05)
#define PMIC_REG_INT_EN2		(0x06)
#define PMIC_REG_INT1			(0x07)
#define PMIC_REG_INT2			(0x08)
#define PMIC_REG_UPSEQ0			(0x09)
#define PMIC_REG_UPSEQ1			(0x0A)
#define PMIC_REG_DWNSEQ0		(0x0B)
#define PMIC_REG_DWNSEQ1		(0x0C)
#define PMIC_REG_TMST1			(0x0D)
#define PMIC_REG_TMST2			(0x0E)
#define PMIC_REG_PG				(0x0F)
#define REG_PMIC_REVID			(0x10)


#define PWR_GOOD_OK            	(0b11111010)




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
	, mPanelState(0)
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
	//mEPaperPMIC.init();
	//
	Wire.begin();
//	Wire.setClock(400000);

	// set default state
	digitalWrite(PMIC_WAKEUP, LOW);
	digitalWrite(PMIC_PWRUP, LOW);
	digitalWrite(PMIC_VCOM, LOW);

	// set power-pin as output
	pinMode(PMIC_WAKEUP, OUTPUT);
	pinMode(PMIC_PWRUP, OUTPUT);
	pinMode(PMIC_VCOM, OUTPUT);
	delay(1);

	// wakeup
	digitalWrite(PMIC_WAKEUP, HIGH);
	delay(10);

	Wire.beginTransmission(PMIC_ADDR);
	Wire.write(PMIC_REG_UPSEQ0);
	Wire.write(0b11100100); // Power up seq.
	Wire.write(0b00000000); // Power up delay (3mS per rail)
	Wire.write(0b00011011); // Power down seq.
	Wire.write(0b00000000); // Power down delay (6mS per rail)
	Wire.endTransmission();
	delay(1);

	Wire.beginTransmission(PMIC_ADDR);
	Wire.write(PMIC_REG_VCOM1);
	Wire.write(0b10010110); // vcom voltage: -1.5v, 150
	Wire.endTransmission();
	delay(1);

#ifdef DEBUG
    //DumpRegister();
#endif

	// suspend
	digitalWrite(PMIC_WAKEUP, LOW);
	delay(100);

	//
	//pinsZstate();
	pinsAsOutputs();
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
		return;

	uint32_t tickStart = millis();

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
		uint8_t *DMemoryNewPtr = pDispBufferPtr + (EPD_WIDTH * EPD_HEIGHT / 8) - 1;
		vscan_start();
		for (int i = 0; i < EPD_HEIGHT; ++i)
		{
			dram = *(DMemoryNewPtr--);

			data = LUTB[dram >> 4];
			_send = mPinLUT[data];
			hscan_start(_send);

			data = LUTB[dram & 0x0F];
			_send = mPinLUT[data];
			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();

			for (int j = 0; j < ((EPD_WIDTH / 8) - 1); ++j)
			{
				dram = *(DMemoryNewPtr--);

				data = LUTB[dram >> 4];
				_send = mPinLUT[data];
				EPD_Set_DATA(_send);
				EPD_Set_CL();
				EPD_Reset_CL();
				EPD_Reset_DATA();

				data = LUTB[dram & 0x0F];
				_send = mPinLUT[data];
				EPD_Set_DATA(_send);
				EPD_Set_CL();
				EPD_Reset_CL();
				EPD_Reset_DATA();
			}

			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();

			vscan_end();
		}
		delayMicroseconds(230);
	}

	//
	uint16_t _pos = (EPD_WIDTH * EPD_HEIGHT / 8) - 1;
	vscan_start();
	for (int i = 0; i < EPD_HEIGHT; ++i)
	{
		dram = *(pDispBufferPtr + _pos);

		data = LUT2[dram >> 4];
		_send = mPinLUT[data];
		hscan_start(_send);

		data = LUT2[dram & 0x0F];
		_send = mPinLUT[data];
		EPD_Set_DATA(_send);
		EPD_Set_CL();
		EPD_Reset_CL();
		EPD_Reset_DATA();

		_pos--;
		for (int j = 0; j < ((EPD_WIDTH / 8) - 1); ++j)
		{
			dram = *(pDispBufferPtr + _pos);

			data = LUT2[dram >> 4];
			_send = mPinLUT[data];
			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();

			data = LUT2[dram & 0x0F];
			_send = mPinLUT[data];
			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();

			_pos--;
		}

		EPD_Set_DATA(_send);
		EPD_Set_CL();
		EPD_Reset_CL();
		EPD_Reset_DATA();

		vscan_end();
	}
	delayMicroseconds(230);

	//
	vscan_start();
	for (int i = 0; i < EPD_HEIGHT; ++i)
	{
		dram = *(pDispBufferPtr + _pos);

		data = 0;
		_send = mPinLUT[data];
		hscan_start(_send);

		data = 0;
		EPD_Set_DATA(_send);
		EPD_Set_CL();
		EPD_Reset_CL();
		EPD_Reset_DATA();

		for (int j = 0; j < ((EPD_WIDTH / 8) - 1); ++j)
		{
			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();

			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();
			EPD_Reset_DATA();
		}

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

	Serial1.printf("display elapsed: %d ms\r\n", millis() - tickStart);
}

void EPaperDisplay::partialUpdate(bool forced, bool leaveOn)
{
}

int EPaperDisplay::einkOn()
{
	if (getPanelState() > 0)
	   return 1;

	//pinsAsOutputs();


	// sleep -> stand-by
	digitalWrite(PMIC_WAKEUP, HIGH);
	delay(2);

	// setup power up/down sequence
	Wire.beginTransmission(PMIC_ADDR);
	Wire.write(PMIC_REG_UPSEQ0);
	Wire.write(0b11100100); // Power up seq.
	Wire.write(0b00000000); // Power up delay (3mS per rail)
	Wire.write(0b00011011); // Power down seq.
	Wire.write(0b00000000); // Power down delay (6mS per rail)
	Wire.endTransmission();
	delay(1);

	// setup vcom voltage;
	Wire.beginTransmission(PMIC_ADDR);
	Wire.write(PMIC_REG_VCOM1);
	Wire.write(0b10010110); // -1.5v -> 150
	Wire.endTransmission();
	delay(1);


	// enable all rails
	//digitalWrite(PMIC_PWRUP, HIGH);
	//delay(1);
    Wire.beginTransmission(PMIC_ADDR);
    Wire.write(PMIC_REG_ENABLE);
    Wire.write(0b10111111);
    Wire.endTransmission();
    delay(10);

    // turn-on VCOM
	digitalWrite(PMIC_VCOM, HIGH);
	delay(2);

	// wait power-good
	unsigned long timer = millis();
	uint8_t data = 0;
	do
	{
		delay(1);

	    Wire.beginTransmission(PMIC_ADDR);
	    Wire.write(PMIC_REG_PG);
	    Wire.endTransmission();

	    Wire.requestFrom(PMIC_ADDR, 1);
	    data = Wire.read();
	    Wire.endTransmission();

	#ifdef DEBUG
	    Serial1.printf("Wait Power On: %X\r\n", data);
	    delay(10);
	#endif
	    if (data == PWR_GOOD_OK)
	    	break;

	} while ((millis() - timer) < 250);

	if ((millis() - timer) >= 250)
	{
#ifdef DEBUG
		DumpRegister();
#endif

		digitalWrite(PMIC_VCOM, LOW);
		digitalWrite(PMIC_PWRUP, LOW);
		digitalWrite(PMIC_WAKEUP, LOW);

		return 0;
	}


#ifdef DEBUG
	Serial1.printf("EPD Turned on!\r\n");
	DumpRegister();
	DumpPort();
#endif

	//
    EPD_Reset_LE();
    EPD_Reset_OE();
    EPD_Reset_CL();
    EPD_Set_SPH();
    EPD_Set_GMODE();
    EPD_Set_SPV();
    EPD_Reset_CKV();
    EPD_Reset_OE();
	EPD_Set_OE();

	setPanelState(1);

	return 1;
}

void EPaperDisplay::einkOff()
{
	if (getPanelState() == 0)
		return;

	EPD_Reset_GMODE();
	EPD_Reset_OE();
	EPD_Reset_LE();
	EPD_Reset_CL();
	EPD_Reset_CKV();
	EPD_Reset_SPH();
	EPD_Reset_SPV();
	EPD_Reset_DATA();

	// VCOM_CLEAR;
	digitalWrite(PMIC_VCOM, LOW);
	delay(6);

	//
	//digitalWrite(PMIC_PWRUP, LOW);

	Wire.beginTransmission(PMIC_ADDR);
	Wire.write(PMIC_REG_ENABLE);
	Wire.write(0x40);
	Wire.endTransmission();
	delay(10);

	unsigned long timer = millis();
	uint8_t data = 0;
	do
	{
		delay(1);

		Wire.beginTransmission(PMIC_ADDR);
		Wire.write(PMIC_REG_PG);
		Wire.endTransmission();

		Wire.requestFrom(PMIC_ADDR, 1);
		data = Wire.read();
		Wire.endTransmission();

		#ifdef DEBUG
		Serial1.printf("Wait Power Off: %X\r\n", data);
		delay(50);
		#endif

	} while (data == PWR_GOOD_OK && (millis() - timer) < 250);


	digitalWrite(PMIC_WAKEUP, LOW);


	//pinsZstate();
	setPanelState(0);

#ifdef DEBUG
	Serial1.printf("EPD Turned off!\r\n");
#endif
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

		for (int i = 0; i < EPD_HEIGHT; ++i)
		{
			hscan_start(_send);

			EPD_Set_DATA(_send);
			EPD_Set_CL();
			EPD_Reset_CL();

			for (int j = 0; j < ((EPD_WIDTH / 8) - 1); ++j)
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
	EPD_Set_CKV();
	delayMicroseconds(7);
	EPD_Reset_SPV();
	delayMicroseconds(10);
	EPD_Reset_CKV();
	delayMicroseconds(0);
	EPD_Set_CKV();
	delayMicroseconds(8);
	EPD_Set_SPV();
	delayMicroseconds(10);
	EPD_Reset_CKV();
	delayMicroseconds(0);
	EPD_Set_CKV();
	delayMicroseconds(18);
	EPD_Reset_CKV();
	delayMicroseconds(0);
	EPD_Set_CKV();
	delayMicroseconds(18);
	EPD_Reset_CKV();
	delayMicroseconds(0);
	EPD_Set_CKV();
}

void EPaperDisplay::vscan_end()
{
	EPD_Reset_CKV();
	EPD_Set_LE();
	EPD_Reset_LE();
	delayMicroseconds(0);
}

void EPaperDisplay::hscan_start(uint32_t data)
{
    EPD_Reset_SPH();
    EPD_Set_DATA(data);
    EPD_Set_CL();
    EPD_Reset_CL();
    EPD_Reset_DATA();
    EPD_Set_SPH();
    EPD_Set_CKV();
}

void EPaperDisplay::pinsZstate()
{
	// nop
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
}

void EPaperDisplay::pinsAsOutputs()
{
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
}



#ifdef DEBUG
void EPaperDisplay::DumpRegister()
{
    Wire.beginTransmission(PMIC_ADDR);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(PMIC_ADDR, 0x11);
    for (int i = 0; i <= 0x10; i++)
    {
    	uint8_t data = Wire.read();
    	Serial1.printf("PMIC #%02X = %02X\r\n", i, data);
    }
    Wire.endTransmission();
}

void EPaperDisplay::DumpPort()
{
	Serial1.printf("PORT(WAKEUP) = %d\r\n", digitalRead(PMIC_WAKEUP));
	Serial1.printf("PORT(POWERUP) = %d\r\n", digitalRead(PMIC_PWRUP));
	Serial1.printf("PORT(VCOM) = %d\r\n", digitalRead(PMIC_VCOM));
}
#endif // DEBUG



#endif // !USE_MODEL_A

