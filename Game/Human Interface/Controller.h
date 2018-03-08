#pragma once

#include <vector>

using namespace std;

class Controller {
public:
	enum Control {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		PRIMARY,
		SECONDARY,
		PAUSE,
		SELECT
	};

	enum ControlState {
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

	Controller();
	~Controller();

	// Accessors


	/**
	 * Shortcut for retrieving input in an extensible manner. 
	 * 
	 * @param control	The abstract control to query.
	 * @param state		The state to check if it is in.
	 */
	virtual Input GetInput(Control control, ControlState state) {
		switch (state) {
		case ControlState::DOWN:
			return GetInputDown(control);
			break;
		case ControlState::HELD:
			return GetInputHeld(control);
			break;
		case ControlState::TRIGGERED:
			return GetInputTriggered(control);
			break;
		}
	};

	virtual Input GetInputDown(Control control);
	virtual Input GetInputHeld(Control control);
	virtual Input GetInputTriggered(Control control);

	virtual vector<Input> GetInputSnapshot();
	
private:
	bool isEnabled;

	// Make an input map, int-to-Control or other way around.
};