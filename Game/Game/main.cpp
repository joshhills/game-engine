#include <string>

#include <nclgl/Window.h>

#include <Common/EventManager.h>
#include <Graphics/Graphics.h>
#include <Human Interface/HumanInterface.h>
#include <Physics/Physics.h>

#include <Box2D\Box2D.h>

#include <Common/Logger.h>

#include "CubeEntity.h"
#include "FloorEntity.h"

int main() {
	/*
	TODO:
	- Add a camera
	- Remove dependencies that are not needed from this class
	*/

	// Set logger settings for debugging purposes.
	Logger::SetLevel(Logger::DEBUG);
	Logger::SetLevelExclusive(true);
	//Logger::SetFilter("Physics");

	// Create reference to events system.
	EventManager * eventManager = new EventManager();

	// Create a list of all game objects.
	vector<Entity *> entities;

	// Create references to subsystems.
	Graphics graphics(eventManager, &entities);
	Physics physics(eventManager, &entities);
	HumanInterface humanInterface(eventManager, &entities);

	// Create entities.
	entities.push_back(new FloorEntity());
	entities.push_back(new CubeEntity());

	// Main game loop.
	while (true) {
		// Update the graphics subsystem.
		graphics.Update();

		// Update the input device subsystem.
		humanInterface.Update();

		// React to input.
		for (auto e : eventManager->GetEventQueue())
		{

		}

		// Update the physics subsystem.
		physics.Update();

		eventManager->RemoveFinishedEvents();

		// Handle quitting.


		// Box2D
		/*world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		b2Vec2 position2 = body->GetPosition();
		float32 angle2 = body->GetAngle();

		o.SetModelMatrix(Matrix4::Translation(Vector3(position.x, position.y, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));
		o.SetModelMatrix(Matrix4::Translation(Vector3(position2.x, position2.y, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));*/
	}

	/**/

	//delete m;
	//delete s;
}