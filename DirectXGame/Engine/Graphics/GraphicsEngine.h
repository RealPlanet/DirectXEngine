#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"

class GraphicsEngine
{
public:
	static GraphicsEngine* get();
	static void create();
	static void release();

	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();
private:
	RenderSystem* m_render_system = nullptr;
	TextureManager* m_tex_manager = nullptr;
	static GraphicsEngine* m_engine;

	GraphicsEngine(); // Initialize GraphicsEngine and DirectX 11 Device
	~GraphicsEngine(); // Release all the occupied resources
};

