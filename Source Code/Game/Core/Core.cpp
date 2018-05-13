#include "Core.h"

Core::Core() :
	eventManager(new EventManager()),
	graphics(eventManager, &entities),
	physics(eventManager, &entities),
	humanInterface(eventManager),
	audio(eventManager),
	profiling(eventManager),
	gameplay(eventManager, &entities)
{
	// Set engine-wide logging settings.
	Logger::SetLevel(Logger::WARN);
	Logger::SetLevelExclusive(true);
	Logger::SetFilter("Profiling");
}

Core::~Core()
{
	// Clean up.
	for (Entity * entity : entities)
	{
		delete entity;
		entity = nullptr;
	}
}

void Core::Step()
{
	graphics.Update();
	humanInterface.Update();
	gameplay.Update();
	physics.Update();
	audio.Update();
	profiling.Update();

	eventManager->RemoveFinishedEvents();
}
