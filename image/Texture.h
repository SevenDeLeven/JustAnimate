/*
 * Texture.h
 *
 *  Created on: Mar 31, 2020
 *      Author: Kyle Karnitz
 */

#ifndef IMAGE_TEXTURE_H_
#define IMAGE_TEXTURE_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

class Texture {
private:
	GLuint texId;
	int width, height;

public:
	Texture(GLuint texId, int width, int height);
	virtual ~Texture();

	void bind();
	void unbind();

};

Texture* loadTexture(const char* filename);

#endif /* IMAGE_TEXTURE_H_ */
