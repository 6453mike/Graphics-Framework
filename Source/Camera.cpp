#include "Camera.h"

// Third-party
#include <GLM/gtx/transform.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}

mat4 Camera::getViewProjectionTransform() const
{
	return getViewTransform() * getProjectionTransform();
}

mat4 Camera::getProjectionTransform() const
{
	return perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
}