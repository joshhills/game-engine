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
	eventMap[Event::MOVE_UP] =		[this](Event * e) {	MoveUp(e);		};
	eventMap[Event::MOVE_DOWN] =	[this](Event * e) { MoveDown(e);	};
	eventMap[Event::MOVE_LEFT] =	[this](Event * e) { MoveLeft(e);	};
	eventMap[Event::MOVE_RIGHT] =	[this](Event * e) { MoveRight(e);	};
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

// TODO: Magic numbers; also ask Will if this is an appropriate way to do physics.
void Physics::MoveUp(Event * e) {
	Move(
		e->entities.at(0), // The only entity in this definition.
		b2Vec2(0, 50)
	);
}

void Physics::MoveDown(Event * e) {
	Move(
		e->entities.at(0), // The only entity in this definition.
		b2Vec2(0, -50)
	);
}

void Physics::MoveLeft(Event * e) {
	Move(
		e->entities.at(0), // The only entity in this definition.
		b2Vec2(50, 0)
	);
}

void Physics::MoveRight(Event * e) {
	Move(
		e->entities.at(0), // The only entity in this definition.
		b2Vec2(-50, 0)
	);
}

void Physics::Move(Entity * entity, b2Vec2 force) {
	b2Body * body = entity->GetPhysicsData()->GetBody();

	body->ApplyForce(
		force,
		body->GetWorldCenter(),
		true
	);
}
