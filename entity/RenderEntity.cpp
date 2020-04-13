/*
 * RenderEntity.cpp
 *
 *  Created on: Mar 30, 2020
 *      Author: Kyle Karnitz
 */

#include "RenderEntity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../image/Texture.h"
#include "Model.h"

RenderEntity::RenderEntity(Model* model, Texture* texture) {
	this->model = model;
	this->tex = texture;
	this->set_translate(0,0,0);
	this->set_rotate(0,0,0);
	this->set_scale(0,0,0);
}

RenderEntity::~RenderEntity() {

}

void RenderEntity::bind() {
	this->model->bind();
	this->tex->bind();

}

void RenderEntity::translate(float x, float y, float z) {
	this->x += x;
	this->y += y;
	this->z += z;
}

void RenderEntity::rotate(float rx, float ry, float rz) {
	this->rx += rx;
	this->ry += ry;
	this->rz += rz;
}

void RenderEntity::scale(float sx, float sy, float sz) {
	this->sx *= sx;
	this->sy *= sy;
	this->sz *= sz;
}

void RenderEntity::set_translate(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void RenderEntity::set_rotate(float rx, float ry, float rz) {
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
}

void RenderEntity::set_scale(float sx, float sy, float sz) {
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
}
