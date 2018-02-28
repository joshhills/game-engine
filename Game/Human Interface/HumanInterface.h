#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <iostream>

using namespace std;

class HumanInterface : Subsystem {
public:
	HumanInterface(EventManager * eventManager, vector<Entity *> * entities);
	~HumanInterface();

	void Update();
private:
	// Engine utility.
	LoggerInstance logger;

	// Engine state.
	EventManager * eventManager;
	vector<Entity*> * entities;

	void CheckForEvents();
	void HandleEvent(Event * e);
	void CheckForDeviceInput();
};