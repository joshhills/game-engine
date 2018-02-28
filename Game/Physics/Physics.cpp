#include "Physics.h"

Physics::Physics(EventManager * eventManager) : world(b2Vec2(0.0f, -10.0f))
{
	this->eventManager = eventManager;
}

Physics::~Physics() {}

void Physics::Update() {
	cout << "Updating graphics subsystem." << endl;
}

void Physics::CheckForEvents()
{
	cout << "Checking for messages in physics subsystem." << endl;

	// Search event queue for messages that pertain to this sub-system.
	//vector<Event *> eventQueue = eventManager->GetEventQueue();
	//for (int i = 0; i < eventQueue.size; i++) {
	//	Event * e = eventQueue.at(i);
	//	vector<Event::Subsystem> subsystems = e->subsystems;
	//	
	//	if (find(subsystems.begin(), subsystems.end(), Event::Subsystem::PHYSICS) != subsystems.end()) {
	//		HandleEvent(e);
	//	}
	//}
}

void Physics::HandleEvent(Event * e) {
	//switch (e->type) {
	//case Event::EventType::MOVE_UP:
	//	
	//}
}
