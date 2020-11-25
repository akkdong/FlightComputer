// TPS65186.h
//

#ifndef __TPS65186_H__
#define __TPS65186_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _PMIC_HandleTypeDef
{
	I2C_HandleTypeDef* i2c;


} PMIC_HandleTypeDef;



void PMIC_Init(PMIC_HandleTypeDef* pmic);

void PMIC_EnableRegulators(PMIC_HandleTypeDef* pmic, uint8_t value);
uint8_t PMIC_ReadPowerStatus(PMIC_HandleTypeDef* pmic);


#ifdef __cplusplus
}
#endif

#endif // __TPS65186_H__

