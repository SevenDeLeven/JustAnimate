/*
 * Joint.h
 *
 *  Created on: Apr 2, 2020
 *      Author: Kyle Karnitz
 */

#ifndef ENTITY_ANIMATION_JOINT_H_
#define ENTITY_ANIMATION_JOINT_H_

#include <glm/glm.hpp>
#include <vector>
#include <string>

class Joint {
private:
	int index;
	std::string name;

	Joint* parent;
	std::vector<Joint*> children;

	glm::mat4 invBindTransform;
	glm::mat4 localBindTransform;

public:
	Joint(int index, std::string name);

	void setBindTransform(glm::mat4 in);
	void setInverseBindTransform(glm::mat4 ibt);
	void updateTransforms();

};

#endif /* ENTITY_ANIMATION_JOINT_H_ */
