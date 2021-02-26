#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine
{
public:
	static GraphicsEngine* get();
	static void create();
	static void release();

	RenderSystem* getRenderSystem();

private:
	RenderSystem* m_render_system = nullptr;
	static GraphicsEngine* m_engine;

	GraphicsEngine(); // Initialize GraphicsEngine and DirectX 11 Device
	~GraphicsEngine(); // Release all the occupied resources
};

