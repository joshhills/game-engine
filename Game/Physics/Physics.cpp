#include "Physics.h"

Physics::~Physics() {}

Physics::Physics(EventManager * eventManager, vector<Entity *> * entities) :
	eventManager(eventManager),
	entities(entities),
	world(b2Vec2(0.0f, -10.0f)),
	logger("Physics")
{}

void Physics::Update() {
	logger.Info("Updating physics subsystem.");

	CheckForEvents();
}

void Physics::CheckForEvents()
{
	logger.Info("Checking for messages in physics subsystem.");

	// Search event queue for messages that pertain to this sub-system.
	vector<Event *> eventQueue = eventManager->GetEventQueue();
	for (int i = 0; i < eventQueue.size(); i++) {
		Event * e = eventQueue.at(i);
		vector<Event::Subsystem> subsystems = e->subsystems;
		
		if (find(subsystems.begin(), subsystems.end(), Event::Subsystem::PHYSICS) != subsystems.end()) {
			HandleEvent(e);
		}
	}
}

void Physics::HandleEvent(Event * e) {
	logger.Debug("Handling event.");
	
	switch (e->type) {
	case Event::EventType::MOVE_UP:
		HandleMovementEvent(e);
		break;
	}
}

void Physics::HandleMovementEvent(Event * e) {
	eventManager->MarkAsHandled(e, Event::Subsystem::PHYSICS);
}
