#pragma once

#include <vector>
#include "TileEntity.h"

using namespace std;

class Level {
public:
	Level(vector<TileEntity *> tiles) : tiles(tiles) {}
private:
	/**
	 * All of the level's tile entities arranged on a grid.
	 */
	vector<TileEntity *> tiles;
};