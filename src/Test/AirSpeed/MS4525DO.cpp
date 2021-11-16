// MS4525DO.cpp
//

#include <Arduino.h>
#include <Wire.h>
#include "MS4525DO.h"

#define ADDRESS_MS4525DO    0x28 



// MS4525D sensor full scale range and units
const int16_t MS4525FullScaleRange = 1;  // 1 psi

// MS4525D Sensor type (A or B) comment out the wrong type assignments
// Type A (10% to 90%)
const int16_t MS4525MinScaleCounts = 1638;
const int16_t MS4525FullScaleCounts = 14746;

const int16_t MS4525Span = MS4525FullScaleCounts - MS4525MinScaleCounts;

//MS4525D sensor pressure style, differential or otherwise. Comment out the wrong one.
//Differential
const int16_t MS4525ZeroCounts = (MS4525MinScaleCounts + MS4525FullScaleCounts) / 2;



///////////////////////////////////////////////////////////////////////////////////////////
//

MS4525DO::MS4525DO()
	: status(0)
	, psi(0.0)
	, temperature(0.0)
	, airspeed(0.0)
	, P_dat(0)
	, T_dat(0)
{
}

MS4525DO::~MS4525DO()
{
}

int MS4525DO::measure(void)
{
	//
	Wire.requestFrom(ADDRESS_MS4525DO, 4);
	uint8_t b1 = Wire.read();
	uint8_t b2 = Wire.read();
	uint8_t b3 = Wire.read();
	uint8_t b4 = Wire.read();
	Wire.endTransmission();
	
	//
	status = ((b1 >> 6) & 0x03);
	P_dat = (((uint16_t)b1 & 0x3F) << 8) | (uint16_t)b2;
	T_dat = ((uint16_t)b3 << 3) | ((b4 >> 5) & 0x07);
	
	return status;
}

float MS4525DO::getPSI(void)
{
	// convert and store PSI
	psi=(static_cast<float>(static_cast<int16_t>(P_dat) - MS4525ZeroCounts))/static_cast<float>(MS4525Span)*static_cast<float>(MS4525FullScaleRange);
	
	// apply PSI calibration data
	// psi = psi + 0.007f;

	/* Below code is Pixhawk code which doesnt seem to work correctly */
	// Calculate differential pressure. As its centered around 8000
	// and can go positive or negative
	/*
	const float P_min = -1.0f;
	const float P_max = 1.0f;
	const float PSI_to_Pa = 6894.757f;
	*/ 
	/*
	this equation is an inversion of the equation in the
	pressure transfer function figure on page 4 of the datasheet
	We negate the result so that positive differential pressures
	are generated when the bottom port is used as the static
	port on the pitot and top port is used as the dynamic port
	*/
	/*
	float diff_press_PSI = -((T_dat - 0.1f * 16383) * (P_max - P_min) / (0.8f * 16383) + P_min);
	float diff_press_pa_raw = diff_press_PSI * PSI_to_Pa;
	*/

	return psi;	
}

float MS4525DO::getTemperature(void)
{
	// convert and store Temperature
	temperature = (static_cast<float>(static_cast<int16_t>(T_dat)));
	temperature = (temperature / 10);   // now in deg F
	temperature = ((temperature -32) / 1.8f);   // now in deg C

	/* Below code is pixhawk version which DOES work correctly */
	/*
	PX4temperature = ((200.0f * T_dat) / 2047) - 50;
	terminal.printf("PX4 Temperature: ");
	terminal.printf("%0.1f\n", PX4temperature);
	*/

	return temperature;
}

float MS4525DO::getAirSpeed(void)
{
	/* Velocity calculation from a pitot tube explanation */
	/* +/- 1PSI, approximately 100 m/s 360000 m/h (360 Km/h) */
	float rho = 1.225; // density of air 
	// velocity = squareroot( (2*differential) / rho )
	float velocity;
	
	if (psi < 0)
		velocity = -sqrt(-(2 * psi) / rho);
	else
		velocity = sqrt((2 * psi) / rho);
	
	velocity = velocity * 10;

	return velocity;
}

int MS4525DO::calibrate(void)
{
	return 0;
}
