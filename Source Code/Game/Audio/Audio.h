#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <Common/PlaySoundEvent.h>
#include <Common/PlayMusicEvent.h>
#include <Common/SubsystemUpdateEvent.h>
#include <Common/StopSoundEvent.h>
#include <iostream>
#include <map>
#include "AudioData.h"

using namespace std;

class Audio : Subsystem {
public:
	Audio(EventManager * eventManager);
	~Audio();

	void Update() override;
private:
	/* Bespoke Event Handlers */
	void HandlePlaySoundEvent(Event * e);
	void HandleStopSoundEvent(Event * e);

	void HandlePlayMusicEvent(Event * e);

	void StopAll();

	// Store a map of all sounds.
	map<string, AudioData *> sounds;

	// Store a reference to a single music file (for overall music like background)
	sf::Music music;
};