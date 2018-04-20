#include "HumanInterface.h"

HumanInterface::HumanInterface(EventManager * eventManager) :
	Subsystem("Human Interface", Event::HUMAN_INTERFACE, eventManager)
{}

HumanInterface::~HumanInterface()
{
}

void HumanInterface::StartUp()
{
	// Initialise controllers.
	controllers.push_back(new XboxController(true, File::LoadControlMap("Settings/XboxController.cfg")));
	controllers.push_back(new KeyboardController(true, File::LoadControlMap("Settings/KeyboardController.cfg")));

	// Set their connection states.
	for (Controller * controller : controllers)
	{
		connectionStates[controller->GetType()] = controller->IsConnected();
	}
}

void HumanInterface::ShutDown()
{
	// Disconnect controllers.
}

void HumanInterface::Update()
{
	Subsystem::Update();

	CheckForDeviceInput();
	CheckDeviceConnection();
}

void HumanInterface::CheckDeviceConnection() {
	for (Controller * controller : controllers)
	{
		if (connectionStates[controller->GetType()] != controller->IsConnected())
		{
			// TODO: Create controller connection event.
			connectionStates[controller->GetType()] = controller->IsConnected();
		}
	}
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
}

void HumanInterface::HandleDeviceInput(Controller::Input input)
{
	eventManager->AddEvent(
		new InputEvent(input)
	);
}