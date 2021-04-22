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

public:
	bool		init();

	void		turnOnPower();
	void		turnOffPower();

	void		turnOnVCOM();
	void		turnOffVCOM();

	bool		isPowerGood();


private:
	TwoWire		mWire;
};


#endif // LIBRARIES_EPD_PIMIC_H_
