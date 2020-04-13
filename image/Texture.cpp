/*
 * Texture.cpp
 *
 *  Created on: Mar 31, 2020
 *      Author: Kyle Karnitz
 */

#include "Texture.h"

#include <SFML/Graphics.hpp>

Texture::Texture(GLuint texId, int width, int height) {
	this->texId = texId;
	this->width = width;
	this->height = height;
}

Texture::~Texture() {

}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, texId);
}

void Texture::unbind() {

}

Texture* loadTexture(const char* name) {
	sf::Image img;
	img.loadFromFile(name);
	GLint width = img.getSize().x;
	GLint height = img.getSize().y;

	GLuint texId;
	glGenTextures(1, &(texId));
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, img.getPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	Texture* tex = new Texture(texId, width, height);
	return tex;
}
