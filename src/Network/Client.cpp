/*
 * Client.cpp
 *
 *  Created on: 18 αιεπ 2013
 *      Author: yuval
 */

#include "Client.h"
#include "Server.h"
#include "../Game.h"
void* ClientRecvThread(void* socket);
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
void StartClient()
{
	Game g;
	IpAddress server("127.0.0.1");
	//connecting to the server
	if (clientSocket.connect(server, Server::PORT) != sf::Socket::Done)
	{
		puts("connection failed");
		exit(1);
	}
	pthread_t t;
	//new thread to reciev data from the socket
	pthread_create(&t,NULL,ClientRecvThread,&clientSocket);
	//start the game
	g.start();
}
void SendPos(vector3df pos,vector3df rot)
{
	//char c[128];
	//sprintf(c,"%f,%f,%f",pos.X,pos.Y,pos.Z);
	//clientSocket.send(c,strlen(c));
	LocationPacket p;
	p.PosX=pos.X;
	p.PosY=pos.Y;
	p.PosZ=pos.Z;
	p.RotX=rot.X;
	p.RotY=rot.Y;
	p.RotZ=rot.Z;
	clientSocket.send(&p,sizeof(p));
}

void* ClientRecvThread(void* socket) {
	TcpSocket *s=(TcpSocket*)socket;
	size_t recieved;
	LocationPacket packet;
	vector3df pos;
	vector3df rot(0,0,0);
	while(true)
	{
		s->receive(&packet,sizeof(packet),recieved);
		//error
		if(recieved==0)
		{
			puts("failed to recv msg");
			return 0;
		}

		//sscanf(in,"%f,%f,%f",&pos.X,&pos.Y,&pos.Z);
		pos.X=packet.PosX;
		pos.Y=packet.PosY;
		pos.Z=packet.PosZ;
		GameBase::seeker->setPosition(pos);
		rot.X=packet.RotX;
		rot.Y=packet.RotY;
		rot.Z=packet.RotZ;
		GameBase::seeker->setRotation(rot);
	}
	return 0;
}
