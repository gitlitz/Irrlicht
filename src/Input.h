/*
 * Inputs.h
 *
 *  Created on: 28 במרס 2013
 *      Author: yuval
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "IEventReceiver.h"
#include "KeyState.h"
using namespace irr;

class Input:public  IEventReceiver{
public:
	virtual bool OnEvent(const SEvent& event);
	/**
	 * return the state of a button
	 * @param keyCode button's code
	 * @return the state of the button
	 */
	KeyState getKeyState(EKEY_CODE keyCode) const;
	void update();
private:
	Input();
	KeyState keys[KEY_KEY_CODES_COUNT];
public:
	//singleton
  static Input& GetInstance()
  {
      static Input inst;
      return inst;
  }

protected:
  Input(const Input&); // Prevent construction by copying
  Input& operator=(const Input&); // Prevent assignment
  ~Input(); // Prevent unwanted destruction
};

#endif /* INPUTS_H_ */
