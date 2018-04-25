#pragma once

#include "Event.h"

class PlaySoundEvent : public Event {
public:
	PlaySoundEvent(string relativePathToAudioFile, bool canStack, float x, float y) :
		Event(Event::AUDIO_PLAY_SOUND, Subsystem::AUDIO),
		relativePathToAudioFile(relativePathToAudioFile),
		canStack(canStack),
		x(x),
		y(y)
	{}

	// Sound string payload.
	string relativePathToAudioFile;
	// Whether the sound will override itself.
	bool canStack;
	// Positional audio.
	float x, y;
};