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
	initCamera();
}

Client::~Client() {
	camera->removeAnimators();
}

bool Client::update() {
	Packet packet;
	packet<<Command::move;
	packet<<camera->getPosition().X;
	packet<<camera->getPosition().Y;
	packet<<camera->getPosition().Z;
	packet<<camera->getRotation().Y;
	socket.send(packet);
	packet.clear();
	if(Input::GetInstance().getKeyState(EKEY_CODE::KEY_KEY_E)==PRESSED)
	{
		shoot();
	}
	if(Input::GetInstance().getKeyState(EKEY_CODE::KEY_KEY_Q)==PRESSED)
		camera->setInputReceiverEnabled(!camera->isInputReceiverEnabled());
	stringw tmp(L"score:");
	tmp+=score;
	device->setWindowCaption(tmp.c_str());

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
		case Command::score:
			puts("score");
			self->score++;
			packet.clear();
			break;
		case Command::spawn:
			puts("spawned");
			self->camera->setPosition(self->SPAWN_POINT);
			break;
		default:
			puts("bad package");
			break;
		}
	}
	return 0;
}

void Client::initCamera() {
	ISceneNodeAnimatorCollisionResponse* anim;
	//setup the keys
	SKeyMap keyMap[9];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;

	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;

	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;
	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_SPACE;

	camera=smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, keyMap, 9, true, 5.f);
	//add dynamic light
	smgr->addLightSceneNode(camera);
	camera->setPosition(SPAWN_POINT);
	anim = smgr->createCollisionResponseAnimator(
			mapSelector, camera,2*radius);
	camera->addAnimator(anim);
	anim->drop();

}

void Client::shoot() {
	Packet packet;
	packet<<Command::score;
	vector3df start=camera->getPosition();
	start+=(camera->getTarget() - start).normalize()*23.0f;
	packet<<start.X;
	packet<<start.Y;
	packet<<start.Z;
	vector3df end=start + (camera->getTarget() - start).normalize() * 1000.0f;
	packet<<end.X;
	packet<<end.Y;
	packet<<end.Z;
	socket.send(packet);
}
