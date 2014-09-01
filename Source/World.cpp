#include "World.h"

// Local
#include "Renderer.h"
#include "Models\Sphere.h"
#include "Models\Cube.h"
#include "StaticCamera.h"
#include "FirstPersonCamera.h"
#include "LightManager.h"

#include <string>

using namespace std;

World::World()
{
	// Add a sphere for testing
	models.push_back(new Sphere());

	// Add a ground for testing
	models.push_back(new Cube(vec3(100.0f, 1.0f, 100.0f)));

	// Scale the hell out of the sphere
	models[0]->setPosition(vec3(0.0f, 10.0f, 0.0f));
	models[1]->setPosition(vec3(0.0f, -2.0f, 0.0f));

	LightManager::addLight(Light("Light Number 1",
		vec3(1.0f), vec3(1.0f), vec3(0.02f), vec4(-5.0f, 5.0f, -5.0f, 1.0f), vec3(0.0f, -1.0f, 1.0f), 20.0f, 0.001f, 0.0f, 0.0f, 0.02f));
	LightManager::addLight(Light("Light Number 2",
		vec3(1.0f), vec3(1.0f), vec3(0.02f), vec4(5.0f, 5.0f, 5.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f), 180.0f, 0.001f, 0.0f, 0.0f, 0.02f));

	//cameras.push_back(new StaticCamera(vec3(0.0f, 150.0f, 0.0f), vec3(0.0f), vec3(1.0f, 0.0f, 0.0f)));
	cameras.push_back(new FirstPersonCamera(vec3(0.0f, 5.0f, 0.0f)));
	currentCameraIndex = 0;
}

World::~World()
{
	// Models
	for (vector<Model*>::iterator it = models.begin(); it < models.end(); ++it)
	{
		delete *it;
	}
	models.clear();

	// Cameras
	for (vector<Camera*>::iterator it = cameras.begin(); it < cameras.end(); ++it)
	{
		delete *it;
	}
	cameras.clear();
}
	
void World::update(float deltaTime)
{
	cameras[0]->update(deltaTime);
}

void World::draw()
{
	Renderer::beginFrame();

	GLuint ViewMatrixID = glGetUniformLocation(Renderer::getCurrentShaderID(), "ViewTransform");
	GLuint ProjMatrixID = glGetUniformLocation(Renderer::getCurrentShaderID(), "ProjectionTransform");

	// Draw models
	for (vector<Model*>::iterator it = models.begin(); it < models.end(); ++it)
	{
		// Send the Projection and View constants to the shader
		mat4 ProjMatrix = cameras[currentCameraIndex]->getProjectionTransform();
		glUniformMatrix4fv(ProjMatrixID, 1, GL_FALSE, &ProjMatrix[0][0]);

		mat4 ViewMatrix = cameras[currentCameraIndex]->getViewTransform();
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		LightManager::sendDataToOpenGL();

		// Draw model
		(*it)->draw();
	}

	Renderer::endFrame();
}