#pragma once

#include <vector>
#include "Entity.h"

using namespace std;

class Event {
public: 
	enum Subsystem {
		PHYSICS,
		GRAPHICS,
		HUMAN_INTERFACE
	};

	enum EventType {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT
	};

	Event();
	~Event();
	
	// Releated subsystems to be informed of the event.
	vector<Subsystem> subsystems;

	vector<Entity *> entities;

	// The explicit type of event that occured.
	EventType type;
};