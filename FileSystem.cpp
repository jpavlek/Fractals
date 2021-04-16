#include "FileSystem.h"
#include <filesystem>
#include <iostream>

bool FileSystem::checkRelativeFilePath(std::string filename)
{
	const std::filesystem::path path = std::filesystem::current_path() / filename;
	
	if (std::filesystem::exists(path)) return true;

#ifdef _DEBUG
	std::cout << path << " does not exist, creating it.\n";
#endif // _DEBUG

	if (std::filesystem::create_directory(path)) return true;
	
	return false;
}
