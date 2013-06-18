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
void StartClient()
{
	Game g;
	IpAddress server("127.0.0.1");
	if (clientSocket.connect(server, Server::PORT) != sf::Socket::Done)
	{
		puts("connection failed");
		return;
	}
	pthread_t t;
	pthread_create(&t,NULL,ClientRecvThread,&clientSocket);
	g.start();
}
void SendPos(vector3df pos)
{
	char c[128];
	sprintf(c,"%f,%f,%f",pos.X,pos.Y,pos.Z);
	clientSocket.send(c,strlen(c));
}

void* ClientRecvThread(void* socket) {
	TcpSocket *s=(TcpSocket*)socket;
	char in[128];
	size_t recieved;
	while(true)
	{
		s->receive(in,sizeof(in),recieved);
		if(recieved==0)
		{
			puts("failed to recv msg");
			return 0;
		}
		in[recieved]='\0';
		puts(in);
		vector3df pos;
		sscanf(in,"%f,%f,%f",&pos.X,&pos.Y,&pos.Z);
		GameBase::seeker->setPosition(pos);
	}
	return 0;
}
