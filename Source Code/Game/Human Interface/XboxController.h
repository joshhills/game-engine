#pragma once

#include "Controller.h"

#include <Windows.h>
#include <Xinput.h>

class XboxController : public Controller {
public:
	// Xbox-specific controls.
	enum Control
	{
		A = 0,
		B = 1,
		DPAD_UP = 2,
		DPAD_DOWN = 3,
		DPAD_LEFT = 4,
		DPAD_RIGHT = 5,
		LEFT_STICK_UP = 6,
		LEFT_STICK_DOWN = 7,
		LEFT_STICK_LEFT = 8,
		LEFT_STICK_RIGHT = 9,
		BACK = 10,
		START = 11
	};

	XboxController();
	XboxController(bool isEnabled, std::map<int, int> customControls);
	~XboxController();

	vector<Controller::Input> ComputeInputSnapshot() override;
private:
	// Object to act as vessel.
	XINPUT_STATE controllerState;

	DWORD GetHardwareControllerState()
	{
		// Zeroise the state
		ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

		// Get the state
		return XInputGetState(0, &controllerState);
	}
};