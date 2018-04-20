#pragma once

#include <Common/Entity.h>

/**
 * Wrapper class for tile entities.
 */
class TileEntity : Entity {
public:

	/**
	 * Tile types and embedded orientation used for
	 * serialisation in file operations.
	 */
	enum class TileTypes {
		NOTHING = 0,
		BLOCK = 1,
		WEDGE_BOTTOM_LEFT = 2,
		WEDGE_TOP_LEFT = 3,
		WEDGE_TOP_RIGHT = 4,
		WEDGE_BOTTOM_RIGHT = 5,
		FLIPPER_TOP = 6,
		FLIPPER_RIGHT = 7,
		FLIPPER_BOTTOM = 8,
		FLIPPER_LEFT = 9,
		FLIPPER_BOTTOM_LEFT = 10,
		FLIPPER_TOP_LEFT = 11,
		FLIPPER_TOP_RIGHT = 12,
		FLIPPER_BOTTOM_RIGHT = 13,
		BUMPER = 14,
		HOLE_ENTER = 15,
		HOLE_EXIT = 16,
		SPAWN = 17,
		FINISH = 18
	};

	/**
	* Constructor to create a tile entity.
	*
	* @param gridPositionX	The position on the grid this entity should be positioned horizontally.
	* @param gridPositionX	The position on the grid this entity should be positioned vertically.
	*/
	TileEntity(int gridPositionX, int gridPositionY) {};

	virtual ~TileEntity() {}
};