/*
 * Client.cpp
 *
 *  Created on: 7 αιεπ 2013
 *      Author: yuval
 */

#include "Client.h"
#include <SFML/Network.hpp>
#include <stdio.h>
#include <pthread.h>
#include "Server.h"
#include <iostream>
using namespace sf;
void* ClientRecvThread(void* socket)
{
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
	}
	return 0;
}


Client::Client(std::string name) {
	IpAddress server("127.0.0.1");

	// Create a socket for communicating with the server
	TcpSocket *socket;

	// Connect to the server
	if (socket->connect(server, Server::PORT) != sf::Socket::Done)
	{
		puts("connection failed");
		return;

	}
	std::cout << "Connected to server " << server << std::endl;

	// Receive a message from the server
	// Send an answer to the server
	pthread_t t;
	pthread_create(&t,NULL,ClientRecvThread,&socket);
	char c[128];
	fgets(c,sizeof(c),stdin);
	while (strcmp(c,"q\n")!=0)
	{
		fgets(c,sizeof(c),stdin);
		if (socket->send(&c, sizeof(c)) != sf::Socket::Done)
		{
			puts("failed to send msg");
			return;
		}
	}
}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

