#include "ResourceManager.h"
#include <Common/PlaySoundEvent.h>
#include <Gameplay/PinballEntity.h>

/*
 * Statically accesible stores for new overrides.
 * The max values are somewhat arbitrary but should
 * never be reached in this simulation.
 */
Store ResourceManager::eventStore = Store(sizeof(PlaySoundEvent), 200);
Store ResourceManager::entityStore = Store(sizeof(PinballEntity), 500);

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}