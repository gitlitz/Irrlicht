/*
 * Client.h
 *
 *  Created on: 7 αιεπ 2013
 *      Author: yuval
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <string>
#include "../GameBase.h"
void* ClientRecvThread(void* socket);

class Client:GameBase {
public:
	Client();
	virtual ~Client();
};

#endif /* CLIENT_H_ */
