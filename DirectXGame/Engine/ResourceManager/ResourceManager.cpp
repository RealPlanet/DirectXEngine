#include "ResourceManager.h"
#include <filesystem>
#include <iostream>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t* file_path)
{
    std::wstring fullPath = std::filesystem::absolute(file_path);
    auto iterator = m_map_resources.find(fullPath);

    if (iterator != m_map_resources.end())
    {
        return iterator->second; //If resource is already present then return it
    }

    Resource* raw_res = this->createResourceFromFileInternal(fullPath.c_str()); //Create and add resource
    if (raw_res)
    {
        ResourcePtr res(raw_res);
        m_map_resources[fullPath] = res;
        return res;
    }
    

    return nullptr;
}
