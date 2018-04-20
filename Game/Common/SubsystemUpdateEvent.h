#pragma once

#include "Event.h"

class SubSystemUpdateEvent : public Event {
public:
	SubSystemUpdateEvent(Subsystem subsystem, int msElapsed) :
		Event(Event::PROFILING_SUBSYSTEM_UPDATE),
		subsystem(subsystem),
		msElapsed(msElapsed)
	{}

	Subsystem subsystem;
	int msElapsed;
};