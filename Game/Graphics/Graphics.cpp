#include "Graphics.h"

Graphics::Graphics(EventManager * eventManager, vector<Entity *> * entities) :
	eventManager(eventManager),
	entities(entities),
	window("Game Engine", 800, 600, false),
	renderer(window),
	logger("Graphics")
{
	// Renderer settings.
	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 90.0f));
	renderer.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 10, -15), Vector3(0, 10, -10)));

	// TODO: Camera!
}

Graphics::~Graphics() {}

void Graphics::Update() {
	logger.Info("Updating graphics subsystem.");

	window.UpdateWindow();
	
	// Update the graphics objects based of their entity (physics, currently -) data.
	// TODO: Decouple this..
	for (auto entity : *entities)
	{
		// If there is graphics data to enact upon.
		if (entity->GetGraphicsData() != nullptr)
		{
			// Extract the current position and rotation.
			b2Vec2 position = entity->GetPhysicsData()->GetBody()->GetPosition();
			float32 angle = entity->GetPhysicsData()->GetBody()->GetAngle();

			logger.Debug("Position is x: " + to_string(position.x) + ", y: " + to_string(position.y));

			// Set the graphics data accordingly.
			Matrix4 newPosition = Matrix4::Translation(
				Vector3(position.x, position.y, 0))
				* Matrix4::Rotation(angle, Vector3(0, 0, 1))
				* Matrix4::Scale(Vector3(1, 1, 1));

			entity->GetGraphicsData()->GetRenderObject().SetModelMatrix(
				newPosition
			);

			entity->GetGraphicsData()->GetRenderObject().Update();
		}
	}

	renderer.ClearBuffers();
	
	// Render scene objects from graphical data.
	for (auto entity: *entities)
	{
		// If there is graphics data to enact upon.
		if (entity->GetGraphicsData() != nullptr)
		{
			renderer.Render(entity->GetGraphicsData()->GetRenderObject());
		}
	}

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