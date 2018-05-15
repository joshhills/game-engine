#pragma once

#include <Common/Entity.h>

class PauseEntity : public Entity {
public:
	PauseEntity(EventManager * eventManager);
	~PauseEntity();
};