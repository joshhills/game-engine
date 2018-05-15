#pragma once

#include <algorithm>
#include <vector>

#include "TileEntity.h"

using namespace std;

class Level {
public:
	Level() {}
	Level(vector<TileEntity *> tiles, vector<Entity *> * entities) : tiles(tiles), entities(entities)
	{
		// Add tiles to entity list.
		if (entities != nullptr)
		{
			for (Entity * tile : tiles)
			{
				entities->push_back(tile);
			}
		}
	}

	~Level()
	{
		for (Entity * tile : tiles)
		{
			entities->erase(std::remove(entities->begin(), entities->end(), tile), entities->end());
			delete tile;
		}
	};

	TileEntity * GetSpawnTile()
	{
		return spawnTile;
	}
	void SetSpawnTile(TileEntity * spawnTile)
	{
		this->spawnTile = spawnTile;
	}

	TileEntity * GetHoleExitTile()
	{
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

	/**
	* The entity list to remove them from on de-spawn.
	*/
	vector<Entity *> * entities;

	TileEntity * spawnTile;
	TileEntity * holeEnterTile;
	TileEntity * holeExitTile;
};