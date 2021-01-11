// epd_drv.h
//
// E-Paper display driver
//


#ifndef __EPD_DRV_H__
#define __EPD_DRV_H__

#include "stm32h7xx_hal.h"

#define GPIO_NUMBER           (16U)


////////////////////////////////////////////////////////////////////////////////////////
//

extern uint32_t pinLUT[256];



////////////////////////////////////////////////////////////////////////////////////////
//

/*
inline void EPD_Set_CKV(void)
{
	// HAL_GPIO_WritePin(EPD_CKV_GPIO_Port, EPD_CKV_Pin, GPIO_PIN_SET);
	// GPIOJ->BSSR = (1 << GPIO_PIN_8);
    GPIOJ->BSRR = 0b100000000;
}

inline void EPD_Set_SPH(void)
{
	// HAL_GPIO_WritePin(EPD_SPH_GPIO_Port, EPD_SPH_Pin, GPIO_PIN_SET);
	// GPIOK->BSSR = (1 << GPIO_PIN_1);
	GPIOK->BSRR = 0b10;
}

inline void EPD_Set_SPV(void)
{
	// HAL_GPIO_WritePin(EPD_SPV_GPIO_Port, EPD_SPV_Pin, GPIO_PIN_SET);
	// GPIOK->BSSR = (1 << GPIO_PIN_2);
	GPIOK->BSRR = 0b100;
}

inline void EPD_Set_LE(void)
{
	// HAL_GPIO_WritePin(EPD_LE_GPIO_Port, EPD_LE_Pin, GPIO_PIN_SET);
	// GPIOJ->BSSR = (1 << GPIO_PIN_11);
    GPIOJ->BSRR = 0b100000000000;
}

inline void EPD_Set_CL(void)
{
	// HAL_GPIO_WritePin(EPD_CL_GPIO_Port, EPD_CL_Pin, GPIO_PIN_SET);
	// GPIOJ->BSSR = (1 << GPIO_PIN_9);
    GPIOJ->BSRR = 0b1000000000;
}

inline void EPD_Set_OE(void)
{
	// HAL_GPIO_WritePin(EPD_OE_GPIO_Port, EPD_OE_Pin, GPIO_PIN_SET);
	// GPIOK->BSSR = (1 << GPIO_PIN_0);
	GPIOK->BSRR = 0b1;
}

inline void EPD_Set_GMODE(void)
{
	// HAL_GPIO_WritePin(EPD_GMODE_GPIO_Port, EPD_GMODE_Pin, GPIO_PIN_SET);
	// GPIOJ->BSSR = (1 << GPIO_PIN_10);
    GPIOJ->BSRR = 0b10000000000;
}

inline void EPD_Set_DATA(uint8_t data)
{
	// DATA Pin: GPIOD [12, 11, 7, 6, 5, 4, 3, 2]
	GPIOD->BSRR = pinLUT[data];
}

inline void EPD_Reset_CKV(void)
{
	// HAL_GPIO_WritePin(EPD_CKV_GPIO_Port, EPD_CKV_Pin, GPIO_PIN_SET);
	// GPIOJ->BSSR = (1 << GPIO_PIN_8) << GPIO_NUMBER;
    GPIOJ->BSRR = (0b100000000 << GPIO_NUMBER);
}

inline void EPD_Reset_SPH(void)
{
	// HAL_GPIO_WritePin(EPD_SPH_GPIO_Port, EPD_SPH_Pin, GPIO_PIN_SET);
	// GPIOK->BSSR = (1 << GPIO_PIN_1) << GPIO_NUMBER;
	GPIOK->BSRR = (0b10 << GPIO_NUMBER);
}

inline void EPD_Reset_SPV(void)
{
	// HAL_GPIO_WritePin(EPD_SPV_GPIO_Port, EPD_SPV_Pin, GPIO_PIN_SET);
	// GPIOK->BSSR = (1 << GPIO_PIN_2) << GPIO_NUMBER;
	GPIOK->BSRR = (0b100 << GPIO_NUMBER);
}

inline void EPD_Reset_LE(void)
{
	// HAL_GPIO_WritePin(EPD_LE_GPIO_Port, EPD_LE_Pin, GPIO_PIN_SET);
	// GPIOJ->BSSR = (1 << GPIO_PIN_11) << GPIO_NUMBER;
    GPIOJ->BSRR = (0b100000000000 << GPIO_NUMBER);
}

inline void EPD_Reset_CL(void)
{
	// HAL_GPIO_WritePin(EPD_CL_GPIO_Port, EPD_CL_Pin, GPIO_PIN_SET);
	// GPIOJ->BSSR = (1 << GPIO_PIN_9) << GPIO_NUMBER;
    GPIOJ->BSRR = (0b1000000000 << GPIO_NUMBER);
}

inline void EPD_Reset_OE(void)
{
	// HAL_GPIO_WritePin(EPD_OE_GPIO_Port, EPD_OE_Pin, GPIO_PIN_SET);
	// GPIOK->BSSR = (1 << GPIO_PIN_0) << GPIO_NUMBER;
	GPIOK->BSRR = (0b1 << GPIO_NUMBER);
}

inline void EPD_Reset_GMODE(void)
{
	// HAL_GPIO_WritePin(EPD_GMODE_GPIO_Port, EPD_GMODE_Pin, GPIO_PIN_SET);
	// GPIOJ->BSSR = (1 << GPIO_PIN_10) << GPIO_NUMBER;
    GPIOJ->BSRR = (0b10000000000 << GPIO_NUMBER);
}
*/

//                                      Bits:     5432109876543210
#define EPD_Set_CKV()		do { GPIOJ->BSRR = (0b0000000100000000); } while (0)
#define EPD_Set_SPH()		do { GPIOK->BSRR = (0b0000000000000010); } while (0)
#define EPD_Set_SPV()		do { GPIOK->BSRR = (0b0000000000000100); } while (0)
#define EPD_Set_LE()		do { GPIOJ->BSRR = (0b0000100000000000); } while (0)
#define EPD_Set_CL()		do { GPIOJ->BSRR = (0b0000001000000000); } while (0)
#define EPD_Set_OE()		do { GPIOK->BSRR = (0b0000000000000001); } while (0)
#define EPD_Set_GMODE()		do { GPIOJ->BSRR = (0b0000010000000000); } while (0)

//                                      Bits:     5432109876543210
#define EPD_Reset_CKV()		do { GPIOJ->BSRR = (0b0000000100000000 << GPIO_NUMBER); } while (0)
#define EPD_Reset_SPH()		do { GPIOK->BSRR = (0b0000000000000010 << GPIO_NUMBER); } while (0)
#define EPD_Reset_SPV()		do { GPIOK->BSRR = (0b0000000000000100 << GPIO_NUMBER); } while (0)
#define EPD_Reset_LE()		do { GPIOJ->BSRR = (0b0000100000000000 << GPIO_NUMBER); } while (0)
#define EPD_Reset_CL()		do { GPIOJ->BSRR = (0b0000001000000000 << GPIO_NUMBER); } while (0)
#define EPD_Reset_OE()		do { GPIOK->BSRR = (0b0000000000000001 << GPIO_NUMBER); } while (0)
#define EPD_Reset_GMODE() 	do { GPIOJ->BSRR = (0b0000010000000000 << GPIO_NUMBER); } while (0)

#define EPD_Set_DATA(data)	do { GPIOD->BSRR = pinLUT[(data)]; } while (0)



////////////////////////////////////////////////////////////////////////////////////////
//

void EPD_Init(void);

void EPD_ClockPixel(void);
void EPD_OutputRow(void);
void EPD_LatchRow(void);
void EPD_VScanStart(void);
void EPD_VScanEnd(void);
void EPD_HScanStart(void);
void EPD_HScanEnd(void);

void EPD_ClearScreen(void);
void EPD_Draw16Gray(const uint8_t* img_bytes);
void EPD_DrawMono(const uint8_t* img_bytes);


void epd_init(void);
void epd_clearScreen(void);

#endif // __EPD_DRV_H__
