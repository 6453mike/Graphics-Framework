#include "FirstPersonCamera.h"

// Local
#include "EventManager.h"

// Third-party
#include <GLM/gtx/transform.hpp>

FirstPersonCamera::FirstPersonCamera(glm::vec3 position) 
	: Camera(), mPosition(position), mLookAtPoint(0, 0, 0), mUpVector(0, 1, 0), alpha(0), beta(0), radius(1), strafeSpeed(2), mouseSensitivity(10)
{
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::update(float deltaTime)
{
	// Prevent from having the camera move only when the cursor is within the windows
	EventManager::disableMouseCursor();

	float mouseMotionX = -EventManager::getMouseDeltaX() * mouseSensitivity * deltaTime;
	float mouseMotionY = EventManager::getMouseDeltaY() * mouseSensitivity * deltaTime;


	beta = fmod(beta + mouseMotionX, 360);
	alpha = glm::clamp(
		(alpha + mouseMotionY),
		-85.0f,
		85.0f
		);

	mLookAtPoint.x = radius * glm::cos(glm::radians(alpha)) * glm::sin(glm::radians(beta));
	mLookAtPoint.y = radius * glm::sin(glm::radians(alpha));
	mLookAtPoint.z = radius * glm::cos(glm::radians(alpha)) * glm::cos(glm::radians(beta));
	
	mRightVector = glm::vec3(
		glm::sin(glm::radians(beta - 90)),
		0,
		glm::cos(glm::radians(beta - 90))
		);

	if (glfwGetKey(EventManager::getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		strafeSpeed = 5;
	}
	else 
	{
		strafeSpeed = 2;
	}
	if (glfwGetKey(EventManager::getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		mPosition += mRightVector * strafeSpeed * deltaTime;
	}
	else if (glfwGetKey(EventManager::getWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		mPosition += mLookAtPoint * strafeSpeed * deltaTime;
	}
	else if (glfwGetKey(EventManager::getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		mPosition -= mRightVector * strafeSpeed * deltaTime;
	}
	else if (glfwGetKey(EventManager::getWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		mPosition -= mLookAtPoint * strafeSpeed * deltaTime;
	}
}

glm::mat4 FirstPersonCamera::getViewTransform() const
{
	// @TODO 3 : Calculate the View Matrix
	return glm::lookAt(mPosition,		// Camera position
		mPosition - mLookAtPoint,	// Look towards this point
		mUpVector		// Up vector
		);
}
