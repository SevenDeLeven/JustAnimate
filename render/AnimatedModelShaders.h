/*
 * AnimatedModelShaders.h
 *
 *  Created on: Apr 3, 2020
 *      Author: Kyle Karnitz
 */

#ifndef RENDER_ANIMATEDMODELSHADERS_H_
#define RENDER_ANIMATEDMODELSHADERS_H_

#include "Shaders.h"

class AnimatedModelShaders : Shaders {
private:
	//No uniforms as of right now (Should include uniforms of joint matrices later)

public:
	AnimatedModelShaders();
	virtual ~AnimatedModelShaders();

	virtual void bindAttributes();
	virtual void getUniforms();

	void projectionMatrix(glm::mat4 mat);
	void viewMatrix(glm::mat4 mat);
	void transformMatrix(glm::mat4 mat4);

	virtual void start();
	virtual void stop();

};

#endif /* RENDER_ANIMATEDMODELSHADERS_H_ */
