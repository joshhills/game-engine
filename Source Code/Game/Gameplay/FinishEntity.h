#pragma once

#include <Common/Entity.h>

class FinishEntity : public Entity {
public:
	FinishEntity(EventManager * eventManager);
	~FinishEntity();
};