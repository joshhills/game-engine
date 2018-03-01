#include "Event.h"

Event::Event()
{}

Event::Event(EventType type) : type(type)
{}

// For simple events with only one of each.
Event::Event(EventType type, Subsystem subsystem, Entity * entity) : Event(type)
{
	AddSubsystem(subsystem)->AddEntity(entity);
}

Event::~Event()
{
}

Event * Event::AddSubsystem(Subsystem subsystem)
{
	subsystems.push_back(subsystem);
	return this;
}

Event * Event::AddEntity(Entity * entity)
{
	entities.push_back(entity);
	return this;
}
