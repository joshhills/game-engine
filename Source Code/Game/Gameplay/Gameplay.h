#pragma once

#include "Level.h"
#include "PinballEntity.h"

#include <File/File.h>

#include <Common/Subsystem.h>
#include <Common/Movement.h>
#include <Common/InputEvent.h>
#include <Common/MoveEvent.h>
#include <Common/ToggleProfilingEvent.h>

using namespace std;

/**
 * This subsystem represents a pinball game.
 */
class Gameplay : Subsystem {
public:
	Gameplay(EventManager * eventManager, vector<Entity *> * entities);
	~Gameplay();

	void Update() override;

	// Accessors.

private:
	// Engine state.
	vector<Entity*> * entities;

	/* Game information. */

	// Overall state.
	bool paused;
	bool finished;

	// Player state.
	Level level;
	PinballEntity * pinball;

	float timeSpent;

	// Current level

	/* Bespoke event handlers */
	
	// Respond to input.
	void HandleHumanInterfaceEvent(Event * e);

	// Respond to collisions.
	
};