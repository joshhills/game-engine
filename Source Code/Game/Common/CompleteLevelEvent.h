#pragma once

#include "Event.h"

class CompleteLevelEvent : public Event{
public:
	CompleteLevelEvent() :
		Event(Event::GAMEPLAY_LEVEL_COMPLETE, Event::Subsystem::GAMEPLAY)
	{}
};