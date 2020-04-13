/*
 * Camera.cpp
 *
 *  Created on: Apr 3, 2020
 *      Author: Kyle Karnitz
 */

#include "Camera.h"

#include <glm/detail/type_mat4x4.hpp>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	this->projectionMatrix = glm::perspective<float>(80, 16.0/9.0, 0.1, 100);
	this->translateTo(0,0,0);
	this->rotateTo(0,0,0);
	forceUpdate();
}

Camera::~Camera() {

}

glm::mat4 Camera::getMatrix() {
	return this->matrix;
}

glm::mat4 Camera::getProjectionMatrix() {
	return this->projectionMatrix;
}

void Camera::update() {
	if (recalculateMatrix) {
		this->forceUpdate();
		recalculateMatrix = false;
	}
}

void Camera::forceUpdate() {
	glm::mat4 cam = glm::mat4();
	cam = glm::translate(cam, glm::vec3(this->x, this->y, this->z));
	cam = glm::rotate(cam, this->rx, glm::vec3(1,0,0));
	cam = glm::rotate(cam, this->ry, glm::vec3(0,1,0));
	cam = glm::rotate(cam, this->rz, glm::vec3(0,0,1));
	this->matrix = cam;
}

void Camera::resize(sf::Vector2u windowSize) {
	this->projectionMatrix = glm::perspective<float>(80, windowSize.x/windowSize.y, 0.1, 100);
}

void Camera::updateTranslate() {
	this->recalculateMatrix = true;
}

void Camera::updateRotate() {
	this->recalculateMatrix = true;
}

void Camera::translateBy(float dx, float dy, float dz) {
	this->x += dx;
	this->y += dy;
	this->z += dz;
	updateTranslate();
}

void Camera::rotateBy(float drx, float dry, float drz) {
	this->rx += drx;
	this->ry += dry;
	this->rz += drz;
	updateRotate();
}

void Camera::translateTo(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	updateTranslate();
}

void Camera::rotateTo(float rx, float ry, float rz) {
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
	updateRotate();
}

void Camera::translateNormal(float x, float y, float z) {

}

float Camera::getX() {
	return this->x;
}
float Camera::getY() {
	return this->y;
}
float Camera::getZ() {
	return this->z;
}
float Camera::getRx() {
	return this->rx;
}
float Camera::getRy() {
	return this->ry;
}
float Camera::getRz() {
	return this->rz;
}
