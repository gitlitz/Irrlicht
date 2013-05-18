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
enum KeyState
{
	UP,
	DOWN,
	PRESSED,
	RELEASED
};
class Input:public  IEventReceiver{
public:
	virtual ~Input();
	virtual bool OnEvent(const SEvent& event);
	static Input* GetInstance();
	enum KeyState getKeyState(EKEY_CODE keyCode) const;
	void update();
private:
	static Input* instance;
	Input();
	enum KeyState keys[KEY_KEY_CODES_COUNT];
};

#endif /* INPUTS_H_ */
