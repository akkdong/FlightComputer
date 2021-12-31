/*
 * fc_main.cpp
 *
 *  Created on: 2021. 11. 25.
 *      Author: akkdong
 */

#include "Arduino.h"
#include "main.h"
#include "common.h"
#include "NMEA/NMEAParser.h"
#include "Sensor/BMP280.hpp"
#include "Sensor/MPU9250.h"
#include "Variometer/KalmanFilter.h"
#include "Variometer/Variometer.h"



//
volatile int notify_cm7 = 0;

lwrb_t* rb_cm4_to_cm7 = (lwrb_t *)BUFF_CM4_TO_CM7_ADDR;
lwrb_t* rb_cm7_to_cm4 = (lwrb_t *)BUFF_CM7_TO_CM4_ADDR;


//
SPIClass spi(SPI4_MOSI, SPI4_MISO, SPI4_SCLK);
//MPU9250 mpu(spi, SPI4_CS1);
BMP280	bmp(spi, SPI4_CS2);
NMEAParser nmea(Serial2);
KalmanFilter kalman(bmp/*, mpu*/);

Variometer vario(kalman, nmea);

//
enum UpdateType
{
	BAT,
	VARIO,
	GPS,
	LED,
	UPDATE_COUNT
};

uint32_t updateTick[UPDATE_COUNT];
char line_buf[128];



///////////////////////////////////////////////////////////////////////////////
//

void init(void)
{
	/*HW semaphore Clock enable*/
	__HAL_RCC_HSEM_CLK_ENABLE();
	/* Activate HSEM notification for Cortex-M4*/
	__HAL_HSEM_ENABLE_IT(HSEM_WAKEUP_CPU2_MASK); // HAL_HSEM_ActivateNotification(HSEM_WAKEUP_CPU2_MASK);
#if CM4_DEBUG || 1
	/*
	Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
	perform system initialization (system clock config, external memory configuration.. )
	*/
	HAL_PWREx_ClearPendingEvent();
	HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);

	/* Clear HSEM flag & Deativate HSEM notification*/
	__HAL_HSEM_CLEAR_FLAG(HSEM_WAKEUP_CPU2_MASK);
	__HAL_HSEM_DISABLE_IT(HSEM_WAKEUP_CPU2_MASK); // HAL_HSEM_DeactivateNotification(HSEM_WAKEUP_CPU2_MASK);
#endif

	/* MCU Configuration--------------------------------------------------------*/
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
}

void setup(void)
{
	//
	pinMode(PWR_LED2, OUTPUT);
	pinMode(SPI4_CS1, OUTPUT);
	pinMode(SPI4_CS2, OUTPUT);
	pinMode(A27, INPUT_ANALOG);

	digitalWrite(PWR_LED2, HIGH);
	digitalWrite(SPI4_CS1, HIGH);
	digitalWrite(SPI4_CS2, HIGH);

	analogReadResolution(12);

	//
	Serial2.begin(9600); // GPS
	spi.begin(); // for sensor(bmp280 & mpu9250)
	spi.setClockDivider(SPI_CLOCK_DIV128);

	vario.begin();

	for (int i = 0; i < UPDATE_COUNT; i++)
		updateTick[i] = millis();


	//
	HAL_NVIC_SetPriority(HSEM2_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(HSEM2_IRQn);
	notify_cm7 = 0;
	HAL_HSEM_ActivateNotification(HSEM_GOTO_STANDBY_MASK);

	//
	lwrb_write_string(rb_cm4_to_cm7, "CM4 Started...\r\n");
}

void loop(void)
{
	// go to sleep ?
	if (notify_cm7)
	{
		char sz[64];
		sprintf(sz, "[CM4] HSEM1 signaled: %d\r\n", notify_cm7);
		lwrb_write_string(rb_cm4_to_cm7, sz);

		if (notify_cm7 & HSEM_GOTO_STANDBY_MASK)
		{
			lwrb_write_string(rb_cm4_to_cm7, "[CM4] Enter StandBy\r\n");

			vario.end();
			spi.end();
			Serial2.end();

			digitalWrite(PWR_LED2, LOW);
			//pinMode(A27, INPUT);
			//pinMode(SPI4_CS1, INPUT);
			//pinMode(SPI4_CS2, INPUT);
			//pinMode(PWR_LED2, INPUT);
			//HAL_NVIC_DisableIRQ(HSEM2_IRQn);

			HAL_SuspendTick();
			HAL_PWREx_ClearPendingEvent();
			// Enter D3 to DStandby mode
			HAL_PWREx_EnterSTANDBYMode(PWR_D3_DOMAIN);
			// Enter D2 to DStandby mode
			HAL_PWREx_EnterSTANDBYMode(PWR_D2_DOMAIN);

			//while(1);
			lwrb_write_string(rb_cm4_to_cm7, "[CM4] wakeup! standby failed!!\r\n");
		}

		notify_cm7 = 0;
		HAL_HSEM_ActivateNotification(HSEM_GOTO_STANDBY_MASK);
	}

#if 0
	while (Serial2.available())
	{
		int ch = Serial2.read();
		lwrb_write(rb_cm4_to_cm7, &ch, 1);
	}
#endif

	//
	vario.loop();

	//
	uint32_t now = millis();

	// update battery power
	if (now - updateTick[BAT] > 1000)
	{
		// measure adc
		uint32_t measure = analogRead(A27);
		// adc(12bit) to voltage: 3.3 : 4095 = voltage : measured_adc
		float voltage = measure * 3.3 / 4095;
		// need to convert from measured voltage to actual voltage: voltage divider 1M : 1.56M
		voltage = voltage * 1560.0 / 1000.0;
		sprintf(line_buf, "[A] measure: %d voltage: %f\r\n", (unsigned int)measure, voltage);
		lwrb_write_string(rb_cm4_to_cm7, line_buf);

		updateTick[BAT] = now;
	}

	// update variometer
	if (now - updateTick[VARIO] > 1200)
	{
		sprintf(line_buf, "[V] v: %.2f, p:%.2f, t:%.0f\r\n", vario.getVerticalSpeed(), vario.getPressure(), vario.getTemperature());
		lwrb_write_string(rb_cm4_to_cm7, line_buf);

		updateTick[VARIO] = now;
	}

	// update gps
	if (now - updateTick[GPS] > 2000)
	{
		if (nmea.is_valid && nmea.fix != 0)
			sprintf(line_buf, "[G] [%.5f, %.5f] %.0f\r\n", nmea.latitude, nmea.longitude, nmea.speed);
		else
			sprintf(line_buf, "[G] N/A\r\n");
		lwrb_write_string(rb_cm4_to_cm7, line_buf);

		updateTick[GPS] = now;
	}

	// blink led
	if (now - updateTick[LED] > 500)
	{
		int high = digitalRead(PWR_LED2);
		digitalWrite(PWR_LED2, high ? LOW : HIGH);

		updateTick[LED] = now;
	}
}


extern "C" void HAL_HSEM_FreeCallback(uint32_t SemMask)
{
	notify_cm7 |= SemMask;
}
