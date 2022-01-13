/*
 * BatteryPower.h
 *
 *  Created on: 2022. 1. 1.
 *      Author: akkdong
 */

#ifndef LIBRARIES_BATTERY_BATTERYPOWER_H_
#define LIBRARIES_BATTERY_BATTERYPOWER_H_

#include "Arduino.h"


//////////////////////////////////////////////////////////////////////////////////////////
//

class BatteryPower
{
public:
	BatteryPower();

public:
	int		begin();
	void	end();

	void	update();

	float	getVoltage();
	int		getPercentage();

protected:
};


#endif /* LIBRARIES_BATTERY_BATTERYPOWER_H_ */
