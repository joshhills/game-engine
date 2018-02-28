#include "Graphics.h"

Graphics::Graphics(EventManager * eventManager, vector<Entity *> * entities) :
	eventManager(eventManager),
	entities(entities),
	window("Game Engine", 800, 600, false),
	renderer(window),
	logger("Graphics")
{}

Graphics::~Graphics() {}

void Graphics::Update() {
	logger.Info("Updating graphics subsystem.");

	// Get the time since last change.

	window.UpdateWindow();

	float msec = window.GetTimer()->GetTimedMS();

	renderer.UpdateScene(msec);
	renderer.ClearBuffers();
	renderer.RenderScene();
	renderer.SwapBuffers();
}

const Window & Graphics::GetWindow() const
{
	return window;
}

const Renderer & Graphics::GetRenderer() const
{
	return renderer;
}

void Graphics::CheckForEvents()
{
	logger.Info("Checking for messages in graphics subsystem.");
}

void Graphics::HandleEvent(Event * e) {
	logger.Debug("Handling event.");
}