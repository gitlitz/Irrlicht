/*
 * Game.cpp
 *
 *  Created on: 16 במרס 2013
 *      Author: yuval
 */

#include "Game.h"
#include <stdio.h>
#include "Network/Client.h"
Game::Game() {
	//dont display the cursor
	device->getCursorControl()->setVisible(false);
	loadNpc();
	loadCamera();
}

Game::~Game() {
	// TODO Auto-generated destructor stub
	camera->removeAnimators();
	npc->removeAnimators();
}

bool Game::update() {
	updateNpc();
	SendPos(camera->getPosition(),camera->getRotation());
	//print the position with the p key
	if(Input::GetInstance().getKeyState(KEY_KEY_P)==PRESSED)
		printf("pos:%1.0f, %1.0f, %1.0f\n",camera->getPosition().X,camera->getPosition().Y,camera->getPosition().Z);
	//stop mouse capture after using the q key
	if(Input::GetInstance().getKeyState(KEY_KEY_Q)==PRESSED)
		camera->setInputReceiverEnabled(!camera->isInputReceiverEnabled());
	//print the fps
	int fps = driver->getFPS();
	stringw tmp(L"");
	tmp += driver->getName();
	tmp += L"] fps: ";
	tmp += fps;
	device->setWindowCaption(tmp.c_str());
	//exit after pressing the esc key
	return Input::GetInstance().getKeyState(KEY_ESCAPE)!=PRESSED;
}

void Game::updateNpc() {
	vector3df current=npc->getPosition();
	vector3df dest=camera->getPosition();
	//npc cant move up and down
	vector3df addition=vector3df(dest.X-current.X,0,dest.Z-current.Z);
	if(addition.getLength()<10)
		npc->setVisible(false);
	vector3df result=current+addition.normalize();
	npc->setPosition(result);
}
void Game::loadNpc() {
	IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");

	npc=smgr->addAnimatedMeshSceneNode(mesh);
	npc->setMaterialTexture( 0, driver->getTexture("media/sydney.bmp") );
	npc->setPosition(vector3df(1278, 462, 886));
	npc->setScale(vector3df(1.8,1.8,1.8));
	npc->setMD2Animation(EMD2_ANIMATION_TYPE::EMAT_STAND);
	//lighting
	npc->setMaterialFlag(EMF_LIGHTING, false);
	//calculate the radius of the texture
	const core::aabbox3d<f32>& box = npc->getBoundingBox();
	core::vector3df radius = box.MaxEdge - box.getCenter();
	//add collision
	npcCollision = smgr->createCollisionResponseAnimator(
			mapSelector, npc, radius*1.8);
	npc->addAnimator(npcCollision);
	npcCollision->drop();
}

void Game::loadCamera() {
	ISceneNodeAnimatorCollisionResponse* anim;
	//setup the keys
	SKeyMap keyMap[9];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;

	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;

	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;
	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_SPACE;

	camera=smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, keyMap, 9, true, 5.f);
	//add dynamic light
	smgr->addLightSceneNode(camera);
	camera->setPosition(vector3df(1478, 462, 886));
	anim = smgr->createCollisionResponseAnimator(
			mapSelector, camera, core::vector3df(30,50,30),
			core::vector3df(0,-10,0), core::vector3df(0,30,0));
	camera->addAnimator(anim);
	anim->drop();
}
