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
	void StopListening();
	void SendMsg(const char *c);
	void Forward(unsigned short senderPort,const char *msg);
	static Server& GetInstance()
	{
		static Server inst;
		return inst;
	}
private:
	Server();
	ListenThreadArgs listenArgs;
	pthread_t listen;
protected:
	Server(const Server&); // Prevent construction by copying
	Server& operator=(const Server&); // Prevent assignment
	~Server(); // Prevent unwanted destruction


};

#endif /* SERVER_H_ */
