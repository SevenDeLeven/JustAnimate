/*
 * Joint.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: Kyle Karnitz
 */

#include "Joint.h"

Joint::Joint(int id, const char* name) {
	this->index = id;
	this->name = name;
	this->parent = nullptr;
}

void Joint::setBindTransform(glm::mat4 bt) {
	this->localBindTransform = bt;
}

void Joint::setInverseBindTransform(glm::mat4 ibt) {
	this->invBindTransform = ibt;
}

