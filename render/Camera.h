/*
 * Camera.h
 *
 *  Created on: Apr 3, 2020
 *      Author: Kyle Karnitz
 */

#ifndef RENDER_CAMERA_H_
#define RENDER_CAMERA_H_

#include <glm/glm.hpp>
#include <SFML/System/Vector2.hpp>

class Camera {
private:
	bool recalculateMatrix = true;

	glm::mat4 matrix;
	glm::mat4 projectionMatrix;

	float x, y, z;
	float rx, ry, rz;

	void updateTranslate();
	void updateRotate();

public:
	Camera();
	virtual ~Camera();

	void update();
	void forceUpdate();
	void resize(sf::Vector2u windowSize);

	glm::mat4 getMatrix();
	glm::mat4 getProjectionMatrix();

	void translateBy(float dx, float dy, float dz);
	void rotateBy(float drx, float dry, float drz);

	void translateTo(float x, float y, float z);
	void translateNormal(float x, float y, float z);
	void rotateTo(float rx, float ry, float rz);

	float getX();
	float getY();
	float getZ();
	float getRx();
	float getRy();
	float getRz();
};

#endif /* RENDER_CAMERA_H_ */
