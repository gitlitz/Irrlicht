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
	ISceneNode* camera=smgr->addCameraSceneNodeFPS();
	smgr->addLightSceneNode(camera);
	cube=smgr->addCubeSceneNode(100);
	cube->setPosition(vector3df(200,0,400));
	smgr->addCubeSceneNode(100,cube)->setPosition(vector3df(0,0,400));

}

Game::~Game() {
	// TODO Auto-generated destructor stub

}

bool Game::update() {
	if(Input::GetInstance()->IsKeyDown(KEY_KEY_A))
		cube->drop();

	if(Input::GetInstance()->IsKeyDown(KEY_KEY_D))
		cube->setRotation(vector3df(cube->getRotation().X+1,0,0));
	int fps = driver->getFPS();
	stringw tmp(L"");
	tmp += driver->getName();
	tmp += L"] fps: ";
	tmp += fps;
	device->setWindowCaption(tmp.c_str());
	return !Input::GetInstance()->IsKeyPressed(KEY_ESCAPE);
}
