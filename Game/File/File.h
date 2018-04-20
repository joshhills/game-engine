#pragma once

#include <map>

#include <Common/LoggerInstance.h>
#include <Common/Event.h>

#include <Game/Level.h>

using namespace std;

class File {
public:
	static const string RESOURCE_ROOT_PATH;

	/**
	 * Base function to load file-stream.
	 *
	 * @param filePath	The relative path to the resource on the host system.
	 */
	//static void LoadPlainTextFile(string filePath);

	/**
	* Load config files
	*/
	static std::map<int, int> LoadControlMap(string relativeFilePath);

	static Level LoadLevel(string relativeFilePath);

private:
	static LoggerInstance logger;
};