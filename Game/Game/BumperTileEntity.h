#pragma once

#include "TileEntity.h"

class BumperTileEntity : public TileEntity {
public:
	BumperTileEntity(TileType type, int gridPositionX, int gridPositionY) : TileEntity(type, gridPositionX, gridPositionY) {
		// Store default graphical settings.
		Mesh * mesh = Mesh::LoadObjFile("Resources/Models/bumper.obj");
		Shader * shader = new Shader("basicvert.glsl", "basicFrag.glsl");
		graphicsData = new GraphicsData(mesh, shader);

		// Store default physical settings.
		b2BodyDef bodyDef;
		bodyDef.position.Set(this->gridPositionX, this->gridPositionY);

		b2CircleShape tile;
		tile.m_radius = 0.5f;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &tile;

		b2Body* body = Physics::world.CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);
		physicsData = new PhysicsData(body);
	}
private:

};