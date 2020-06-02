/*
 * JointTransform.h
 *
 *  Created on: May 10, 2020
 *      Author: Kyle Karnitz
 */

#ifndef RENDER_ANIMATION_JOINTTRANSFORM_H_
#define RENDER_ANIMATION_JOINTTRANSFORM_H_

#include <glm/glm.hpp>
#include "../../util/Quaternion.h"

class JointTransform {

private:

	glm::vec3 position;
	Quaternion rotation;

public:

	JointTransform(glm::vec3 position, Quaternion rotation);

	glm::mat4 getLocalTransform();



};

JointTransform interpolateTransforms(JointTransform t1, JointTransform t2, float factor);

#endif /* RENDER_ANIMATION_JOINTTRANSFORM_H_ */
