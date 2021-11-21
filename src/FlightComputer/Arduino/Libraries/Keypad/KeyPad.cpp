/*
 * KeyPad.cpp
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */


#include "Arduino.h"
#include "KeyPad.h"


void KeyPad::begin()
{
	attachInterrupt(KEY_LEFT, Key_LEFT, CHANGE);
	attachInterrupt(KEY_RIGHT, Key_RIGHT, CHANGE);
	attachInterrupt(KEY_UP, Key_UP, CHANGE);
	attachInterrupt(KEY_DOWN, Key_DOWN, CHANGE);
	attachInterrupt(KEY_ENTER, Key_ENTER, CHANGE);
	attachInterrupt(KEY_FUNC1, Key_FUNC1, CHANGE);
	attachInterrupt(KEY_FUNC2, Key_FUNC2, CHANGE);
	attachInterrupt(KEY_MENU, Key_MENU, CHANGE);
	attachInterrupt(KEY_ESCAPE, Key_ESCAPE, CHANGE);
}

void KeyPad::end()
{
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

int KeyPad::keyState(int& key, int& state)
{
	if (enter != 0)
	{
		key = 1;
		state = enter < 0 ? 0 : 1;
		enter = 0;

		return 1;
	}
	if (escape != 0)
	{
		key = 2;
		state = escape < 0 ? 0 : 1;
		escape = 0;

		return 1;
	}

	return 0;
}

int KeyPad::enter = 0;
int KeyPad::escape = 0;

void KeyPad::Key_LEFT()
{
	Serial1.printf("LEFT: %s\r\n", digitalRead(KEY_LEFT) == LOW ? "RELEASE" : "PRESSED");
}

void KeyPad::Key_RIGHT()
{
	Serial1.printf("RIGHT: %s\r\n", digitalRead(KEY_RIGHT) == LOW ? "RELEASE" : "PRESSED");
}

void KeyPad::Key_UP()
{
	Serial1.printf("UP: %s\r\n", digitalRead(KEY_UP) == LOW ? "RELEASE" : "PRESSED");
}

void KeyPad::Key_DOWN()
{
	Serial1.printf("DOWN: %s\r\n", digitalRead(KEY_DOWN) == LOW ? "RELEASE" : "PRESSED");
}

void KeyPad::Key_ENTER()
{
	enter = (digitalRead(KEY_ENTER) == LOW) ? -1 : 1;
	Serial1.printf("ENTER: %s\r\n", enter < 0 ? "RELEASE" : "PRESSED");
}

void KeyPad::Key_FUNC1()
{
	Serial1.printf("FUNC1: %s\r\n", digitalRead(KEY_FUNC1) == LOW ? "RELEASE" : "PRESSED");
}

void KeyPad::Key_FUNC2()
{
	Serial1.printf("FUNC2: %s\r\n", digitalRead(KEY_FUNC2) == LOW ? "RELEASE" : "PRESSED");
}

void KeyPad::Key_MENU()
{
	Serial1.printf("MENU: %s\r\n", digitalRead(KEY_MENU) == LOW ? "RELEASE" : "PRESSED");
}

void KeyPad::Key_ESCAPE()
{
	escape = (digitalRead(KEY_ESCAPE) == LOW) ? -1 : 1;
	Serial1.printf("ESCAPE: %s\r\n", escape < 0 ? "RELEASE" : "PRESSED");
}
