#include "CubeEntity.h"

CubeEntity::CubeEntity()
{
	// Set things up in a bespoke manner for a demo cube.
	// Create graphical representation.
	Mesh * mesh = Mesh::LoadMeshFile("cube.asciimesh");
	Shader * shader = new Shader("basicvert.glsl", "basicFrag.glsl");

	this->graphicsData = new GraphicsData(mesh, shader);

	// Create physical representation.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 10.0f);
	b2Body* body = Physics::world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	this->physicsData = new PhysicsData(body);
}

CubeEntity::~CubeEntity()
{}
