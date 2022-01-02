/*
 * Variometer.h
 *
 *  Created on: 2021. 12. 31.
 *      Author: akkdong
 */

#ifndef LIBRARIES_VARIOMETER_VARIOMETER_H_
#define LIBRARIES_VARIOMETER_VARIOMETER_H_

#include "Arduino.h"
#include "KalmanFilter.h"
#include "NMEA/NMEAParser.h"


////////////////////////////////////////////////////////////////////////////////////
//

class Variometer
{
public:
	Variometer(KalmanFilter& imu, NMEAParser& nmea);


public:
	int			begin();
	void		loop();
	void		end();

	float		getVerticalSpeed();
	float		getAltitude();
	float		getPressure();
	float		getTemperature();

protected:
	KalmanFilter& imu;
	NMEAParser& nmea;

	uint		lastUpdate;
};


#endif /* LIBRARIES_VARIOMETER_VARIOMETER_H_ */
