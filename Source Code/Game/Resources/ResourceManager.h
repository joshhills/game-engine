#pragma once

#include "Store.h"

/**
* Responsible for loading a resource manifest at engine startup
* and furthermore managing the creation of common dynamic objects
* for the purposes of efficiency.
*/
class ResourceManager {
public:
	/*
	* Managed stores - theoretically everything
	* could be memory-managed, however these are
	* the most duplicitous.
	*/

	// Manage events.
	static Store eventStore;
	// Manage entities.
	static Store entityStore;

	ResourceManager();
	~ResourceManager();

	/**
	* Asset list of file paths relative to resource root.
	*/
	//struct Manifest {
	//	string meshes[];
	//};

private:
	//Manifest * manifest;
};