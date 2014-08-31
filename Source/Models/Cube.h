#pragma once

// Local
#include "Model.h"

class Cube : public Model
{
public:
	Cube(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~Cube();

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

	unsigned int vertexArrayID;
	unsigned int vertexBufferID;

	// Material Coefficients
	const float ka = 0.2f;
	const float kd = 0.8f;
	const float ks = 0.2f;
	const float n = 50.0f;
};
