#include "ResourceManagement.h"
#include <Common/InputEvent.h>

// Statically accesible stores for new overrides.
//Store ResourceManagement::eventStore = Store(sizeof(InputEvent), 200);

ResourceManagement::ResourceManagement(EventManager * eventManager) :
	Subsystem("Resource Management", Event::RESOURCE_MANAGEMENT, eventManager)
{}

ResourceManagement::~ResourceManagement()
{
}

void ResourceManagement::StartUp()
{
	/* For every type of resource in the manifest, call the relevant load function. */

	// Meshes.
	//for (int i = 0; i < manifest->meshes->length(); i++)
	//{

	//}
}

void ResourceManagement::Update()
{
	Subsystem::Update();

	// Check if need to defragment.

}
