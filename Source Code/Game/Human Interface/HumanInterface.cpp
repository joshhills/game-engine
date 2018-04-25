#include "HumanInterface.h"
#include <Common/ControllerConnectionEvent.h>

HumanInterface::HumanInterface(EventManager * eventManager) :
	Subsystem("Human Interface", Event::HUMAN_INTERFACE, eventManager)
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

HumanInterface::~HumanInterface()
{}

void HumanInterface::Update()
{
	// Measure time taken.
	clock_t start = clock();

	Subsystem::Update();

	CheckForDeviceInput();
	CheckDeviceConnection();

	// Send time taken to complete function.
	clock_t stop = clock();
	float elapsed = (float)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	eventManager->AddEvent(new SubsystemUpdateEvent(subSystemType, elapsed));
}

void HumanInterface::CheckDeviceConnection() {
	for (Controller * controller : controllers)
	{
		if (connectionStates[controller->GetType()] != controller->IsConnected())
		{
			connectionStates[controller->GetType()] = controller->IsConnected();
			
			// Inform the rest of the engine.
			eventManager->AddEvent(new ControllerConnectionEvent(controller->GetType(), controller->IsConnected()));
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