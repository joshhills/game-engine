#pragma once

#include "TileEntity.h"

class SpawnTileEntity : public TileEntity {
public:
	SpawnTileEntity(EventManager * eventManager, TileType type, int gridPositionX, int gridPositionY) : TileEntity(eventManager, type, gridPositionX, gridPositionY) {}
};