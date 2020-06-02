/*
 * KeyFrame.h
 *
 *  Created on: May 10, 2020
 *      Author: Kyle Karnitz
 */

#ifndef RENDER_ANIMATION_KEYFRAME_H_
#define RENDER_ANIMATION_KEYFRAME_H_

#include <map>
#include "JointTransform.h"

class KeyFrame {

private:

	const float timestamp;
	std::map<const char*, JointTransform> pose;

public:

	KeyFrame(float timestamp, std::map<const char*, JointTransform> pose);

	long getTimestamp();

	std::map<const char*, JointTransform> getPose();

};

#endif /* RENDER_ANIMATION_KEYFRAME_H_ */
