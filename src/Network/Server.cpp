/*
 * Server.cpp
 *
 *  Created on: 1 αιεμ 2013
 *      Author: yuval
 */

#include "Server.h"
#include <pthread.h>
#include "../def.h"
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

Server::Server():GameBase(EDT_NULL) {
	if(listener.listen(PORT) != sf::Socket::Done)
	{
		puts("cant listen to port");
		exit(1);
	}
	pthread_create(&listenThread,NULL,Server::ListenThread,this);
}

Server::~Server() {
	for(auto i:clients)
	{
		pthread_cancel(i.thread);
		delete i.socket;
	}
}

void* Server::ListenThread(void* server) {
	Server* self=(Server*)server;
	while(true)
	{
		TcpSocket* socket=new TcpSocket();
		if(self->listener.accept(*socket) != Socket::Done)
		{
			puts("failed to accept client");
			return 0;
		}
		puts("client connected");
		RecvThreadArgs args;
		args.self=self;
		args.socket=socket;
		SocketThread client;
		client.socket=socket;
		pthread_create(&client.thread,NULL,Server::RecvThread,&args);
		self->clients.push_back(client);
	}
	return 0;
}

void* Server::RecvThread(void* recvThreadArgs) {
	RecvThreadArgs* args=(RecvThreadArgs*)recvThreadArgs;
	Server* self=args->self;
	TcpSocket* socket=args->socket;
	Packet packet;
	int command;
	float rotY;
	vector3df pos;
	ClientInfo info;
	info.ip=socket->getRemoteAddress();
	info.port=socket->getRemotePort();
	Uint32 ip=info.ip.toInteger();
	while(true)
	{
		if(socket->receive(packet)!=Socket::Done)
		{
			puts("connection failed");
			exit(1);
		}
		packet>>command;
		switch(command)
		{
		case Command::move:
			packet>>pos.X;
			packet>>pos.Y;
			packet>>pos.Z;
			packet>>rotY;
			self->MovePlayer(info,pos,rotY);
			packet.clear();
			packet<<Command::move;
			packet<<ip;
			packet<<info.port;
			packet<<pos.X;
			packet<<pos.Y;
			packet<<pos.Z;
			packet<<rotY;
			self->Forward(socket,packet);
			packet.clear();
			break;
		default:
			puts("bad package");
		}
	}
	return 0;
}

bool Server::update() {
	return true;
}

void Server::Forward(TcpSocket* sender, Packet packet) {
	for(auto i:clients)
		if(i.socket!=sender)
			i.socket->send(packet);
}
