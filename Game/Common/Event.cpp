#include "Event.h"
#include <Resource Management/ResourceManagement.h>


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

Event::~Event()
{
	//ResourceManagement::eventStore.Remove(this);
}

//void * Event::operator new(size_t count)
//{
//	return ResourceManagement::eventStore.Add();
//}

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
