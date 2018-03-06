#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <iostream>

using namespace std;

class Audio : Subsystem {
public:
	Audio(EventManager * eventManager, vector<Entity *> * entities);
	~Audio();

	void Update();

	/* Bespoke Event Handlers */
	void PlaySound(Event * e);

private:
	// Engine state.
	vector<Entity*> * entities;

	// TODO: Needs a listener (attached to the camera?)
};