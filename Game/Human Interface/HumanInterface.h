#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <iostream>

#include "XboxController.h"

using namespace std;

class HumanInterface : Subsystem {
public:
	HumanInterface(EventManager * eventManager, vector<Entity *> * entities);
	~HumanInterface();

	void Update();
private:
	// Engine state.
	vector<Entity*> * entities;

	void HandleEvent(Event * e);
	void CheckForDeviceInput();

	// TODO: Store input devices
	XboxController xboxController;

	vector<Controller> controllers;
};