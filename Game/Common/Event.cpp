#include "Event.h"
#include <Physics/Physics.h>
#include <Resources/ResourceManager.h>

Event::Event()
{}

Event::Event(EventType type) : type(type)
{}

// For simple events with only a subsystem to notify.
Event::Event(EventType type, Subsystem subsystem) : Event(type)
{
	AddSubsystem(subsystem);
}

// For simple events with only one of each.
Event::Event(EventType type, Subsystem subsystem, Entity * entity) : Event(type)
{
	AddSubsystem(subsystem)->AddEntity(entity);
}

void * Event::operator new(size_t count)
{
	return ResourceManager::eventStore.Add();
}

Event::~Event()
{
	ResourceManager::eventStore.Remove(this);
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
