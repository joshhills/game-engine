#pragma once

#include <Common/Subsystem.h>
#include <Common/FPSEvent.h>
#include <Common/SubsystemUpdateEvent.h>
#include <File/File.h>

class Profiling : public Subsystem {
public:
	Profiling(EventManager * eventManager);
	~Profiling();

private:
	void Report(string content, bool isFileEnabled = true, bool isPrintEnabled = true);

	void HandleProfilingToggleEvent(Event * e);
	void HandleFPSEvent(Event * e);
	void HandleSubsystemUpdateEvent(Event * e);

	// Store last FPS to check for changes (and prevent spam).
	int lastFPS = -1;

	// Toggle profiling state (for debug).
	bool isPrintEnabled = false;
	bool isFileEnabled = false;
};