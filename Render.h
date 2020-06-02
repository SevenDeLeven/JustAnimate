/*
 * Render.h
 *
 *  Created on: Mar 30, 2020
 *      Author: Kyle Karnitz
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <SFML/Window.hpp>

#include "entity/Model.h"
#include "render/Camera.h"
#include "render/shaders/AnimatedModelShaders.h"

class Render {
private:
	Camera* camera;
	AnimatedModelShaders* animShaders;


public:
	Render();
	virtual ~Render();

	void init();
	void draw();
	void deinit();

	void moveCameraGlobal(float x, float y, float z);
	void moveCameraNormal(float x, float y, float z);
	void rotateCamera(float rx, float ry, float rz);

	void resize(sf::Vector2u size);

};

#endif /* RENDER_H_ */
