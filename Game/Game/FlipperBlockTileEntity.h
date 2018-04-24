#pragma once

#include "TileEntity.h"

class FlipperBlockTileEntity : public TileEntity {
public:
	FlipperBlockTileEntity(TileType type, int gridPositionX, int gridPositionY) : TileEntity(type, gridPositionX, gridPositionY) {
		// Store default graphical settings.
		Mesh * mesh = Mesh::LoadObjFile("Resources/Models/flipper-block.obj");
		Shader * shader = new Shader("basicvert.glsl", "basicFrag.glsl");
		graphicsData = new GraphicsData(mesh, shader);

		// Store default physical settings.
		b2BodyDef bodyDef;
		bodyDef.position.Set(this->gridPositionX, this->gridPositionY);
		b2PolygonShape tile;
		
		// Switch on orientation of tile.
		switch (type)
		{
		case TileType::FLIPPER_RIGHT:
			bodyDef.angle = DegToRad(90);
			break;
		case TileType::FLIPPER_BOTTOM:
			bodyDef.angle = DegToRad(180);
			break;
		case TileType::FLIPPER_LEFT:
			bodyDef.angle = DegToRad(270);
			break;
		}
		
		tile.SetAsBox(1, 1);
		b2Body* body = Physics::world.CreateBody(&bodyDef);
		body->CreateFixture(&tile, 0.0f);
		physicsData = new PhysicsData(body);
	}
private:

};