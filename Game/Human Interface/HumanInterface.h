#pragma once

#include <Common/Subsystem.h>
#include <Common/SubsystemLifecycle.h>
#include <Common/Event.h>
#include <File/File.h>
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
	HumanInterface(EventManager * eventManager);
	~HumanInterface();

	void StartUp() override;
	void ShutDown() override;

	void Update() override;
private:
	void CheckForDeviceInput();
	void CheckDeviceConnection();
	void HandleDeviceInput(Controller::Input input);

	vector<Controller *> controllers;
	map<int, bool> connectionStates;
};