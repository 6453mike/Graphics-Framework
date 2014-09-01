#pragma once

// Local
#include "Model.h"

class Sphere : public Model
{
public:
	Sphere();
	virtual ~Sphere();

	virtual void update(float deltaTime);
	virtual void draw();

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		vec3 position;
		vec3 normal;
		vec3 color;
	};

	unsigned int numberOfVertices;

	unsigned int vertexArrayID;
	unsigned int vertexBufferID;

	// Material Coefficients
	const float ka = 0.4f;
	const float kd = 0.8f;
	const float ks = 0.9f;
	const float n = 100.0f;
};

