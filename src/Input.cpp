/*
 * Inputs.cpp
 *
 *  Created on: 28 במרס 2013
 *      Author: yuval
 */

#include "Input.h"
#include "stdio.h"
#include "debug settings.h"
Input* Input::instance=NULL;
Input* Input::GetInstance() {
	if(instance==NULL)
		instance=new Input();
	return instance;
}

bool Input::IsKeyDown(EKEY_CODE keyCode) const {
	return KeyIsDown[keyCode];
}

bool Input::IsKeyPressed(EKEY_CODE keyCode) const {
	return KeyIsDown[keyCode];
}

Input::Input() {
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
	{
		KeyIsDown[i] = false;
		KeyIsPressed[i] = false;
	}
}

Input::~Input() {
	// TODO Auto-generated destructor stub
}

bool Input::OnEvent(const SEvent& event) {
	if (event.EventType == EET_KEY_INPUT_EVENT)
	{
		if(KeyIsDown[event.KeyInput.Key] != event.KeyInput.PressedDown)
		{
			KeyIsPressed[event.KeyInput.Key]= event.KeyInput.PressedDown;
#ifdef DEBUG_KEY_PRESSED
			if(event.KeyInput.PressedDown)
				printf("key pressed %d \n",event.KeyInput.Key);
#endif
		}
		else
			KeyIsPressed[event.KeyInput.Key]=false;
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	return false;
}
