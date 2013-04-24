/*
 * Inputs.h
 *
 *  Created on: 28 במרס 2013
 *      Author: yuval
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "IEventReceiver.h"
using namespace irr;
class Input:public  IEventReceiver{
public:
	virtual ~Input();
	virtual bool OnEvent(const SEvent& event);
	static Input* GetInstance();
	bool IsKeyDown(EKEY_CODE keyCode) const;
	bool IsKeyPressed(EKEY_CODE keyCode) const;

private:
	static Input* instance;
	Input();
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool KeyIsPressed[KEY_KEY_CODES_COUNT];
};

#endif /* INPUTS_H_ */
