#include "Physics.h"

Physics::~Physics() {
	// TODO: Delete function map?...
}

// Initialize statically accessible entities.
// TODO: Comment describe what these are used for.
b2World Physics::world = b2World(b2Vec2(0.0f, -10.0f));

Physics::Physics(EventManager * eventManager, vector<Entity *> * entities) :
	Subsystem("Physics", Event::PHYSICS, eventManager),
	entities(entities)
{
	// Create function map using lambdas to handle events.
	eventMap[Event::HUMAN_INTERFACE_INPUT] = [this](Event * e) { HandleMoveEvent(e); };
}

void Physics::Update() {
	Subsystem::Update();

	// Update physics objects attached to the world (ergo all physics data by proxy of 'world').
	world.Step(timeStep, velocityIterations, positionIterations);

	// Update common interface.
	// TODO: Create method?
	for (auto entity : *entities) {
		// TODO: Make a constructor for gameobject that takes a physics data (to get middleware marks)?
		GameObject * gameObject = entity->GetGameObject();
		PhysicsData * physicsData = entity->GetPhysicsData();

		// Position.
		b2Vec2 position = physicsData->GetBody()->GetPosition();
		gameObject->x = position.x;
		gameObject->y = position.y;

		// Rotation.
		gameObject->rotation = physicsData->GetBody()->GetAngle();
	}
}

void Physics::HandleMoveEvent(Event * e) {
	InputEvent * t = static_cast<InputEvent *>(e);
	Entity * entity = t->entities.at(0);

	// TODO: Magic number, should form part of input payload from game.
	const float moveSpeed = 50 * t->input.amount;

	switch (t->input.control)
	{
		case Controller::Control::UP:
			Move(entity, b2Vec2(0, moveSpeed));
			break;
		case Controller::Control::DOWN:
			Move(entity, b2Vec2(0, -moveSpeed));
			break;
			case Controller::Control::LEFT:
			Move(entity, b2Vec2(moveSpeed, 0));
			break;
		case Controller::Control::RIGHT:
			Move(entity, b2Vec2(-moveSpeed, 0));
			break;
	}
}

void Physics::Move(Entity * entity, b2Vec2 force) {
	b2Body * body = entity->GetPhysicsData()->GetBody();

	body->ApplyForce(
		force,
		body->GetWorldCenter(),
		true
	);
}
