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
#include <SFML/Network.hpp>
#include <iostream>
#include <map>
#include <string>
using namespace irr;

using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace core;
enum Command
{
	move,
	score
};

struct ClientInfo
{
	short port;
	sf::IpAddress ip;
	 bool operator<( const ClientInfo & n ) const {
		 if(this->ip==n.ip)
			 return this->port>n.port;
		 return this->ip>n.ip;
	 }
};
struct MovePacket
{
	ClientInfo info;
	vector3df position;
	float rotationY;
};
struct Coordinate
{
	core::vector3df position;
	float rotationY;
};
class GameBase {
public:
	GameBase(E_DRIVER_TYPE driver=EDT_OPENGL);
	virtual ~GameBase();
	void start();
	static IrrlichtDevice *device;

	static IVideoDriver* driver;
	static ISceneManager* smgr;
	static IGUIEnvironment* guienv;

protected:
	/**
	 * called before every iteration fo the game
	 * @return should continue to run (not exit)
	 */
	virtual bool update()=0;
	//can be used only in the constructor
	ITriangleSelector *mapSelector;
	IAnimatedMeshSceneNode* sampleNode;
	void MovePlayer(ClientInfo info,core::vector3df position,float rotY);
	IAnimatedMeshSceneNode* CreateNewPlayerNode();
	vector3df radius;
private:
	//init the selector for the map
	void create_mapSelector();
	void loadSampleNode();

	std::map<ClientInfo,IAnimatedMeshSceneNode*> players;

	IAnimatedMesh* playerMesh;
	ITexture* playerTexture;

};

#endif /* GAMEBASE_H_ */
