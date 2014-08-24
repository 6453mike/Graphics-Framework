#include "Model.h"

// Third-party
#include <glm/gtc/matrix_transform.hpp>

Model::Model() : position(0.0f, 0.0f, 0.0f), scaling(1.0f, 1.0f, 1.0f), rotationAxis(0.0f, 1.0f, 0.0f), rotationAngleInDegrees(0.0f)
{
}

Model::~Model()
{
}

void Model::update(float dt)
{
}

void Model::draw()
{
}

mat4 Model::getWorldTransform() const
{
	mat4 worldTransform(1.0f);

	worldTransform = translate(worldTransform, position);
	worldTransform = rotate(worldTransform, rotationAngleInDegrees, rotationAxis);
	worldTransform = scale(worldTransform, scaling);

	return worldTransform;
}

void Model::setPosition(vec3 position)
{
	this->position = position;
}

void Model::setScaling(vec3 scaling)
{
	this->scaling = scaling;
}

void Model::setRotation(vec3 rotationAxis, float rotationAngleDegrees)
{
	this->rotationAxis = rotationAxis;
	this->rotationAngleInDegrees = rotationAngleDegrees;
}
