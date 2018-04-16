#include "File.h"

#include <Common/Event.h>

File::File(EventManager * eventManager, vector<Entity *> * entities) :
	Subsystem("File", Event::FILE, eventManager),
	entities(entities)
{}

File::~File()
{
}

void File::Update()
{
	Subsystem::Update();
}