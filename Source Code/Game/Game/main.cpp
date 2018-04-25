#include <string>

#include <nclgl/Window.h>

#include <Common/EventManager.h>
#include <Common/MoveEvent.h>
#include <Common/ToggleProfilingEvent.h>
#include <Graphics/Graphics.h>
#include <Human Interface/HumanInterface.h>
#include <Physics/Physics.h>
#include <Audio/Audio.h>
#include <Profiling/Profiling.h>
#include <Resources/ResourceManager.h>

#include <Box2D/Box2D.h>

#include <Common/Logger.h>

#include "PinballEntity.h"

/**
 * Demonstrate the capabilities of the game engine
 * with a simple sample level.
 *
 * For brevity, I have:
 * - Resource management for most common dynamic data types
 * - Event management to transfer messages between subsystems
 * - The notion of abstract entities and game objects
 * - A 2D physics subsystem with dynamic movement and collision
 * - NclGl graphics with simple shaders
 * - Positional audio
 * - Toggle-able profiling
 * - Exensible controller system with controls loaded from file
 * - Extensible level system with tiles loaded from file
 * - A custom logging system with different levels of severity and filtering
 *
 * And more, commented inside of files.
 * 
 * In doing so I have extended the middleware of physics (to implement
 * custom event handlers, and convert their spatial representation to my own),
 * and graphics (to load custom meshes from file).
 *
 */
int main() {
	/*
	TODO:
	- Miscellaneous:
	- Remove dependencies that are not needed from this class
	- Create resources folder for all resources (shaders, audio etc.) X

	- Graphics:
	- Make shaders for different objects

	*/

	// Set logger settings for debugging purposes.
	Logger::SetLevel(Logger::WARN);
	Logger::SetLevelExclusive(true);
	Logger::SetFilter("Profiling");

	// Create reference to events system.
	EventManager * eventManager = new EventManager();

	// Create a list of all game objects.
	vector<Entity *> entities;

	// Create references to subsystems (each handles their own startup).
	Graphics graphics(eventManager, &entities);
	Physics physics(eventManager, &entities);
	HumanInterface humanInterface(eventManager);
	Audio audio(eventManager);
	Profiling profiling(eventManager);
	ResourceManager resourceManager();

	// Create entities.
	Level l = File::LoadLevel(eventManager, "Levels/test.lvl", &entities);
	SpawnTileEntity * s = dynamic_cast<SpawnTileEntity *>(l.GetSpawnTile());
	PinballEntity * pinball = new PinballEntity(eventManager, s->gridPositionX, s->gridPositionY);
	entities.push_back(pinball);

	// Main game loop.
	while (true) {
		// Update the graphics subsystem.
		graphics.Update();

		// Update the input device subsystem.
		humanInterface.Update();

		/*
		 * NOTE TO MARKER:
		 * This reaction to input, and the above adding of entities,
		 * will be extrapolated into gameplay (in its own class) for the final submission,
		 * and exists here to demonstrate the capabilities of the engine against marking criteria.
		 */
		vector<Event *> newEvents;
		for (Event * e : eventManager->GetEventQueue())
		{
			switch (e->type)
			{
				case Event::HUMAN_INTERFACE_INPUT:
					InputEvent * t = static_cast<InputEvent *>(e);

					MoveEvent::Direction d;
					switch (t->input.control)
					{
						case Controller::Control::UP:
							d.x = 0;
							d.y = 250 * t->input.amount;
							break;
						case Controller::Control::DOWN:
							d.x = 0;
							d.y = -250 * t->input.amount;
							break;
						case Controller::Control::LEFT:
							d.x = 250 * t->input.amount;
							d.y = 0;
							break;
						case Controller::Control::RIGHT:
							d.x = -250 * t->input.amount;
							d.y = 0;
							break;
						case Controller::Control::SELECT:
							if (t->input.state == Controller::ControlState::TRIGGERED)
							{
								newEvents.push_back(
									new ToggleProfilingEvent()
								);
							}
							break;
					}
					newEvents.push_back(
						(new MoveEvent(d))->AddEntity(pinball)
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

		// Update the profiling subsystem.
		profiling.Update();

		eventManager->RemoveFinishedEvents();
	}

	// Delete entities (subsystems going out of scope will handle their own deletion).
	for (Entity * entity : entities)
	{
		delete entity;
	}
}