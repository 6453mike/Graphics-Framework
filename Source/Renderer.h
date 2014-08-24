#pragma once

// Third-party
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

// Standard
#include <vector>

// Namespaces
using namespace std;

enum ShaderType
{
	DEFAULT_SHADER = 0
};

class Renderer
{
public:
	static void initialize();
	static void terminate();

	static void beginFrame();
	static void endFrame();

	// Accessors
	static unsigned int getCurrentShaderID();
	
	// Mutators
	static void setCurrentShaderType(ShaderType shaderType);

private:
	static GLFWwindow* pWindow;

	static vector<unsigned int> shaderIDs;
	static unsigned int currentShaderIndex;
};

