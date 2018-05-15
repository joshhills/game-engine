#include "Gameplay.h"

Gameplay::Gameplay(EventManager * eventManager, vector<Entity*>* entities) :
	Subsystem("Gameplay", Event::GAMEPLAY, eventManager),
	entities(entities)
{
	// Create function map using lambdas to handle events.
	eventMap[Event::HUMAN_INTERFACE_INPUT] =	[this](Event * e)	{ HandleHumanInterfaceEvent(e); };
	eventMap[Event::GAMEPLAY_LEVEL_COMPLETE] =	[this](Event * e)	{ HandleCompleteLevelEvent(e);	};
	eventMap[Event::GAMEPLAY_HOLE_ENTER] =		[this](Event * e)	{ HandleHoleEnterEvent(e);		};
	eventMap[Event::CAMERA_TRACK] =				[this](Event * e)	{ HandleCameraTrackEvent(e);	};

	// Initialise file I/O (after graphics, as a requirement).
	File::InitialiseTileGraphicsData();

	// Create background.
	background = new BackgroundEntity(eventManager);
	entities->push_back(background);

	// Create the player entity.
	// Get the initial spawn location.
	pinball = new PinballEntity(eventManager);
	entities->push_back(pinball);

	// Create pause entity.
	pauseEntity = new PauseEntity(eventManager);
	entities->push_back(pauseEntity);

	// Create finish entity.
	finishEntity = new FinishEntity(eventManager);
	entities->push_back(finishEntity);

	// Initialise level.
	AdvanceLevel();

	// Play background music.
	eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/background-music.wav", true, 0, 0));
}

Gameplay::~Gameplay()
{
	delete pinball;
	delete finishEntity;
	delete pauseEntity;
}

void Gameplay::Update()
{
	// Measure time taken.
	clock_t start = clock();

	// Update pinball state.
	if (!paused)
	{
		noBumpIn += start - lastClockReading;
		canBump = noBumpIn > BUMP_DELAY;
		pinball->UpdateShaderBasedOnBumpAbility(canBump);
	}
	
	lastClockReading = start;

	// Reset the player movement direction vector.
	shouldBump = false;
	lastDirection = MoveEvent::Direction();

	Subsystem::Update();

	// Having likely built a movement event during event handling, send the most recent one off
	// (if conditions are correct)
	if (!paused & (lastDirection.x != 0 || lastDirection.y != 0))
	{
		if (shouldBump)
		{
			noBumpIn = 0;
			lastDirection.x *= BUMP_INTENSIFIER;
			lastDirection.y *= BUMP_INTENSIFIER;
		}

		eventManager->AddEvent(
			(new MoveEvent(lastDirection))->AddEntity(pinball)
		);
	}

	// Send time taken to complete function.
	clock_t stop = clock();
	float elapsed = (float)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	eventManager->AddEvent(new SubsystemUpdateEvent(subSystemType, elapsed));
}

bool Gameplay::IsPaused() const
{
	return paused;
}

bool Gameplay::IsFinished() const
{
	return finished;
}

bool Gameplay::IsCompleted() const
{
	return completed;
}

void Gameplay::AdvanceLevel()
{
	// Advance the current level index.
	currentLevel++;
	if (currentLevel > NUM_LEVELS) {
		currentLevel = 1;
	}

	// Load the level data.
	delete level;
	level = File::LoadLevel(eventManager, "Levels/" + to_string(currentLevel) + ".lvl", entities);
	// Get the spawn tile for that level.
	SpawnTileEntity * s = dynamic_cast<SpawnTileEntity *>(level->GetSpawnTile());
	// Set the pinball's location.
	pinball->GetPhysicsData()->GetBody()->SetTransform(b2Vec2(s->gridPositionX, s->gridPositionY), 0);
	pinball->GetPhysicsData()->GetBody()->SetAngularVelocity(0);
	pinball->GetPhysicsData()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
}

void Gameplay::HandleHumanInterfaceEvent(Event * e)
{
	// Respond to input.
	InputEvent * t = static_cast<InputEvent *>(e);
	
	// Handle updating high-level game state machine based on user input.
	switch (t->input.control)
	{
		// Pausing.
		case Controller::Control::SELECT:
			if (t->input.state == Controller::ControlState::TRIGGERED)
			{
				if (!completed) {
					paused = !paused;

					pauseEntity->SetEnabled(paused);
				}
				else
				{
					completed = false;
					currentLevel = 0;
					finishEntity->SetEnabled(false);
					AdvanceLevel();
				}
			}
			break;
		// Quitting.
		case Controller::Control::PAUSE:
			finished = (t->input.state == Controller::ControlState::TRIGGERED);
			break;
		// Profiling.
		case Controller::Control::SECONDARY:
			if (t->input.state == Controller::ControlState::TRIGGERED)
			{
				eventManager->AddEvent(
					new ToggleProfilingEvent()
				);
			}
			break;
		// Base Movement.
		case Controller::Control::UP:
			lastDirection.y += MOVE_SPEED * t->input.amount;
			break;
		case Controller::Control::DOWN:
			lastDirection.y += -MOVE_SPEED * t->input.amount;
			break;
		case Controller::Control::LEFT:
			lastDirection.x += MOVE_SPEED * t->input.amount;
			break;
		case Controller::Control::RIGHT:
			lastDirection.x += -MOVE_SPEED * t->input.amount;
			break;
		// Boost.
		case Controller::Control::PRIMARY:
			shouldBump = t->input.state == Controller::ControlState::TRIGGERED && canBump;
			break;
	}
}

void Gameplay::HandleHoleEnterEvent(Event * e)
{
	// Set the position of the pinball to the hole exit singleton tile instance.
	pinball->GetPhysicsData()->GetBody()->SetTransform(
		b2Vec2(
			level->GetHoleExitTile()->gridPositionX,
			level->GetHoleExitTile()->gridPositionY
		),
		pinball->GetPhysicsData()->GetBody()->GetAngle()
	);
}

void Gameplay::HandleCompleteLevelEvent(Event * e)
{
	if (currentLevel + 1> NUM_LEVELS) {
		// Have won!
		completed = true;
		finishEntity->SetEnabled(true);
	}

	if (!completed) {
		AdvanceLevel();
	}
}

void Gameplay::HandleCameraTrackEvent(Event * e)
{
	// Convert the event pointer to the correct format.
	CameraTrackEvent * ce = static_cast<CameraTrackEvent *>(e);

	// Update the position of static UI overlay entities.
	pauseEntity->GetGameObject()->x = ce->x;
	pauseEntity->GetGameObject()->y = ce->y;

	finishEntity->GetGameObject()->x = ce->x;
	finishEntity->GetGameObject()->y = ce->y;

	background->GetGameObject()->x = ce->x;
	background->GetGameObject()->y = ce->y;
}
