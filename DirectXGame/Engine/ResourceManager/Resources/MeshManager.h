#pragma once
#include "ResourceManager.h"

class MeshManager : public ResourceManager
{
public:
	MeshManager() : ResourceManager() {};
	MeshPtr createMeshFromFile(const wchar_t* file_path);

protected:
	virtual Resource* createResourceFromFileInternal(const wchar_t* file_path) override;
};
