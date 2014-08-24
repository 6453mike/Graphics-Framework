#include "World.h"

// Local
#include "Renderer.h"
#include "Models\Sphere.h"
#include "StaticCamera.h"

World::World()
{
	// Add a sphere for testing
	models.push_back(new Sphere());

	// Use a static camera for now
	cameras.push_back(new StaticCamera(vec3(6.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f)));
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
	
}

void World::draw()
{
	Renderer::beginFrame();

	GLuint ViewMatrixID = glGetUniformLocation(Renderer::getCurrentShaderID(), "ViewTransform");
	GLuint ProjMatrixID = glGetUniformLocation(Renderer::getCurrentShaderID(), "ProjectonTransform");

	// Draw models
	for (vector<Model*>::iterator it = models.begin(); it < models.end(); ++it)
	{
		// Send the Projection and View constants to the shader
		mat4 ProjMatrix = cameras[currentCameraIndex]->getProjectionMatrix();
		glUniformMatrix4fv(ProjMatrixID, 1, GL_FALSE, &ProjMatrix[0][0]);

		mat4 ViewMatrix = cameras[currentCameraIndex]->getViewMatrix();
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		// Draw model
		(*it)->draw();
	}

	Renderer::endFrame();
}