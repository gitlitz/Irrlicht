/*
 * Client.h
 *
 *  Created on: 18 αιεπ 2013
 *      Author: yuval
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <stdio.h>
#include <SFML/Network.hpp>
#include <pthread.h>
#include "../GameBase.h"
#include <map>
using namespace std;
using namespace sf;
//start a client program
void StartClient();
/**
 * send pos to the server
 * @param pos pos to be sent
 */
void SendPos(vector3df pos,vector3df rot);
#endif /* CLIENT_H_ */
