#pragma once

#include <stdio.h>
#include <map>

#include <Common/LoggerInstance.h>
#include <Common/Event.h>

#include <Game/Level.h>

using namespace std;

/**
 * Gateway library to manage file I/O operations.
 */
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

	// TODO: Comment.
	static Level LoadLevel(string relativeFilePath);

	static void WriteToFile(string relativeFilePath, string contents, size_t maxFileSize = 30000);
private:
	static LoggerInstance logger;
};