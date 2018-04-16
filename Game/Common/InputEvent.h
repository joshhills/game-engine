#pragma once

#include "Event.h"
#include <Human Interface\Controller.h>

class InputEvent : public Event {
public:
	InputEvent(Controller::Input input);
	
	Controller::Input input;
};