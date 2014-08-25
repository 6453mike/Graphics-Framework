#pragma once

// Local
#include "Camera.h"

class FirstPersonCamera : public Camera
{
public:
	FirstPersonCamera(vec3 position);
	virtual ~FirstPersonCamera();

	virtual void update(float deltaTime);

	virtual mat4 getViewTransform() const;

private:
	mat4 viewMatrix;
	vec3 mLookAtPoint;
	vec3 mUpVector;
	vec3 mRightVector;
	vec3 mPosition;

	float alpha;
	float beta;
	float radius;
	float strafeSpeed;
	float mouseSensitivity;
};
