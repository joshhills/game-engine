#pragma once

#include <iostream>
#include <Box2D/Box2D.h>

#include <Common/Subsystem.h>
#include <Common/Movement.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <Common/MoveEvent.h>
#include "ContactListener.h"
#include <Common/SubsystemUpdateEvent.h>

using namespace std;

class Physics : Subsystem {
public:
	Physics(EventManager * eventManager, vector<Entity *> * entities);
	~Physics();

	void Update();

	// Middleware prerequisite.
	static b2World world;
private:
	// Engine state.
	vector<Entity*> * entities;

	// Instance of contact listener used by Box2D to resolve collisions.
	ContactListener i;

	float32 timeStep = 1.0f / 60.0f; // The delta time the system should update each frame.
	int32 velocityIterations = 6;	 // The number of velocity calculation passes. 
	int32 positionIterations = 2;	 // The number of position calculation passes. 
	
	/* Bespoke Event Handlers */
	void HandleMoveEvent(Event * e);

	/**
	* Shortcut method for altering the
	* physics data of an entity.
	*
	* @param e		The entity to move.
	* @param force	The vector to apply force.
	*/
	static void Move(Entity * e, b2Vec2 force);
};