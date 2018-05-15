#pragma once

#include "TileEntity.h"

class FlipperWedgeTileEntity : public TileEntity {
public:
	FlipperWedgeTileEntity(EventManager * eventManager, GraphicsData * graphicsData, TileType type, int gridPositionX, int gridPositionY) : TileEntity(eventManager, type, gridPositionX, gridPositionY) {
		// Store default graphical settings.
		this->graphicsData = graphicsData;

		// Store default physical settings.
		b2BodyDef bodyDef;
		bodyDef.position.Set(this->gridPositionX, this->gridPositionY);

		b2PolygonShape tile;
		const int32 count = 3;
		b2Vec2 vertices[count];
		vertices[0].Set(-1.0f, -1.0f);
		vertices[1].Set(1.0f, -1.0f);
		vertices[2].Set(1.0f, 1.0f);

		// Switch on orientation of tile.
		switch (type)
		{
		case TileType::FLIPPER_TOP_LEFT:
			bodyDef.angle = DegToRad(90);
			break;
		case TileType::FLIPPER_TOP_RIGHT:
			bodyDef.angle = DegToRad(180);
			break;
		case TileType::FLIPPER_BOTTOM_RIGHT:
			bodyDef.angle = DegToRad(270);
			break;
		}

		tile.Set(vertices, count);

		b2Body* body = Physics::world.CreateBody(&bodyDef);
		body->CreateFixture(&tile, 0.0f);
		body->SetUserData(this);
		physicsData = new PhysicsData(body);
	}
};