#include "stdafx.h"
#include "JScriptManager.h"

std::wstring JScriptManager::ReadJScript(std::wstring path)
{
	std::wifstream file(path);
	std::wstringstream fileStream;
	fileStream << file.rdbuf();
	return fileStream.str();
}
