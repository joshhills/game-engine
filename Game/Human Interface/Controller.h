#pragma once

#include <vector>
#include <map>

#include <Common/LoggerInstance.h>

using namespace std;

/**
 * Not interrupt driven, no concept of multi-user.
 */
class Controller {
public:
	// Engine-wide controls.
	enum Control {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3,
		PRIMARY = 4,
		SECONDARY = 5,
		PAUSE = 6,
		SELECT = 7,
		MAX = 8,
		NUM_CONTROLS = 9
	};

	// Variations of engine-wide controls.
	enum class ControlState {
		NONE,
		DOWN,
		HELD,
		TRIGGERED
	};

	/**
	 * Multi-purpose solution for both analog
	 * and digital control - amount is a percentage
	 * scale, 1 if digital.
	 */
	struct Input {
		Control control;
		ControlState state;
		float amount = -1;
	};

	Controller(string controllerName) : logger(controllerName), isEnabled(true), isConnected(false) {}
	virtual ~Controller() {}

	// Accessors.
	bool IsEnabled() const
	{
		return isEnabled;
	}

	void SetEnabled(bool isEnabled)
	{
		this->isEnabled = isEnabled;
	}

	bool IsConnected() const
	{
		return isConnected;
	}

	void SetConnected(bool isConnected)
	{
		this->isConnected = isConnected;
	}

	/**
	 * Update the internal historic state of the inputs.
	 */
	virtual void UpdateInput()
	{
		lastInputSnapshot = GetInputSnapshot();
	}

	/**
	 * Shortcut for retrieving input in an extensible manner. 
	 * 
	 * @param control	The abstract control to query.
	 * @param state		The state to check if it is in.
	 */
	virtual bool IsInput(Control control, ControlState state)
	{
		switch (state) {
		case ControlState::HELD:
			return IsInputHeld(control);
			break;
		case ControlState::TRIGGERED:
			return IsInputTriggered(control);
			break;
		default:
			return IsInputDown(control);
			break;
		}
	};

	virtual bool IsInputDown(Control control) {
		return inputDownStates[control];
	};
	virtual bool IsInputHeld(Control control) {
		return inputHoldStates[control];
	};
	virtual bool IsInputTriggered(Control control) {
		return inputTriggeredStates[control];
	};

	/**
	 * Construct a list of active inputs.
	 * TODO: Do I also want to return the inactive to track changes?
	 */
	virtual vector<Controller::Input> ComputeInputSnapshot() = 0;
	
	virtual Controller::Input SetInput(int control, bool isActive = true, float amount = 1)
	{
		// Check if this is an empty change.
		if (!isActive)
		{
			return ZeroInput(control);
		}

		Controller::Input input;

		// Determine control.
		// TODO: Error-handling?
		int mapping = customControls[control];
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

		input.amount = amount;

		return input;
	}

	virtual Controller::Input ZeroInput(int control)
	{
		Controller::Input input;

		int mapping = customControls[control];
		input.control = static_cast<Controller::Control>(mapping);
		input.amount = 0;
		input.state = Controller::ControlState::NONE;

		// Reset the state.
		inputTriggeredStates[input.control] = false;
		inputDownStates[input.control] = false;
		inputHoldStates[input.control] = false;

		return input;
	}

	virtual vector<Controller::Input> GetInputSnapshot()
	{
		return lastInputSnapshot;
	}

protected:
	LoggerInstance logger;

	bool isEnabled;
	bool isConnected;

	// Store last input state snapshot.
	vector<Controller::Input> lastInputSnapshot;

	// Store historical bitmap of input changes.
	bool inputTriggeredStates[Control::MAX];
	bool inputDownStates[Control::MAX];
	bool inputHoldStates[Control::MAX];

	// Store input maps per controller.
	map<int, int> defaultControls;
	map<int, int> customControls;
};