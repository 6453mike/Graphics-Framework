#pragma once

// Third-party
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLM/glm.hpp>

// Standard
#include <string>
#include <vector>

// Namespaces
using namespace glm;
using namespace std;

struct Light
{
	string name;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec4 position;
	vec3 direction;
	float cutoff, exponent;
	float constantAttenuation, linearAttenuation, quadraticAttenuation;

	Light(string name,
		vec3 ambient,
		vec3 diffuse,
		vec3 specular,
		vec4 position,
		vec3 direction,
		float cutoff,
		float exponent,
		float constantAttenuation,
		float linearAttenuation,
		float quadraticAttenuation)
		: ambient(ambient),
		diffuse(diffuse),
		specular(specular),
		position(position),
		direction(direction),
		cutoff(cutoff),
		exponent(exponent),
		constantAttenuation(constantAttenuation),
		linearAttenuation(linearAttenuation),
		quadraticAttenuation(quadraticAttenuation) {}
};

class LightManager
{
public:
	static void addLight(Light light);
	static void sendDataToOpenGL();

private:
	static vec3 sceneAmbient;
	static vector<Light> lights;
};

