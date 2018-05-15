#include "File.h"

// Initialize statically accessible entities.
const string File::RESOURCE_ROOT_PATH = "./Resources/";

map<File::ShaderType, Shader *> File::shaderTypes = {};
map<File::MeshType, Mesh *> File::meshTypes = {};

LoggerInstance File::logger("File");

void File::InitialiseTileGraphicsData()
{
	shaderTypes = {
		{ ShaderType::BLOCK_TILE,	new Shader(RESOURCE_ROOT_PATH + "Shaders/baseTileVert.glsl", RESOURCE_ROOT_PATH + "Shaders/blockTileFrag.glsl") },
		{ ShaderType::BUMPER_TILE,	new Shader(RESOURCE_ROOT_PATH + "Shaders/baseTileVert.glsl", RESOURCE_ROOT_PATH + "Shaders/bumperTileFrag.glsl") },
		{ ShaderType::FLIPPER_TILE, new Shader(RESOURCE_ROOT_PATH + "Shaders/baseTileVert.glsl", RESOURCE_ROOT_PATH + "Shaders/flipperTileFrag.glsl") },
		{ ShaderType::HOLE_TILE,	new Shader(RESOURCE_ROOT_PATH + "Shaders/baseTileVert.glsl", RESOURCE_ROOT_PATH + "Shaders/holeTileFrag.glsl") },
		{ ShaderType::FINISH_TILE,	new Shader(RESOURCE_ROOT_PATH + "Shaders/baseTileVert.glsl", RESOURCE_ROOT_PATH + "Shaders/finishTileFrag.glsl") }
	};

	meshTypes = {
		{ MeshType::BLOCK,							Mesh::LoadObjFile(RESOURCE_ROOT_PATH + "Models/block.obj") },
		{ MeshType::BLOCK_HALF_DIAGONAL,			Mesh::LoadObjFile(RESOURCE_ROOT_PATH + "Models/block-half-diagonal.obj") },
		{ MeshType::BUMPER,							Mesh::LoadObjFile(RESOURCE_ROOT_PATH + "Models/bumper.obj") },
		{ MeshType::FLIPPER_BLOCK,					Mesh::LoadObjFile(RESOURCE_ROOT_PATH + "Models/flipper-block.obj") },
		{ MeshType::FLIPPER_BLOCK_HALF_DIAGONAL,	Mesh::LoadObjFile(RESOURCE_ROOT_PATH + "Models/flipper-block-half-diagonal.obj") },
		{ MeshType::HOLE_ENTER,						Mesh::LoadObjFile(RESOURCE_ROOT_PATH + "Models/hole-enter.obj") },
		{ MeshType::HOLE_EXIT,						Mesh::LoadObjFile(RESOURCE_ROOT_PATH + "Models/hole-exit.obj") }
	};
}

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

Level * File::LoadLevel(EventManager * eventManager, string relativeFilePath, vector<Entity *> * entities)
{
	vector<TileEntity *> tiles;

	ifstream file(RESOURCE_ROOT_PATH + relativeFilePath);

	if (!file) {
		logger.Error("Could not load level file " + relativeFilePath + ".");
		return new Level(tiles, entities);
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
				// Read in the tile type and shader.
				int rawTileType;
				int rawShaderType;
				int rawMeshType;

				file >> rawTileType;
				file >> rawShaderType;
				file >> rawMeshType;

				TileEntity::TileType tileType = static_cast<TileEntity::TileType>(rawTileType);
				ShaderType shaderType = static_cast<ShaderType>(rawShaderType);
				MeshType meshType = static_cast<MeshType>(rawMeshType);

				Shader * shader = nullptr;
				Mesh * mesh = nullptr;

				if (rawShaderType > 0)
				{
					try
					{
						shader = shaderTypes.at(shaderType);
					} 
					catch (out_of_range e)
					{
						logger.Warn("Undefined shader type" + to_string((int) shaderType) + " for tile");
					}
				}

				if (rawMeshType > 0)
				{
					try
					{
						mesh = meshTypes.at(meshType);
					}
					catch (out_of_range e)
					{
						logger.Warn("Undefined mesh type" + to_string((int) meshType) + " for tile");
					}
				}

				// Convert this type to a tile type.
				switch (tileType)
				{
					case TileEntity::TileType::BLOCK:
						tiles.push_back(new BlockTileEntity(eventManager, new GraphicsData(mesh, shader), tileType, width - j, height - i));
						break;
					case TileEntity::TileType::BUMPER:
						tiles.push_back(new BumperTileEntity(eventManager, new GraphicsData(mesh, shader), tileType, width - j, height - i));
						break;
					case TileEntity::TileType::FINISH:
						tiles.push_back(new FinishTileEntity(eventManager, new GraphicsData(mesh, shader), tileType, width - j, height - i));
						break;
					case TileEntity::TileType::FLIPPER_TOP:
					case TileEntity::TileType::FLIPPER_LEFT:
					case TileEntity::TileType::FLIPPER_BOTTOM:
					case TileEntity::TileType::FLIPPER_RIGHT:
						tiles.push_back(new FlipperBlockTileEntity(eventManager, new GraphicsData(mesh, shader), tileType, width - j, height - i));
						break;
					case TileEntity::TileType::FLIPPER_TOP_LEFT:
					case TileEntity::TileType::FLIPPER_TOP_RIGHT:
					case TileEntity::TileType::FLIPPER_BOTTOM_LEFT:
					case TileEntity::TileType::FLIPPER_BOTTOM_RIGHT:
						tiles.push_back(new FlipperWedgeTileEntity(eventManager, new GraphicsData(mesh, shader), tileType, width - j, height - i));
						break;
					case TileEntity::TileType::HOLE_ENTER:
						tiles.push_back(new HoleEnterTileEntity(eventManager, new GraphicsData(mesh, shader), tileType, width - j, height - i));
						break;
					case TileEntity::TileType::HOLE_EXIT:
						holeExitTile = new HoleExitTileEntity(eventManager, new GraphicsData(mesh, shader), tileType, width - j, height - i);
						tiles.push_back(holeExitTile);
						break;
					case TileEntity::TileType::SPAWN:
						spawnTile = new SpawnTileEntity(eventManager, tileType, width - j, height - i);
						tiles.push_back(spawnTile);
						break;
					case TileEntity::TileType::WEDGE_BOTTOM_LEFT:
					case TileEntity::TileType::WEDGE_BOTTOM_RIGHT:
					case TileEntity::TileType::WEDGE_TOP_LEFT:
					case TileEntity::TileType::WEDGE_TOP_RIGHT:
						tiles.push_back(new WedgeTileEntity(eventManager, new GraphicsData(mesh, shader), tileType, width - j, height - i));
						break;
				}
			}
		}
	}
	catch (std::invalid_argument e)
	{
		logger.Warn("Level file " + relativeFilePath + " is invalid.");
	}

	Level * l = new Level(tiles, entities);
	if (spawnTile != nullptr)
	{
		l->SetSpawnTile(spawnTile);
		l->SetHoleExitTile(holeExitTile);
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
