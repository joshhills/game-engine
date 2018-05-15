#pragma once

#include <Common/Entity.h>

class BackgroundEntity : public Entity {
public:
	BackgroundEntity(EventManager * eventManager);
	~BackgroundEntity();
};