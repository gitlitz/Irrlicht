/*
 * Main.cpp
 *
 *  Created on: 16 במרס 2013
 *      Author: yuval
 */
#include <stdio.h>
#include <SFML/Network.hpp>
#include "Network/Server.h"
#include "Network/Client.h"

void server();
void client();


int main()
{
	//Game g=Game();
	//g.start();
	//return 0;

	char who;
	puts("Do you want to be a server (s) or a client (c) ?");
	who=getchar();
	if(who=='s')
		server();
	else
		client();
	return 0;
}

void server()
{
	Server::GetInstance();
	getchar();
	getchar();
}

void client()
{
	StartClient();
}




