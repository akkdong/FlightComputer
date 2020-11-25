// TPS65186.c
//


#include "stm32h7xx_hal.h"
#include "TPS65186.h"

#define PMIC_ADDR			(0x48 << 1)

#define REG_TMST_VALUE		0x00
#define REG_ENABLE			0x01
#define REG_VADJ			0x02
#define REG_VCOM1			0x03
#define REG_VCOM2			0x04
#define REG_INT_EN1			0x05
#define REG_INT_EN2			0x06
#define REG_INT1			0x07
#define REG_INT2			0x08
#define REG_UPSEQ0			0x09
#define REG_UPSEQ1			0x0A
#define REG_DWNSEQ0			0x0B
#define REG_DWNSEQ1			0x0C
#define REG_TMST1			0x0D
#define REG_TMST2			0x0E
#define REG_PG				0x0F
#define REG_REVID			0x10



////////////////////////////////////////////////////////////////////////////////////////////////
//

void PMIC_Init(PMIC_HandleTypeDef* pmic)
{
	uint8_t data[] = {
		REG_UPSEQ0,
		0b00011011, // Power up sequence.
		0b00000000, // Power up delay (3mS per rail)
		0b00011011, // Power down sequence.
		0b00000000, // Power down delay (6mS per rail)
	};

	/*HAL_StatusTypeDef status =*/ HAL_I2C_Master_Transmit(pmic->i2c, PMIC_ADDR, &data[0], sizeof(data) / sizeof(data[0]), 1000);
}

void PMIC_EnableRegulators(PMIC_HandleTypeDef* pmic, uint8_t value)
{
	uint8_t data[] = { REG_ENABLE, value };
	HAL_I2C_Master_Transmit(pmic->i2c, PMIC_ADDR, &data[0], sizeof(data) / sizeof(data[0]), 1000);
}

uint8_t PMIC_ReadPowerStatus(PMIC_HandleTypeDef* pmic)
{
	uint8_t addr = REG_PG;
	uint8_t data = 0;

	HAL_I2C_Master_Transmit(pmic->i2c, PMIC_ADDR, &addr, 1, 1000);
	HAL_I2C_Master_Receive(pmic->i2c, PMIC_ADDR, &data, 1, 1000);

	return data;
}
