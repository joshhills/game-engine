#pragma once

#include <Common/Subsystem.h>
#include <Common/EventManager.h>

#include <iostream>
#include <nclgl/Window.h>
#include "Renderer.h"

using namespace std;

class Graphics : Subsystem {
public:
	Graphics::Graphics();
	Graphics(EventManager * eventManager);
	~Graphics();

	void Update();

	const Window & GetWindow() const;
	const Renderer & GetRenderer() const;

	void CheckForEvents();
	void HandleEvent(Event * event);
private:
	EventManager * eventManager;

	Window window;
	Renderer renderer;
};