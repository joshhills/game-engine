#pragma once

#include <vector>
#include "TileEntity.h"

using namespace std;

class Level {
public:
	Level(vector<TileEntity *> tiles) : tiles(tiles) {}

	TileEntity * GetSpawnTile() {
		return spawnTile;
	}
	void SetSpawnTile(TileEntity * spawnTile)
	{
		this->spawnTile = spawnTile;
	}

	TileEntity * GetHoleEnterTile() {
		return holeEnterTile;
	}
	void SetHoleEnterTile(TileEntity * holeEnterTile)
	{
		this->holeEnterTile = holeEnterTile;
	}

	TileEntity * GetHoleExitTile() {
		return holeExitTile;
	}
	void SetHoleExitTile(TileEntity * holeExitTile)
	{
		this->holeExitTile = holeExitTile;
	}
private:
	/**
	 * All of the level's tile entities arranged on a grid.
	 */
	vector<TileEntity *> tiles;

	TileEntity * spawnTile;
	TileEntity * holeEnterTile;
	TileEntity * holeExitTile;
};