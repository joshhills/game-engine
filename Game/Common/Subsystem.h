#pragma once

#include "Event.h"

class Subsystem {
public:
	virtual void Update() = 0;
	virtual void CheckForEvents() = 0;
	virtual void HandleEvent(Event * event) = 0;
};