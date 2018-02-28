#include "HumanInterface.h"

#include <Common/Event.h>
#include <nclgl/Window.h>
#include <nclgl/Keyboard.h>

HumanInterface::HumanInterface(EventManager * eventManager, vector<Entity *> * entities) :
	eventManager(eventManager),
	entities(entities),
	logger("Human Interface")
{}

HumanInterface::~HumanInterface()
{
}

void HumanInterface::Update()
{
	logger.Info("Updating human interface subsystem.");

	CheckForEvents();
	CheckForDeviceInput();
}

void HumanInterface::CheckForEvents()
{
	logger.Info("Checking for messages in human interface subsystem.");
}

void HumanInterface::HandleEvent(Event * e) {
	logger.Debug("Handling an event.");
}

void HumanInterface::CheckForDeviceInput() {
	// Check keyboard.
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_W)) {
		// Create event.
		Event * e = new Event();
		e->type = Event::EventType::MOVE_UP;
		e->subsystems.push_back(Event::Subsystem::PHYSICS);

		eventManager->AddEvent(e);
	}
}