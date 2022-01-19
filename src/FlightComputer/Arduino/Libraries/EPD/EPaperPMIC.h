// EPaperPMIC.h
//

#ifndef LIBRARIES_EPD_PIMIC_H_
#define LIBRARIES_EPD_PIMIC_H_

#include "stm32h7xx_hal.h"
#include "Wire/Wire.h"


////////////////////////////////////////////////////////////////////////////////////////
// class EPaperPMIC

class EPaperPMIC
{
public:
	EPaperPMIC();

	enum State {
		SLEEP,
		STANDBY,
		ACTIVE
	};

public:
	bool		init();

	int			wakeup(); 	// sleep --> standby
	void		sleep();  	// standby/active --> sleep

	int			powerOn();	// standby --> active
	int			powerOff();	// active --> standby

	State		getState() { return mState; }

protected:
	uint8_t		getPowerGood();

#ifdef DEBUG
	void		DumpRegister();
	void		DumpPort();
#endif

private:
	TwoWire		mWire;
	State		mState;
};


#endif // LIBRARIES_EPD_PIMIC_H_
