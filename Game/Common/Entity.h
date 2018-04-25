#pragma once

#include "GameObject.h"
#include <Graphics/GraphicsData.h>
#include <Physics/PhysicsData.h>
class EventManager;

class Entity {
public:
	Entity(EventManager * eventManager);
	virtual ~Entity();

	GameObject * GetGameObject();
	GraphicsData * GetGraphicsData();
	PhysicsData * GetPhysicsData();

	// Override 'new' and 'delete' for resource management.
	void * operator new(size_t count);
	void operator delete(void * ptr);
protected:
	GameObject * gameObject;
	GraphicsData * graphicsData;
	PhysicsData * physicsData;

	EventManager * eventManager;
};