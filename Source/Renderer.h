#pragma once

// Third-party
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

class Renderer
{
public:
	static void initialize();
	static void terminate();

	static void beginFrame();
	static void endFrame();

private:
	static GLFWwindow* pWindow;
};

