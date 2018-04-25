#pragma once

#include "Controller.h"

#include <nclgl/Window.h>
#include <nclgl/Keyboard.h>

class KeyboardController : public Controller {
public:
	// Keyboard-specific controls.
	enum Control
	{
		Z = 0,
		X = 1,
		UP_ARROW = 2,
		LEFT_ARROW = 3,
		DOWN_ARROW = 4,
		RIGHT_ARROW = 5,
		ESC = 6,
		RETURN = 7
	};

	KeyboardController();
	KeyboardController(bool isEnabled, std::map<int, int> customControls);
	~KeyboardController();

	vector<Input> ComputeInputSnapshot() override;
};