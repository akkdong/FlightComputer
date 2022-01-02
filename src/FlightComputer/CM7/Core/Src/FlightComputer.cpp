/*
 * FlightComputer.cpp
 *
 *  Created on: 2021. 12. 31.
 *      Author: akkdong
 */

#include "main.h"
#include "FlightComputer.h"
#if SUPPORT_LVGL
#include "lv_port.h"
#endif
#include "common.h"
#include "debug.h"


#include "Adafruit_GFX/Fonts/FreeSans24pt7b.h"
#include "Adafruit_GFX/Fonts/FreeSans18pt7b.h"



/////////////////////////////////////////////////////////////////////////////////////
//


/* Ringbuffer variables */
extern lwrb_t* rb_cm4_to_cm7;
extern lwrb_t* rb_cm7_to_cm4;


//static HardwareSerial& Debug = Serial;
//static HardwareSerial& RPI = Serial3;


int32_t shell_hello(int32_t argc, char** argv)
{
	TRACE("Hi~\r\n");

	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////
// class FlightComputer

FlightComputer::FlightComputer()
	: rb_cm4_to_cm7((lwrb_t *)BUFF_CM4_TO_CM7_ADDR)
	, rb_cm7_to_cm4((lwrb_t *)BUFF_CM7_TO_CM4_ADDR)
	, varioState((vario_t *)BUFF_VARIO_STATE_ADDR)
	, displayUpdateCount(0)
	, enterStandby(0)
{
	// mm.registerClient(&debug);
}

bool FlightComputer::flash_ok = false;
bool FlightComputer::sdram_ok = false;



void FlightComputer::setup(void)
{
	//
	pinMode(PWR_LED1, OUTPUT);
	digitalWrite(PWR_LED1, LOW);

	//RPI.begin(115200);
	//delay(100);

	// device check
	if (!flash_ok)
		TRACE("[DEBUG] Flash initialization failed.\r\n");
	if (!sdram_ok)
		TRACE("[DEBUG] SDRAM initialization failed.\r\n");

	//
#if SUPPORT_LVGL
	lv_init();
	hal_init();
	app_init();
#endif

	//
	//epdCont.begin();
	epdDisp.begin();
	keyPad.begin();

	//
	lwshell_init();
	lwshell_register_cmd("hello", shell_hello, "Answer me!");

	//
	drawVarioState();
	updateScreen(false);
}

void FlightComputer::loop()
{
	// sleep now
	if (enterStandby)
		standby();

	// process debug-shell event
	procDebugShell();
	// process keyboard event
	procKeyboard();
	// process interprocess event
	procInterProcess();

#if SUPPORT_LVGL
	// lvgl timer handler
	procLVGL();
#endif

	// update sreen
	if (millis() - displayUpdateTick > 1000)
		updateScreen();

	// debug purpose: blink LED
	{
		static uint32_t tick = millis();
		if ((millis() - tick) > 1000)
		{
			digitalToggle(PWR_LED1);
			tick = millis();
		}
	}



	// [TEST] forward GPS to Debug console
	//if (GPS.available())
	//	Debug.write(GPS.read());
	// [TEST] echo RPI & forward to Debug console
	//if (RPI.available())
	//{
	//	int ch = RPI.read();
	//	Debug.write(ch);
	//	RPI.write(ch);
	//}

	// console
	// CommandConsole console;
	//
	// console.SetInterface(Debug);
	// console.SetClient(SerialShell);

	//
	//epdCont.run();

	/*
	SPIClass spi(SPI4_MOSI, SPI4_MISO, SPI4_SCLK);

	spi.begin();
	spi.transfer(data);
	spi.transfer(ptr, size);
	spi.end();

	SPIClassEx spiEx;

	spiEx.begin(init_function);
	spiEx.transfer(sendPtr, sendLen, recvPtr, recvLen);

	spiEx.receive(dataPtr, dataLen, timeout, callback);


	Timer aaa;
	aaa.Expire(1000, class::callback);
	spiEx.end();
	*/
}


void FlightComputer::OnUpdateVario()
{
	TRACE("OnUpdateVario\r\n");

	drawVarioState();
	updateScreen();
}

void FlightComputer::OnUpdateGPS()
{
	TRACE("OnUpdateGPS\r\n");

	drawVarioState();
	updateScreen();
}

void FlightComputer::standby()
{
	TRACE("Enter standby mode\r\n");
	// flush cm4 message during 1s
	uint32_t tick = millis();
	while (millis() - tick < 500)
		procInterProcess();

	// show standby-screen
	drawStandby();
	updateScreen(false);
	HAL_Delay(200);

	// setup wakeup pin
	PWREx_WakeupPinTypeDef sPinParams;
	sPinParams.WakeUpPin    = PWR_WAKEUP_PIN1;
	sPinParams.PinPolarity  = PWR_PIN_POLARITY_LOW;
	sPinParams.PinPull      = PWR_PIN_NO_PULL;
	HAL_PWREx_EnableWakeUpPin(&sPinParams);

	// enter standby mode
	HAL_SuspendTick();
	HAL_PWREx_ClearPendingEvent();
	HAL_PWREx_EnterSTANDBYMode(PWR_D1_DOMAIN);

	// never comes here
	while(1);
	//TRACE("CM7 standby failed!!\r\n");
}


void FlightComputer::procDebugShell()
{
	// process shell command
	while (Serial.available())
	{
		int ch = Serial.read();
		lwshell_input(&ch, 1);
	}
}

void FlightComputer::procInterProcess()
{
	// Check if CM4 sent some data to CM7 core
	size_t len;
	void* addr;

	while ((len = lwrb_get_linear_block_read_length(rb_cm4_to_cm7)) > 0)
	{
		addr = lwrb_get_linear_block_read_address(rb_cm4_to_cm7);

		// forward to debug-shell
		Serial.write((const char *)addr, len);
		// or you can parse message and doing something

		// mark buffer as read
		lwrb_skip(rb_cm4_to_cm7, len);
	}
}

void FlightComputer::procKeyboard()
{
	// process key-event
	Key.run();

	// key-event handling
	int event = Key.getEvent();
	if (event == EVENT_NOKEY)
		return;
	TRACE("Key event: %X\r\n", event);

	//
	if ((event & EVENT_MASK_STATE) == EVENT_KEYUP)
	{
		if ((event & EVENT_MASK_KEY) == KeyPad::ENTER)
		{
#if 0 // bitmap drawing examples
			uint32_t lastTick = millis();

			if (imageType == 0)
			{
				epdDisp.drawBitmapBM(alien_bytes,  0,  0,  EPD_WIDTH, EPD_HEIGHT, COLOR_BLACK, bm_invert);
			}
			else if (imageType == 1)
			{
				epdDisp.drawBitmapBM(landscape_bytes,  0,  0,  EPD_WIDTH, EPD_HEIGHT, COLOR_BLACK, bm_invert);
			}
			else if (imageType == 2)
			{
				volatile uint8_t* ptr = epdDisp.getCanvas();

				// draw check-pattern
				for (int y = 0; y < 600; y++)
					{
						for (int x = 0; x < 100 /*800/8*/; x++)
						{
							int iy = y / 60; // 0 ~ 9
							int ix = x / 10; // 0 ~ 9

							*ptr++ = ((iy % 2) == (ix % 2)) ? 0xFF : 0x00;
						}
				}
			}
			imageType = (imageType + 1) % 3;

			updateScreen();
			TRACE("draw bitmap!: %u ms\r\n", millis() - lastTick);
#endif
		}
		else if ((event & EVENT_MASK_KEY) == KeyPad::ESCAPE)
		{
			// refresh screen
			updateScreen(false);
		}
		else if ((event & EVENT_MASK_KEY) == KeyPad::MENU)
		{

		}
		else if ((event & EVENT_MASK_KEY) == KeyPad::UP)
		{
		}
		else if ((event & EVENT_MASK_KEY) == KeyPad::DOWN)
		{
		}
		else if ((event & EVENT_MASK_KEY) == KeyPad::FUNC1)
		{
		}
		else if ((event & EVENT_MASK_KEY) == KeyPad::FUNC2)
		{
			// go to standby: signal to CM4
			HAL_HSEM_FastTake(HSEM_GOTO_STANDBY);
			HAL_HSEM_Release(HSEM_GOTO_STANDBY, 0);

			// now turn-on standby flag
			enterStandby = 1;
		}
	}
}

#if SUPPORT_LVGL
void FlightComputer::procLVGL()
{
	// lvgl timer handler
	static uint32_t tick = millis();
	if ((millis() - tick) > 5)
	{
		lv_timer_handler();
		tick = millis();
	}
}
#endif

void FlightComputer::updateScreen(bool fast)
{
	displayUpdateCount = fast ? (displayUpdateCount + 1) % 50 : 0;
	displayUpdateTick = millis();

	epdDisp.refresh(displayUpdateCount == 0 ? false : true);
	TRACE("[D] screen updated (%d)\r\n", displayUpdateCount);
}

void FlightComputer::drawStandby()
{
	epdDisp.clearScreen();
	epdDisp.setFont(&FreeSans24pt7b);
	epdDisp.setTextColor(COLOR_BLACK);

	int x = 16;
	int y = FreeSans24pt7b.yAdvance;
	epdDisp.setCursor(x, y);
	epdDisp.print("Press ENTER to wake-up!");
}

void FlightComputer::drawVarioState()
{
	epdDisp.clearScreen();
	epdDisp.setFont(&FreeSans24pt7b);
	epdDisp.setTextColor(COLOR_BLACK);

	int x = 16;
	int y = FreeSans24pt7b.yAdvance;
	epdDisp.setCursor(x, y);
	epdDisp.print("Flight computer Sensor TEST");

	epdDisp.setFont(&FreeSans18pt7b);

	y += FreeSans24pt7b.yAdvance + 8;
	epdDisp.setCursor(x, y);
	epdDisp.printf("Altitude(Baro): %.1f m", varioState->altitudeBaro);
	y += FreeSans18pt7b.yAdvance;
	epdDisp.setCursor(x, y);
	epdDisp.printf("Altitude(GPS): %.1f m", varioState->altitudeGPS);
	y += FreeSans18pt7b.yAdvance;
	epdDisp.setCursor(x, y);
	epdDisp.printf("Latitude: %.3f", varioState->latitude);
	y += FreeSans18pt7b.yAdvance;
	epdDisp.setCursor(x, y);
	epdDisp.printf("Longitude: %.3f", varioState->longitude);
	y += FreeSans18pt7b.yAdvance;
	epdDisp.setCursor(x, y);
	epdDisp.printf("Vertical speed: %.2f cm/s", varioState->speedVertActive * 10);
	y += FreeSans18pt7b.yAdvance;
	epdDisp.setCursor(x, y);
	epdDisp.printf("Ground speed: %.3f km/h", varioState->speedGround);

	y += FreeSans18pt7b.yAdvance + 8;
	epdDisp.setCursor(x, y);
	epdDisp.printf("Battery power: %.3f V", varioState->batteryVoltage);
	y += FreeSans18pt7b.yAdvance;
	epdDisp.setCursor(x, y);
	epdDisp.printf("Pressure: %.2f hPa", varioState->pressure);
	y += FreeSans18pt7b.yAdvance;
	epdDisp.setCursor(x, y);
	epdDisp.printf("Temperature: %.1f C", varioState->temperature);
}
