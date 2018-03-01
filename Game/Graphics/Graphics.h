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

	void HandleEvent(Event * event) override;
private:
	// Store engine state.
	vector<Entity*> * entities;

	Window window;
	Renderer renderer;
};