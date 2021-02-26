#include "TextureManager.h"
#include "Texture.h"

TexturePtr TextureManager::createTextureFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<Texture>(createResourceFromFile(file_path));
}

Resource* TextureManager::createResourceFromFileInternal(const wchar_t* file_path)
{
	Texture* tex = nullptr;

	try
	{
		tex = new Texture(file_path);
	}
	catch (...) { }
	return tex;
}
