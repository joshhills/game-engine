#include <string>

#include <nclgl/Window.h>
#include <SFML/Audio.hpp>

#include <Common/EventManager.h>
#include <Common/InputEvent.h>
#include <Graphics/Graphics.h>
#include <Human Interface/HumanInterface.h>
#include <Physics/Physics.h>
#include <Audio/Audio.h>
#include <Audio/AudioData.h>

#include <Box2D\Box2D.h>

#include <Common/Logger.h>

#include "CubeEntity.h"
#include "FloorEntity.h"

int main() {
	/*
	TODO:
	- Add a camera
	- Remove dependencies that are not needed from this class
	- Create resources folder for all resources (shaders, audio etc.)
	*/

	// Set logger settings for debugging purposes.
	Logger::SetLevel(Logger::WARN);
	//Logger::SetLevelExclusive(true);
	Logger::SetFilter("Audio");

	// Create reference to events system.
	EventManager * eventManager = new EventManager();

	// Create a list of all game objects.
	vector<Entity *> entities;

	// Create references to subsystems.
	Graphics graphics(eventManager, &entities);
	Physics physics(eventManager, &entities);
	HumanInterface humanInterface(eventManager, &entities);
	Audio audio(eventManager, &entities);

	// Create entities.
	CubeEntity * player = new CubeEntity();

	entities.push_back(new FloorEntity());
	entities.push_back(player);

	// Main game loop.
	while (true) {
		// Update the graphics subsystem.
		graphics.Update();

		// Update the input device subsystem.
		humanInterface.Update();

		// React to input.
		vector<Event *> newEvents;
		for (Event * e : eventManager->GetEventQueue())
		{
			// TODO: Make this a subsystem itself?
			switch (e->type)
			{
				case Event::INPUT:
					InputEvent * t = static_cast<InputEvent *>(e);

					newEvents.push_back(
						(new InputEvent(t->input))->AddEntity(player)->AddSubsystem(Event::PHYSICS)
					);

					break;
			}
		}

		for (Event * e : newEvents)
		{
			eventManager->AddEvent(e);
		}

		// Update the physics subsystem.
		physics.Update();

		// Update the audio subsystem.
		audio.Update();

		eventManager->RemoveFinishedEvents();

		// Handle quitting.

	}

	// TODO: Delete things...
}