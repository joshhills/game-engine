#pragma once

#include "Event.h"

class PlaySoundEvent : public Event {
public:
	PlaySoundEvent(string relativePathToAudioFile, bool canStack) :
		Event(Event::AUDIO_PLAY_SOUND, Subsystem::AUDIO),
		relativePathToAudioFile(relativePathToAudioFile),
		canStack(canStack)
	{}

	// Sound string payload.
	string relativePathToAudioFile;
	// Whether the sound will override itself.
	bool canStack;
};