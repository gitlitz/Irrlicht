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
	device = createDevice(video::EDT_OPENGL,dimension2d<u32>(640, 480), 16, false,false,true,Input::GetInstance());

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	create_mapSelector();
}

GameBase::~GameBase() {
	device->drop();
	delete Input::GetInstance();
}

void GameBase::start() {
	mapSelector->drop();
	while(device->run()&&update())
	{

		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();
		Input::GetInstance()->update();
		driver->endScene();
	}

}

void GameBase::create_mapSelector() {
	device->getFileSystem()->addFileArchive("media/map.pk3");
	IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");

	if(!q3levelmesh)
	{
		puts("failed to load map map.pk3");
		exit(1);
	}
	IMeshSceneNode* mapNode =smgr->addOctreeSceneNode(q3levelmesh->getMesh(0));
	q3levelmesh->drop();
	mapNode->setPosition(vector3d<float>(0,0,0));

	mapSelector=smgr->createOctreeTriangleSelector(mapNode->getMesh(),mapNode);

}
