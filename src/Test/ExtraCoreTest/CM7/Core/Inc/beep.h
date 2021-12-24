/*
 * beep.h
 *
 *  Created on: 2021. 12. 24.
 *      Author: akkdong
 */

#ifndef INC_BEEP_H_
#define INC_BEEP_H_

typedef enum
{
	NOTE_C4,
	NOTE_D4,
	NOTE_E4,
	NOTE_F4,
	NOTE_G4,
	NOTE_A4,
	NOTE_B4

} NOTE;


void beep_init(void);

void beep_setFreq(int freq);
void beep_setNode(NOTE note);
void beep_mute();


uint32_t beep_GetTimerTick(uint32_t freq);



#endif /* INC_BEEP_H_ */
