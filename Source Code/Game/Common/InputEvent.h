#pragma once

#include "Event.h"
#include <Human Interface\Controller.h>

class InputEvent : public Event {
public:
	InputEvent(Controller::Input input) :
		Event(Event::HUMAN_INTERFACE_INPUT),
		input(input)
	{}
	
	Controller::Input input;
};