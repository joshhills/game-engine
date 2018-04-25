#pragma once

#include <Box2D\Box2D.h>

class PhysicsData {
public:
	PhysicsData(b2Body * body);
	~PhysicsData();

	b2Body * GetBody();
private:
	b2Body * body;
};