#include "Profiling.h"

Profiling::Profiling(EventManager * eventManager) :
	Subsystem("Profiling", Event::PROFILING, eventManager)
{
	// Create function map using lambdas to handle events.
	eventMap[Event::PROFILING_TOGGLE] = [this](Event * e) { HandleProfilingToggleEvent(e); };
	eventMap[Event::PROFILING_FPS] = [this](Event * e) { HandleFPSEvent(e); };
	eventMap[Event::PROFILING_SUBSYSTEM_UPDATE] = [this](Event * e) { HandleSubsystemUpdateEvent(e); };
}

Profiling::~Profiling()
{}

void Profiling::HandleProfilingToggleEvent(Event * e)
{
	// Invert logging variables.
	isPrintEnabled = !isPrintEnabled;
	isFileEnabled = !isFileEnabled;
}

void Profiling::HandleFPSEvent(Event * e)
{
	// Convert the event pointer to the correct format.
	FPSEvent * fe = static_cast<FPSEvent *>(e);
	lastFPS = fe->fps;

	// Only print if profiling is turned on.
	string printStr = "FPS is " + to_string(lastFPS);
	Report(printStr, false);
}

void Profiling::HandleSubsystemUpdateEvent(Event * e)
{
	// Convert the event pointer to the correct format.
	SubsystemUpdateEvent * se = static_cast<SubsystemUpdateEvent *>(e);

	// Only print if profiling is turned on.
	string printStr = "Subsystem " + to_string(se->subsystem) + " took " + to_string(se->msElapsed) + "ms to complete";
	Report(printStr);
}

void Profiling::Report(string content, bool isFileEnabled, bool isPrintEnabled)
{
	if (isFileEnabled && this->isFileEnabled)
	{
		File::WriteToFile("Logs/log.txt", content);
	}
	if (isPrintEnabled && this->isPrintEnabled)
	{
		logger.Info(content);
	}
}