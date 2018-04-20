#include "ResourceManager.h"

ResourceManagement::ResourceManagement(EventManager * eventManager) :
	Subsystem("Resource Manager", Event::RESOURCE_MANAGEMENT, eventManager)
{}

ResourceManagement::~ResourceManagement()
{
}

void ResourceManagement::StartUp()
{
	/* For every type of resource in the manifest, call the relevant load function. */

	// Meshes.
	for (int i = 0; i < manifest->meshes->length(); i++)
	{

	}

	// Create stores.
	eventStore = Store();
}

void ResourceManagement::Update()
{
	Subsystem::Update();

	// Check if need to defragment.
	
}
