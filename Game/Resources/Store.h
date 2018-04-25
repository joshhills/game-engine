#pragma once

#include <map>
#include <vector>
#include <malloc.h>

/**
 * Store objects of a specific size in bins. 
 */
class Store {
public:
	/**
	 * @param size	The maximum potential size of the object type to store.
	 * @param count	The bin size.
	 */
	Store(size_t size, int count);

	~Store();

	void * Add();
	void Remove(void * location);

	enum class MemoryState
	{
		FREE,
		ALLOCATED
	};

	struct MemoryChunk
	{
		MemoryState state;
		int binIndex;
		int index;
	};
private:
	// The max potential size of the object type to store.
	size_t size;

	// The bin size.
	int count;

	// Store a reference to the start of all bins.
	std::vector<char *> bins;
	int lastActiveBinIndex = 0;

	// Store a pointer to the last free space.
	char * lastFreeSpace;
	int lastFreeIndex;

	std::map<char *, MemoryChunk> memoryStates;

	MemoryState GetMemoryState(char * location) const;
	bool IsFree(char * location) const;
	char * AllocateNewBin();
	void FreeMemoryStatesForBin(int binIndex);

	// TODO: Do this function to replace the loop in add.
	int GetNextFreeSpaceInBin(char * bin, int offset);
};