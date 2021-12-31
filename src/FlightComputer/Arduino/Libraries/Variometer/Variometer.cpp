/*
 * Variometer.cpp
 *
 *  Created on: 2021. 12. 31.
 *      Author: akkdong
 */

#include "Variometer.h"



Variometer::Variometer(KalmanFilter& _imu, NMEAParser& _nmea)
	: imu(_imu)
	, nmea(_nmea)
{

}


int Variometer::begin()
{
	//
	imu.begin(/*zVariance, zAccelVariance, zAccelBiasVariance*/);
	nmea.begin();

	//
	lastUpdate = millis();

	return 0;
}

void Variometer::loop()
{
	nmea.update();

	// update every 100ms (10Hz)
	uint32_t now = millis();
	if (now - lastUpdate > 10)
	{
		imu.update();
		lastUpdate = now;
	}
}

void Variometer::end()
{
	// nop
}


float Variometer::getVerticalSpeed()
{
	return imu.getVelocity();
}

float Variometer::getPressure()
{
	imu.getPressure();
}

float Variometer::getTemperature()
{
	return imu.getTemperature();
}
