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
	//port to bind for the server
	static const unsigned short PORT = 5000;
	//dont accept more clients
	void StopListening();
	/**
	 * send a message to all the clients
	 * @param c msg to be sent
	 */
	void SendMsg(const char *c);
	/**
	 * forward a message from a port to all
	 * the other clients
	 * @param senderPort the sender's port
	 * @param msg msg to send to all the other clients
	 */
	void Forward(unsigned short senderPort,const char *msg);
	//singleton
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
