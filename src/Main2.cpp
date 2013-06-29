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
	char who;
	puts("Do you want to be a server (s) or a client (c) ?");
	who=getchar();
	if(who=='s')
		server();
	else
		client();
	return 0;
}
/*
 * run a server program
 */
void server()
{
	Server::GetInstance();
	//block
	getchar();
	getchar();
}
/*
 * run a client program
 */
void client()
{
	StartClient();
}

