/*
 * AnimatedModel.h
 *
 *  Created on: Apr 2, 2020
 *      Author: Kyle Karnitz
 */

#ifndef ENTITY_ANIMATEDMODEL_H_
#define ENTITY_ANIMATEDMODEL_H_


#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

class AnimatedModel {
private:
	GLuint vao;
	GLuint vbo;
	GLuint uvbo;
	GLuint nvbo;
	GLuint jointVBO;
	GLuint weightVBO;



public:
	AnimatedModel(GLuint vao, GLuint vbo, GLuint uvbo, GLuint nvbo, GLuint jointVBO, GLuint weightVBO);
	virtual ~AnimatedModel();

};

#endif /* ENTITY_ANIMATEDMODEL_H_ */
