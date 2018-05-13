#include "Core.h"

Core::Core() :
	graphics(eventManager, &entities),
	physics(eventManager, &entities),
	humanInterface(eventManager),
	audio(eventManager),
	profiling(eventManager)
{
	// Set engine-wide logging settings.
	Logger::SetLevel(Logger::WARN);
	Logger::SetLevelExclusive(true);
	Logger::SetFilter("Profiling");

	// Initialise file I/O (after graphics, as a requirement).
	File::InitialiseTileGraphicsData();
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
	physics.Update();
	audio.Update();
	profiling.Update();
}
