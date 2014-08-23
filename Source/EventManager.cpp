#include "EventManager.h"

// Third-party
#include <GLFW\glfw3.h>

// Standard
#include <iostream>

// Namespaces
using namespace std;

// Static variables
GLFWwindow* EventManager::pWindow = 0;

double EventManager::previousFrameTime = glfwGetTime();
float  EventManager::frameTime = 0.0f;

void EventManager::initialize()
{
	// Initialize GLFW
	if (glfwInit() == false)
		throw runtime_error("Failed to initialize GLFW\n");

	// Set multisampling
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Set client API compatibility
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Disable window resizing
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create the application window
	pWindow = glfwCreateWindow(1024, 768, "Mike's Framework", NULL, NULL);
	if (pWindow == 0)
		throw runtime_error("Failed to create GLFW window\n");
}

void EventManager::terminate()
{
	// End GLFW
	glfwTerminate();

	// Remove dangling pointers
	pWindow = 0;
}

void EventManager::update()
{
	// Update inputs
	glfwPollEvents();

	// Update the delta time
	double currentTime = glfwGetTime();
	frameTime = static_cast<float>(currentTime - previousFrameTime);
	previousFrameTime = currentTime;
}

GLFWwindow* EventManager::getWindow()
{
	return pWindow;
}

float EventManager::getFrameTime()
{
	return frameTime;
}

bool EventManager::isExitRequested()
{
	return glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(pWindow);
}