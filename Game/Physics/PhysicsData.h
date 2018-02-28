#pragma once

#include <Box2D\Box2D.h>

class PhysicsData {
public:
	PhysicsData();
	~PhysicsData();
private:
	b2Body * body;
};