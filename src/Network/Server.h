/*
 * Server.h
 *
 *  Created on: 1 αιεμ 2013
 *      Author: yuval
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "../GameBase.h"
#include <SFML/Network.hpp>
#include <pthread.h>
#include <vector>
using namespace sf;
struct SocketThread
{
	TcpSocket* socket;
	pthread_t thread;
};
class Server: public GameBase {
public:
	Server();
	virtual ~Server();
	static void* ListenThread(void* server);
	static void* RecvThread(void* recvThreadArgs);
protected:
	bool update();
private:
	struct RecvThreadArgs
	{
		Server* self;
		TcpSocket* socket;
	};
	void Forward(TcpSocket* sender,Packet packet);
	pthread_t listenThread;
	TcpListener listener;
	std::vector<SocketThread> clients;
	ISceneCollisionManager* collMan;
	ISceneNode* shoot(Packet packet);
	void ReSpawnNode(ISceneNode* node);
};

#endif /* SERVER_H_ */
