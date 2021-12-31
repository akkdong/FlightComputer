/*
 * FlightComputer.cpp
 *
 *  Created on: 2021. 12. 31.
 *      Author: akkdong
 */

#include "main.h"
#include "FlightComputer.h"
#include "lv_port.h"
#include "common.h"
#include "debug.h"


#include "../../../../Test/FC_Test/CM7/Core/Inc/image_mono.h"
#include "../../../../Test/FC_Test/CM7/Core/Inc/landscape.h"
#include "Adafruit_GFX/Fonts/FreeSans24pt7b.h"



/////////////////////////////////////////////////////////////////////////////////////
//

int image_type = 0;


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
	lv_init();
	hal_init();
	app_init();

	//
	//epdCont.begin();
	epdDisp.begin();
	keyPad.begin();

	//
	lwshell_init();
	lwshell_register_cmd("hello", shell_hello, "Answer me!");

	//
	epdDisp.clearScreen();
	epdDisp.setFont(&FreeSans24pt7b);
	epdDisp.setCursor(100, 100);
	epdDisp.setTextColor(COLOR_BLACK);
	epdDisp.print("Welcome!");
	epdDisp.refresh(false);
}

void FlightComputer::loop()
{
	int enter_standby = 0;

	while(1)
	{
		if (enter_standby)
		{
			TRACE("Enter standby mode\r\n");
			//wait C4 enter standby
			{
				uint32_t tick = millis();
				volatile RCC_TypeDef * rcc = (volatile RCC_TypeDef *)RCC;
				while (1)
				{
					uint32_t CR = rcc->CR;
					if (!(CR & (1 << 15)))
						break;
					if (millis() - tick > 1000)
						break;

					{
						size_t len;
						void* addr;
						while ((len = lwrb_get_linear_block_read_length(rb_cm4_to_cm7)) > 0)
						{
							addr = lwrb_get_linear_block_read_address(rb_cm4_to_cm7);

							/* Transmit data */
							Serial.write((const char *)addr, len);

							/* Mark buffer as read */
							lwrb_skip(rb_cm4_to_cm7, len);
						}
					}
				}
				//while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (millis() - tick < 2000));
				if (rcc->CR & (1 << 15))
					TRACE("CM4 is still running!!\r\n");
			}

			epdDisp.clearScreen();
			epdDisp.setFont(&FreeSans24pt7b);
			epdDisp.setCursor(100, 100);
			epdDisp.setTextColor(COLOR_BLACK);
			epdDisp.print("Press Enter To Wakeup!");
			epdDisp.refresh(false);
			HAL_Delay(200);

			digitalWrite(PWR_EN_PERIPH, LOW);
			digitalWrite(PWR_EN_EXTRA, LOW);
			digitalWrite(PWR_LED1, LOW);

			// wakeup pin 1
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
			TRACE("CM7 standby failed!!\r\n");
		}

		// process shell command
		while (Serial.available())
		{
			int ch = Serial.read();
			lwshell_input(&ch, 1);
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

		// lvgl timer handler
		{
			static uint32_t tick = millis();
			if ((millis() - tick) > 5)
			{
				lv_timer_handler();
				tick = millis();
			}
		}

		// debug purpose
		{
			static uint32_t tick = millis();
			if ((millis() - tick) > 1000)
			{
				digitalToggle(PWR_LED1);
				tick = millis();
			}
		}

		//
		//epdCont.run();


		//
		Key.run();

		int event = Key.getEvent();
		if (event != EVENT_NOKEY)
		{
			TRACE("Key event: %X\r\n", event);

			if ((event & EVENT_MASK_STATE) == EVENT_KEYUP)
			{
				if ((event & EVENT_MASK_KEY) == KeyPad::ENTER)
				{
					uint32_t lastTick = millis();

					if (image_type == 0)
					{
						epdDisp.drawBitmapBM(alien_bytes,  0,  0,  EPD_WIDTH, EPD_HEIGHT, COLOR_BLACK, bm_invert);
					}
					else if (image_type == 1)
					{
						epdDisp.drawBitmapBM(landscape_bytes,  0,  0,  EPD_WIDTH, EPD_HEIGHT, COLOR_BLACK, bm_invert);
					}
					else if (image_type == 2)
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
					image_type = (image_type + 1) % 3;

					epdDisp.refresh();
					TRACE("draw bitmap!: %u ms\r\n", millis() - lastTick);
				}
				else if ((event & EVENT_MASK_KEY) == KeyPad::ESCAPE)
				{
					uint32_t lastTick = millis();
					epdDisp.clearScreen();
					epdDisp.refresh();
					TRACE("clear screen!: %u ms\r\n", millis() - lastTick);
				}
				else if ((event & EVENT_MASK_KEY) == KeyPad::MENU)
				{
					uint32_t lastTick = millis();

					epdDisp.setFont(&FreeSans24pt7b);
					epdDisp.setCursor(100, 100);
					epdDisp.setTextColor(COLOR_BLACK);
					epdDisp.print("Hello everyone!");
					epdDisp.refresh(true);

					TRACE("fast update!: %u ms\r\n", millis() - lastTick);
				}
				else if ((event & EVENT_MASK_KEY) == KeyPad::UP)
				{
					uint32_t lastTick = millis();

					epdDisp.fillScreen(COLOR_WHITE);
					epdDisp.refresh(true);

					TRACE("fast fill white!: %u ms\r\n", millis() - lastTick);
				}
				else if ((event & EVENT_MASK_KEY) == KeyPad::DOWN)
				{
					uint32_t lastTick = millis();

					epdDisp.fillScreen(COLOR_BLACK);
					epdDisp.refresh(true);

					TRACE("fast fill black!: %u ms\r\n", millis() - lastTick);
				}
				else if ((event & EVENT_MASK_KEY) == KeyPad::FUNC1)
				{
					//HAL_HSEM_FastTake(HSEM_ID_0);
					//HAL_HSEM_Release(HSEM_ID_0, 0);
				}
				else if ((event & EVENT_MASK_KEY) == KeyPad::FUNC2)
				{
					// go to standby: signal to CM4
					HAL_HSEM_FastTake(HSEM_GOTO_STANDBY);
					HAL_HSEM_Release(HSEM_GOTO_STANDBY, 0);

					enter_standby = 1;
				}
			}
		}


		//
	    /* Check if CPU2 sent some data to CPU1 core */
		{
			size_t len;
			void* addr;
			while ((len = lwrb_get_linear_block_read_length(rb_cm4_to_cm7)) > 0)
			{
				addr = lwrb_get_linear_block_read_address(rb_cm4_to_cm7);

				/* Transmit data */
				Serial.write((const char *)addr, len);

				/* Mark buffer as read */
				lwrb_skip(rb_cm4_to_cm7, len);
			}
		}
	}


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
