// CurrentMeasure.ino
//

#include <Wire.h>
#include "INA219.h"
#include "MultiFuncShield.h"


// Current sensor and shunt used 
INA219 ina219;

#define R_SHUNT 			0.002
#define V_SHUNT_MAX 		0.004
#define V_BUS_MAX 			16
#define I_MAX_EXPECTED 		2

#define UPDATE_PERIOD		(1000)


enum DISPLAY_TYPE {
	DISP_BATVOLTAGE, // or DISP_BUSVOLTAGE
	DISP_SHUNTVOLTAGE,
	DISP_SHUNTCURRENT,
	DISP_AMPHEREHOUR,
	DISP_TYPECOUNT
};

enum DISPLAY_MODE {
	MODE_BATVOLTAGE,
	MODE_SHUNTVOLTAGE,
	MODE_SHUNTCURRENT,
	MODE_AMPHEREHOUR,
	MODE_ROTATE
};

// current and voltage readings
float shuntvoltage = 0;
float busvoltage = 0;
float current_A = 0;
float batvoltage = 0;
float power = 0;
float Ah = 0;

const unsigned long updatePeriod = UPDATE_PERIOD;
int displayType = DISP_SHUNTCURRENT;
int displayMode = MODE_SHUNTCURRENT;
unsigned long lastUpdateTick;
unsigned long lastReadTick = 0; // used to calculate Ah


void displayData()
{
	switch (displayType)
	{
	case DISP_BATVOLTAGE:
		MFS.write(busvoltage, 2);
		break;
	case DISP_SHUNTVOLTAGE:
		MFS.write(fabs(shuntvoltage), 3);
		break;
	case DISP_SHUNTCURRENT:
		MFS.write(fabs(current_A), 3);
		break;
	case DISP_AMPHEREHOUR:	
		MFS.write(fabs(Ah), 2);
		break;
	}
	
	
	MFS.writeLeds(LED_ALL, OFF);
	MFS.writeLeds((1 << displayType), ON);
}



void setup()
{
	//
	Serial.begin(115200);
	Serial.println("Current Measure...");

	//
	ina219.begin();
	ina219.configure(INA219::RANGE_16V, INA219::GAIN_2_80MV, INA219::ADC_16SAMP, INA219::ADC_16SAMP, INA219::CONT_SH_BUS);
	ina219.calibrate(R_SHUNT, V_SHUNT_MAX, V_BUS_MAX, I_MAX_EXPECTED);
	
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


	//	
	lastUpdateTick = millis();
	
	displayType = DISP_SHUNTCURRENT;
	displayMode = MODE_SHUNTCURRENT;
	
	//
	readCurrent();
	displayData();	
}

void loop()
{
	delay(50);
	readCurrent();
	
	unsigned long currentTick = millis();  
	if (currentTick - lastUpdateTick >= updatePeriod)
	{
		//
		displayData();
		
		if (displayMode == MODE_ROTATE)
			displayType = (displayType + 1) % DISP_TYPECOUNT;
		
		// displays data
		Serial.print("Bus Voltage:   "); Serial.print(busvoltage,3); Serial.println(" V");
		Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage,3); Serial.println(" mV");
		Serial.print("Bat Voltage:   "); Serial.print(batvoltage,3); Serial.println(" V");
		Serial.print("Current:       "); Serial.print(current_A,3); Serial.println(" A");
		Serial.print("Power:         "); Serial.print(power,3); Serial.println(" W");
		Serial.print("Ah:            "); Serial.print(Ah,3); Serial.println(" Ah");
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
		// display each values
		displayMode = MODE_ROTATE;
		// update display
		displayData();
	}	
}


void readCurrent() {
	uint32_t count = 0;

//  Serial.println("waiting data ready");

	// reads busVoltage
	busvoltage = ina219.busVoltage() + 0.035;
	// waits for conversion ready
	while(!ina219.ready() && count < 500) {
		count++;
		delay(1);
		busvoltage = ina219.busVoltage() + 0.0;  
	}

	// read the other values
	shuntvoltage = ina219.shuntVoltage() * 1000 + 0.02;
	current_A = ina219.shuntCurrent() + 0.001;
	batvoltage = busvoltage + (shuntvoltage / 1000);
	power = ina219.busPower();
	
	unsigned long now = millis();
	unsigned long tick = now - lastReadTick;
	Ah += (current_A * tick) / 3600000.0;
	lastReadTick = now;

	// prepare for next read -- this is security just in case the ina219 is reset by transient curent
	ina219.recalibrate();
	ina219.reconfig();
}