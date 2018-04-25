#pragma once

#include "Event.h"

class ToggleProfilingEvent : public Event {
public:
	ToggleProfilingEvent() :
		Event(Event::PROFILING_TOGGLE, Event::Subsystem::PROFILING)
	{}
};