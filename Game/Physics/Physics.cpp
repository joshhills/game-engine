#include "Physics.h"

Physics::~Physics() {}

// Initialize statically accessible entities.
// TODO: Comment describe what these are used for.
b2World Physics::world = b2World(b2Vec2(0.0f, -40.0f));

Physics::Physics(EventManager * eventManager, vector<Entity *> * entities) :
	Subsystem("Physics", Event::PHYSICS, eventManager),
	entities(entities)
{
	// Middleware prerequisite.
	world.SetContactListener(&i);

	// Create function map using lambdas to handle events.
	eventMap[Event::MOVE] = [this](Event * e) { HandleMoveEvent(e); };
}

void Physics::Update() {
	Subsystem::Update();

	// Update physics objects attached to the world (ergo all physics data by proxy of 'world').
	world.Step(timeStep, velocityIterations, positionIterations);

	// Update common interface.
	for (Entity * entity : *entities)
	{
		// If there is physics data to enact upon.
		if (entity->GetPhysicsData() != nullptr)
		{
			// TODO: Make a constructor for gameobject that takes a physics data (to get middleware marks)?
			GameObject * gameObject = entity->GetGameObject();
			PhysicsData * physicsData = entity->GetPhysicsData();

			// Position.
			b2Vec2 position = physicsData->GetBody()->GetPosition();

			// Check for changes in position (accounting for floating-point precision).
			if (abs(gameObject->x - position.x) > numeric_limits<float>::epsilon()
				|| abs(gameObject->y - position.y) > numeric_limits<float>::epsilon())
			{
				// Check if it implements a listener.
				if (Movement * movement = dynamic_cast<Movement *>(entity))
				{
					movement->OnMove(eventManager, gameObject->x, gameObject->y, position.x, position.y);
				}
			}
			gameObject->x = position.x;
			gameObject->y = position.y;

			// Rotation (convert from radians to degrees).
			gameObject->rotation = RadToDeg(physicsData->GetBody()->GetAngle());
		}
	}
}

// TODO: Make this not a human interface event.
void Physics::HandleMoveEvent(Event * e) {
	MoveEvent * t = static_cast<MoveEvent *>(e);
	
	for (Entity * entity : t->entities)
	{
		Move(entity, b2Vec2(t->direction.x, t->direction.y));
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
