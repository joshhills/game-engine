#pragma once

#include <stdio.h>
#include <map>

#include <Common/LoggerInstance.h>
#include <Common/Event.h>
#include <Common/EventManager.h>

#include <Game/Level.h>
#include <Game/TileEntity.h>
#include <Game/BlockTileEntity.h>
#include <Game/BumperTileEntity.h>
#include <Game/FinishTileEntity.h>
#include <Game/FlipperBlockTileEntity.h>
#include <Game/FlipperWedgeTileEntity.h>
#include <Game/HoleEnterTileEntity.h>
#include <Game/HoleExitTileEntity.h>
#include <Game/SpawnTileEntity.h>
#include <Game/WedgeTileEntity.h>

using namespace std;

/**
 * Gateway library to manage file I/O operations.
 */
class File {
public:
	// For second submission, embed shader type into data.
	enum class ShaderType
	{
		BLOCK_TILE = 1,
		BUMPER_TILE = 2,
		FLIPPER_TILE = 3,
		HOLE_TILE = 4
	};

	enum class MeshType
	{
		BLOCK = 1,
		BLOCK_HALF_DIAGONAL = 2,
		BUMPER = 3,
		FLIPPER_BLOCK = 4,
		FLIPPER_BLOCK_HALF_DIAGONAL = 5,
		HOLE_ENTER = 6,
		HOLE_EXIT = 7
	};

	static const string RESOURCE_ROOT_PATH;

	/** 
	 * Initialise shader map for level I/O (after OpenGL context has been created).
	 */
	static void InitialiseTileGraphicsData();

	/**
	* Load controller configuration file.
	* 
	* @param relativeFilePath	The relative path to the resource on the host system.
	*/
	static std::map<int, int> LoadControlMap(string relativeFilePath);

	/**
	 * Load a game level's tiles.
	 */
	static Level LoadLevel(EventManager * eventManager, string relativeFilePath, vector<Entity *> * entities);

	static void WriteToFile(string relativeFilePath, string contents, size_t maxFileSize = 30000);
private:
	static LoggerInstance logger;

	// Store shader resolution per tile (so ones for tiles are re-used).
	static map<ShaderType, Shader *> shaderTypes;
	static map<MeshType, Mesh *> meshTypes;
};