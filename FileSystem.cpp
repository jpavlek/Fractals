#include "FileSystem.h"
#include <iostream>

#if (__cplusplus >= 201703L) //201703L (C++17) //202002L (C++20)
#include <filesystem>
#elif (__cplusplus >= 201402L) //201402L (C++14)
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#else //201103L (C++11) //199711L (C++98 or C++03) 
#include <windows.h>
#endif

#if (__cplusplus >= 201703L) //202002L (C++20) //201703L (C++17)
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

#elif (__cplusplus >= 201402L) //201402L (C++14)

bool FileSystem::checkRelativeFilePath(std::string filename)
{
	const std::experimental::filesystem::path path = std::experimental::filesystem::current_path() / filename;
	if (std::experimental::filesystem::exists(path)) return true;

#ifdef _DEBUG
	std::cout << path << " does not exist, creating it.\n";
#endif // _DEBUG
	if (std::experimental::filesystem::create_directory(path)) return true;

	return false;
}

#else //201103L (C++11) //199711L (C++98 or C++03) 
bool FileSystem::checkRelativeFilePath(std::string filename)
{
	checkFilePath(filename);
	return false;
}

bool FileSystem::checkFilePath(std::string filename)
{
	bool result = false;

	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	errno_t err;
	int r = strcpy_s(path_buffer, sizeof path_buffer, filename.c_str());

	std::cout << "\nPath buffer: " << path_buffer << "\n\n";
	err = _splitpath_s(path_buffer, drive, _MAX_DRIVE, dir, _MAX_DIR, fname,
		_MAX_FNAME, ext, _MAX_EXT);
	if (err != 0)
	{
		std::cout << "\nError splitting the path. Error code " << err << ".\n";
		result = false;
	}

	const char* dirName = dir;
	if (!CreateDirectoryA(dirName, NULL))
	{
		std::cout << "\nDirectory: " << dirName << " could not be created... Check if it already exists.\n";
		result = false;
	}

	return result;
}

#endif


