#include "HumanInterface.h"

HumanInterface::HumanInterface(EventManager * eventManager, vector<Entity *> * entities) :
	Subsystem("Human Interface", Event::HUMAN_INTERFACE, eventManager),
	entities(entities)
{}

HumanInterface::~HumanInterface()
{
}

void HumanInterface::StartUp()
{
	// Initialise controllers.
	controllers.push_back(new XboxController(true, File::LoadControlMap("Settings/XboxController.cfg")));
	controllers.push_back(new KeyboardController(true, File::LoadControlMap("Settings/KeyboardController.cfg")));
}

void HumanInterface::ShutDown()
{

}

void HumanInterface::Update()
{
	Subsystem::Update();

	CheckForDeviceInput();
}

void HumanInterface::HandleEvent(Event * e) {
	logger.Debug("Handling an event.");
}

void HumanInterface::CheckForDeviceInput() {	
	for (Controller * controller : controllers)
	{
		if (controller->IsEnabled())
		{
			vector<Controller::Input> snapshot = controller->ComputeInputSnapshot();

			for (Controller::Input input : snapshot)
			{
				HandleDeviceInput(input);
			}
		}
	}

	//// Normalise the thumb stick.
	//float normLX = fmaxf(-1, (float)controllerState.Gamepad.sThumbLX / 32767);
	//float normLY = fmaxf(-1, (float)controllerState.Gamepad.sThumbLY / 32767);

	//float deadzoneX = 0.15f;
	//float deadzoneY = 0.02f;

	//float leftStickX = (abs(normLX) < deadzoneX ? 0 : normLX);
	//float leftStickY = (abs(normLY) < deadzoneY ? 0 : normLY);

	/*if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)
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
	}*/
}

void HumanInterface::HandleDeviceInput(Controller::Input input)
{
	eventManager->AddEvent(
		new InputEvent(input)
	);
}