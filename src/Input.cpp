/*
 * Inputs.cpp
 *
 *  Created on: 28 במרס 2013
 *      Author: yuval
 */

#include "Input.h"
#include "stdio.h"
Input* Input::instance=NULL;
Input* Input::GetInstance() {
	puts("i was here");
	if(instance==NULL)
		instance=new Input();
	return instance;
}

Input::Input() {
	// TODO Auto-generated constructor stub

}

Input::~Input() {
	// TODO Auto-generated destructor stub
}

bool Input::OnEvent(const SEvent& event) {
	return false;
}
