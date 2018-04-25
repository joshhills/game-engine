#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

GraphicsData * Entity::GetGraphicsData()
{
	return graphicsData;
}

PhysicsData * Entity::GetPhysicsData()
{
	return physicsData;
}
