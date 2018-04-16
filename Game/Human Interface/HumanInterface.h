#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <iostream>

#include "Controller.h"
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

	// Create events.
	void CheckForDeviceInput();
	void HandleDeviceInput(Controller::Input input);

	vector<Controller *> controllers;
};