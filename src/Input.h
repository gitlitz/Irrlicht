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
private:
	static Input* instance;
	Input();
};

#endif /* INPUTS_H_ */
