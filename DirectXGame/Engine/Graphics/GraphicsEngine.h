#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine
{
public:
	
	bool init(); // Initialize GraphicsEngine and DirectX 11 Device
	bool release(); // Release all the occupied resources
	static GraphicsEngine* get();
	RenderSystem* getRenderSystem();
private:
	RenderSystem* m_render_system = nullptr;
};

