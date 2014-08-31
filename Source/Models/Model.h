#pragma once

// Third-party
#include <GLM/glm.hpp>

// Namespaces
using namespace glm;

class Model
{
public:
	Model();
	virtual ~Model();

	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;

	// Accessors
	virtual glm::mat4 getWorldTransform() const;

	vec3 getPosition() const { return position; }
	vec3 getScaling() const	{ return scaling; }
	vec3 getRotationAxis() const { return rotationAxis; }
	float getRotationAngle() const { return rotationAngleInDegrees; }

	// Mutators
	void setPosition(vec3 position);
	void setScaling(vec3 scaling);
	void setRotation(vec3 axis, float angleDegrees);

protected:
	vec3 position;
	vec3 scaling;
	vec3 rotationAxis;
	float rotationAngleInDegrees;

	// Material coefficients default values
	const float ka = 0.1f;
	const float kd = 0.8f;
	const float ks = 0.9f;
	const float n = 100.0f;
};
