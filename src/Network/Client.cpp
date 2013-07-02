/*
 * Client.cpp
 *
 *  Created on: 18 αιεπ 2013
 *      Author: yuval
 */

#include "Client.h"
#include "../def.h"
#include "../Game.h"
#include <iostream>
#include <string>

sf::TcpSocket clientSocket;
struct LocationPacket
{
	float PosX;
	float PosY;
	float PosZ;

	float RotX;
	float RotY;
	float RotZ;
};

Client::Client() {
	IpAddress server("127.0.0.1");
	//connecting to the server
	if (socket.connect(server, PORT) != sf::Socket::Done)
	{
		puts("connection failed");
		exit(1);
	}
	//new thread to reciev data from the socket
	pthread_create(&recvThread,NULL,Client::RecvThread,this);
	camera=smgr->addCameraSceneNodeFPS();
}

Client::~Client() {
}

bool Client::update() {
	Packet packet;
	packet<<Command::move;
	packet<<camera->getPosition().X;
	packet<<camera->getPosition().Y;
	packet<<camera->getPosition().Z;
	packet<<camera->getRotation().Y;
	socket.send(packet);
	if(Input::GetInstance().getKeyState(EKEY_CODE::KEY_KEY_Q)==PRESSED)
		camera->setInputReceiverEnabled(!camera->isInputReceiverEnabled());
	return true;
}

void* Client::RecvThread(void* client) {
	Client* self=(Client*)client;
	Packet packet;
	ClientInfo info;
	float rotY;
	vector3df pos;
	int command;
	Uint32 ip;
	while(true)
	{
		//error
		if(self->socket.receive(packet)!=Socket::Done)
		{
			puts("connection failed");
			return 0;
		}
		packet>>command;
		switch (command) {
		case Command::move:
			packet>>ip;
			info.ip=IpAddress(ip);
			packet>>info.port;
			packet>>pos.X;
			packet>>pos.Y;
			packet>>pos.Z;
			packet>>rotY;
			self->MovePlayer(info,pos,rotY);
			break;
		default:
			puts("bad package");
			break;
		}
	}
	return 0;
}
