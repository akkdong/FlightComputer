// EPaperPMIC.cpp
//

#include "Arduino.h"
#include "EPaperPMIC.h"



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
// class EPaperPMIC

EPaperPMIC::EPaperPMIC()
	: mWire(Wire)
	, mState(SLEEP)
{
}


bool EPaperPMIC::init()
{
	//
	mWire.begin();
	mWire.setClock(1000000);

	// set default state
	digitalWrite(PMIC_WAKEUP, LOW);
	digitalWrite(PMIC_PWRUP, LOW);
	digitalWrite(PMIC_VCOM, LOW);

	// set power-pin as output
	pinMode(PMIC_WAKEUP, OUTPUT);
	pinMode(PMIC_PWRUP, OUTPUT);
	pinMode(PMIC_VCOM, OUTPUT);

	/*
	// wakeup
	digitalWrite(PMIC_WAKEUP, HIGH);
	delay(10);

	mWire.beginTransmission(PMIC_ADDR);
	mWire.write(PMIC_REG_UPSEQ0);
	mWire.write(0b11100100); // Power up seq.
	mWire.write(0b00000000); // Power up delay (3mS per rail)
	mWire.write(0b00011011); // Power down seq.
	mWire.write(0b00000000); // Power down delay (6mS per rail)
	mWire.endTransmission();
	delay(1);

	mWire.beginTransmission(PMIC_ADDR);
	mWire.write(PMIC_REG_VCOM1);
	mWire.write(0b10010110); // vcom voltage: -1.5v, 150
	mWire.endTransmission();
	delay(1);

#ifdef DEBUG
	Serial1.println("Dump PMIC registers on EPaperPMIC::init()");
    DumpRegister();
#endif
	 */

	// suspend
	digitalWrite(PMIC_WAKEUP, LOW);
	delay(100);

	//
	mState = SLEEP;

    return true;
}

int EPaperPMIC::wakeup()
{
	if (mState == SLEEP)
	{
		digitalWrite(PMIC_WAKEUP, HIGH);
		delay(10);

#if 0
		mWire.beginTransmission(PMIC_ADDR);
		mWire.write(PMIC_REG_UPSEQ0);
		mWire.write(0b11100100); // Power up seq.
		mWire.write(0b00000000); // Power up delay (3mS per rail)
		mWire.write(0b00011011); // Power down seq.
		mWire.write(0b00000000); // Power down delay (6mS per rail)
		mWire.endTransmission();
		delay(1);
#endif

#if 0
		mWire.beginTransmission(PMIC_ADDR);
		mWire.write(PMIC_REG_VCOM1);
		mWire.write(0b10010110); // vcom voltage: -1.5v, 150
		mWire.endTransmission();
		delay(1);
#endif

#ifdef DEBUG
		Serial1.println("Dump PMIC registers on EPpaperPMIC::wakeup()");
		DumpRegister();
		DumpPort();
#endif

		mState = STANDBY;
	}

    return (mState == STANDBY) ? 0 : -1;
}

void EPaperPMIC::sleep()
{
	if (mState != SLEEP)
	{
		powerOff();

		// turn-Off WAKEUP pin
		digitalWrite(PMIC_WAKEUP, LOW);

		mState = SLEEP;
	}
}

int EPaperPMIC::powerOn()
{
	if (mState == STANDBY)
	{
		/*
		// setup power up/down sequence
		mWire.beginTransmission(PMIC_ADDR);
		mWire.write(PMIC_REG_UPSEQ0);
		mWire.write(0b11100100); // Power up seq.
		mWire.write(0b00000000); // Power up delay (3mS per rail)
		mWire.write(0b00011011); // Power down seq.
		mWire.write(0b00000000); // Power down delay (6mS per rail)
		mWire.endTransmission();
		delay(1);

		// setup vcom voltage;
		mWire.beginTransmission(PMIC_ADDR);
		mWire.write(PMIC_REG_VCOM1);
		mWire.write(0b10010110); // -1.5v -> 150
		mWire.endTransmission();
		delay(1);
		*/

		// enable all rails
	    mWire.beginTransmission(PMIC_ADDR);
	    mWire.write(PMIC_REG_ENABLE);
	    mWire.write(0b10111111);
	    mWire.endTransmission();
	    delay(1);

	    // turn-on VCOM
		digitalWrite(PMIC_VCOM, HIGH);
		delay(6);

	    // wait power-good
		uint32_t tick = millis();
		do {
			delay(1);
#ifdef DEBUG
			//delay(49);
#endif

		} while (getPowerGood() != PWR_GOOD_OK && (millis() - tick) < 250);

		if (millis() - tick >= 250)
		{
#ifdef DEBUG
			Serial1.println("Dump PMIC registers on EPpaperPMIC::powerOn()");
			DumpRegister();
			DumpPort();
#endif

			digitalWrite(PMIC_WAKEUP, LOW);
			digitalWrite(PMIC_VCOM, LOW);
			digitalWrite(PMIC_PWRUP, LOW);

			mState = SLEEP;
		}
		else
		{
#ifdef DEBUG
			Serial1.println("PMIC Power OK!");
#endif

			// turn-on VCOM pin
			//digitalWrite(PMIC_VCOM, HIGH);
			//delay(6);

			mState = ACTIVE;
		}
	}

	return (mState == ACTIVE) ? 0 : -1;
}

int EPaperPMIC::powerOff()
{
	if (mState == ACTIVE)
	{
		// turn-off VCOM pin
		digitalWrite(PMIC_VCOM, LOW);
		//delay(6);

		// disable all rails
		mWire.beginTransmission(PMIC_ADDR);
		mWire.write(PMIC_REG_ENABLE);
		mWire.write(0b01000000); // disable all rails
		mWire.endTransmission();

		uint32_t tick = millis();
		do {
			delay(1);
#ifdef DEBUG
			//delay(49);
#endif
		//} while (getPowerGood() == PWR_GOOD_OK && (millis() - tick) < 250);
		} while (getPowerGood() != 0x00 && (millis() - tick) < 250);

		mState = STANDBY;
	}

#ifdef DEBUG
	Serial1.println("PMIC Power Off!");
#endif
	return (mState == STANDBY) ? 0 : -1;
}

uint8_t EPaperPMIC::getPowerGood()
{
	uint8_t data;

    mWire.beginTransmission(PMIC_ADDR);
    mWire.write(PMIC_REG_PG);
    mWire.endTransmission();

    mWire.requestFrom(PMIC_ADDR, 1);
    data = mWire.read();
    mWire.endTransmission();

#ifdef DEBUG
    //Serial1.printf("PMIC PowerGood: %02X\r\n", data);
#endif
    return data;
}



#ifdef DEBUG
void EPaperPMIC::DumpRegister()
{
    mWire.beginTransmission(PMIC_ADDR);
    mWire.write(0x00);
    mWire.endTransmission();

    mWire.requestFrom(PMIC_ADDR, 0x11);
    for (int i = 0; i <= 0x10; i++)
    {
    	uint8_t data = mWire.read();
    	Serial1.printf("PMIC #%02X = %02X\r\n", i, data);
    }
    mWire.endTransmission();
}

void EPaperPMIC::DumpPort()
{
	Serial1.printf("PORT(WAKEUP) = %d\r\n", digitalRead(PMIC_WAKEUP));
	Serial1.printf("PORT(POWERUP) = %d\r\n", digitalRead(PMIC_PWRUP));
	Serial1.printf("PORT(VCOM) = %d\r\n", digitalRead(PMIC_VCOM));
}

#endif // DEBUG
