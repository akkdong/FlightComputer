// CurrentMeasure.ino
//

#include <Wire.h>
#include "MultiFuncShield.h"
#include "MS4525DO.h"

#define DAMPING_FACTOR		(0.2)

MS4525DO	ms4525;

// filtered pressure, temperature & speed
float	filtered_p, filtered_t, filtered_s;

//
const unsigned long updatePeriod = 1000;
int displayType = 0; // 0: pressure, 1: temperature, 2: air-speed
int displayMode = 0; // 0: pressure, 1: temperature, 2: air-speed, 3: rotate
unsigned long lastUpdateTick;

void displayData()
{
	float data = 0;
	
	switch (displayType)
	{
	case 0: data = filtered_p; break;
	case 1: data = filtered_t; break;
	case 2: data = filtered_s; break;
	}
	
	MFS.write(data, 2);
	
	MFS.writeLeds(LED_ALL, OFF);
	MFS.writeLeds((1 << displayType), ON);
}

void setup()
{
	//
	Wire.begin();
	
	//
	Serial.begin(115200);
	Serial.println("AirSpeed measurement...");
	
	// put your setup code here, to run once:
	MFS.initialize();    // initialize multifunction shield library
	MFS.write(0.0, 1);	

	MFS.writeLeds(LED_ALL, ON);
	delay(500);
	MFS.writeLeds(LED_ALL, OFF);
	delay(500);
	MFS.writeLeds(LED_ALL, ON);
	delay(500);
	MFS.writeLeds(LED_ALL, OFF);
	
	int retry = 0;
	while (1)
	{
		int status = ms4525.measure();
		if (status == 0)
			break;

		if (++retry > 10)
		{
			MFS.blinkLeds(LED_ALL);
			while(1);
		}
		
		delay(500);
	}
	
	filtered_p = ms4525.getPSI();
	filtered_t = ms4525.getTemperature();
	filtered_s = ms4525.getAirSpeed();
	
	lastUpdateTick = millis();
	displayType = 0;
	
	displayData();
}

void loop()
{
	// 
	delay(200);
	
	//
	int status = ms4525.measure();
	if (status != 0)
		return;
	
	filtered_p = filtered_p * (1 - DAMPING_FACTOR) + ms4525.getPSI() * DAMPING_FACTOR;
	filtered_t = filtered_t * (1 - DAMPING_FACTOR) + ms4525.getTemperature() * DAMPING_FACTOR;
	filtered_s = filtered_s * (1 - DAMPING_FACTOR) + ms4525.getAirSpeed() * DAMPING_FACTOR;	
	
	//
	unsigned long currentTick = millis();  
	if (currentTick - lastUpdateTick >= updatePeriod)
	{
		if (displayMode == 3)
			displayType = (displayType + 1) % 3;
		displayData();
		
		Serial.print("Pressure:   "); Serial.println(filtered_p);
		Serial.print("Temerature: "); Serial.println(filtered_t);
		Serial.print("Air speed:  "); Serial.println(filtered_s);
		Serial.println("");		
		
		lastUpdateTick = currentTick;
	}
	
	//
	byte btn = MFS.getButton();
	if (btn == BUTTON_1_SHORT_RELEASE)
	{
		// next type is new mode
		displayMode = displayType = (displayType + 1) % 3;
		// update display
		displayData();
	}
	else if (btn == BUTTON_1_LONG_PRESSED)
	{
		// 
		displayMode = 3;
		// update display
		displayData();
	}
}
