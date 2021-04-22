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
{
}


bool EPaperPMIC::init()
{
	//
	mWire.begin();

	// set default state
	digitalWrite(PMIC_WAKEUP, LOW);
	digitalWrite(PMIC_PWRUP, LOW);
	digitalWrite(PMIC_VCOM, LOW);

	// set power-pin as output
	pinMode(PMIC_WAKEUP, OUTPUT);
	pinMode(PMIC_PWRUP, OUTPUT);
	pinMode(PMIC_VCOM, OUTPUT);
	delay(100);

	// wakeup
	digitalWrite(PMIC_WAKEUP, HIGH);
	delay(100);

    mWire.beginTransmission(PMIC_ADDR);
    mWire.write(PMIC_REG_UPSEQ0);
    mWire.write(B00011011); // Power up seq.
    mWire.write(B00000000); // Power up delay (3mS per rail)
    mWire.write(B00011011); // Power down seq.
    mWire.write(B00000000); // Power down delay (6mS per rail)
    mWire.endTransmission();
    delay(10);

    digitalWrite(PMIC_WAKEUP, LOW);


    return true;
}

void EPaperPMIC::turnOnPower()
{
	digitalWrite(PMIC_WAKEUP, HIGH);
	delay(1);
	digitalWrite(PMIC_PWRUP, HIGH);

    mWire.beginTransmission(PMIC_ADDR);
    mWire.write(PMIC_REG_ENABLE);
    mWire.write(B10111111);
    mWire.endTransmission();
}

void EPaperPMIC::turnOffPower()
{
	digitalWrite(PMIC_PWRUP, LOW);
	digitalWrite(PMIC_WAKEUP, LOW);
}

void EPaperPMIC::turnOnVCOM()
{
	digitalWrite(PMIC_VCOM, HIGH);
}

void EPaperPMIC::turnOffVCOM()
{
	digitalWrite(PMIC_VCOM, LOW);
	delay(6);
}


bool EPaperPMIC::isPowerGood()
{
    mWire.beginTransmission(PMIC_ADDR);
    mWire.write(PMIC_REG_PG);
    mWire.endTransmission();

    mWire.requestFrom(PMIC_ADDR, 1);
    return mWire.read() == PWR_GOOD_OK;
}
