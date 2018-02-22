#include "HumanInterface.h"

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

	checkForDeviceInput();
}

void HumanInterface::checkForDeviceInput() {
	// Check keyboard.
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		// Create event.
		cout << "Pressed W"<< endl;
	}
}