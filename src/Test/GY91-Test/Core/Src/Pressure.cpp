/*
 * Pressure.cpp
 *
 *  Created on: 2021. 12. 21.
 *      Author: akkdong
 */

#include "main.h"
#include "BMP280/BMP280.hpp"


//
//
//

extern SPI_HandleTypeDef hspi1;


BMP280 baro(&hspi1);





//
//
//

class KalmanVario
{
public:
	KalmanVario(BMP280 & baro);

public:
	int						begin(float zVariance = 400.0, float zAccelVariance = 1000.0, float zAccelBiasVariance = 1.0);
	void					end();

	int						available();
	void					flush();

	void					update();

	float					getPressure() { return baro.measurement.pressure; }
	float					getTemperature() { return baro.measurement.temperature; }
	float					getAltitude2() { return z_; }
	float					getAltitude() { return baro.measurement.altitude; }
	float					getCalibratedAltitude() { return baro.measurement.altitude; }
	float					getVelocity() { return v_; }

	uint32_t				getTimestamp() { return t_; }

	void					calibrateAltitude(float altitudeRef);
	void					calculateSeaLevel(float altitude);

protected:
//	static void IRAM_ATTR 	TimerProc();

	static KalmanVario *	mActiveVario;


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


KalmanVario::KalmanVario(BMP280 & _baro)
	: baro(_baro)
	, seaLevel(1013.25)
//	, mTimer(NULL)
//	, mSemaphore(xSemaphoreCreateBinary())
//	, mMux(portMUX_INITIALIZER_UNLOCKED)
{
}


int KalmanVario::begin(float zVariance, float zAccelVariance, float zAccelBiasVariance)
{
	//
	baro.initialize();

	// read dummy data 100 times (2 seconds)
	// it may be stabilize data...
	for (int i = 0; i < 100; i++)
	{
		HAL_Delay(5);
		baro.measure();
	}

	// init values
	zAccelVariance_ = zAccelVariance;
    zAccelBiasVariance_ = zAccelBiasVariance;
	zVariance_ = zVariance;

	init();

	//
	varioUpdated = false;
	t_ = HAL_GetTick();

	//
	//Task::createPinnedToCore(1);

	//
	//mActiveVario = this;
	//mTimer = timerBegin(0, 80, true); // ESP32 Counter: 80 MHz, Prescaler: 80 --> 1MHz timer
	//timerAttachInterrupt(mTimer, TimerProc, true);
	//timerAlarmWrite(mTimer, 1000000 / 50, true); // 100Hz -> alarm very 10msec, 118Hz -> 8.4746 msec  :  the measure period need to be greater than 8.22 msec
	//timerAlarmEnable(mTimer);

	//
	//baro.startConvert();

	return 0;
}

void KalmanVario::init()
{
	z_ = baro.measurement.altitude;
	v_ = 0.0f; // vInitial;
	aBias_ = 0.0f; // aBiasInitial;
	Pzz_ = 1.0f;
	Pzv_ = 0.0f;
	Pza_ = 0.0f;

	Pvz_ = 0.0f;
	Pvv_ = 1.0f;
	Pva_ = 0.0f;

	Paz_ = 0.0f;
	Pav_ = 0.0;
	Paa_ = 100000.0f;

	baroAltitude = z_;
	altitudeDrift = 0.0;
}

void KalmanVario::update()
{
	//if (baro.available())
	{
		// read pressure & vertical acceleration
		float va = 0;

		//
		baro.measure();
		float altitude = baro.measurement.altitude;
		baroAltitude += (altitude - baroAltitude) * 0.1; // dampling factor

		// delta time
		uint32_t lastTick = HAL_GetTick();
//		unsigned long deltaTime = 20; // lastTick - t_;
		unsigned long deltaTime = lastTick - t_;
		float dt = ((float)deltaTime) / 1000.0;
		t_ = lastTick;

		//
		// prediction
		//
		float accel = va - aBias_;
		v_ += accel * dt;
		z_ += v_ * dt;

		// Predict State Covariance matrix
		float t00,t01,t02;
		float t10,t11,t12;
		float t20,t21,t22;

		float dt2div2 = dt * dt / 2.0f;
		float dt3div2 = dt2div2 * dt;
		float dt4div4 = dt2div2 * dt2div2;

		t00 = Pzz_ + dt * Pvz_ - dt2div2 * Paz_;
		t01 = Pzv_ + dt * Pvv_ - dt2div2 * Pav_;
		t02 = Pza_ + dt * Pva_ - dt2div2 * Paa_;

		t10 = Pvz_ - dt * Paz_;
		t11 = Pvv_ - dt * Pav_;
		t12 = Pva_ - dt * Paa_;

		t20 = Paz_;
		t21 = Pav_;
		t22 = Paa_;

		Pzz_ = t00 + dt * t01 - dt2div2 * t02;
		Pzv_ = t01 - dt * t02;
		Pza_ = t02;

		Pvz_ = t10 + dt * t11 - dt2div2 * t12;
		Pvv_ = t11 - dt * t12;
		Pva_ = t12;

		Paz_ = t20 + dt * t21 - dt2div2 * t22;
		Pav_ = t21 - dt * t22;
		Paa_ = t22;

		Pzz_ += dt4div4 * zAccelVariance_;
		Pzv_ += dt3div2 * zAccelVariance_;

		Pvz_ += dt3div2 * zAccelVariance_;
		Pvv_ += dt * dt * zAccelVariance_;

		Paa_ += zAccelBiasVariance_;

		// Error
		float innov = altitude - z_;
		float sInv = 1.0f / (Pzz_ + zVariance_);

		// Kalman gains
		float kz = Pzz_ * sInv;
		float kv = Pvz_ * sInv;
		float ka = Paz_ * sInv;

		// Update state
		z_ += kz * innov;
		v_ += kv * innov;
		aBias_ += ka * innov;

		//*pZ = z_;
		//*pV = v_;

		// Update state covariance matrix
		Paz_ -= ka * Pzz_;
		Pav_ -= ka * Pzv_;
		Paa_ -= ka * Pza_;

		Pvz_ -= kv * Pzz_;
		Pvv_ -= kv * Pzv_;
		Pva_ -= kv * Pza_;

		Pzz_ -= kz * Pzz_;
		Pzv_ -= kz * Pzv_;
		Pza_ -= kz * Pza_;

		//
		varioUpdated = true;
	}
}


KalmanVario vario(baro);


//
//
//

extern "C"
{


int vario_init()
{
	vario.begin();

	return 0;
}

float vario_update()
{
	vario.update();

	return vario.getVelocity();
}


int baro_init()
{
	if (baro.initialize() != 0)
		return -1;

	baro.measure();
	baro.measure();

	return 0;
}

void baro_measure()
{
	baro.measure();
}


float baro_getTemperature()
{
	return baro.measurement.temperature;
}
float baro_getPressure()
{
	return baro.measurement.pressure;
}

float baro_getAltitude()
{
	return baro.measurement.altitude;
}



//
//
//

}
