/*
 * PlayersData.h
 *
 *  Created on: 7 αιεπ 2013
 *      Author: yuval
 */

#ifndef PLAYERSDATA_H_
#define PLAYERSDATA_H_
#include <map>
#include <irrlicht.h>
#include <string>
using namespace std;
struct Location
{
	irr::core::vector3df Position;
	irr::core::vector3df Rotation;
};
map<string,Location> playersData;
#endif /* PLAYERSDATA_H_ */
