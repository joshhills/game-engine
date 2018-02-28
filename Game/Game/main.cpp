#include <nclgl/Window.h>

#include <Common/EventManager.h>
#include <Graphics/Graphics.h>
#include <Human Interface/HumanInterface.h>
#include <Physics/Physics.h>

#include <Box2D\Box2D.h>

#include <Common/Logger.h>

int main() {
	// Create reference to events system.
	EventManager * eventManager = new EventManager();

	// Create a list of all game objects.
	vector<Entity *> entities;

	// Create references to subsystems.
	Graphics graphics(eventManager, &entities);
	Physics physics(eventManager, &entities);
	HumanInterface humanInterface(eventManager, &entities);

	// Set logger settings for debugging purposes.
	Logger::SetLevel(Logger::INFO);
	Logger::SetLevelExclusive(true);
	Logger::SetFilter("Event Manager");

	/*
	
	FOR WHEN YOU COME BACK TO THIS:
	- Add an entity list
	- Move graphics inside graphics
	- Add a camera
	- Remove dependencies that are not needed from this class
	- Get WASD movement working
	
	*/

	//Mesh*	m = Mesh::LoadMeshFile("cube.asciimesh");
	//Shader* s = new Shader("basicvert.glsl", "basicFrag.glsl");

	//if (s->UsingDefaultShader()) {
	//	cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
	//	cout << "Press any key to continue." << endl;
	//	std::cin.get();
	//}

	//RenderObject o(m, s);
	//o.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));
	//r.AddRenderObject(o);

	//RenderObject o2(m, s);
	//o2.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));
	//r.AddRenderObject(o2);

	//r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));

	//r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));

	//// Box2D test

	//// World
	//b2Vec2 gravity(0.0f, -10.0f);
	//b2World world(gravity);

	//// Ground
	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0.0f, -10.0f);
	//b2Body* groundBody = world.CreateBody(&groundBodyDef);

	//b2PolygonShape groundBox;
	//groundBox.SetAsBox(50.0f, 10.0f);

	//groundBody->CreateFixture(&groundBox, 0.0f);

	//// object 1
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 4.0f);
	//b2Body* body = world.CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(0.65f, 0.65f);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;

	//body->CreateFixture(&fixtureDef);

	//// object 2
	//b2BodyDef bodyDef2;
	//bodyDef2.type = b2_dynamicBody;
	//bodyDef2.position.Set(2.0f, 10.0f);
	//b2Body* body2 = world.CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox2;
	//dynamicBox2.SetAsBox(0.65f, 0.65f);

	//b2FixtureDef fixtureDef2;
	//fixtureDef2.shape = &dynamicBox2;
	//fixtureDef2.density = 1.0f;
	//fixtureDef2.friction = 0.3f;

	//body2->CreateFixture(&fixtureDef2);

	//// Simulate world
	//float32 timeStep = 1.0f / 60.0f;

	//int32 velocityIterations = 6;
	//int32 positionIterations = 2;

	/**/

	// Initialisation();

	// Main game loop.
	while (true) {
		// Update the graphics subsystem.
		graphics.Update();

		// Update the input device subsystem.
		humanInterface.Update();

		// React to input.


		// Update the physics subsystem.
		physics.Update();

		eventManager->RemoveFinishedEvents();

		// Handle quitting.


		// Box2D
		/*world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		b2Vec2 position2 = body->GetPosition();
		float32 angle2 = body->GetAngle();

		o.SetModelMatrix(Matrix4::Translation(Vector3(position.x, position.y, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));
		o.SetModelMatrix(Matrix4::Translation(Vector3(position2.x, position2.y, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));*/
	}

	/**/

	//delete m;
	//delete s;

	/*Physics * physics = new Physics();

	while (true) {
		physics->update(1.0f);
	}*/
}