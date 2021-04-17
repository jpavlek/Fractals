#pragma once
#include <string>

class FileSystem
{
public:
	static bool checkRelativeFilePath(std::string filename);

#if (__cplusplus < 201402L) //201103L (C++11) //199711L (C++98 or C++03) 
	static bool checkFilePath(std::string filename);
#endif

};

