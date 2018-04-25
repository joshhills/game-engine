#pragma once

#include <Common/Subsystem.h>
#include <Common/Event.h>
#include <File/File.h>
#include <Common/InputEvent.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <Common/SubsystemUpdateEvent.h>
#include <iostream>

#include "Controller.h"
#include "KeyboardController.h"
#include "XboxController.h"

using namespace std;

class HumanInterface : Subsystem {
public:
	HumanInterface(EventManager * eventManager);
	~HumanInterface();

	void Update() override;
private:
	void CheckForDeviceInput();
	void CheckDeviceConnection();
	void HandleDeviceInput(Controller::Input input);

	vector<Controller *> controllers;
	map<int, bool> connectionStates;
};