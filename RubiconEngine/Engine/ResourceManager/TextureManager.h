#pragma once
#include "ResourceManager.h"

class TextureManager : public ResourceManager
{
public:
	TextureManager() : ResourceManager() {};
	TexturePtr createTextureFromFile(const wchar_t* file_path);

protected:
	virtual Resource* createResourceFromFileInternal(const wchar_t* file_path) override;
};

