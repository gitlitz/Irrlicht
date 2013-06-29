/*
 * Server.cpp
 *
 *  Created on: 27 במאי 2013
 *      Author: yuval
 */

#include "Server.h"
#include <SFML/Network.hpp>
#include <stdio.h>
#include <pthread.h>
//mutex for the clients vector
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

Server::Server() {
	//bind the server
	if (listenArgs.listener.listen(PORT) != sf::Socket::Done)
	{
		printf("failed listening to port:%d \n",PORT);
		exit(-1);
	}
	puts("listening");
	listenArgs.isListening=true;
	//start listen thread
	pthread_create(&listen,NULL,ListenThread,&listenArgs);
}

Server::~Server() {
	StopListening();
	for(auto i:listenArgs.clients)
	{
		pthread_cancel(i.recvThread);
		delete i.socket;
	}
}

void* ListenThread(void* listenThreadArgs) {
	ListenThreadArgs* args=(ListenThreadArgs*)listenThreadArgs;
	while(args->isListening)
	{
		TcpSocket* socket=new TcpSocket();
		//accept a new socket
		if(args->listener.accept(*socket) != Socket::Done)
		{
			puts("failed to accept client");
			return 0;
		}
		//dont allow other thread to use the vector
		pthread_mutex_lock( &mutex );
		printf("connected %d\n",socket->getRemotePort());
		ClientInfo client;
		pthread_create(&client.recvThread,NULL,RecvThread,socket);
		client.socket=socket;
		args->clients.push_back(client);
		pthread_mutex_unlock( &mutex );

	}
	return 0;
}

void* RecvThread(void* socket) {
	TcpSocket* s=(TcpSocket*)socket;
	char in[128];
	std::size_t received;
	while(true)
	{
		if (s->receive(in, sizeof(in), received) != sf::Socket::Done)
		{
			puts("failed to recv msg");
			exit(0);
		}
		//end of a string end with \0
		in[received]='\0';
		//printf("recv from port %d:%s\n",s->getRemotePort(),in);

		Server::GetInstance().Forward(s->getRemotePort(),in);
	}
	return 0;
}

void Server::StopListening() {

	if(listenArgs.isListening==true)
	{
		listenArgs.isListening=false;
		//cant stop the thread if adding a new client to the clients vector
		pthread_mutex_lock( &mutex );

		pthread_cancel(listen);
		pthread_mutex_unlock( &mutex );
	}
}
/*
 *
 */
void Server::SendMsg(const char *c) {
	for(auto i:listenArgs.clients)
		i.socket->send(c,strlen(c));
}

void Server::Forward(unsigned short senderPort, const char* msg) {
	for(auto i:listenArgs.clients)
		if(i.socket->getRemotePort()!=senderPort)
			i.socket->send(msg,strlen(msg));
}
