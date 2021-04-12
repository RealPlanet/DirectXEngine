#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "RenderSystem.h"
#include "..\ResourceManager\TextureManager.h"
#include "..\ResourceManager\MeshManager.h"

class GraphicsEngine
{
public:
	static GraphicsEngine* get();
	static void create();
	static void release();

	RenderSystem*	getRenderSystem();
	TextureManager* getTextureManager();
	MeshManager*	getMeshManager();

	void getVertexMeshLayoutByteCodeAndSize(void** bytecode, size_t* size);
private:
	RenderSystem*	m_render_system = nullptr;
	TextureManager* m_tex_manager	= nullptr;
	MeshManager*	m_mesh_manager	= nullptr;
	static GraphicsEngine* m_engine;

	GraphicsEngine(); // Initialize GraphicsEngine and DirectX 11 Device
	~GraphicsEngine(); // Release all the occupied resources

	unsigned char m_mesh_layout_bytecode[1024];
	size_t m_mesh_layout_size = 0;
};

