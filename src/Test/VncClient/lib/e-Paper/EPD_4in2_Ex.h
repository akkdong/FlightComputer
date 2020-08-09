// EPD_4in2_Ex.h
//

#ifndef __EPD_4IN2_EX_H__
#define __EPD_4IN2_EX_H__

#include "DEV_Config.h"

// Display resolution
#define EPD_4IN2_WIDTH       400
#define EPD_4IN2_HEIGHT      300

void EPD_4IN2_Ex_Init(void);
void EPD_4IN2_Ex_Clear(void);
void EPD_4IN2_Ex_Display(UBYTE *Image);
void EPD_4IN2_Ex_PartialDisplay(UWORD X_start,UWORD Y_start,UWORD X_end,UWORD Y_end, UBYTE *Image);
void EPD_4IN2_Ex_Sleep(void);


#endif // __EPD_4IN2_EX_H__