/*
 * Inputs.cpp
 *
 *  Created on: 28 במרס 2013
 *      Author: yuval
 */

#include "Input.h"
#include "stdio.h"
#include "debug settings.h"


KeyState Input::getKeyState(EKEY_CODE keyCode) const {
	return keys[keyCode];
}

void Input::update() {
	for (int i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
		if(keys[i]==PRESSED)
			keys[i]=DOWN;
		else if(keys[i]==RELEASED)
			keys[i]=UP;
	}
}

Input::Input() {
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
		keys[i]=UP;
}

Input::~Input() {
	// TODO Auto-generated destructor stub
}

bool Input::OnEvent(const SEvent& event) {
	if (event.EventType == EET_KEY_INPUT_EVENT)
	{
		if(event.KeyInput.PressedDown)
		{
			if(keys[event.KeyInput.Key]!=DOWN)
				keys[event.KeyInput.Key]=PRESSED;
		}
		else
			keys[event.KeyInput.Key]=RELEASED;
	}

	return false;
}
