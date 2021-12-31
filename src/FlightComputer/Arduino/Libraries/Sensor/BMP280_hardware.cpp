#include "BMP280.hpp"
#include "BMP280_defines.h"

#include <stdint.h>

/* ---------------------------------------------------------------------------
 * Register read/write definitions -------------------------------------------
 * ------------------------------------------------------------------------ */

/**
 * Read a register
 * @param address: Register address.
 * @return Register value.
 * */
uint8_t BMP280::readRegister(uint8_t address)
{
	spiCSNlow();
	spiReadWrite(address);
	uint8_t value = spiReadWrite(0);
	spiCSNhigh();
	return value;
}

/**
 * Write to a register
 * @param address: Register address.
 * @param value: Value to write.
 * */
void BMP280::writeRegister(uint8_t address, uint8_t value)
{
	spiCSNlow();
	spiReadWrite(address & BMP280_SPI_MASK_WRITE);
	spiReadWrite(value);
	spiCSNhigh();
}

/**
 * Read a multi-byte register
 * @param address: Register address.
 * @param values: Array pointer to store values in.
 * @param length: Number of bytes to read.
 * */
void BMP280::readMBRegister(uint8_t address, uint8_t *values, uint8_t length)
{
	spiCSNlow();
	spiReadWrite(address);
#if OLD_METHOD
	while (length--)
	{
		*values++ = spiReadWrite(0);
	}
#else
#if USE_SPI_HANDLE || 1
	HAL_SPI_TransmitReceive(spi.getHandle(), values, values, length, HAL_MAX_DELAY);
#else
	spi.transfer(CS_PIN_CONTROLLED_BY_USER, values, values, length);
#endif
#endif
	spiCSNhigh();
}


/* ---------------------------------------------------------------------------
 * SPI interface definitions -------------------------------------------------
 * (ADAPT THESE METHODS TO YOUR HARDWARE) ------------------------------------
 * ------------------------------------------------------------------------ */

/**
 * SPI transmit and receive one byte simultaneously
 * @param tx_message: Transmit byte.
 * @return Received byte.
 * */
uint8_t BMP280::spiReadWrite(uint8_t tx_message)
{
	uint8_t rx_message = 255;
#if USE_SPI_HANDLE || 1
	HAL_SPI_TransmitReceive(spi.getHandle(), &tx_message, &rx_message, 1, HAL_MAX_DELAY);
#else
	spi.transfer(CS_PIN_CONTROLLED_BY_USER, &tx_message, &rx_message, 1);
#endif
	return rx_message;
}

/** Pull chip select high (inactive) */
void BMP280::spiCSNhigh()
{
#if USE_SPI_HANDLE
	HAL_GPIO_WritePin(PORTE, GPIO_PIN_4, GPIO_PIN_SET);
#else
	digitalWrite(csPin, HIGH);
#endif
}

/** Pull chip select low (active) */
void BMP280::spiCSNlow()
{
#if USE_SPI_HANDLE
	HAL_GPIO_WritePin(PORTE, GPIO_PIN_4, GPIO_PIN_RESET);
#else
	digitalWrite(csPin, LOW);
#endif
}

/** Millisecond Delay */
void BMP280::delay_ms(uint32_t milliseconds)
{
	HAL_Delay(milliseconds);
}
