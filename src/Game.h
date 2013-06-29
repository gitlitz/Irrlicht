/*
 * Game.h
 *
 *  Created on: 16 במרס 2013
 *      Author: yuval
 */

#ifndef GAME_H_
#define GAME_H_

#include "GameBase.h"

class Game: public GameBase {
public:
	Game();
	virtual ~Game();
protected:
	bool update();
private:
	ICameraSceneNode* camera;
	IAnimatedMeshSceneNode* npc;
	ISceneNodeAnimatorCollisionResponse* npcCollision;
	/**
	 * update the npc. called on every iteration
	 */
	void updateNpc();
	/**
	 * create the npc node
	 */
	void loadNpc();
	/**
	 * load the camera
	 */
	void loadCamera();
};

#endif /* GAME_H_ */
