/*
 * GameBase.cpp
 *
 *  Created on: 16 במרס 2013
 *      Author: yuval
 */

#include "GameBase.h"

IrrlichtDevice *GameBase::device=NULL;
IVideoDriver* GameBase::driver=NULL;
ISceneManager *GameBase::smgr=NULL;
IGUIEnvironment *GameBase::guienv=NULL;


GameBase::GameBase() {
	// TODO Auto-generated constructor stub
	device = createDevice(video::EDT_OPENGL,dimension2d<u32>(640, 480), 16, false,false,true);

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

}

GameBase::~GameBase() {
	device->drop();
}

void GameBase::start() {
	while(device->run())
	{
		update();
		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}
}
