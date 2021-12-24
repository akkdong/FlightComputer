// beep.c
//

#include "main.h"
#include "beep.h"


#define NS       	128
#define TIMER_CLK  	66000000
#define FREQ 		1500



extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern DMA_HandleTypeDef hdma_tim4_ch1;
extern DMA_HandleTypeDef hdma_tim4_ch2;


uint32_t Wave_LUT[NS] = {
    512, 537, 562, 587, 612, 637, 661, 685, 709, 732, 754, 776, 798, 818, 838,
    857, 875, 893, 909, 925, 939, 952, 965, 976, 986, 995, 1002, 1009, 1014, 1018,
    1021, 1023, 1023, 1022, 1020, 1016, 1012, 1006, 999, 990, 981, 970, 959, 946, 932,
    917, 901, 884, 866, 848, 828, 808, 787, 765, 743, 720, 697, 673, 649, 624,
    600, 575, 549, 524, 499, 474, 448, 423, 399, 374, 350, 326, 303, 280, 258,
    236, 215, 195, 175, 157, 139, 122, 106, 91, 77, 64, 53, 42, 33, 24,
    17, 11, 7, 3, 1, 0, 0, 2, 5, 9, 14, 21, 28, 37, 47,
    58, 71, 84, 98, 114, 130, 148, 166, 185, 205, 225, 247, 269, 291, 314,
    338, 362, 386, 411, 436, 461, 486, 511
};

uint32_t DestAddressCH3 = (uint32_t) &(TIM3->CCR3);
uint32_t DestAddressCH4 = (uint32_t) &(TIM3->CCR4);

uint32_t TIM_Ticks = TIMER_CLK / (NS * FREQ);


uint32_t beep_GetTimerTick(uint32_t freq)
{
	if (freq == 0)
		return 0;

	return TIMER_CLK / (NS * freq);
}


void beep_init(void)
{
#if 0
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

	HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_2);

	HAL_DMA_Start_IT(&hdma_tim4_ch1, (uint32_t)Wave_LUT, DestAddressCH3, NS);
	HAL_DMA_Start_IT(&hdma_tim4_ch2, (uint32_t)Wave_LUT, DestAddressCH4, NS);

	__HAL_TIM_ENABLE_DMA(&htim4, TIM_DMA_CC1);
	__HAL_TIM_ENABLE_DMA(&htim4, TIM_DMA_CC2);
#endif
}

static int beep_on = 0;

void beep_setFreq(int freq)
{
	// set CCR
	TIM4->ARR = beep_GetTimerTick(freq);

	if (beep_on == 0)
	{
		// start PWM
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

		// start timer
		HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_1);
		HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_2);
		// start DMA
		HAL_DMA_Start_IT(&hdma_tim4_ch1, (uint32_t)Wave_LUT, DestAddressCH3, NS);
		HAL_DMA_Start_IT(&hdma_tim4_ch2, (uint32_t)Wave_LUT, DestAddressCH4, NS);
		// enable DMA
		__HAL_TIM_ENABLE_DMA(&htim4, TIM_DMA_CC1);
		__HAL_TIM_ENABLE_DMA(&htim4, TIM_DMA_CC2);

		//
		beep_on = 1;
	}
}

void beep_setNode(NOTE note)
{

}

void beep_mute()
{
	// stop PWM
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);

	// disable DMA
	__HAL_TIM_DISABLE_DMA(&htim4, TIM_DMA_CC1);
	__HAL_TIM_DISABLE_DMA(&htim4, TIM_DMA_CC2);
	// abort DMA
	HAL_DMA_Abort_IT(&hdma_tim4_ch1);
	HAL_DMA_Abort_IT(&hdma_tim4_ch2);
	// stop timer
	HAL_TIM_OC_Stop(&htim4, TIM_CHANNEL_1);
	HAL_TIM_OC_Stop(&htim4, TIM_CHANNEL_2);

	//
	beep_on = 0;
}
