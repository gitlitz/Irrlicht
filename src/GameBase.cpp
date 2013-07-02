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
GameBase::GameBase(E_DRIVER_TYPE driver) {
	device = createDevice(video::EDT_OPENGL,dimension2d<u32>(640, 480), 16, false,false,true,&Input::GetInstance());
	this->driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	playerMesh = smgr->getMesh("media/sydney.md2");
	playerTexture=this->driver->getTexture("media/sydney.bmp");
	create_mapSelector();
	const core::aabbox3d<f32>& box = playerMesh->getBoundingBox();
	radius = box.MaxEdge - box.getCenter();
}

GameBase::~GameBase() {
	device->drop();
}

void GameBase::start() {
	mapSelector->drop();
	while(device->run()&&update())
	{
		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();
		Input::GetInstance().update();
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

void GameBase::MovePlayer(ClientInfo info, vector3df position,float rotY) {
	IAnimatedMeshSceneNode* node;
	if(players.find(info)==players.end())
	{
		//todo:error here
		puts("new node");
		node=CreateNewPlayerNode();
		ITriangleSelector* selector=smgr->createTriangleSelector(node);
		node->setTriangleSelector(selector);
		selector->drop();
		players[info]=node;
	}
	else
		node=players[info];
	node->setPosition(position-radius);
	vector3df rot=node->getRotation();
	rot.Y=rotY;
	node->setRotation(rot);

}

void GameBase::loadSampleNode() {

	sampleNode=smgr->addAnimatedMeshSceneNode(playerMesh);
	sampleNode->setMaterialTexture( 0, playerTexture );
	sampleNode->setPosition(vector3df(1278, 462, 886));
	sampleNode->setMD2Animation(EMD2_ANIMATION_TYPE::EMAT_STAND);
	//lighting
	sampleNode->setMaterialFlag(EMF_LIGHTING, false);
	//calculate the radius of the texture
	/*const core::aabbox3d<f32>& box = sampleNode->getBoundingBox();
	core::vector3df radius = box.MaxEdge - box.getCenter();
	//add collision
	ISceneNodeAnimatorCollisionResponse* collision = smgr->createCollisionResponseAnimator(
			mapSelector, sampleNode, radius);
	sampleNode->addAnimator(collision);
	collision->drop();
	*/
}

IAnimatedMeshSceneNode* GameBase::CreateNewPlayerNode() {
	IAnimatedMeshSceneNode* node=smgr->addAnimatedMeshSceneNode(playerMesh);
	node->setMaterialTexture( 0, playerTexture );
	node->setMD2Animation(EMD2_ANIMATION_TYPE::EMAT_STAND);
	node->setMaterialFlag(EMF_LIGHTING, false);
	return node;
}
