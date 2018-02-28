#include "Entity.h"

Entity::Entity()
{}

Entity::~Entity()
{
	delete physicsData;
	delete graphicsData;
}

GraphicsData * Entity::GetGraphicsData()
{
	return graphicsData;
}

PhysicsData * Entity::GetPhysicsData()
{
	return physicsData;
}
