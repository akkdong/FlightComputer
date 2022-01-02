/*
 * KalmanFilter.h
 *
 *  Created on: 2021. 12. 31.
 *      Author: akkdong
 */

#ifndef LIBRARIES_SENSOR_KALMANFILTER_H_
#define LIBRARIES_SENSOR_KALMANFILTER_H_

#include "Sensor/BMP280.hpp"
#include "Sensor/MPU9250.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////
//

class KalmanFilter
{
public:
	KalmanFilter(BMP280 & baro);

public:
	int						begin(float zVariance = 400.0, float zAccelVariance = 1000.0, float zAccelBiasVariance = 1.0);
	void					end();

	int						available();
	void					flush();

	void					update();

	float					getPressure() { return baro.measurement.pressure; }
	float					getTemperature() { return baro.measurement.temperature; }
	float					getAltitude2() { return z_; }
	float					getAltitude() { return baroAltitude; }
	float					getCalibratedAltitude() { return baro.measurement.altitude; }
	float					getVelocity() { return v_; }

	uint32_t				getTimestamp() { return t_; }

	void					calibrateAltitude(float altitudeRef);
	void					calculateSeaLevel(float altitude);

protected:
//	static void IRAM_ATTR 	TimerProc();
//	static KalmanFilter *	mActiveFilter;


private:
	void					init();

private:
	// State being tracked
	float					z_;  // position
	float					v_;  // velocity
	float					aBias_;  // acceleration

	// 3x3 State Covariance matrix
	float					Pzz_;
	float					Pzv_;
	float					Pza_;
	float					Pvz_;
	float					Pvv_;
	float					Pva_;
	float					Paz_;
	float					Pav_;
	float					Paa_;
	float					zAccelBiasVariance_; // assumed fixed.
	float					zAccelVariance_;  // dynamic acceleration variance
	float					zVariance_; //  z measurement noise variance fixed

	// timestamp
	uint32_t				t_;

	// barometer altitude
	float					baroAltitude;
	// altitude calibration
	float					altitudeDrift;

	//
	int						varioUpdated;

	//
	BMP280 &				baro;
	float					seaLevel;

protected:
//	hw_timer_t *			mTimer;
//	SemaphoreHandle_t		mSemaphore;
//	portMUX_TYPE			mMux;
};


#endif /* LIBRARIES_SENSOR_KALMANFILTER_H_ */
