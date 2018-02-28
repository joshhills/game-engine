#include "FloorEntity.h"

FloorEntity::FloorEntity()
{
	// Set things up in a bespoke manner for a demo floor.
	// Create physical representation (no graphics necessary at the moment).
	b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, -10.0f);
	b2Body* body = Physics::world.CreateBody(&bodyDef);

	b2PolygonShape floorBox;
	floorBox.SetAsBox(50.0f, 10.0f);

	body->CreateFixture(&floorBox, 0.0f);

	this->physicsData = new PhysicsData(body);
}
