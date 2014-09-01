#include "LightManager.h"

// Local
#include "ShaderStrings.h"
#include "Renderer.h"

// Static variables
vec3 LightManager::sceneAmbient = vec3(0.1f, 0.1f, 0.1f);
vector<Light> LightManager::lights;

void LightManager::addLight(Light light)
{
	lights.push_back(light);
}

void LightManager::sendDataToOpenGL()
{
	GLuint ambientID, diffuseID, specularID, positionID, directionID, cutoffID, exponentID, constantAttenuationID, linearAttenuationID, quadraticAttenuationID, sceneAmbientID;

	for (vector<Light>::size_type i = 0; i != lights.size(); i++)
	{
		ambientID = glGetUniformLocation(Renderer::getCurrentShaderID(), (ShaderStrings::LIGHT_ARRAY + "[" + to_string(i) + "]." + ShaderStrings::LIGHT_AMBIENT).c_str());
		diffuseID = glGetUniformLocation(Renderer::getCurrentShaderID(), (ShaderStrings::LIGHT_ARRAY + "[" + to_string(i) + "]." + ShaderStrings::LIGHT_DIFFUSE).c_str());
		specularID = glGetUniformLocation(Renderer::getCurrentShaderID(), (ShaderStrings::LIGHT_ARRAY + "[" + to_string(i) + "]." + ShaderStrings::LIGHT_SPECULAR).c_str());
		positionID = glGetUniformLocation(Renderer::getCurrentShaderID(), (ShaderStrings::LIGHT_ARRAY + "[" + to_string(i) + "]." + ShaderStrings::LIGHT_POSITION).c_str());
		directionID = glGetUniformLocation(Renderer::getCurrentShaderID(), (ShaderStrings::LIGHT_ARRAY + "[" + to_string(i) + "]." + ShaderStrings::LIGHT_DIRECTION).c_str());
		cutoffID = glGetUniformLocation(Renderer::getCurrentShaderID(), (ShaderStrings::LIGHT_ARRAY + "[" + to_string(i) + "]." + ShaderStrings::LIGHT_CUTOFF).c_str());
		exponentID = glGetUniformLocation(Renderer::getCurrentShaderID(), (ShaderStrings::LIGHT_ARRAY + "[" + to_string(i) + "]." + ShaderStrings::LIGHT_EXPONENT).c_str());
		constantAttenuationID = glGetUniformLocation(Renderer::getCurrentShaderID(), (ShaderStrings::LIGHT_ARRAY + "[" + to_string(i) + "]." + ShaderStrings::LIGHT_CONSTANT_ATTENUATION).c_str());
		linearAttenuationID = glGetUniformLocation(Renderer::getCurrentShaderID(), (ShaderStrings::LIGHT_ARRAY + "[" + to_string(i) + "]." + ShaderStrings::LIGHT_LINEAR_ATTENUATION).c_str());
		quadraticAttenuationID = glGetUniformLocation(Renderer::getCurrentShaderID(), (ShaderStrings::LIGHT_ARRAY + "[" + to_string(i) + "]." + ShaderStrings::LIGHT_QUADRATIC_ATTENUATION).c_str());

		glUniform3f(ambientID, lights[i].ambient.x, lights[i].ambient.y, lights[i].ambient.z);
		glUniform3f(diffuseID, lights[i].diffuse.x, lights[i].diffuse.y, lights[i].diffuse.z);
		glUniform3f(specularID, lights[i].specular.x, lights[i].specular.y, lights[i].specular.z);
		glUniform4f(positionID, lights[i].position.x, lights[i].position.y, lights[i].position.z, lights[i].position.w);
		glUniform3f(directionID, lights[i].direction.x, lights[i].direction.y, lights[i].direction.z);
		glUniform1f(cutoffID, lights[i].cutoff);
		glUniform1f(exponentID, lights[i].exponent);
		glUniform1f(constantAttenuationID, lights[i].constantAttenuation);
		glUniform1f(linearAttenuationID, lights[i].linearAttenuation);
		glUniform1f(quadraticAttenuationID, lights[i].quadraticAttenuation);
	}

	sceneAmbientID = glGetUniformLocation(Renderer::getCurrentShaderID(), ShaderStrings::LIGHT_SCENE_AMBIENT.c_str());

	glUniform3f(sceneAmbientID, sceneAmbient.x, sceneAmbient.y, sceneAmbient.z);
}
