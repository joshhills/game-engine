#pragma once

#include "TileEntity.h"

class BlockTileEntity : public TileEntity {
public:
	BlockTileEntity(EventManager * eventManager, TileType type, int gridPositionX, int gridPositionY) : TileEntity(eventManager, type, gridPositionX, gridPositionY) {
		// Store default graphical settings.
		Mesh * mesh = Mesh::LoadObjFile("Resources/Models/block.obj");
		Shader * shader = new Shader("basicvert.glsl", "basicFrag.glsl");
		graphicsData = new GraphicsData(mesh, shader);

		// Store default physical settings.
		b2BodyDef bodyDef;
		bodyDef.position.Set(this->gridPositionX, this->gridPositionY);
		b2Body* body = Physics::world.CreateBody(&bodyDef);
		b2PolygonShape tile;
		tile.SetAsBox(1, 1);
		body->CreateFixture(&tile, 0.0f);
		physicsData = new PhysicsData(body);
	}
};