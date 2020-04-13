/*
 * Shaders.h
 *
 *  Created on: Apr 3, 2020
 *      Author: Kyle Karnitz
 */

#ifndef RENDER_SHADERS_H_
#define RENDER_SHADERS_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <glm/glm.hpp>

class Shaders {
protected:
	GLuint program;
public:
	Shaders(const char* vertFile, const char* fragFile);
	virtual ~Shaders();

	GLuint getUniform(const char* name);

	virtual void bindAttributes();
	virtual void getUniforms();

	virtual void start();
	virtual void stop();
	void clean();

	GLint getUniformLocation(const char* name);

	void uniformMat4(GLint location, glm::mat4 matrix);
};

#endif /* RENDER_SHADERS_H_ */
