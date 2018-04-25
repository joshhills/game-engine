#include "File.h"

// Initialize statically accessible entities.
const string File::RESOURCE_ROOT_PATH = "./Resources/";

LoggerInstance File::logger("File");

// Inspired by SO 13262568.
std::map<int, int> File::LoadControlMap(string relativeFilePath)
{
	std::map<int, int> controlMap;

	ifstream file(RESOURCE_ROOT_PATH + relativeFilePath);

	if (!file) {
		logger.Error("Could not load settings file " + relativeFilePath + ".");
		return controlMap;
	}

	string line;

	int lineNumber = 0;
	while (std::getline(file, line))
	{
		lineNumber++; 

		int pos = line.find('=');
		if (pos != string::npos)
		{
			// TODO: Error handling.
			string keyString = line.substr(0, pos);
			string valueString = line.substr(pos + 1);
			
			try
			{
				int key = std::stoi(keyString);
				int value = std::stoi(valueString);

				controlMap[key] = value;
			}
			catch (std::invalid_argument e)
			{
				logger.Warn("Invalid argument found in settings file " + relativeFilePath + ", line; skipping it." + std::to_string(lineNumber));
			}
		}
	}

	return controlMap;
}

Level File::LoadLevel(EventManager * eventManager, string relativeFilePath, vector<Entity *> * entities)
{
	vector<TileEntity *> tiles;

	ifstream file(RESOURCE_ROOT_PATH + relativeFilePath);

	if (!file) {
		logger.Error("Could not load level file " + relativeFilePath + ".");
		return Level(tiles);
	}

	// Store references to singleton tiles.
	SpawnTileEntity * spawnTile = nullptr;
	HoleEnterTileEntity * holeEnterTile = nullptr;
	HoleExitTileEntity * holeExitTile = nullptr;

	try
	{
		// Read in width and height first.
		int width, height;
		file >> width;
		file >> height;

		// Scan over tiles in set.
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				// Read in the tile type.
				int tile;
				file >> tile;
				TileEntity::TileType type = static_cast<TileEntity::TileType>(tile);

				// Convert this type to a tile type.
				switch (type)
				{
					case TileEntity::TileType::BLOCK:
						tiles.push_back(new BlockTileEntity(eventManager, type, width - j, height - i));
						break;
					case TileEntity::TileType::BUMPER:
						tiles.push_back(new BumperTileEntity(eventManager, type, width - j, height - i));
						break;
					case TileEntity::TileType::FINISH:
						tiles.push_back(new FinishTileEntity(eventManager, type, width - j, height - i));
						break;
					case TileEntity::TileType::FLIPPER_TOP:
					case TileEntity::TileType::FLIPPER_LEFT:
					case TileEntity::TileType::FLIPPER_BOTTOM:
					case TileEntity::TileType::FLIPPER_RIGHT:
						tiles.push_back(new FlipperBlockTileEntity(eventManager, type, width - j, height - i));
						break;
					case TileEntity::TileType::FLIPPER_TOP_LEFT:
					case TileEntity::TileType::FLIPPER_TOP_RIGHT:
					case TileEntity::TileType::FLIPPER_BOTTOM_LEFT:
					case TileEntity::TileType::FLIPPER_BOTTOM_RIGHT:
						tiles.push_back(new FlipperWedgeTileEntity(eventManager, type, width - j, height - i));
						break;
					case TileEntity::TileType::HOLE_ENTER:
						holeEnterTile = new HoleEnterTileEntity(eventManager, type, width - j, height - i);
						tiles.push_back(holeEnterTile);
						break;
					case TileEntity::TileType::HOLE_EXIT:
						holeExitTile = new HoleExitTileEntity(eventManager, type, width - j, height - i);
						tiles.push_back(holeExitTile);
						break;
					case TileEntity::TileType::SPAWN:
						spawnTile = new SpawnTileEntity(eventManager, type, width - j, height - i);
						tiles.push_back(spawnTile);
						break;
					case TileEntity::TileType::WEDGE_BOTTOM_LEFT:
					case TileEntity::TileType::WEDGE_BOTTOM_RIGHT:
					case TileEntity::TileType::WEDGE_TOP_LEFT:
					case TileEntity::TileType::WEDGE_TOP_RIGHT:
						tiles.push_back(new WedgeTileEntity(eventManager, type, width - j, height - i));
						break;
				}
			}
		}
	}
	catch (std::invalid_argument e)
	{
		logger.Warn("Level file " + relativeFilePath + " is invalid.");
	}

	if (entities != nullptr)
	{
		for (Entity * tile : tiles)
		{
			entities->push_back(tile);
		}
	}

	Level l = Level(tiles);
	if (spawnTile != nullptr)
	{
		l.SetSpawnTile(spawnTile);
		l.SetHoleEnterTile(holeEnterTile);
		l.SetHoleExitTile(holeExitTile);
	}

	return l;
}

void File::WriteToFile(string relativeFilePath, string contents, size_t maxFileSize)
{
	ofstream file(RESOURCE_ROOT_PATH + relativeFilePath, ios_base::app);

	// Read contents into file (to retrieve pointer to position).
	file << '\n' << contents;

	// Start from the start if simply overwrite the contents.
	// This could be extended to incorporate a cyclical buffer.
	size_t fileSize = file.tellp();
	if (fileSize > maxFileSize)
	{
		ofstream fileOverwrite(RESOURCE_ROOT_PATH + relativeFilePath, ios_base::trunc);

		fileOverwrite << contents;
	}
}
