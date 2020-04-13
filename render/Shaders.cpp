/*
 * Shaders.cpp
 *
 *  Created on: Apr 3, 2020
 *      Author: Kyle Karnitz
 */

#include "Shaders.h"

#include <fstream>
#include <iostream>
#include <string>
#include <memory>

int loadShader(const char* filename, GLuint shaderType) {
	std::string out;
	std::ifstream f(filename);

	std::string line = "";
	while (!f.eof()) {
		std::getline(f, line);
		out.append(line + "\n");
	}

	f.close();

	const char* buffer = out.c_str();

	GLuint shaderId;
	shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &buffer, NULL);
	glCompileShader(shaderId);
	GLint param;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &param);
	if (param == GL_FALSE) {
		std::cout << "could not load shader " << filename << std::endl;
		char out[500];
		GLsizei len;
		glGetShaderInfoLog(shaderId, 500, &len, out);
		std::cerr << out << std::endl;
	}
	return shaderId;
}

Shaders::Shaders(const char* vertFile, const char* fragFile) {
	this->program = glCreateProgram();
	GLuint vertShader = loadShader(vertFile, GL_VERTEX_SHADER);
	GLuint fragShader = loadShader(fragFile, GL_FRAGMENT_SHADER);
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	this->bindAttributes();
	glLinkProgram(program);
	glDetachShader(program, vertShader);
	glDetachShader(program, fragShader);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shaders::~Shaders() {

}

void Shaders::bindAttributes() {

}

void Shaders::getUniforms() {
	glValidateProgram(program);
}

void Shaders::start() {
	glUseProgram(program);
}

void Shaders::stop() {
	glUseProgram(0);
}

void Shaders::clean() {
	glDeleteProgram(program);
}

GLint Shaders::getUniformLocation(const char* name) {
	return glGetUniformLocation(this->program, name);
}

void Shaders::uniformMat4(GLint location, glm::mat4 matrix) {

	glUniformMatrix4fv(location, 1, false, &matrix[0][0]);

}
