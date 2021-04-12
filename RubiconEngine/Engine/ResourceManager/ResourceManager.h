#pragma once
#include <unordered_map>
#include <string>
#include "..\Graphics\Prerequisites.h"
#include "Resources\Resource.h"

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	ResourcePtr createResourceFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileInternal(const wchar_t* file_path) = 0;
private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
};

