#pragma once

#include "Event.h"

class CameraTrackEvent : public Event {
public:
	CameraTrackEvent(float x, float y) :
		Event(Event::CAMERA_TRACK, Event::Subsystem::GRAPHICS),
		x(x),
		y(y)
	{}

	float x, y;
};