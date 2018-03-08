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
	// TODO: Sequester into a new class.
	// Check keyboard and xbox controller...

	// Get Xbox controller input...
	XINPUT_STATE controllerState = xboxController.GetControllerState();
	// Normalise the thumb stick.
	float normLX = fmaxf(-1, (float)controllerState.Gamepad.sThumbLX / 32767);
	float normLY = fmaxf(-1, (float)controllerState.Gamepad.sThumbLY / 32767);

	float deadzoneX = 0.15f;
	float deadzoneY = 0.02f;

	float leftStickX = (abs(normLX) < deadzoneX ? 0 : normLX);
	float leftStickY = (abs(normLY) < deadzoneY ? 0 : normLY);

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)
		|| (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
		eventManager->AddEvent(
			new Event(Event::CONTROL_UP)
		);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)
		|| leftStickX < 0) {
		eventManager->AddEvent(
			new Event(Event::CONTROL_LEFT)
		);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		eventManager->AddEvent(
			new Event(Event::CONTROL_DOWN)
		);
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)
		|| leftStickX > 0) {
		eventManager->AddEvent(
			new Event(Event::CONTROL_RIGHT)
		);
	}
}