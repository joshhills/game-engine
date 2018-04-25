#pragma once

#include "Event.h"

class SubsystemUpdateEvent : public Event {
public:
	SubsystemUpdateEvent(Subsystem subsystem, int msElapsed) :
		Event(Event::PROFILING_SUBSYSTEM_UPDATE, Event::Subsystem::PROFILING),
		subsystem(subsystem),
		msElapsed(msElapsed)
	{}

	Subsystem subsystem;
	int msElapsed;
};