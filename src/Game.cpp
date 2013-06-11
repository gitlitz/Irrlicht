/*
 * Game.cpp
 *
 *  Created on: 16 במרס 2013
 *      Author: yuval
 */

#include "Game.h"
#include <stdio.h>
Game::Game() {

	device->getCursorControl()->setVisible(false);

	camera=smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, 0, 0, true, 5.f);

	smgr->addLightSceneNode(camera);
	camera->setPosition(vector3df(1478, 462, 886));
	cube=smgr->addCubeSceneNode(100);
	cube->setPosition(vector3df(200,0,400));
	anim = smgr->createCollisionResponseAnimator(
			mapSelector, camera, core::vector3df(30,50,30),
			core::vector3df(0,-10,0), core::vector3df(0,30,0));
	//Danny was here!!!
	camera->addAnimator(anim);
	anim->drop();

}

Game::~Game() {
	// TODO Auto-generated destructor stub
	camera->removeAnimators();
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
