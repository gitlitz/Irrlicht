/*
 * Client.h
 *
 *  Created on: 7 αιεπ 2013
 *      Author: yuval
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <string>
void* ClientRecvThread(void* socket);

class Client {
public:
	Client(std::string name);
	virtual ~Client();
};

#endif /* CLIENT_H_ */
