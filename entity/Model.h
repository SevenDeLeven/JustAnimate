/*
 * Model.h
 *
 *  Created on: Mar 30, 2020
 *      Author: Kyle Karnitz
 */

#ifndef ENTITY_MODEL_H_
#define ENTITY_MODEL_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <glm/glm.hpp>

class Model {
private:

	int vertexCount;
	GLuint vao;
	GLuint vbo;
	GLuint uvbo;
	GLuint nvbo;

public:
	Model(int vertexCount, GLuint vao, GLuint vbo, GLuint uvbo, GLuint nvbo);
	virtual ~Model();

	void bind();
	void unbind();

	int getVertexCount();

};

Model* loadOBJ(const char* filename);
Model* loadCollada(const char* filename);

#endif /* ENTITY_MODEL_H_ */
