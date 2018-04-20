#include "XboxController.h"
#include <iostream>

XboxController::XboxController(bool isEnabled, std::map<int, int> customControls) : Controller("XboxController")
{
	// Define default controls (explicitly namespaced for clarity).
	defaultControls = {
		{ XboxController::Control::DPAD_UP,			 Controller::Control::UP },
		{ XboxController::Control::DPAD_LEFT,		 Controller::Control::LEFT },
		{ XboxController::Control::DPAD_DOWN,		 Controller::Control::DOWN },
		{ XboxController::Control::DPAD_RIGHT,		 Controller::Control::RIGHT },
		{ XboxController::Control::LEFT_STICK_UP,	 Controller::Control::UP },
		{ XboxController::Control::LEFT_STICK_LEFT,	 Controller::Control::LEFT },
		{ XboxController::Control::LEFT_STICK_DOWN,	 Controller::Control::DOWN },
		{ XboxController::Control::LEFT_STICK_RIGHT, Controller::Control::RIGHT },
		{ XboxController::Control::A,				 Controller::Control::PRIMARY },
		{ XboxController::Control::B,				 Controller::Control::SECONDARY },
		{ XboxController::Control::START,			 Controller::Control::PAUSE },
		{ XboxController::Control::BACK,			 Controller::Control::SELECT }
	};

	if (customControls.empty())
	{
		this->customControls = defaultControls;
	}
	else
	{
		if (customControls.size() < NUM_CONTROLS)
		{
			logger.Warn("There may be unbound controls.");
		}

		this->customControls = customControls;
	}

	// Set connection.
	GetHardwareControllerState();
	isConnected = XInputGetState(0, &controllerState) == ERROR_SUCCESS;

	// Set enabled.
	this->isEnabled = isEnabled;
}

XboxController::XboxController() : XboxController(true, std::map<int, int>())
{}

XboxController::~XboxController()
{}

vector<Controller::Input> XboxController::ComputeInputSnapshot()
{
	vector<Controller::Input> inputSnapshot;
	
	// Get hardware snapshot.
	GetHardwareControllerState();

	/* For every kind of input, create a response object. */

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::A,
			(controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0
		)
	);

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::B,
			(controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0
		)
	);

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::DPAD_UP,
			(controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0
		)
	);

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::DPAD_LEFT,
			(controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0
		)
	);
	
	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::DPAD_DOWN,
			(controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0
		)
	);

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::DPAD_RIGHT,
			(controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0
		)
	);

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::BACK,
			(controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0
		)
	);

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::START,
			(controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0
		)
	);

	// Analog stick.
	float normLX = fmaxf(-1, (float)controllerState.Gamepad.sThumbLX / 32767);
	float normLY = fmaxf(-1, (float)controllerState.Gamepad.sThumbLY / 32767);

	// TODO: Make class constants.
	float deadzoneX = 0.15f;
	float deadzoneY = 0.05f;

	float leftStickX = (abs(normLX) < deadzoneX ? 0 : normLX);
	float leftStickY = (abs(normLY) < deadzoneY ? 0 : normLY);

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::LEFT_STICK_UP,
			leftStickY > 0,
			abs(leftStickY)
		)
	);

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::LEFT_STICK_DOWN,
			leftStickY < 0,
			abs(leftStickY)
		)
	);

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::LEFT_STICK_LEFT,
			leftStickX < 0,
			abs(leftStickX)
		)
	);

	inputSnapshot.push_back(
		SetInput(
			XboxController::Control::LEFT_STICK_RIGHT,
			leftStickX > 0,
			abs(leftStickX)
		)
	);

	// Store it as latest input.
	// Note that duplicates are not handled here as assumptions cannot be made about the game logic.
	lastInputSnapshot = inputSnapshot;
	return lastInputSnapshot;
}