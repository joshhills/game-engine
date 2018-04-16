#include "InputEvent.h"

InputEvent::InputEvent(Controller::Input input) : Event(Event::INPUT), input(input)
{}