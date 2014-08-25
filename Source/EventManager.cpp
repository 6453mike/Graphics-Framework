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
float EventManager::frameTime = 0.0f;

float EventManager::mouseDeltaX = 0.0f;
float EventManager::mouseDeltaY = 0.0f;
float EventManager::previousMousePositionX = 0.0f;
float EventManager::previousMousePositionY = 0.0f;

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

	// Update mouse info
	double x, y;
	glfwGetCursorPos(pWindow, &x, &y);
	mouseDeltaX = static_cast<float>(x - previousMousePositionX);
	mouseDeltaY = static_cast<float>(y - previousMousePositionY);
	previousMousePositionX = x;
	previousMousePositionY = y;

	// Update the delta time
	double currentTime = glfwGetTime();
	frameTime = static_cast<float>(currentTime - previousFrameTime);
	previousFrameTime = currentTime;
}

void EventManager::enableMouseCursor()
{
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void EventManager::disableMouseCursor()
{
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLFWwindow* EventManager::getWindow()
{
	return pWindow;
}

float EventManager::getFrameTime()
{
	return frameTime;
}

float EventManager::getMouseDeltaX()
{
	return mouseDeltaX;
}

float EventManager::getMouseDeltaY()
{
	return mouseDeltaY;
}

bool EventManager::isExitRequested()
{
	return glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(pWindow);
}