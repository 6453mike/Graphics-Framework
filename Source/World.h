#pragma once

// Local
#include "Models\Model.h"
#include "Camera.h"

// Standard
#include <vector>

// Namespaces
using namespace std;

class World
{
public:
	World();
	~World();
	
	void update(float deltaTime);
	void draw();

private:
	vector<Model*> models;

	vector<Camera*> cameras;
	unsigned int currentCameraIndex;
};
