#include "Graphics.h"

Graphics::Graphics(): window("Game Engine", 800, 600, false), renderer(window) {}

Graphics::Graphics(EventManager * eventManager) : Graphics()
{
	this->eventManager = eventManager;
}

Graphics::~Graphics() {}

void Graphics::Update() {
	cout << "Updating graphics subsystem." << endl;

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
