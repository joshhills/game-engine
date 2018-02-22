#pragma once

#include <Common/Subsystem.h>
#include <Common/EventManager.h>
#include <iostream>

using namespace std;

class HumanInterface : Subsystem {
public:
	HumanInterface();
	HumanInterface(EventManager * eventManager);
	~HumanInterface();

	void Update();
private:
	EventManager * eventManager;

	void CheckForEvents();
	void HandleEvent(Event * e);
	void CheckForDeviceInput();
};