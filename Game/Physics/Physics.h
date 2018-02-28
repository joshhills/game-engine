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

	void CheckForEvents();
	void HandleEvent(Event * e);

	void HandleMovementEvent(Event * e);
private:
	// Engine utility.
	LoggerInstance logger;

	// Engine state.
	EventManager * eventManager;
	vector<Entity*> * entities;

	// Configuration.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// Pre-requisites.
	b2World world;
};