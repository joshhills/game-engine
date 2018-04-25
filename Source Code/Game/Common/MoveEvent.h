#pragma once

#include "Event.h"

class MoveEvent : public Event {
public:
	struct Direction {
		float x;
		float y;
	};

	MoveEvent(Direction direction) :
		Event(Event::MOVE, Event::Subsystem::PHYSICS),
		direction(direction)
	{}

	Direction direction;
};