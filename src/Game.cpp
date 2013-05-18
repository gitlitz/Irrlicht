/*
 * Game.cpp
 *
 *  Created on: 16 במרס 2013
 *      Author: yuval
 */

#include "Game.h"
#include <stdio.h>
Game::Game() {
	guienv->addStaticText(L"hello world",rect<signed int>(0,0,50,50),true);
	camera=smgr->addCameraSceneNodeFPS();
	smgr->addLightSceneNode(camera);
	camera->setPosition(vector3df(1478, 462, 886));
	cube=smgr->addCubeSceneNode(100);
	cube->setPosition(vector3df(200,0,400));
	smgr->addCubeSceneNode(100,cube)->setPosition(vector3df(0,0,400));

}

Game::~Game() {
	// TODO Auto-generated destructor stub

}

bool Game::update() {
	if(Input::GetInstance()->getKeyState(KEY_KEY_P)==PRESSED)
		printf("pos:%1.0f, %1.0f, %1.0f\n",camera->getPosition().X,camera->getPosition().Y,camera->getPosition().Z);

	int fps = driver->getFPS();
	stringw tmp(L"");
	tmp += driver->getName();
	tmp += L"] fps: ";
	tmp += fps;
	device->setWindowCaption(tmp.c_str());
	return Input::GetInstance()->getKeyState(KEY_ESCAPE)!=PRESSED;
}
