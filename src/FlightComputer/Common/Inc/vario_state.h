/*
 * vario_state.h
 *
 *  Created on: 2022. 1. 1.
 *      Author: akkdong
 */

#ifndef INC_VARIO_STATE_H_
#define INC_VARIO_STATE_H_

#include <stdint.h>
#include <time.h>

#define MAX_VARIO_HISTORY				(30)


typedef struct
{
	//
	float			altitudeGPS;		// QNH
	float			altitudeBaro;		// QNE
	float			altitudeCalibrated; // Baro + (Baro <-> GPS differential : altitudeDrift)
	float			altitudeAGL;		// QFE (from terrain)
	float			altitudeRef1;		// QFE (from take-off)
	float			altitudeRef2;		// QFE (from landing)
	float			altitudeRef3;		// QFE (from any-altitude)

	float			altitudeStart;		// take-off altitude
	float			altitudeGround;		//

//	float			altitudeDrift;

	//
//	float			altitudeAbtain;
	float			thermalTime;
	float			thermalGain;
//	float			glideRatio;

	//
	float			speedGround;
	float			speedAir;
	float			speedVertActive;
	float			speedVertLazy;
//	float			speedVertMean2S;
//	float			speedVertStat;

	float			speedVertHistory[MAX_VARIO_HISTORY]; // 1s vertial speed history
	float			speedVertSumTotal;
	int16_t			speedVertSumCount;
	int16_t			speedVertNext;

	//
	float			longitude;
	float			latitude;

	float			longitudeLast;
	float			latitudeLast;

//	float			longitudeStart;	// take-off longitude
//	float			latitudeStart;	// take-off latitude

//	float			distTakeoff;	// distance from take-off place
//	float			distFlight;		// total flight distance(odometer?)

	int16_t			heading;
	int16_t			headingLast;
//	int16_t			bearing;

	//
	float			pressure;
	float			temperature;		// by barometer
	float			temperatureAlt;		// by thermometer

	//
	time_t			timeCurrent;
//	time_t			timeStart;
//	time_t			timeFly;

} vario_t;



#if __cplusplus
extern "C"
{
#endif

void vario_reset(vario_t* state);

#if __cplusplus
}
#endif


#endif /* INC_VARIO_STATE_H_ */
