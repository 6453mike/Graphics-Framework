#include "Renderer.h"
#include "EventManager.h"

int main(int argc, char*argv[])
{
	EventManager::initialize();
	Renderer::initialize();

	// The Loop
	do
	{
		EventManager::update();

		float deltaTime = EventManager::getFrameTime();
		

	} while (EventManager::isExitRequested() == false);

	Renderer::terminate();
	EventManager::terminate();

	return 0;
}
