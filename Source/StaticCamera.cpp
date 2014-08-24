#include "StaticCamera.h"

// Third-party
#include <GLM/gtx/transform.hpp>

StaticCamera::StaticCamera(vec3 position, vec3 lookAtPosition, vec3 upVector)
	: Camera(), position(position), lookAtPosition(lookAtPosition), upVector(upVector)
{
}

StaticCamera::~StaticCamera()
{
}

void StaticCamera::update(float deltaTime)
{
}

mat4 StaticCamera::getViewMatrix() const
{
	return lookAt(position, lookAtPosition, upVector);
}