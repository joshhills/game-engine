#pragma once

#include "TileEntity.h"

class SpawnTileEntity : public TileEntity {
public:
	SpawnTileEntity(TileType type, int gridPositionX, int gridPositionY) : TileEntity(type, gridPositionX, gridPositionY) {}
private:

};