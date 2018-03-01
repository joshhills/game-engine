#include "Entity.h"

Entity::Entity() : gameObject(new GameObject())
{}

Entity::~Entity()
{
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
