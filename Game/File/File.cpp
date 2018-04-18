#include "File.h"

#include <Common/Event.h>

// Initialize statically accessible entities.
const string File::RESOURCE_ROOT_PATH = "./Resources/";

// Inspired by SO 13262568.
std::map<int, int> File::LoadControlMap(string relativeFilePath)
{
	ifstream file(RESOURCE_ROOT_PATH + relativeFilePath);
	string line;

	std::map<int, int> controlMap;

	while (std::getline(file, line))
	{
		int pos = line.find('=');
		if (pos != string::npos)
		{
			// TODO: Error handling.
			string keyString = line.substr(0, pos);
			string valueString = line.substr(pos + 1);
			
			int key = std::stoi(keyString);
			int value = std::stoi(valueString);

			controlMap[key] = value;
		}
	}

	return controlMap;
}
