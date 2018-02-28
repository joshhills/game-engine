#pragma once

#include <vector>
#include "Entity.h"

using namespace std;

class Event {
public: 
	enum Subsystem {
		PHYSICS = 0,
		GRAPHICS = 1,
		HUMAN_INTERFACE = 2
	};

	enum EventType {
		MOVE_UP = 0,
		MOVE_DOWN = 1,
		MOVE_LEFT = 2,
		MOVE_RIGHT = 3
	};

	Event();
	~Event();
	
	// Releated subsystems to be informed of the event.
	vector<Subsystem> subsystems;

	// Entities associated with this event.
	vector<Entity *> entities;

	// The explicit type of event that occured.
	EventType type;
};