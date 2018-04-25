#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <Common/PlaySoundEvent.h>
#include <Common/StopSoundEvent.h>
#include <iostream>
#include <map>
//#include "AudioData.h"

using namespace std;

class Audio : Subsystem {
public:
	Audio(EventManager * eventManager);
	~Audio();

	void Update() override {
		Subsystem::Update();
	}
private:
	/* Bespoke Event Handlers */
	//void HandlePlayMusicEvent(Event * e);
	//void HandleStopMusicEvent(Event * e);

	void HandlePlaySoundEvent(Event * e);
	void HandleStopSoundEvent(Event * e);

	//void StopAllSounds();

	// Store a map of all sounds.
	//map<string, AudioData> sounds;#include <SFML/Audio.hpp>

	// Store a map of all music.
	//map<string, sf::Sound> music;
};