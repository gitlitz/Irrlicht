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
	ISceneNode* cube;
	ICameraSceneNode* camera;
	ISceneNodeAnimatorCollisionResponse* anim;
};

#endif /* GAME_H_ */
