#include "XboxController.h"

XboxController::XboxController()
{
	//Invoke the memset(); function to zero the XBOX_CONTROLLER_State. 
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
	
	isConnected = XInputGetState(0, &controllerState) == ERROR_SUCCESS;
}

XboxController::~XboxController()
{}

bool XboxController::GetIsConnected() const
{
	return isConnected;
}

XINPUT_STATE XboxController::GetControllerState()
{
	// Zeroise the state
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(0, &controllerState);

	return controllerState;
}
