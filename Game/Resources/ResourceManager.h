#pragma once

#include "Store.h"

/**
* Responsible for loading a resource manifest at engine startup
* and furthermore managing the creation of common dynamic objects
* for the purposes of efficiency.
*/
class ResourceManager {
public:
	static Store eventStore;

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

	//Store gameObjectStore;
	//Store meshStore;
	//Store audioStore;

	// Store bins for all types of information.
	// Entity bin
	// Level bin
	// Controller settings bin
};