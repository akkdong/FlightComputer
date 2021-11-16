// MS4525DO.h
//

#ifndef __MS4525DO_H__
#define __MS4525DO_H__



//////////////////////////////////////////////////////////////////////////////////////////////////
// class MS4525DO

class MS4525DO
{
public:
	MS4525DO();
	~MS4525DO();

public:
	int 		measure(void);              // returns status of measurement
	float 		getPSI(void);             	// returns the PSI of last measurement
	float 		getTemperature(void);     	// returns temperature of last measurement
	float 		getAirSpeed(void);        	// calculates and returns the airspeed
	int 		calibrate(void);            // attempts to calibrate and returns a status code
	
	uint16_t	getRawPressure() { return P_dat; }
	uint16_t 	getRawTemperature() { return T_dat; }

private:
	char        status;
	float       psi;
	float       temperature;
	float       airspeed;
	
	uint16_t    P_dat;  // 14 bit pressure data
	uint16_t    T_dat;  // 11 bit temperature data
};

#endif // __MS4525DO_H__
