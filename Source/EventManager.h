#pragma once

// Third-party
#include <GLFW\glfw3.h>

class EventManager
{
public:
	static void initialize();
	static void terminate();

	static void update();

	static void enableMouseCursor();
	static void disableMouseCursor();

	// Accessors
	static GLFWwindow* getWindow();
	static float getFrameTime();

	static float getMouseDeltaX();
	static float getMouseDeltaY();

	// Status
	static bool isExitRequested();

private:
	// App window
	static GLFWwindow* pWindow;

	// Frame times
	static double previousFrameTime;
	static float frameTime;

	// Mouse info
	static float mouseDeltaX;
	static float mouseDeltaY;
	static float previousMousePositionX;
	static float previousMousePositionY;
};
