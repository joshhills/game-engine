#include "Gameplay.h"

Gameplay::Gameplay(EventManager * eventManager, vector<Entity*>* entities) :
	Subsystem("Gameplay", Event::GAMEPLAY, eventManager),
	entities(entities)
{
	// Create function map using lambdas to handle events.
	eventMap[Event::HUMAN_INTERFACE_INPUT] = [this](Event * e) { HandleHumanInterfaceEvent(e); };

	// Initialise file I/O (after graphics, as a requirement).
	File::InitialiseTileGraphicsData();

	// Initialise level.
	level = File::LoadLevel(eventManager, "Levels/test.lvl", entities);

	// Create the player entity.
	// Get the initial spawn location.
	SpawnTileEntity * s = dynamic_cast<SpawnTileEntity *>(level.GetSpawnTile());
	pinball = new PinballEntity(eventManager, s->gridPositionX, s->gridPositionY);
	entities->push_back(pinball);
}

Gameplay::~Gameplay()
{
}

void Gameplay::Update()
{
	// Measure time taken.
	clock_t start = clock();

	Subsystem::Update();

	// Send time taken to complete function.
	clock_t stop = clock();
	float elapsed = (float)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	eventManager->AddEvent(new SubsystemUpdateEvent(subSystemType, elapsed));
}

void Gameplay::HandleHumanInterfaceEvent(Event * e)
{
	// TODO: Replace with more sophisticated methods.
	// Respond to input.
	InputEvent * t = static_cast<InputEvent *>(e);
	
	MoveEvent::Direction d;
	switch (t->input.control)
	{
		case Controller::Control::UP:
			d.x = 0;
			d.y = 250 * t->input.amount;
			break;
		case Controller::Control::DOWN:
			d.x = 0;
			d.y = -250 * t->input.amount;
			break;
		case Controller::Control::LEFT:
			d.x = 250 * t->input.amount;
			d.y = 0;
			break;
		case Controller::Control::RIGHT:
			d.x = -250 * t->input.amount;
			d.y = 0;
			break;
		case Controller::Control::SELECT:
			if (t->input.state == Controller::ControlState::TRIGGERED)
			{
				eventManager->AddEvent(
					new ToggleProfilingEvent()
				);
			}
			break;
	}

	//if (d.x > 0 || d.y > 0)
	//{
		eventManager->AddEvent(
			(new MoveEvent(d))->AddEntity(pinball)
		);
	//}
}
