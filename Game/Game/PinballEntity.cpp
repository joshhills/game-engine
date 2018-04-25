#include "PinballEntity.h"

PinballEntity::PinballEntity(EventManager * eventManager, int spawnX, int spawnY)
	: Entity(eventManager)
{
	// Set things up in a bespoke manner for a demo cube.
	// Create graphical representation.
	Mesh * mesh = Mesh::LoadObjFile("Resources/Models/pinball.obj");
	Shader * shader = new Shader("basicvert.glsl", "basicFrag.glsl");
	graphicsData = new GraphicsData(mesh, shader);

	// Create physical representation.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(spawnX, spawnY);
	b2Body* body = Physics::world.CreateBody(&bodyDef);
	body->SetUserData(this);

	b2CircleShape circle;
	circle.m_radius = 0.5f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 5.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	physicsData = new PhysicsData(body);
}

PinballEntity::~PinballEntity()
{}

void PinballEntity::OnMove(EventManager * eventManager, float oldX, float oldY, float newX, float newY)
{
	eventManager->AddEvent(new CameraTrackEvent(newX, newY));
}

void PinballEntity::OnCollisionStart()
{
	cout << "\nPinball has collided with something!";

	eventManager->AddEvent(new PlaySoundEvent("jump.wav", true, gameObject->x, gameObject->y));
}
