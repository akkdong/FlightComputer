// bmp280_port.c
//

#include "bmp280_port.h"
#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#define SPI_BUFFER_LEN 28
#define SPI_READ	0x80
#define SPI_WRITE	0x7F
#define BME280_DATA_INDEX	1
#define BME280_ADDRESS_INDEX	2

#define	BME280_INIT_VALUE				(0)
#define	BME280_CHIP_ID_READ_COUNT			(5)
#define	BME280_INVALID_DATA				(0)


#if USE_SPI
static int8_t SPI_RegRead(uint32_t dev_param, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
	BMP280_HandleTypeDef* dev = (BMP280_HandleTypeDef *)dev_param;

#if 0
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
	HAL_Delay(2);
	HAL_SPI_Transmit(dev->spi, &reg_addr, 1, 1000);
	HAL_SPI_Receive(dev->spi, &data[0], len, 1000);
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
	HAL_Delay(2);

	return 0;
#else
	HAL_StatusTypeDef status = HAL_OK;
	int32_t iError=BME280_INIT_VALUE;
	uint8_t txarray[SPI_BUFFER_LEN]={0,};
	uint8_t rxarray[SPI_BUFFER_LEN] = {0,};
	uint8_t stringpos;
	/*	For the SPI mode only 7 bits of register addresses are used.
	The MSB of register address is declared the bit what functionality it is
	read/write (read as 1/write as BME280_INIT_VALUE)*/
	for (int i = 0; i < SPI_BUFFER_LEN; i++)
	{
		txarray[i] = 0x00;
		rxarray[i] = 0x00;
	}
	txarray[BME280_INIT_VALUE] = reg_addr|SPI_READ;/*read routine is initiated register address is mask with 0x80*/

	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
	status = HAL_SPI_TransmitReceive(dev->spi, (uint8_t *)(&txarray), (uint8_t *)(&rxarray), len+1, 100);
	while(dev->spi->State == HAL_SPI_STATE_BUSY ) {};
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
	HAL_Delay(5); // since i can't find a buffer flushing command
	printf("BMP280 READ(%02X) :", reg_addr);
	for (stringpos = BME280_INIT_VALUE; stringpos < len; stringpos++) {
		*(data + stringpos) = rxarray[stringpos+BME280_DATA_INDEX];
		printf(" %02X", *(data + stringpos));
	}
	printf("\n");

    if (status != HAL_OK)
    {
    	// The BME280 API calls for 0 return value as a success, and -1 returned as failure
    	iError = (-1);
    }
	return (int8_t)iError;
#endif
}

static int8_t SPI_RegWrite(uint32_t dev_param, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
	BMP280_HandleTypeDef* dev = (BMP280_HandleTypeDef *)dev_param;

#if 0
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
	HAL_Delay(2);
	HAL_SPI_Transmit(dev->spi, &reg_addr, 1, 1000);
	HAL_SPI_Transmit(dev->spi, &data[0], len, 1000);
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
	HAL_Delay(2);

	return 0;
#else
	HAL_StatusTypeDef status = HAL_OK;
	int32_t iError = BME280_INIT_VALUE;
	uint8_t array[SPI_BUFFER_LEN * BME280_ADDRESS_INDEX];
	uint8_t stringpos = BME280_INIT_VALUE;
	uint8_t index = BME280_INIT_VALUE;
	printf("BMP280 WRITE(%02X) :", reg_addr);
	//for (int i = 0; i < SPI_BUFFER_LEN * BME280_ADDRESS_INDEX; i++)
	//	array[i] = 0x00;
	for (stringpos = BME280_INIT_VALUE; stringpos < len; stringpos++) {
		/* the operation of (reg_addr++)&0x7F done as per the
		SPI communication protocol specified in the data sheet*/
		index = stringpos * BME280_ADDRESS_INDEX;
		array[index] = (reg_addr++) & SPI_WRITE;
		printf(" %02X", array[index]);
		array[index + BME280_DATA_INDEX] = *(data + stringpos);
		printf(" %02X ", array[index + BME280_DATA_INDEX]);
	}
	printf("\n");

	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
	status = HAL_SPI_Transmit(dev->spi, (uint8_t*)(&array), len*2, 1000);
	while(dev->spi->State == HAL_SPI_STATE_BUSY ) {};
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);

	if (status != HAL_OK)
	{
		// The BME280 API calls for 0 return value as a success, and -1 returned as failure
		iError = (-1);
	}
		return (int8_t)iError;
#endif
}

#else

static int8_t I2C_RegRead(uint32_t dev_param, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
	BMP280_HandleTypeDef* dev = (BMP280_HandleTypeDef *)dev_param;
	HAL_I2C_Mem_Read(dev->i2c, dev->bmp.dev_id, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, 1000);

	return 0;
}

static int8_t I2C_RegWrite(uint32_t dev_param, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
	BMP280_HandleTypeDef* dev = (BMP280_HandleTypeDef *)dev_param;
	HAL_I2C_Mem_Write(dev->i2c, dev->bmp.dev_id, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, 1000);

	return 0;
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

void BMP280_Init(BMP280_HandleTypeDef* dev)
{
#if USE_SPI
	dev->bmp.intf = BMP280_SPI_INTF;
	dev->bmp.delay_ms = HAL_Delay;
	dev->bmp.read = SPI_RegRead;
	dev->bmp.write = SPI_RegWrite;
#else
	dev->bmp.intf = BMP280_I2C_INTF;
	dev->bmp.delay_ms = HAL_Delay;
	dev->bmp.read = I2C_RegRead;
	dev->bmp.write = I2C_RegWrite;
#endif
	dev->bmp.dev_id = (0x76 << 1);
	dev->bmp.dev_param = (uint32_t)dev;

	int8_t result = bmp280_init(&dev->bmp);
	result = bmp280_get_config(&dev->conf, &dev->bmp);

	// configuring the temperature over-sampling, filter coefficient and output data rate
	// Overwrite the desired settings
	dev->conf.filter = BMP280_FILTER_COEFF_8;
	// Pressure over-sampling set at 4x
	dev->conf.os_pres = BMP280_OS_16X;
	// Setting the output data rate as 1HZ(1000ms)
	dev->conf.odr = BMP280_ODR_62_5_MS;
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

	bmp280_get_comp_temp_32bit(&dev->temp32, dev->ucomp_data.uncomp_press, &dev->bmp);
	bmp280_get_comp_temp_double(&dev->temp, dev->ucomp_data.uncomp_press, &dev->bmp);
}
