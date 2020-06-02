/*
 * Quaternion.h
 *
 *  Created on: May 4, 2020
 *      Author: Kyle Karnitz
 */

#ifndef UTIL_QUATERNION_H_
#define UTIL_QUATERNION_H_

#include <glm/glm.hpp>

class Quaternion {
private:
	float x, y, z, w;

public:
	Quaternion(float x, float y, float z, float w);
	Quaternion(glm::mat4 mat);

	void normalize();
	glm::mat4 toRotationMatrix();

	static Quaternion interpolate(Quaternion a, Quaternion b, float blend);


};

#endif /* UTIL_QUATERNION_H_ */
