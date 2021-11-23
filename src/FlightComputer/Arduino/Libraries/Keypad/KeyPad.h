/*
 * KeyPad.h
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#ifndef LIBRARIES_KEYPAD_KEYPAD_H_
#define LIBRARIES_KEYPAD_KEYPAD_H_

#include "HardwareTimer.h"


#define EVENT_MASK_KEY				(0x000F)
#define EVENT_MASK_STATE			(0xF000)

#define EVENT_NOKEY					(0x0000)
#define EVENT_KEYDOWN				(0x1000)
#define EVENT_KEYUP					(0x2000)
#define EVENT_LONGKEY				(0x4000)



//////////////////////////////////////////////////////////////////////////
// class KeyPad

class KeyPad
{
public:
	KeyPad();

	enum KEY_TYPE {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		ENTER,
		FUNC1,
		FUNC2,
		MENU,
		ESCAPE,
		COUNT
	};

	enum KEY_STATE {
		RELEASED,
		DEBOUNCE,
		PRESSED,
	};

public:
	void 				begin();
	void 				end();

	int					getEventCount();
	uint32_t			getEvent();

protected:
	int					push(uint32_t event);
	uint32_t			pop();

protected:
	static void 		ButtonHandler_LEFT();
	static void 		ButtonHandler_RIGHT();
	static void 		ButtonHandler_UP();
	static void 		ButtonHandler_DOWN();
	static void 		ButtonHandler_ENTER();
	static void 		ButtonHandler_FUNC1();
	static void 		ButtonHandler_FUNC2();
	static void 		ButtonHandler_MENU();
	static void 		ButtonHandler_ESCAPE();
	static void 		ButtonHandler(KEY_TYPE key);

	static void 		TimerHanlder();


protected:
	HardwareTimer		mTimer;

	uint32_t			mState[COUNT];
	uint32_t			mEventTick[COUNT];
	uint32_t			mEventQueue[16];
	volatile int		mEventRear;
	volatile int		mEventFront;

	static int			mKeyLUT[COUNT];
};


extern KeyPad		Key;


#endif /* LIBRARIES_KEYPAD_KEYPAD_H_ */
