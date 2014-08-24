#include "Camera.h"

// Third-party
#include <GLM/gtx/transform.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}

mat4 Camera::getViewProjectionMatrix() const
{
	return getViewMatrix() * getProjectionMatrix();
}

mat4 Camera::getProjectionMatrix() const
{
	return perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}