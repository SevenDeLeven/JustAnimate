/*
 * Quaternion.cpp
 *
 *  Created on: May 4, 2020
 *      Author: Kyle Karnitz
 */

#include "Quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w)  {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::Quaternion(glm::mat4 matrix) {
	float diagonal = matrix[0][0] + matrix[1][1] + matrix[2][2];
	if (diagonal > 0) {
		float w4 = (float) (sqrt(diagonal + 1) * 2);
		w = w4 / 4;
		x = (matrix[2][1] - matrix[1][2]) / w4;
		y = (matrix[0][2] - matrix[2][0]) / w4;
		z = (matrix[1][0] - matrix[0][1]) / w4;
	} else if ((matrix[0][0] > matrix[1][1]) && (matrix[0][0] > matrix[2][2])) {
		float x4 = (float) (sqrt(1 + matrix[0][0] - matrix[1][1] - matrix[2][2]) * 2);
		w = (matrix[2][1] - matrix[1][2]) / x4;
		x = x4 / 4;
		y = (matrix[0][1] + matrix[1][0]) / x4;
		z = (matrix[0][2] + matrix[2][0]) / x4;
	} else if (matrix[1][1] > matrix[2][2]) {
		float y4 = (float) (sqrt(1 + matrix[1][1] - matrix[0][0] - matrix[2][2]) * 2);
		w = (matrix[0][2] - matrix[2][0]) / y4;
		x = (matrix[0][1] + matrix[1][0]) / y4;
		y = y4 / 4;
		z = (matrix[1][2] + matrix[2][1]) / y4;
	} else {
		float z4 = (float) (sqrt(1 + matrix[2][2] - matrix[0][0] - matrix[1][1]) * 2);
		w = (matrix[1][0] - matrix[0][1]) / z4;
		x = (matrix[0][2] + matrix[2][0]) / z4;
		y = (matrix[1][2] + matrix[2][1]) / z4;
		z = z4 / 4;
	}
}

glm::mat4 Quaternion::toRotationMatrix() {
	glm::mat4 matrix;
	const float xy = x * y;
	const float xz = x * z;
	const float xw = x * w;
	const float yz = y * z;
	const float yw = y * w;
	const float zw = z * w;
	const float xSquared = x * x;
	const float ySquared = y * y;
	const float zSquared = z * z;
	matrix[0][0] = 1 - 2 * (ySquared + zSquared);
	matrix[0][1] = 2 * (xy - zw);
	matrix[0][2] = 2 * (xz + yw);
	matrix[0][3] = 0;
	matrix[1][0] = 2 * (xy + zw);
	matrix[1][1] = 1 - 2 * (xSquared + zSquared);
	matrix[1][2] = 2 * (yz - xw);
	matrix[1][3] = 0;
	matrix[2][0] = 2 * (xz - yw);
	matrix[2][1] = 2 * (yz + xw);
	matrix[2][2] = 1 - 2 * (xSquared + ySquared);
	matrix[2][3] = 0;
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
	return matrix;
}

Quaternion Quaternion::interpolate(Quaternion a, Quaternion b, float factor) {
	Quaternion result(0,0,0,1);
	float dot = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
	float blendI = 1 - factor;
	if (dot < 0) {
		result.w = blendI * a.w + factor * -b.w;
		result.x = blendI * a.x + factor * -b.x;
		result.y = blendI * a.y + factor * -b.y;
		result.z = blendI * a.z + factor * -b.z;
	} else {
		result.w = blendI * a.w + factor * b.w;
		result.x = blendI * a.x + factor * b.x;
		result.y = blendI * a.y + factor * b.y;
		result.z = blendI * a.z + factor * b.z;
	}
	result.normalize();
	return result;
}
