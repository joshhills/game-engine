#include <string>

#include <nclgl/Window.h>
#include <SFML/Audio.hpp>

#include <Common/EventManager.h>
#include <Common/InputEvent.h>
#include <Graphics/Graphics.h>
#include <Human Interface/HumanInterface.h>
#include <Physics/Physics.h>
#include <Audio/Audio.h>
#include <Profiling/Profiling.h>
#include <Audio/AudioData.h>
#include <Resources/ResourceManager.h>

#include <Box2D\Box2D.h>

#include <Common/Logger.h>

#include "PinballEntity.h"

int main() {
	/*
	TODO:
	- Miscellaneous:
	- Make the screen better?
	- Remove dependencies that are not needed from this class
	- Create resources folder for all resources (shaders, audio etc.) X
		- Move things there.
	- Comment properly
	- Comment extended bits
	- Make example settings and level files
	
	- Profiler:
	- Toggle on/off

	- Memory Manager:
	- Store bins of common objects (entity, event); use article

	- Graphics:
	- Extend constructor
	- Make shaders for different objects.

	- File:
	- Look into the idea of a 'manifest'

	- Game:
	- Rename to core
	
	- Game:
	- Create a gameplay subsystem

	*/

	// Set logger settings for debugging purposes.
	Logger::SetLevel(Logger::INFO);
	//Logger::SetLevelExclusive(true);
	Logger::SetFilter("awdawd");

	// Create reference to events system.
	EventManager * eventManager = new EventManager();

	// Create a list of all game objects.
	vector<Entity *> entities;

	// Create references to subsystems.
	Graphics graphics(eventManager, &entities);
	Physics physics(eventManager, &entities);
	HumanInterface humanInterface(eventManager);
	Audio audio(eventManager);
	Profiling profiling(eventManager);
	ResourceManager resourceManager();

	Event * e1 = new Event(Event::AUDIO_PLAY_SOUND);
	Event * e2 = new Event(Event::CAMERA_TRACK);
	Event * e3 = new Event(Event::HUMAN_INTERFACE_CONTROLLER_CONNECTION);
	Event * e4 = new Event(Event::HUMAN_INTERFACE_INPUT);
	Event * e5 = new Event(Event::MOVE_DOWN);

	delete e1;
	delete e2;
	delete e3;
	delete e4;
	delete e5;

	//// Create entities.
	//Level l = File::LoadLevel("Levels/test.lvl", &entities);
	//SpawnTileEntity * s = dynamic_cast<SpawnTileEntity *>(l.GetSpawnTile());
	//PinballEntity * pinball = new PinballEntity(s->gridPositionX, s->gridPositionY);

	//entities.push_back(pinball);
	//////

	//// Startup
	//humanInterface.StartUp();

	//// Main game loop.
	//while (true) {
	//	// Update the graphics subsystem.
	//	graphics.Update();

	//	// Update the input device subsystem.
	//	humanInterface.Update();

	//	// React to input.
	//	vector<Event *> newEvents;
	//	for (Event * e : eventManager->GetEventQueue())
	//	{
	//		// TODO: Make this a subsystem itself?
	//		switch (e->type)
	//		{
	//			case Event::HUMAN_INTERFACE_INPUT:
	//				InputEvent * t = static_cast<InputEvent *>(e);

	//				newEvents.push_back(
	//					(new InputEvent(t->input))->AddEntity(pinball)->AddSubsystem(Event::PHYSICS)
	//				);

	//				break;
	//		}
	//	}
	//	for (Event * e : newEvents)
	//	{
	//		eventManager->AddEvent(e);
	//	}

	//	// Update the physics subsystem.
	//	physics.Update();

	//	// Update the audio subsystem.
	//	// TODO: Remove.
	//	audio.Update();

	//	// Update the profiling subsystem.
	//	profiling.Update();

	//	eventManager->RemoveFinishedEvents();

	//	// Handle quitting.

	//}

	// TODO: Delete things...
}