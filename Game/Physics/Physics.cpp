#include "Physics.h"

Physics::Physics() {}

Physics::Physics(EventManager * eventManager)
{
	this->eventManager = eventManager;
}

Physics::~Physics() {}

void Physics::Update() {
	cout << "Updating graphics subsystem." << endl;
}
