/*
 * Client.h
 *
 *  Created on: 18 αιεπ 2013
 *      Author: yuval
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <stdio.h>
#include <SFML/Network.hpp>
#include <pthread.h>
#include "../GameBase.h"
#include <map>
using namespace std;
using namespace sf;
using namespace core;
//start a client program
class Client:public GameBase
{
public:
	Client();
	~Client();
	TcpSocket socket;
protected:
	bool update();
private:
	pthread_t recvThread;
	static void* RecvThread(void* client);
	ICameraSceneNode* camera;
	int score=0;
	void initCamera();
	void shoot();
	const vector3df SPAWN_POINT=vector3df(1478, 462, 886);
};
#endif /* CLIENT_H_ */
