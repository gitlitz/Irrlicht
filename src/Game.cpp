/*
 * Game.cpp
 *
 *  Created on: 16 במרס 2013
 *      Author: yuval
 */

#include "Game.h"

Game::Game() {
	guienv->addStaticText(L"hello world",rect<signed int>(0,0,50,50),true);
}

Game::~Game() {
	// TODO Auto-generated destructor stub

}

void Game::update() {
	int fps = driver->getFPS();
	stringw tmp(L"");
	tmp += driver->getName();
	tmp += L"] fps: ";
	tmp += fps;
	device->setWindowCaption(tmp.c_str());
}
