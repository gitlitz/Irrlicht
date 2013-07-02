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
	collMan=smgr->getSceneCollisionManager();
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
	ISceneNode* hitNode;
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
		case Command::score:
			hitNode= self->shoot(packet);
			if(hitNode)
			{
				packet.clear();
				packet<<Command::score;
				socket->send(packet);
			}
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
ISceneNode* Server::shoot(Packet packet)
{
	vector3df start;
	packet>>start.X;
	packet>>start.Y;
	packet>>start.Z;
	vector3df end;
	packet>>end.X;
	packet>>end.Y;
	packet>>end.Z;

	core::line3d<f32> ray;
	ray.start = start;
	ray.end = end;
	core::vector3df intersection;
	core::triangle3df hitTriangle;

	ISceneNode * selectedSceneNode=collMan->getSceneNodeAndCollisionPointFromRay(ray,intersection,hitTriangle);
	return (selectedSceneNode);
}
