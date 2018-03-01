#include "Subsystem.h"

Subsystem::Subsystem(string id, Event::Subsystem subSystemType, EventManager * eventManager) :
	id(id),
	subSystemType(subSystemType),
	eventManager(eventManager),
	logger(id)
{}

Subsystem::~Subsystem()
{}
