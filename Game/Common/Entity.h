#pragma once

#include <Graphics\GraphicsData.h>
#include <Physics\PhysicsData.h>

class Entity {
public:
	Entity();
	~Entity();

	GraphicsData * GetGraphicsData();
	PhysicsData * GetPhysicsData();
private:
	GraphicsData * graphicsData;
	PhysicsData * physicsData;
};