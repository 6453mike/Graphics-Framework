#pragma once

// Third-party
#include <GLFW\glfw3.h>

class EventManager
{
public:
	static void initialize();
	static void terminate();

	static void update();

	// Accessors
	static GLFWwindow* getWindow();
	static float getFrameTime();

	// Status
	static bool isExitRequested();

private:
	// App window
	static GLFWwindow* pWindow;

	// Frame times
	static double previousFrameTime;
	static float frameTime;
};
