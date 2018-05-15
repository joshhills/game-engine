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

	// Initialise objects into positons once.
	physics.Update();
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

bool Core::Step()
{
	graphics.Update();
	humanInterface.Update();
	gameplay.Update();

	if (!gameplay.IsPaused() && !gameplay.IsFinished() && !gameplay.IsCompleted())
	{
		physics.Update();
	}

	if (!gameplay.IsFinished())
	{
		audio.Update();
		profiling.Update();

		eventManager->RemoveFinishedEvents();
	}

	return !(gameplay.IsFinished() || graphics.IsFinished());
}
