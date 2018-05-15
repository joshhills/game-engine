#include "Entity.h"
#include <Resources/ResourceManager.h>
#include <Common/EventManager.h>

Entity::Entity(EventManager * eventManager) : eventManager(eventManager), gameObject(new GameObject())
{}

Entity::~Entity()
{
	// Clean up pointers to other units of data.
	delete gameObject;
	delete physicsData;
	delete graphicsData;
}

GameObject * Entity::GetGameObject()
{
	return gameObject;
}

GraphicsData * Entity::GetGraphicsData()
{
	return graphicsData;
}

PhysicsData * Entity::GetPhysicsData()
{
	return physicsData;
}

void * Entity::operator new(size_t count)
{
	return ResourceManager::entityStore.Add();
}

void Entity::operator delete(void * ptr)
{
	ResourceManager::entityStore.Remove(ptr);
}

void Entity::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}

bool Entity::IsEnabled()
{
	return enabled;
}

void Entity::SetTransparent(bool transparent)
{
	this->transparent = transparent;
}

bool Entity::IsTransparent()
{
	return transparent;
}
