/*
 * AnimatedModelShaders.cpp
 *
 *  Created on: Apr 3, 2020
 *      Author: Kyle Karnitz
 */

#include "./AnimatedModelShaders.h"

AnimatedModelShaders::AnimatedModelShaders() : Shaders("shaders/animatedmodel.vert", "shaders/animatedmodel.frag") {

}

AnimatedModelShaders::~AnimatedModelShaders() {

}

void AnimatedModelShaders::bindAttributes() {
	glBindAttribLocation(program, 0, "pos");
	glBindAttribLocation(program, 1, "uv");
	glBindAttribLocation(program, 2, "normal");
}

void AnimatedModelShaders::getUniforms() {
	getUniformLocation("projectionMatrix");
	getUniformLocation("viewMatrix");
}

void AnimatedModelShaders::projectionMatrix(glm::mat4 mat) {
	Shaders::uniformMat4(getUniformLocation("projectionMatrix"), mat);
}
void AnimatedModelShaders::viewMatrix(glm::mat4 mat) {
	Shaders::uniformMat4(getUniformLocation("viewMatrix"), mat);
}
void AnimatedModelShaders::transformMatrix(glm::mat4 mat) {
	Shaders::uniformMat4(getUniformLocation("transformMatrix"), mat);
}

void AnimatedModelShaders::start() {
	this->Shaders::start();
}

void AnimatedModelShaders::stop() {
	this->Shaders::stop();
}
