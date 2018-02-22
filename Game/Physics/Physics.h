#pragma once

#include <Common/Subsystem.h>
#include <Common/EventManager.h>
#include <iostream>

using namespace std;

class Physics : Subsystem {
public:
	Physics();
	Physics(EventManager * eventManager);
	~Physics();

	void Update();
private:
	EventManager * eventManager;
};