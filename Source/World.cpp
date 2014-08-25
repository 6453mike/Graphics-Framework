#include "World.h"

// Local
#include "Renderer.h"
#include "Models\Sphere.h"
#include "StaticCamera.h"
#include "FirstPersonCamera.h"

World::World()
{
	// Add a sphere for testing
	models.push_back(new Sphere());

	// Scale the hell out of it
	models[0]->setScaling(vec3(5.0f, 5.0f, 5.0f));


	//cameras.push_back(new StaticCamera(vec3(0.0f, 150.0f, 0.0f), vec3(0.0f), vec3(1.0f, 0.0f, 0.0f)));
	cameras.push_back(new FirstPersonCamera(vec3(0.0f, 10.0f, 0.0f)));
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
	GLuint ProjMatrixID = glGetUniformLocation(Renderer::getCurrentShaderID(), "ProjectonTransform");

	// Get a handle for Light Attributes uniform for World Lighting
	GLuint LightPositionID = glGetUniformLocation(Renderer::getCurrentShaderID(), "WorldLightPosition");
	GLuint LightColorID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lightColor");
	GLuint LightAttenuationID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lightAttenuation");
	
	GLuint LightDirectionID = glGetUniformLocation(Renderer::getCurrentShaderID(), "direction");
	GLuint LightCutOffID = glGetUniformLocation(Renderer::getCurrentShaderID(), "spotLightCutOff");
	GLuint LightDecayID = glGetUniformLocation(Renderer::getCurrentShaderID(), "spotLightDecay");

	// Draw models
	for (vector<Model*>::iterator it = models.begin(); it < models.end(); ++it)
	{
		// Send the Projection and View constants to the shader
		mat4 ProjMatrix = cameras[currentCameraIndex]->getProjectionTransform();
		glUniformMatrix4fv(ProjMatrixID, 1, GL_FALSE, &ProjMatrix[0][0]);

		mat4 ViewMatrix = cameras[currentCameraIndex]->getViewTransform();
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		// Send the World Lighting constants to the shader
		glUniform4f(LightPositionID, 0, 10, 0, 1.0);
		glUniform3f(LightColorID, 1, 1, 1);
		glUniform3f(LightAttenuationID, 0, 0, 0.05);

		glUniform3f(LightDirectionID, 0, -10, 0);
		glUniform1f(LightCutOffID, 20);
		glUniform1f(LightDecayID, 0.99);

		// Draw model
		(*it)->draw();
	}

	Renderer::endFrame();
}