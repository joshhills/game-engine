#include "Graphics.h"

Graphics::Graphics(EventManager * eventManager, vector<Entity *> * entities) :
	Subsystem("Graphics", Event::GRAPHICS, eventManager),
	entities(entities),
	window("Game Engine", 800, 600, false),
	renderer(window)
{
	// Renderer settings.
	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 90.0f));
	renderer.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 10, -15), Vector3(0, 10, -10)));

	// TODO: Camera!
}

Graphics::~Graphics() {}

void Graphics::Update() {
	// Measure time taken.
	clock_t start = clock();

	Subsystem::Update();

	// Update the 3rd party library.
	window.UpdateWindow();
	
	// Update the graphics objects based of their entity (physics, currently -) data.
	for (auto entity : *entities)
	{
		// If there is graphics data to enact upon.
		if (entity->GetGraphicsData() != nullptr)
		{
			GameObject * gameObject = entity->GetGameObject();
			RenderObject * renderObject = &(entity->GetGraphicsData()->GetRenderObject());

			// Set the graphics data accordingly.
			// TODO: Make a constructor in nclgl Matrix4 to take in a game object.
			Matrix4 newPosition = Matrix4::Translation(
				Vector3(gameObject->x, gameObject->y, 0))
				* Matrix4::Rotation(gameObject->rotation, Vector3(0, 0, 1))
				* Matrix4::Scale(Vector3(1, 1, 1));

			// Update the local position.
			renderObject->SetModelMatrix(
				newPosition
			);

			// Update the world position relative to scene graph.
			renderObject->Update();
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

	/* Profiling operations. */

	// Send an FPS update event to profiler.
	eventManager->AddEvent(new FPSEvent(ComputeFPS()));

	// Send time taken to complete function.
	clock_t stop = clock();
	float elapsed = (float)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	eventManager->AddEvent(new SubsystemUpdateEvent(subSystemType, elapsed));
}

float Graphics::ComputeFPS() {
	return 1000 / window.GetTimer()->GetTimedMS();
}

const Window & Graphics::GetWindow() const
{
	return window;
}

const Renderer & Graphics::GetRenderer() const
{
	return renderer;
}

void Graphics::HandleEvent(Event * e) {
	logger.Debug("Handling event.");
}