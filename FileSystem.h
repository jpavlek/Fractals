#pragma once
#include <string>

class FileSystem
{
public:
	static bool checkRelativeFilePath(std::string filename);
	static bool checkFilePath(std::string filename);
};

