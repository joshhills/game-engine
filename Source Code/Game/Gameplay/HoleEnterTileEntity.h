#pragma once

#include "TileEntity.h"

class HoleEnterTileEntity : public TileEntity {
public:
	HoleEnterTileEntity(EventManager * eventManager, GraphicsData * graphicsData, TileType type, int gridPositionX, int gridPositionY) : TileEntity(eventManager, type, gridPositionX, gridPositionY) {
		// Store default graphical settings.
		this->graphicsData = graphicsData;

		// Store default physical settings.
		b2BodyDef bodyDef;
		bodyDef.position.Set(this->gridPositionX, this->gridPositionY);

		b2CircleShape tile;
		tile.m_radius = 0.5f;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &tile;

		b2Body* body = Physics::world.CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);
		body->SetUserData(this);
		physicsData = new PhysicsData(body);
	}
};