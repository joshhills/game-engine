#pragma once

#include "EventManager.h"

class Movement {
public:
	virtual void OnMove(EventManager * eventManager, float oldX, float oldY, float newX, float newY) = 0;
};