#pragma once

#include <Common/Subsystem.h>
#include <Common/SubsystemLifecycle.h>
#include <Common/Event.h>
#include <Common/InputEvent.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <iostream>

#include "Controller.h"
#include "KeyboardController.h"
#include "XboxController.h"

using namespace std;

class HumanInterface : Subsystem, SubsystemLifecycle {
public:
	HumanInterface(EventManager * eventManager, vector<Entity *> * entities);
	~HumanInterface();

	void StartUp() override;
	void ShutDown() override;

	void Update() override;
private:
	// Engine state.
	vector<Entity*> * entities;
	void HandleEvent(Event * e);

	// Create events.
	void CheckForDeviceInput();
	void HandleDeviceInput(Controller::Input input);

	vector<Controller *> controllers;
};