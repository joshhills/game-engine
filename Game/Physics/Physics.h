#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <Common/InputEvent.h>
#include <iostream>
#include <Box2D/Box2D.h>

using namespace std;

class Physics : Subsystem {
public:
	Physics(EventManager * eventManager, vector<Entity *> * entities);
	~Physics();

	void Update();

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

	// TODO: Is there a better way to attach entities to a world?
	// Middleware prerequisite.
	static b2World world;
private:
	// Engine state.
	vector<Entity*> * entities;

	float32 timeStep = 1.0f / 60.0f; // The delta time the system should update each frame.
	int32 velocityIterations = 6;	 // The number of velocity calculation passes. 
	int32 positionIterations = 2;	 // The number of position calculation passes. 
};