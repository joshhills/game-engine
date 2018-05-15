#pragma once

#include "Event.h"

class HoleEnterEvent : public Event {
public:
	HoleEnterEvent() :
		Event(Event::GAMEPLAY_HOLE_ENTER, Event::Subsystem::GAMEPLAY)
	{}
};