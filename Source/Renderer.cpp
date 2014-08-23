#include "Renderer.h"

// Local
#include "EventManager.h"

// Third-party
#include <GLFW\glfw3.h>

// Standard
#include <iostream>

// Namespaces
using namespace std;

// Static variables
GLFWwindow* Renderer::pWindow = 0;

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