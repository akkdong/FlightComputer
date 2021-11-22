/*
 * KeyPad.h
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#ifndef LIBRARIES_KEYPAD_KEYPAD_H_
#define LIBRARIES_KEYPAD_KEYPAD_H_

#include "HardwareTimer.h"


#define EVENT_KEY_MASK				(0x000F)
#define EVENT_STATE_MASK			(0xF000)
#define EVENT_NONE					(0x0000)
#define EVENT_PRESSED				(0x1000)
#define EVENT_RELEASED				(0x2000)
#define EVENT_LPRESSED				(0x3000)
#define EVENT_LRELEASED				(0x4000)


//////////////////////////////////////////////////////////////////////////
// class KeyPad

class KeyPad
{
public:
	KeyPad();

	enum KEY_VALUE {
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
	static void 		ButtonHandler(KEY_VALUE key);

	static void 		TimerHanlder();


protected:
	HardwareTimer		mTimer;

	uint32_t			mKeyState[COUNT];
	uint32_t			mPressTick[COUNT];

	uint32_t			mKeyEvent[16];
	volatile int		mRearEvent;
	volatile int		mFrontEvent;

	int					mKeyLUT[COUNT] = {
							KEY_LEFT,
							KEY_RIGHT,
							KEY_UP,
							KEY_DOWN,
							KEY_ENTER,
							KEY_FUNC1,
							KEY_FUNC2,
							KEY_MENU,
							KEY_ESCAPE
	                    };

};


extern KeyPad		Key;


#endif /* LIBRARIES_KEYPAD_KEYPAD_H_ */
