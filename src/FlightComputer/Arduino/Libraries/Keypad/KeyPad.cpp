/*
 * KeyPad.cpp
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */


#include "Arduino.h"
#include "KeyPad.h"

#define TIMER_HZ			(20) 		// 1000 / 20 = 50ms interval
#define DEBOUNCE_PERIOD		(20)		// 20ms
#define LONGKEY_PERIOD		(2000)		// 2s


//////////////////////////////////////////////////////////////////////////
// class KeyPad

int KeyPad::mKeyLUT[KeyPad::COUNT] = {
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


KeyPad::KeyPad()
	: mTimer(TIM4)
	, mState{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	, mEventTick{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	, mEventRear(0)
	, mEventFront(0)
{
}

void KeyPad::begin()
{
	attachInterrupt(KEY_LEFT, ButtonHandler_LEFT, RISING);
	attachInterrupt(KEY_RIGHT, ButtonHandler_RIGHT, RISING);
	attachInterrupt(KEY_UP, ButtonHandler_UP, RISING);
	attachInterrupt(KEY_DOWN, ButtonHandler_DOWN, RISING);
	attachInterrupt(KEY_ENTER, ButtonHandler_ENTER, RISING);
	attachInterrupt(KEY_FUNC1, ButtonHandler_FUNC1, RISING);
	attachInterrupt(KEY_FUNC2, ButtonHandler_FUNC2, RISING);
	attachInterrupt(KEY_MENU, ButtonHandler_MENU, RISING);
	attachInterrupt(KEY_ESCAPE, ButtonHandler_ESCAPE, RISING);

	mTimer.setOverflow(TIMER_HZ, HERTZ_FORMAT);
	mTimer.attachInterrupt(TimerHanlder);
	mTimer.resume();
}

void KeyPad::end()
{
	mTimer.detachInterrupt();

	detachInterrupt(KEY_LEFT);
	detachInterrupt(KEY_RIGHT);
	detachInterrupt(KEY_UP);
	detachInterrupt(KEY_DOWN);
	detachInterrupt(KEY_ENTER);
	detachInterrupt(KEY_FUNC1);
	detachInterrupt(KEY_FUNC2);
	detachInterrupt(KEY_MENU);
	detachInterrupt(KEY_ESCAPE);
}

int KeyPad::getEventCount()
{
	return 0;
}

uint32_t KeyPad::getEvent()
{
	return pop();
}

int KeyPad::push(uint32_t event)
{
	int next = (mEventFront + 1) & 0x0F;
	if (next == mEventRear)
		return -1; // FULL!!!

	mEventQueue[mEventFront] = event;
	mEventFront = next;

	return 0;
}

uint32_t KeyPad::pop()
{
	uint32_t event = 0;

	if (mEventRear != mEventFront)
	{
		event = mEventQueue[mEventRear];
		mEventRear = (mEventRear + 1) & 0x0F;
	}

	return event;
}

void KeyPad::ButtonHandler_LEFT()
{
#ifdef DEBUG
	Serial1.printf("LEFT: %s\r\n", digitalRead(KEY_LEFT) == LOW ? "RELEASE" : "PRESSED");
#endif
	ButtonHandler(LEFT);
}

void KeyPad::ButtonHandler_RIGHT()
{
#ifdef DEBUG
	Serial1.printf("RIGHT: %s\r\n", digitalRead(KEY_RIGHT) == LOW ? "RELEASE" : "PRESSED");
#endif
	ButtonHandler(RIGHT);
}

void KeyPad::ButtonHandler_UP()
{
#ifdef DEBUG
	Serial1.printf("UP: %s\r\n", digitalRead(KEY_UP) == LOW ? "RELEASE" : "PRESSED");
#endif
	ButtonHandler(UP);
}

void KeyPad::ButtonHandler_DOWN()
{
#ifdef DEBUG
	Serial1.printf("DOWN: %s\r\n", digitalRead(KEY_DOWN) == LOW ? "RELEASE" : "PRESSED");
#endif
	ButtonHandler(DOWN);
}

void KeyPad::ButtonHandler_ENTER()
{
#ifdef DEBUG
	Serial1.printf("ENTER: %s\r\n", digitalRead(KEY_ENTER) == LOW ? "RELEASE" : "PRESSED");
#endif
	ButtonHandler(ENTER);
}

void KeyPad::ButtonHandler_FUNC1()
{
#ifdef DEBUG
	Serial1.printf("FUNC1: %s\r\n", digitalRead(KEY_FUNC1) == LOW ? "RELEASE" : "PRESSED");
#endif
	ButtonHandler(FUNC1);
}

void KeyPad::ButtonHandler_FUNC2()
{
#ifdef DEBUG
	Serial1.printf("FUNC2: %s\r\n", digitalRead(KEY_FUNC2) == LOW ? "RELEASE" : "PRESSED");
#endif
	ButtonHandler(FUNC2);
}

void KeyPad::ButtonHandler_MENU()
{
#ifdef DEBUG
	Serial1.printf("MENU: %s\r\n", digitalRead(KEY_MENU) == LOW ? "RELEASE" : "PRESSED");
#endif
	ButtonHandler(MENU);
}

void KeyPad::ButtonHandler_ESCAPE()
{
#ifdef DEBUG
	Serial1.printf("ESCAPE: %s\r\n", digitalRead(KEY_ESCAPE) == LOW ? "RELEASE" : "PRESSED");
#endif
	ButtonHandler(ESCAPE);
}

void KeyPad::ButtonHandler(KEY_TYPE key)
{
	if (Key.mState[key] != RELEASED)
		return;

	Key.mState[key] = DEBOUNCE;
	Key.mEventTick[key] = millis();
}

void KeyPad::TimerHanlder()
{
	for (int key = 0; key < COUNT; key++)
	{
		uint32_t state = Key.mState[key];
		if (state == RELEASED)
			continue;

		uint32_t elapse = millis() - Key.mEventTick[key];
		int data = digitalRead(mKeyLUT[key]);

		if (state == DEBOUNCE)
		{
			if (elapse > DEBOUNCE_PERIOD)
			{
				if (data == LOW)
				{
					Key.push(EVENT_KEYDOWN | key);
					Key.mState[key] = PRESSED;
				}
				else
				{
					Key.mState[key] = RELEASED;
				}
			}
		}
		else //if (state == PRESSED)
		{
			if (data == LOW)
			{
				if (elapse > LONGKEY_PERIOD)
				{
					Key.push(EVENT_LONGKEY | key);
					Key.mState[key] = RELEASED;
				}
			}
			else
			{
				if (elapse < LONGKEY_PERIOD)
				{
					Key.push(EVENT_KEYUP | key);
				}
				//else
				//{
				//	LONGKEY_UP
				//}

				Key.mState[key] = RELEASED;
			}
		}
	}
}




//////////////////////////////////////////////////////////////////////////
// KeyPad global variable

KeyPad	Key;

