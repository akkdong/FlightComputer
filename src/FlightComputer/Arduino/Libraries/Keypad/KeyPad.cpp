/*
 * KeyPad.cpp
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */


#include "Arduino.h"
#include "KeyPad.h"


//////////////////////////////////////////////////////////////////////////
// class KeyPad

KeyPad::KeyPad()
	: mTimer(TIM4)
	, mKeyState{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	, mPressTick{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	, mRearEvent(0)
	, mFrontEvent(0)
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

	//mTimer.setOverflow(val, format);
	mTimer.attachInterrupt(TimerHanlder);
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
	int next = (mFrontEvent + 1) & 0x0F;
	if (next == mRearEvent)
		return -1; // FULL!!!

	mKeyEvent[mFrontEvent] = event;
	mFrontEvent = next;

	return 0;
}

uint32_t KeyPad::pop()
{
	uint32_t event = 0;

	if (mRearEvent != mFrontEvent)
	{
		event = mKeyEvent[mRearEvent];
		mRearEvent = (mRearEvent + 1) & 0x0F;
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

void KeyPad::ButtonHandler(KEY_VALUE key)
{
	if (Key.mKeyState[key] != RELEASED)
		return;

	Key.mKeyState[key] = DEBOUNCE;
	Key.mPressTick[key] = millis();
}

void KeyPad::TimerHanlder()
{
	for (int key = 0; key < COUNT; key++)
	{
		uint32_t state = Key.mKeyState[key];
		if (state == RELEASED)
			continue;

		uint32_t elapse = millis() - Key.mPressTick[key];
		int data = digitalRead(Key.mKeyLUT[key]);

		if (state == DEBOUNCE)
		{
			if (elapse > 50)
			{
				if (data == LOW)
				{
					Key.push(EVENT_PRESSED | key);
					Key.mKeyState[key] = PRESSED;
				}
				else
				{
					Key.mKeyState[key] = RELEASED;
				}
			}
		}
		else // if (state == PRESSED)
		{
			if (data == LOW)
			{
				if (elapse > 3000)
				{
					Key.push(EVENT_LPRESSED | key);
					Key.mKeyState[key] = RELEASED;
				}
			}
			else
			{
				if (elapse < 3000)
				{
					Key.push(EVENT_RELEASED | key);
				}
				else
				{
					Key.push(EVENT_LRELEASED | key);
				}

				Key.mKeyState[key] = RELEASED;
			}
		}
	}
}




//////////////////////////////////////////////////////////////////////////
// KeyPad global variable

KeyPad	Key;

