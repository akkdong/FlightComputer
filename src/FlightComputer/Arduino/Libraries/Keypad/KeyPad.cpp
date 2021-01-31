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
	Serial1.printf("ENTER: %s\r\n", digitalRead(KEY_ENTER) == LOW ? "RELEASE" : "PRESSED");
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
	Serial1.printf("ESCAPE: %s\r\n", digitalRead(KEY_ESCAPE) == LOW ? "RELEASE" : "PRESSED");
}
