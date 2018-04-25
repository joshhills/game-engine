#pragma once

#include "TileEntity.h"
#include <Common/Collider.h>

class BumperTileEntity : public TileEntity {
public:
	BumperTileEntity(EventManager * eventManager, TileType type, int gridPositionX, int gridPositionY) : TileEntity(eventManager, type, gridPositionX, gridPositionY) {
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
		body->SetUserData(this);
		body->CreateFixture(&fixtureDef);
		physicsData = new PhysicsData(body);
	}
};