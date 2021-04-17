#pragma once
#include <string>

namespace FileSystem
{

class FileSystem
{
public:
	static bool checkRelativeFilePath(std::string filename);

/**
*	By default __cplusplus variable in MS Visual Studio (2019) is set to pre-C++-11-standard value: 199711L (C++98 or C++03) for backward compatibility reasons.
*	To get the correct value of __cplusplus in order to support different versions of C++ standard, compiler option /Zc:__cplusplus should be enabled.
*	To enable /Zc:__cplusplus option, go to Project -> Fractals Properties -> Configuration Properties -> C/C++ -> Command Line -> Additional Options: /Zc:__cplusplus.
*	Please, make sure that it is properly set in both Debug and Release Configuration, as well as for x64 (and Win32) platform(s).
*/
#if (__cplusplus < 201402L) //201103L (C++11) //199711L (C++98 or C++03) 
	static bool checkFilePath(std::string filename);
#endif

};

}