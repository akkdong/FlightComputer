// bmp280_port.c
//

#include "bmp280_port.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

static int8_t SPI_RegRead(uint32_t dev_param, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
	BMP280_HandleTypeDef* dev = (BMP280_HandleTypeDef *)dev_param;

	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(dev->spi, &reg_addr, 1, 1000);
	HAL_SPI_Receive(dev->spi, data, len, 1000);
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);

	return 0;
}

static int8_t SPI_RegWrite(uint32_t dev_param, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
	BMP280_HandleTypeDef* dev = (BMP280_HandleTypeDef *)dev_param;

	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(dev->spi, &reg_addr, 1, 1000);
	HAL_SPI_Transmit(dev->spi, data, len, 1000);
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);

	return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

void BMP280_SPI_Init(BMP280_HandleTypeDef* dev, SPI_HandleTypeDef* spi, GPIO_TypeDef* port, uint16_t pin)
{
	//
	dev->spi = spi;
	dev->cs_port = port;
	dev->cs_pin = pin;

	//
	dev->bmp.intf = BMP280_SPI_INTF;
	dev->bmp.dev_id = (uint32_t)dev;
	dev->bmp.delay_ms = HAL_Delay;
	dev->bmp.read = SPI_RegRead;
	dev->bmp.write = SPI_RegWrite;

	int8_t result = bmp280_init(&dev->bmp);
	result = bmp280_get_config(&dev->conf, &dev->bmp);

	// configuring the temperature over-sampling, filter coefficient and output data rate
	// Overwrite the desired settings
	dev->conf.filter = BMP280_FILTER_COEFF_2;
	// Pressure over-sampling set at 4x
	dev->conf.os_pres = BMP280_OS_4X;
	// Setting the output data rate as 1HZ(1000ms)
	dev->conf.odr = BMP280_ODR_1000_MS;
	result = bmp280_set_config(&dev->conf, &dev->bmp);

	// Always set the power mode after setting the configuration
	result =bmp280_set_power_mode(BMP280_NORMAL_MODE, &dev->bmp);
}


void BMP280_Update(BMP280_HandleTypeDef* dev)
{
	/* Reading the raw data from sensor */
	int8_t rslt = bmp280_get_uncomp_data(&dev->ucomp_data, &dev->bmp);

	/* Getting the compensated pressure using 32 bit precision */
	rslt = bmp280_get_comp_pres_32bit(&dev->pres32, dev->ucomp_data.uncomp_press, &dev->bmp);

	/* Getting the compensated pressure using 64 bit precision */
	rslt = bmp280_get_comp_pres_64bit(&dev->pres64, dev->ucomp_data.uncomp_press, &dev->bmp);

	/* Getting the compensated pressure as floating point value */
	rslt = bmp280_get_comp_pres_double(&dev->pres, dev->ucomp_data.uncomp_press, &dev->bmp);
}
