// bmp280_port.h
//

#ifndef __BMP280_PORT_H__
#define __BMP280_PORT_H__

#include "stm32h7xx_hal.h"
#include "bmp280.h"

#define USE_SPI		(1)

////////////////////////////////////////////////////////////////////////////////////////////////////////
//

typedef struct _BMP280_HandleTypeDef
{
#if USE_SPI
	SPI_HandleTypeDef*	spi;
	GPIO_TypeDef *		cs_port;
	uint16_t			cs_pin;
#else
	I2C_HandleTypeDef* i2c;
#endif

	struct bmp280_dev bmp;
	struct bmp280_config conf;
	struct bmp280_uncomp_data ucomp_data;

	uint32_t pres32, pres64;
	double pres;
	uint32_t temp32;
	double temp;

} BMP280_HandleTypeDef;




void BMP280_Init(BMP280_HandleTypeDef* dev);
void BMP280_Update(BMP280_HandleTypeDef* dev);


#endif // __BMP280_PORT_H__
