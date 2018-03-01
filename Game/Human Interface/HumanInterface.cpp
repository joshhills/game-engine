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
	// Check keyboard...
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		eventManager->AddEvent(
			new Event(Event::CONTROL_UP)
		);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		eventManager->AddEvent(
			new Event(Event::CONTROL_LEFT)
		);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		eventManager->AddEvent(
			new Event(Event::CONTROL_DOWN)
		);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		eventManager->AddEvent(
			new Event(Event::CONTROL_RIGHT)
		);
	}
}