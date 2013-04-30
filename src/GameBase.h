/*
 * GameBase.h
 *
 *  Created on: 16 במרס 2013
 *      Author: yuval
 */

#ifndef GAMEBASE_H_
#define GAMEBASE_H_

#include <irrlicht.h>
#include "Input.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GameBase {
public:
	GameBase();
	virtual ~GameBase();
	void start();

	static IrrlichtDevice *device;

	static IVideoDriver* driver;
	static ISceneManager* smgr;
	static IGUIEnvironment* guienv;

protected:
	virtual bool update()=0;

};

#endif /* GAMEBASE_H_ */
