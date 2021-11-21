/*
 * KeyPad.h
 *
 *  Created on: 2021. 1. 30.
 *      Author: akkdong
 */

#ifndef LIBRARIES_KEYPAD_KEYPAD_H_
#define LIBRARIES_KEYPAD_KEYPAD_H_


class KeyPad
{
public:
	KeyPad() = default;

	void begin();
	void end();

	int keyState(int& key, int& state);

protected:
	static int enter;
	static int escape;

protected:
	static void Key_LEFT();
	static void Key_RIGHT();
	static void Key_UP();
	static void Key_DOWN();
	static void Key_ENTER();
	static void Key_FUNC1();
	static void Key_FUNC2();
	static void Key_MENU();
	static void Key_ESCAPE();
};


#endif /* LIBRARIES_KEYPAD_KEYPAD_H_ */
