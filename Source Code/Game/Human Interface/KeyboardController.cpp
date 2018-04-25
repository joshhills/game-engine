#include "KeyboardController.h"

KeyboardController::KeyboardController(bool isEnabled, std::map<int, int> customControls) : Controller(ControllerType::KEYBOARD, "KeyboardController")
{
	// Define default controls (explicitly namespaced for clarity).
	defaultControls = {
		{ KeyboardController::Control::UP_ARROW,	Controller::Control::UP			},
		{ KeyboardController::Control::LEFT_ARROW,	Controller::Control::LEFT		},
		{ KeyboardController::Control::DOWN_ARROW,	Controller::Control::DOWN		},
		{ KeyboardController::Control::RIGHT_ARROW, Controller::Control::RIGHT		},
		{ KeyboardController::Control::Z,			Controller::Control::PRIMARY	},
		{ KeyboardController::Control::X,			Controller::Control::SECONDARY	},
		{ KeyboardController::Control::ESC,			Controller::Control::PAUSE		},
		{ KeyboardController::Control::RETURN,		Controller::Control::SELECT		}
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

	// Assumed to be connected, does not break if not.
	isConnected = true;
}

KeyboardController::KeyboardController() : KeyboardController(true, std::map<int, int>())
{}

KeyboardController::~KeyboardController()
{}

vector<Controller::Input> KeyboardController::ComputeInputSnapshot()
{
	vector<Controller::Input> inputSnapshot;

	/* For every kind of input, create a response object. */
	inputSnapshot.push_back(
		SetInput(
			KeyboardController::Control::Z,
			Window::GetKeyboard()->KeyDown(KEYBOARD_Z)
		)
	);

	inputSnapshot.push_back(
		SetInput(
			KeyboardController::Control::X,
			Window::GetKeyboard()->KeyDown(KEYBOARD_X)
		)
	);

	inputSnapshot.push_back(
		SetInput(
			KeyboardController::Control::ESC,
			Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)
		)
	);

	inputSnapshot.push_back(
		SetInput(
			KeyboardController::Control::RETURN,
			Window::GetKeyboard()->KeyDown(KEYBOARD_RETURN)
		)
	);

	inputSnapshot.push_back(
		SetInput(
			KeyboardController::Control::UP_ARROW,
			Window::GetKeyboard()->KeyDown(KEYBOARD_UP)
		)
	);

	inputSnapshot.push_back(
		SetInput(
			KeyboardController::Control::DOWN_ARROW,
			Window::GetKeyboard()->KeyDown(KEYBOARD_DOWN)
		)
	);

	inputSnapshot.push_back(
		SetInput(
			KeyboardController::Control::LEFT_ARROW,
			Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT)
		)
	);

	inputSnapshot.push_back(
		SetInput(
			KeyboardController::Control::RIGHT_ARROW,
			Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT)
		)
	);

	// Store it as latest input.
	// Note that duplicates are not handled here as assumptions cannot be made about the game logic.
	lastInputSnapshot = inputSnapshot;
	return lastInputSnapshot;
}