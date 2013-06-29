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

#include <map>
#include <string>
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
	static ISceneNode * seeker;

protected:
	/**
	 * called before every iteration fo the game
	 * @return should continue to run (not exit)
	 */
	virtual bool update()=0;
	//can be used only in the constructor
	ITriangleSelector *mapSelector;

private:
	//init the selector for the map
	void create_mapSelector();
};

#endif /* GAMEBASE_H_ */
