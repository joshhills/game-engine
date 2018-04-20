#include "Profiling.h"

Profiling::Profiling(EventManager * eventManager) :
	Subsystem("Profiling", Event::PROFILING, eventManager)
{
	// Create function map using lambdas to handle events.
	eventMap[Event::PROFILING_FPS] = [this](Event * e) { HandleFPSEvent(e); };
	eventMap[Event::PROFILING_SUBSYSTEM_UPDATE] = [this](Event * e) { HandleSubsystemUpdateEvent(e); };
}
