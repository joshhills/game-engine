#pragma once

#include <Common/Subsystem.h>

class Profiling : Subsystem {
public:
	Profiling(EventManager * eventManager);
	~Profiling();

	void Update() override;
private:
	void HandleFPSEvent(Event * e);
	void HandleSubsystemUpdateEvent(Event * e);

	// Store last FPS to check for changes (and prevent spam).
	int lastFPS = -1;
};