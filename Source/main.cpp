// Local
#include "Renderer.h"
#include "EventManager.h"
#include "World.h"

int main(int argc, char*argv[])
{
	EventManager::initialize();
	Renderer::initialize();

	World world;

	// The Loop
	do
	{
		EventManager::update();

		float deltaTime = EventManager::getFrameTime();
		world.update(deltaTime);
		
		world.draw();
	}
	while (EventManager::isExitRequested() == false);

	Renderer::terminate();
	EventManager::terminate();

	return 0;
}
