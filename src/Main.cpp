/*
 * Main.cpp
 *
 *  Created on: 16 במרס 2013
 *      Author: yuval
 */
#include <stdio.h>
#include "Game.h"
#include <SFML/Network.hpp>
#include "Network/Server.h"
void server();
void client();
int main()
{

	char who;
	puts("Do you want to be a server (s) or a client (c) ?");
	who=getchar();
	if(who=='s')
		server();
	else
		client();
	return 0;
	Game g=Game();
	g.start();
	return 0;

}

void server()
{
	Server::GetInstance();
}

void client()
{

}
