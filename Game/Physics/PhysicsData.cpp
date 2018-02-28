#include "PhysicsData.h"

PhysicsData::PhysicsData(b2Body * body) : body(body)
{}

PhysicsData::~PhysicsData()
{
	/* Box2D manages it own memory, cannot 'delete'
	 * in the traditional way.
	 */
	body->GetWorld()->DestroyBody(body);
}

b2Body * PhysicsData::GetBody()
{
	return body;
}
