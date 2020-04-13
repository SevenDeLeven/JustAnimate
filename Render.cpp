/*
 * Render.cpp
 *
 *  Created on: Mar 30, 2020
 *      Author: Kyle Karnitz
 */

#include "Render.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/functions.hpp>

#include <iostream>

Model* tposeModel;

glm::mat4 transform;

Render::Render() {

}

Render::~Render() {
}

void Render::moveCameraGlobal(float x, float y, float z) {
	this->camera->translateBy(x,y,z);
}

void Render::moveCameraNormal(float x, float y, float z) {
	this->camera->translateNormal(x,y,z);
}

void Render::rotateCamera(float rx, float ry, float rz) {
	this->camera->rotateBy(rx,ry,rz);
}

void Render::init() {
	std::cout << "Loading Models" << std::endl;
	tposeModel = loadCollada("models/tpose2.dae");
	std::cout << "Loading Shaders" << std::endl;
	animShaders = new AnimatedModelShaders();

	camera = new Camera();
}

void Render::draw() {
	camera->update();

	animShaders->start();

	tposeModel->bind();

	animShaders->projectionMatrix(camera->getProjectionMatrix());
	animShaders->viewMatrix(camera->getMatrix());
	animShaders->transformMatrix(transform);

	glDrawArrays(GL_TRIANGLES, 0, tposeModel->getVertexCount());

	tposeModel->unbind();

	animShaders->stop();
}

void Render::deinit() {
	delete this->animShaders;
	delete this->camera;
}

void Render::resize(sf::Vector2u size) {
	glViewport(0, 0, size.x, size.y);
	camera->resize(size);
}
