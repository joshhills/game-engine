#pragma once

#include "Event.h"

class FPSEvent : public Event {
public:
	FPSEvent(int fps) :
		Event(Event::PROFILING_FPS, Event::Subsystem::PROFILING),
		fps(fps)
	{}

	int fps;
};