#pragma once

// Third-party
#include <GLM/glm.hpp>

// Namespaces
using namespace glm;

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void update(float deltaTime) = 0;

	virtual mat4 getViewMatrix() const = 0;
	virtual mat4 getProjectionMatrix() const;
	mat4 getViewProjectionMatrix() const;
private:

};
