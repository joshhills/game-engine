#pragma once

#include "GameObject.h"
#include <Graphics\GraphicsData.h>
#include <Physics\PhysicsData.h>

class Entity {
public:
	Entity();
	~Entity();

	GameObject * GetGameObject();
	GraphicsData * GetGraphicsData();
	PhysicsData * GetPhysicsData();
protected:
	GameObject * gameObject;
	GraphicsData * graphicsData;
	PhysicsData * physicsData;
};