#include "HumanInterface.h"

#include <Common/Event.h>
#include <nclgl/Window.h>
#include <nclgl/Keyboard.h>

HumanInterface::HumanInterface(EventManager * eventManager, vector<Entity *> * entities) :
	Subsystem("Human Interface", Event::HUMAN_INTERFACE, eventManager),
	entities(entities)
{}

HumanInterface::~HumanInterface()
{
}

void HumanInterface::Update()
{
	logger.Info("Updating human interface subsystem.");

	HandleEvents();
	CheckForDeviceInput();
}

void HumanInterface::HandleEvent(Event * e) {
	logger.Debug("Handling an event.");
}

void HumanInterface::CheckForDeviceInput() {
	// Check keyboard.
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		// Create event.
		Event * e = new Event();
		e->type = Event::EventType::MOVE_UP;
		e->subsystems.push_back(Event::Subsystem::PHYSICS);

		eventManager->AddEvent(e);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		// Create event.
		Event * e = new Event();
		e->type = Event::EventType::MOVE_LEFT;
		e->subsystems.push_back(Event::Subsystem::PHYSICS);

		eventManager->AddEvent(e);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		// Create event.
		Event * e = new Event();
		e->type = Event::EventType::MOVE_DOWN;
		e->subsystems.push_back(Event::Subsystem::PHYSICS);

		eventManager->AddEvent(e);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		// Create event.
		Event * e = new Event();
		e->type = Event::EventType::MOVE_RIGHT;
		e->subsystems.push_back(Event::Subsystem::PHYSICS);

		eventManager->AddEvent(e);
	}
}