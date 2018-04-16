#include "XboxController.h"

XboxController::XboxController()
{
	// Define default controls (explicitly namespaced for clarity).
	defaultControls = {
		{ XboxController::Control::DPAD_UP, Controller::Control::UP },
		{ XboxController::Control::DPAD_DOWN, Controller::Control::DOWN },
		{ XboxController::Control::DPAD_LEFT, Controller::Control::LEFT },
		{ XboxController::Control::DPAD_RIGHT, Controller::Control::RIGHT },
		{ XboxController::Control::A, Controller::Control::PRIMARY },
		{ XboxController::Control::B, Controller::Control::SECONDARY },
		{ XboxController::Control::START, Controller::Control::PAUSE },
		{ XboxController::Control::BACK, Controller::Control::SELECT }
	};

	// TODO: Load in custom from file.
	customControls = defaultControls;

	GetHardwareControllerState();
	isConnected = XInputGetState(0, &controllerState) == ERROR_SUCCESS;
}

XboxController::~XboxController()
{}

vector<Controller::Input> XboxController::ComputeInputSnapshot()
{
	vector<Controller::Input> inputSnapshot;
	
	// Get hardware snapshot.
	GetHardwareControllerState();

	// For every kind of input, create a response object.
	if ((controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
	{
		Controller::Input input;

		// Determine control.
		// TODO: Error-handling?
		int mapping = defaultControls[XboxController::Control::A];
		input.control = static_cast<Controller::Control>(mapping);

		// Determine the state.
		if (!IsInputDown(input.control))
		{
			inputTriggeredStates[input.control] = true;
			inputDownStates[input.control] = true;

			input.state = Controller::ControlState::TRIGGERED;
		}
		else
		{
			inputTriggeredStates[input.control] = false;
			inputHoldStates[input.control] = true;

			input.state = Controller::ControlState::HELD;
		}

		// Determine amount.
		input.amount = 1;

		inputSnapshot.push_back(input);
	}
	else
	{
		Controller::Input input;
		int mapping = defaultControls[XboxController::Control::A];
		input.control = static_cast<Controller::Control>(mapping);
		input.amount = 0;
		input.state = Controller::ControlState::NONE;
		inputSnapshot.push_back(input);

		// Reset the state.
		inputTriggeredStates[input.control] = false;
		inputDownStates[input.control] = false;
		inputHoldStates[input.control] = false;
	}

	// Store it as latest input.
	lastInputSnapshot = inputSnapshot;
	return lastInputSnapshot;
}

void XboxController::UpdateInput()
{
	lastInputSnapshot = GetInputSnapshot();
}