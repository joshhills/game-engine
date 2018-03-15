#pragma once

#include <Common/Subsystem.h>
#include <Common/LoggerInstance.h>
#include <Common/EventManager.h>

using namespace std;

class File : Subsystem {
public:
	File(EventManager * eventManager, vector<Entity *> * entities);
	~File();

	void Update();
private:
	// Engine state.
	vector<Entity*> * entities;

	/**
	 * Base function to load file-stream.
	 *
	 * @param filePath	The relative path to the resource on the host system.
	 */
	void LoadPlainTextFile(string filePath);

	// TODO: Return references to class objects.
};