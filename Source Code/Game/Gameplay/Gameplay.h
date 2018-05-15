#pragma once

#include "Level.h"
#include "PinballEntity.h"
#include "PauseEntity.h"
#include "FinishEntity.h"
#include "BackgroundEntity.h"

#include <File/File.h>

#include <Common/Subsystem.h>
#include <Common/Movement.h>
#include <Common/InputEvent.h>
#include <Common/MoveEvent.h>
#include <Common/ToggleProfilingEvent.h>
#include <Common/CameraTrackEvent.h>

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
	bool IsPaused() const;
	bool IsFinished() const;
	bool IsCompleted() const;
private:
	// Engine state.
	vector<Entity*> * entities;

	/* Game information. */

	// Overall state.
	// Have paused the game.
	bool paused = true;
	// Have finished all levels but not quit.
	bool completed = false;
	// Have quit.
	bool finished = false;

	// Level state.
	const int NUM_LEVELS = 3;
	int currentLevel = 0;
	Level * level;

	// Background.
	BackgroundEntity * background;

	// Player.
	PinballEntity * pinball;
	MoveEvent::Direction lastDirection;
	bool shouldBump = false;
	const float BUMP_DELAY = 3000;
	float noBumpIn = BUMP_DELAY;
	clock_t lastClockReading;
	bool canBump = true;

	float timeSpent;
	const int BUMP_INTENSIFIER = 50;
	const int MOVE_SPEED = 250;

	// Tutorialisation.
	PauseEntity * pauseEntity;
	FinishEntity * finishEntity;

	/* Utility */
	void AdvanceLevel();

	/* Bespoke event handlers */
	
	// Respond to input.
	void HandleHumanInterfaceEvent(Event * e);

	//void HandleMoveEvent(Event * e);

	// Respond to a warp hole being hit.
	void HandleHoleEnterEvent(Event * e);

	// Respond to complete level.
	void HandleCompleteLevelEvent(Event * e);

	// Respond to pinball moving.
	void HandleCameraTrackEvent(Event *e);

	// Respond to collisions.
	
};