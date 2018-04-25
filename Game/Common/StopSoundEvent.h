#pragma once

#include "Event.h"

class StopSoundEvent : public Event {
public:
	StopSoundEvent(string relativePathToAudioFile, bool canStack) :
		Event(Event::AUDIO_STOP_SOUND, Subsystem::AUDIO),
		relativePathToAudioFile(relativePathToAudioFile)
	{}

	// Sound string payload.
	string relativePathToAudioFile;
};