#pragma once

#include <Windows.h>
#include <Xinput.h>

class XboxController {
public:
	XboxController();
	~XboxController();

	bool GetIsConnected() const;
	XINPUT_STATE GetControllerState();
private:
	bool isConnected;
	XINPUT_STATE controllerState;
};