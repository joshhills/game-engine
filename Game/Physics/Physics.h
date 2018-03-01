#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>
#include <iostream>
#include <Box2D/Box2D.h>

using namespace std;

class Physics : Subsystem {
public:
	Physics(EventManager * eventManager, vector<Entity *> * entities);
	~Physics();

	void Update();

	void HandleEvent(Event * e) override;

	/* Bespoke Event Handlers */
	void HandleMovementEvent(Event * e);

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