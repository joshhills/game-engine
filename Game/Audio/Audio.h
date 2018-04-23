#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <iostream>

using namespace std;

class Audio : Subsystem {
public:
	Audio(EventManager * eventManager);
	~Audio();

	void Update();

	/* Bespoke Event Handlers */
	void PlaySound(Event * e);

private:

	// TODO: Needs a listener (attached to the camera?)
};