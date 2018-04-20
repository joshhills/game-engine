#include "File.h"

// Initialize statically accessible entities.
const string File::RESOURCE_ROOT_PATH = "./Resources/";

LoggerInstance File::logger("File");

// Inspired by SO 13262568.
std::map<int, int> File::LoadControlMap(string relativeFilePath)
{
	std::map<int, int> controlMap;

	ifstream file(RESOURCE_ROOT_PATH + relativeFilePath);

	if (!file) {
		logger.Error("Could not load settings file " + relativeFilePath + ".");
		return controlMap;
	}

	string line;

	int lineNumber = 0;
	while (std::getline(file, line))
	{
		lineNumber++; 

		int pos = line.find('=');
		if (pos != string::npos)
		{
			// TODO: Error handling.
			string keyString = line.substr(0, pos);
			string valueString = line.substr(pos + 1);
			
			try
			{
				int key = std::stoi(keyString);
				int value = std::stoi(valueString);

				controlMap[key] = value;
			}
			catch (std::invalid_argument e)
			{
				logger.Warn("Invalid argument found in settings file " + relativeFilePath + ", line; skipping it." + std::to_string(lineNumber));
			}
		}
	}

	return controlMap;
}

Level File::LoadLevel(string relativeFilePath)
{
	vector<TileEntity *> tiles;

	ifstream file(RESOURCE_ROOT_PATH + relativeFilePath);

	if (!file) {
		logger.Error("Could not load settings file " + relativeFilePath + ".");
		return Level(tiles);
	}



	return Level(tiles);
}
