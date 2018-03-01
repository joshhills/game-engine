#include "Subsystem.h"

Subsystem::Subsystem(string id, Event::Subsystem eventType, EventManager * eventManager) :
	eventType(eventType),
	id(id),
	eventManager(eventManager),
	logger(id)
{}

Subsystem::~Subsystem()
{}
