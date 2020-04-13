/*
 * RenderEntity.h
 *
 *  Created on: Mar 30, 2020
 *      Author: Kyle Karnitz
 */

#ifndef ENTITY_RENDERENTITY_H_
#define ENTITY_RENDERENTITY_H_

#include <glm/detail/type_mat.hpp>

class Texture;

class Model;

class RenderEntity {
private:
	bool recalculateMatrix;

	float x, y, z;
	float rx, ry, rz;
	float sx, sy, sz;

	glm::mat4* transformMatrix;

	Model* model;
	Texture* tex;

public:
	RenderEntity(Model* model, Texture* texture);
	virtual ~RenderEntity();

	void bind();

	void translate(float x, float y, float z);
	void rotate(float rx, float ry, float rz);
	void scale(float sx, float sy, float sz);

	void set_translate(float x, float y, float z);
	void set_rotate(float rx, float ry, float rz);
	void set_scale(float sx, float sy, float sz);

};

#endif /* ENTITY_RENDERENTITY_H_ */
