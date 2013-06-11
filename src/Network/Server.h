/*
 * Server.h
 *
 *  Created on: 27 במאי 2013
 *      Author: yuval
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <pthread.h>
#include <SFML/Network.hpp>
#include <map>
using namespace std;
using namespace sf;

struct ClientInfo{
	TcpSocket* socket;
	pthread_t recvThread;
};
struct ListenThreadArgs{
	TcpListener listener;
	bool isListening;
	vector<ClientInfo> clients;
};
void *ListenThread(void* listenThreadArgs);
void *RecvThread(void* socket);

class Server {
public:
	static const unsigned short PORT = 5000;
	virtual ~Server();
	void StopListening();
	void SendMsg(const char *c);
	static Server* GetInstance();
private:
	Server();
	static Server* instance;
	ListenThreadArgs listenArgs;
	pthread_t listen;

};

#endif /* SERVER_H_ */
