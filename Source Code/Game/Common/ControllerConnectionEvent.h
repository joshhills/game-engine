#pragma once

#include "Event.h"
#include <Human Interface\Controller.h>

class ControllerConnectionEvent : public Event {
public:
	ControllerConnectionEvent(Controller::ControllerType controllerType, bool connected) :
		Event(Event::HUMAN_INTERFACE_CONTROLLER_CONNECTION),
		controllerType(controllerType),
		connected(connected)
	{}

	Controller::ControllerType controllerType;
	bool connected;
};