#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>

#include <Box2D/Box2D.h>

#include <iostream>
#include <nclgl/Window.h>
#include "Renderer.h"

using namespace std;

class Graphics : Subsystem {
public:
	Graphics(EventManager * eventManager, vector<Entity *> * entities);
	~Graphics();

	void Update();

	const Window & GetWindow() const;
	const Renderer & GetRenderer() const;

	void CheckForEvents();
	void HandleEvent(Event * event);
private:
	// Engine utility.
	LoggerInstance logger;

	// Store engine state.
	EventManager * eventManager;
	vector<Entity*> * entities;

	Window window;
	Renderer renderer;
};