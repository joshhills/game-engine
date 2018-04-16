#pragma once

#include <vector>
#include "Entity.h"

using namespace std;

class Event {
public: 
	// Enum describing available subsystems.
	enum Subsystem {
		PHYSICS = 0,
		GRAPHICS = 1,
		HUMAN_INTERFACE = 2,
		AUDIO = 3
	};

	// Enum describing kinds of events that may occur.
	enum EventType {
		// Controls
		INPUT,

		// Physics
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT, 
		MOVE_RIGHT,

		// Audio
		PLAY_SOUND
	};

	Event();
	Event(EventType type);
	Event(EventType type, Subsystem subsystem, Entity * entity);

	~Event();

	// Builder pattern for simple event creation.
	Event * AddSubsystem(Subsystem subsystem);
	Event * AddEntity(Entity * entity);

	// Releated subsystems to be informed of the event.
	vector<Subsystem> subsystems;

	// Entities associated with this event.
	vector<Entity *> entities;

	// The explicit type of event that occured.
	EventType type;
};