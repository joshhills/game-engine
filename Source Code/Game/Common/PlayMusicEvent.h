#pragma once

#include "Event.h"

class PlayMusicEvent : public Event {
public:
	PlayMusicEvent(string relativePathToAudioFile, bool canStack, float x, float y) :
		Event(Event::AUDIO_PLAY_SOUND, Subsystem::AUDIO),
		relativePathToAudioFile(relativePathToAudioFile),
		x(x),
		y(y)
	{}

	// Sound string payload.
	string relativePathToAudioFile;

	// Positional audio.
	float x, y;
};