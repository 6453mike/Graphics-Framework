#pragma once

// Local
#include "Camera.h"

class StaticCamera : public Camera
{
public:
	StaticCamera(vec3 position, vec3 lookAtPosition, vec3 upVector);
	virtual ~StaticCamera();

	virtual void update(float deltaTime);

	virtual mat4 getViewTransform() const;

private:
	vec3 position;
	vec3 lookAtPosition;
	vec3 upVector;
};
