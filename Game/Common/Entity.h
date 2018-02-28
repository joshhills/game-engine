#pragma once

#include <Graphics\GraphicsData.h>
#include <Physics\PhysicsData.h>

class Entity {
public:
	Entity();
	~Entity();

	GraphicsData * GetGraphicsData();
	PhysicsData * GetPhysicsData();
protected:
	GraphicsData * graphicsData;
	PhysicsData * physicsData;
};