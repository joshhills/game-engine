#include "PinballEntity.h"

PinballEntity::PinballEntity(EventManager * eventManager)
	: Entity(eventManager)
{
	// Set things up in a bespoke manner for a demo cube.
	// Create graphical representation.
	Mesh * mesh = Mesh::LoadObjFile("./Resources/Models/pinball.obj");
	bumpShader = new Shader("./Resources/Shaders/baseTileVert.glsl", "./Resources/Shaders/pinballFragBump.glsl");
	noBumpShader = new Shader("./Resources/Shaders/baseTileVert.glsl", "./Resources/Shaders/pinballFragNoBump.glsl");
	graphicsData = new GraphicsData(mesh, bumpShader);

	// Create physical representation.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 0);
	b2Body* body = Physics::world.CreateBody(&bodyDef);
	body->SetUserData(this);

	b2CircleShape circle;
	circle.m_radius = 0.5f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 10.0f;
	fixtureDef.restitution = 0.4f;
	fixtureDef.friction = 0.1f;

	body->CreateFixture(&fixtureDef);

	physicsData = new PhysicsData(body);
}

PinballEntity::~PinballEntity()
{}

void PinballEntity::OnMove(EventManager * eventManager, float oldX, float oldY, float newX, float newY)
{
	eventManager->AddEvent(new CameraTrackEvent(newX, newY));
}

void PinballEntity::OnCollisionStart(Entity * e)
{
	float newCollisionTime = clock();

	std::cout << newCollisionTime << '\n';
	std::cout << lastFinishedColliding << "\n\n\n";

	if (newCollisionTime - lastFinishedColliding > COLLISION_SOUND_THRESHOLD)
	{
		eventManager->AddEvent(new PlaySoundEvent("./Resources/Audio/collide-wall.wav", true, gameObject->x, gameObject->y));
	}
}

void PinballEntity::OnCollisionEnd(Entity * e)
{
	lastFinishedColliding = clock();
}

void PinballEntity::UpdateShaderBasedOnBumpAbility(bool canBump)
{
	if (canBump)
	{
		graphicsData->ChangeShader(bumpShader);
	}
	else 
	{
		graphicsData->ChangeShader(noBumpShader);
	}
}

