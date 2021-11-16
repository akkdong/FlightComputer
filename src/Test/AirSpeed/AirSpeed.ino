// CurrentMeasure.ino
//

#include <Wire.h>
#include "MultiFuncShield.h"
#include "MS4525DO.h"

#define DAMPING_FACTOR		(0.2)

enum DISPLAY_TYPE {
	DISP_RAWDATA,
	DISP_PRESSURE,
	DISP_TEMPERATURE,
	DISP_SPEED,
	DISP_TYPECOUNT
};

enum DISPLAY_MODE {
	MODE_RAWDATA,
	MODE_PRESSURE,
	MODE_TEMPERATURE,
	MODE_SPEED,
	MODE_ROTATE
}

MS4525DO	ms4525;

// filtered pressure, temperature & speed
uint16_t raw_data;
float	filtered_p, filtered_t, filtered_s;

//
const unsigned long updatePeriod = 1000;
int displayType = 0; // DISPLAY_TYPE
int displayMode = 0; // DISPLAY_MODE
unsigned long lastUpdateTick;

void displayData()
{
	float data = 0;
	
	switch (displayType)
	{
	case DIS_RAWDATA:
		MFS.write(raw_data);
		break;
	case DISP_PRESSURE: 
		data = filtered_p;
		MFS.write(data, 2);
		break;
	case DISP_TEMPERATURE: 
		data = filtered_t;
		break;
		MFS.write(data, 2);
	case DISP_SPEED: data = 
		filtered_s;
		MFS.write(data, 2);
		break;
	}
	
	
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
	raw_data = ms4525.getRawPressure();
	
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
	raw_data = ms4525.getRawPressure();	
	
	//
	unsigned long currentTick = millis();  
	if (currentTick - lastUpdateTick >= updatePeriod)
	{
		if (displayMode == MODE_ROTATE)
			displayType = (displayType + 1) % DISP_TYPECOUNT;
		displayData();
		
		Serial.print("Raw pressure:"); Serial.println(raw_data);
		Serial.print("Pressure:    "); Serial.println(filtered_p);
		Serial.print("Temerature:  "); Serial.println(filtered_t);
		Serial.print("Air speed:   "); Serial.println(filtered_s);
		Serial.println("");		
		
		lastUpdateTick = currentTick;
	}
	
	//
	byte btn = MFS.getButton();
	if (btn == BUTTON_1_SHORT_RELEASE)
	{
		// next type becomes new mode
		displayMode = displayType = (displayType + 1) % DISP_TYPECOUNT;
		// update display
		displayData();
	}
	else if (btn == BUTTON_1_LONG_PRESSED)
	{
		// 
		displayMode = MODE_ROTATE;
		// update display
		displayData();
	}
}
