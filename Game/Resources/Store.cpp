#include "Store.h"

Store::Store(size_t size, int count)
	: size(size),
	count(count)
{
	// Initialise bin/space mapping.
	AllocateNewBin();
}

Store::~Store()
{
	// Free memory bins.
	for (char * bin : bins)
	{
		delete bin;
	}
}

void * Store::Add()
{
	// Find the next free space.
	bool isFree;

	// From the last free space logged...
	for (int i = lastActiveBinIndex; i < bins.size(); i++)
	{
		// Check if it is indeed free.
		int nextFreeSpace = GetNextFreeSpaceInBin(bins[i], lastFreeIndex);

		isFree = nextFreeSpace != -1;

		if (isFree)
		{
			lastActiveBinIndex = i;
			lastFreeIndex = nextFreeSpace;
			lastFreeSpace = bins[i] + (size * lastFreeIndex);

			break;
		}
	}

	// If there were no free spaces in any of the bins.
	if (!isFree)
	{
		AllocateNewBin();
	}

	// By this point, we have a pointer to a free space.
	MemoryChunk mc;
	mc.binIndex = lastActiveBinIndex;
	mc.index = lastFreeIndex;
	mc.state = MemoryState::ALLOCATED;
	memoryStates[lastFreeSpace] = mc;

	return lastFreeSpace;
}

void Store::Remove(void * location)
{
	char * l = (char *)location;

	// Remove from mapping.
	memoryStates[l].state = MemoryState::FREE;

	// If this newly freed space is earlier sequentially than the last free space, overwrite it.
	if ((memoryStates[l].binIndex < lastActiveBinIndex)
		|| (memoryStates[l].binIndex == lastActiveBinIndex && memoryStates[l].index < lastFreeIndex))
	{
		lastFreeIndex = memoryStates[l].index;
		lastActiveBinIndex = memoryStates[l].binIndex;
		lastFreeSpace = bins[lastActiveBinIndex] + size * lastFreeIndex;
	}
}

Store::MemoryState Store::GetMemoryState(char * location) const
{
	return memoryStates.at(location).state;
}

bool Store::IsFree(char * location) const
{
	return GetMemoryState(location) == MemoryState::FREE;
}

char * Store::AllocateNewBin()
{
	lastFreeSpace = (char *)malloc(size * count);
	lastFreeIndex = 0;

	bins.push_back(lastFreeSpace);

	lastActiveBinIndex = bins.size() - 1;

	FreeMemoryStatesForBin(lastActiveBinIndex);

	return lastFreeSpace;
}

void Store::FreeMemoryStatesForBin(int binIndex)
{
	// Set all states in bin to free.
	for (int i = 0; i < count; i++)
	{
		MemoryChunk mc = memoryStates[bins[binIndex] + (size * i)];
		mc.state = MemoryState::FREE;
		mc.binIndex = binIndex;
		mc.index = i;
	}
}

int Store::GetNextFreeSpaceInBin(char * bin, int offset)
{
	bool isFree;

	do
	{
		isFree = IsFree(bin + size * offset);
		offset++;
	} while (!isFree && offset < count);

	if (isFree)
	{
		return offset - 1;
	}
	else
	{
		return -1;
	}
}