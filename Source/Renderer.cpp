#include "Renderer.h"

// Local
#include "EventManager.h"
#include "Loader.h"

// Third-party
#include <GLFW\glfw3.h>

// Standard
#include <iostream> 

// Namespaces
using namespace std;

// Static variables
GLFWwindow* Renderer::pWindow = 0;
vector<unsigned int> Renderer::shaderIDs;
unsigned int Renderer::currentShaderIndex;

void Renderer::initialize()
{
	pWindow = EventManager::getWindow();
	
	// Set the current window
	glfwMakeContextCurrent(pWindow);

	// Make sure that experimental or pre-release drivers expose all extensions
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw runtime_error("Failed to initialize GLEW\n");

	// Set the background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Fragments that are closest to the camera are accepted
	glDepthFunc(GL_LESS);

	// Load program shaders
	shaderIDs.push_back(Loader::LoadShaders("../Source/Shaders/Default.vertexshader", "../Source/Shaders/Default.fragmentshader"));

	// Set default shader
	currentShaderIndex = DEFAULT_SHADER;
}

void Renderer::terminate()
{
	// Remove dangling pointers
	pWindow = 0;
}

void Renderer::beginFrame()
{
	// Clear the window color to the colors previously set by glClearColor and glClearDepth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::endFrame()
{
	// Swap the front and back buffers
	glfwSwapBuffers(pWindow);
}

unsigned int Renderer::getCurrentShaderID()
{
	return shaderIDs[currentShaderIndex];
}

void Renderer::setCurrentShaderType(ShaderType shaderType)
{
	if (shaderType >= 0 && shaderType < shaderIDs.size())
		currentShaderIndex = shaderType;
}