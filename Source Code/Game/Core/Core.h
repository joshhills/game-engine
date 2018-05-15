#pragma once

#include <string>

#include <Common/Logger.h>

#include <Gameplay/Gameplay.h>
#include <Graphics/Graphics.h>
#include <Human Interface/HumanInterface.h>
#include <Physics/Physics.h>
#include <Audio/Audio.h>
#include <Profiling/Profiling.h>
#include <Resources/ResourceManager.h>

#include <Common/EventManager.h>
#include <Common/MoveEvent.h>
#include <Common/ToggleProfilingEvent.h>

/** 
 * Encapuslate core engine logic,
 * and a surplantable gameplay subsytem.
 */
class Core
{
public:
	Core();
	~Core();
	
	/**
	 * Main update loop, returns true if there is more to do.
	 */
	bool Step();

	/* Accessor methods. */

private:
	// A list of all events per cycle.
	EventManager * eventManager;
	
	// A list of all entities.
	vector<Entity *> entities;

	// All subsystems to be updated.
	Graphics graphics;
	Physics physics;
	HumanInterface humanInterface;
	Audio audio;
	Profiling profiling;
	ResourceManager resourceManager;

	// Gameplay subsystem.
	Gameplay gameplay;
};