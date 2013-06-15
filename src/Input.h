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
	virtual bool OnEvent(const SEvent& event);
//	static Input* GetInstance();
	enum KeyState getKeyState(EKEY_CODE keyCode) const;
	void update();
private:
	static Input* instance;
	Input();
	enum KeyState keys[KEY_KEY_CODES_COUNT];
public:
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
