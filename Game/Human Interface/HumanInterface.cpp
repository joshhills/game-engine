#include "HumanInterface.h"

#include <Common/Event.h>
#include <nclgl/Window.h>
#include <nclgl/Keyboard.h>

HumanInterface::HumanInterface()
{
}

HumanInterface::HumanInterface(EventManager * eventManager)
{
	this->eventManager = eventManager;
}

HumanInterface::~HumanInterface()
{
}

void HumanInterface::Update()
{
	cout << "Updating human interface subsystem." << endl;

	CheckForEvents();
	CheckForDeviceInput();
}

void HumanInterface::CheckForEvents()
{
	cout << "Checking for messages in human interface subsystem." << endl;
}

void HumanInterface::HandleEvent(Event * e) {

}

void HumanInterface::CheckForDeviceInput() {
	// Check keyboard.
	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_W)) {
		// Create event.
		Event e = Event();
		e.type = Event::EventType::MOVE_UP;
		e.subsystems.push_back(Event::Subsystem::PHYSICS);
	}
}