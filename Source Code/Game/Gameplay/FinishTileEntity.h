#pragma once

#include "TileEntity.h"

#include <Common/Collider.h>
#include <Common/PlaySoundEvent.h>

class FinishTileEntity : public TileEntity {
public:
	FinishTileEntity(EventManager * eventManager, GraphicsData * graphicsData, TileType type, int gridPositionX, int gridPositionY) : TileEntity(eventManager, type, gridPositionX, gridPositionY)
	{
		// Store default graphical settings.
		this->graphicsData = graphicsData;

		// Store default physical settings.
		b2BodyDef bodyDef;
		bodyDef.position.Set(this->gridPositionX, this->gridPositionY);
		b2Body* body = Physics::world.CreateBody(&bodyDef);
		body->SetUserData(this);

		b2PolygonShape tile;
		tile.SetAsBox(1, 1);
		body->CreateFixture(&tile, 0.0f);
		physicsData = new PhysicsData(body);
	}
};