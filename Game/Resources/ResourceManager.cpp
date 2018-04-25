#include "ResourceManager.h"
#include <Common/InputEvent.h>

// Statically accesible stores for new overrides.
Store ResourceManager::eventStore = Store(sizeof(InputEvent), 200);

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}