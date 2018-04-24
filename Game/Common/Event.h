#pragma once

#include <vector>
#include "Entity.h"


using namespace std;

class Event {
public: 
	// Enum describing available subsystems.
	enum Subsystem {
		PHYSICS = 0,
		GRAPHICS = 1,
		HUMAN_INTERFACE = 2,
		AUDIO = 3,
		FILE = 4,
		RESOURCE_MANAGEMENT = 5,
		PROFILING = 6
	};

	// Enum describing kinds of events that may occur.
	enum EventType {
		// Graphics
		CAMERA_TRACK,

		// Physics
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT, 
		MOVE_RIGHT,

		// Audio
		AUDIO_PLAY_SOUND,

		// Human Interface
		HUMAN_INTERFACE_INPUT,
		HUMAN_INTERFACE_CONTROLLER_CONNECTION,

		// Profiling
		PROFILING_TOGGLE,
		PROFILING_FPS,
		PROFILING_SUBSYSTEM_UPDATE,
	};

	Event();
	Event(EventType type);
	Event(EventType type, Subsystem subsystem);
	Event(EventType type, Subsystem subsystem, Entity * entity);

	~Event();

	// Override new for resource management.
	//void * operator new (size_t count);

	// Builder pattern for simple event creation.
	Event * AddSubsystem(Subsystem subsystem);
	Event * AddEntity(Entity * entity);

	// Releated subsystems to be informed of the event.
	vector<Subsystem> subsystems;

	// Entities associated with this event.
	vector<Entity *> entities;

	// The explicit type of event that occured.
	EventType type;
};