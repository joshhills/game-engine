#pragma once

#include <Common/Subsystem.h>
#include <Common/SubsystemLifecycle.h>
#include <Common/InputEvent.h>
#include "Store.h"

/**
* Responsible for loading a resource manifest at engine startup
* and furthermore managing the creation of common dynamic objects
* for the purposes of efficiency.
*/
class ResourceManagement : Subsystem, SubsystemLifecycle {
public:
	ResourceManagement(EventManager * eventManager);
	~ResourceManagement();

	/**
	* Create stores for common dynamic objects and
	* furthermore load manifest.
	*/
	void StartUp() override;

	/**
	* Flush managed memory.
	*/
	void ShutDown() override {};

	/**
	* Degragmentation operations.
	*/
	void Update() override;

	/**
	* Asset list of file paths relative to resource root.
	*/
	struct Manifest {
		string meshes[];
	};

	//static Store eventStore;

private:
	Manifest * manifest;


	//Store gameObjectStore;
	//Store meshStore;
	//Store audioStore;

	// Store bins for all types of information.
	// Entity bin
	// Level bin
	// Controller settings bin
};