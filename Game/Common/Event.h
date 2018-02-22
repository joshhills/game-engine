#pragma once

#include <vector>
#include "Entity.h"

using namespace std;

enum SubSystem {
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

class Event {
public: 
	Event(const EventType type);
	~Event();

	// Releated subsystems to be informed of the event.
	vector<SubSystem> subsystems;

	vector<Entity *> entities;

	// The explicit type of event that occured.
	EventType type;
};