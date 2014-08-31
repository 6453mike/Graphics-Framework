#include "World.h"

// Local
#include "Renderer.h"
#include "Models\Sphere.h"
#include "Models\Cube.h"
#include "StaticCamera.h"
#include "FirstPersonCamera.h"

World::World()
{
	// Add a sphere for testing
	models.push_back(new Sphere());

	// Add a ground for testing
	models.push_back(new Cube(vec3(100.0f, 1.0f, 100.0f)));

	// Scale the hell out of the sphere
	models[0]->setPosition(vec3(0.0f, 10.0f, 0.0f));
	models[1]->setPosition(vec3(0.0f, -2.0f, 0.0f));

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

	GLuint ambientID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[0].ambient");
	GLuint diffuseID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[0].diffuse");
	GLuint specularID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[0].specular");
	GLuint positionID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[0].position");
	GLuint directionID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[0].direction");
	GLuint cutoffID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[0].cutoff");
	GLuint exponentID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[0].exponent");
	GLuint constantAttenuationID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[0].constantAttenuation");
	GLuint linearAttenuationID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[0].linearAttenuation");
	GLuint quadraticAttenuationID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[0].quadraticAttenuation");

	GLuint ambient2ID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[1].ambient");
	GLuint diffuse2ID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[1].diffuse");
	GLuint specular2ID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[1].specular");
	GLuint position2ID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[1].position");
	GLuint direction2ID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[1].direction");
	GLuint cutoff2ID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[1].cutoff");
	GLuint exponent2ID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[1].exponent");
	GLuint constantAttenuation2ID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[1].constantAttenuation");
	GLuint linearAttenuation2ID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[1].linearAttenuation");
	GLuint quadraticAttenuation2ID = glGetUniformLocation(Renderer::getCurrentShaderID(), "lights[1].quadraticAttenuation");
	
	GLuint sceneAmbientID = glGetUniformLocation(Renderer::getCurrentShaderID(), "sceneAmbient");

	// Draw models
	for (vector<Model*>::iterator it = models.begin(); it < models.end(); ++it)
	{
		// Send the Projection and View constants to the shader
		mat4 ProjMatrix = cameras[currentCameraIndex]->getProjectionTransform();
		glUniformMatrix4fv(ProjMatrixID, 1, GL_FALSE, &ProjMatrix[0][0]);

		mat4 ViewMatrix = cameras[currentCameraIndex]->getViewTransform();
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		// Send the lighting information
		glUniform3f(ambientID, 1.0, 1.0, 1.0);
		glUniform3f(diffuseID, 1.0, 1.0, 1.0);
		glUniform3f(specularID, 0.02, 0.02, 0.02);
		glUniform4f(positionID, -5.0, 5.0, -5.0, 1.0);
		glUniform3f(directionID, 0.0, -1.0, -3.0);
		glUniform1f(cutoffID, 180.0);
		glUniform1f(exponentID, 0.001);
		glUniform1f(constantAttenuationID, 0.0);
		glUniform1f(linearAttenuationID, 0.0);
		glUniform1f(quadraticAttenuationID, 0.02);

		glUniform3f(ambient2ID, 1.0, 1.0, 1.0);
		glUniform3f(diffuse2ID, 1.0, 1.0, 1.0);
		glUniform3f(specular2ID, 0.02, 0.02, 0.02);
		glUniform4f(position2ID, 5.0, 5.0, 0.0, 1.0);
		glUniform3f(direction2ID, 0.0, -1.0, -3.0);
		glUniform1f(cutoff2ID, 180.0);
		glUniform1f(exponent2ID, 0.001);
		glUniform1f(constantAttenuation2ID, 0.0);
		glUniform1f(linearAttenuation2ID, 0.0);
		glUniform1f(quadraticAttenuation2ID, 0.02);

		glUniform3f(sceneAmbientID, 0.1, 0.1, 0.1);

		// Draw model
		(*it)->draw();
	}

	Renderer::endFrame();
}