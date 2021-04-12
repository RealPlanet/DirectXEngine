#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "DeviceContext.h"
#include <d3dcompiler.h>
#include <iostream>

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		m_render_system = new RenderSystem();
	}
	catch (...) { throw std::exception("Failed to create RenderSystem"); }

	try
	{
		m_tex_manager = new TextureManager(); //This depends on RenderSystem so goes after
	}
	catch (...) { throw std::exception("Failed to create TextureManager"); }

	try
	{
		m_mesh_manager = new MeshManager(); //This depends on RenderSystem so goes after
	}
	catch (...) { throw std::exception("Failed to create MeshManager"); }


	void* shader_bytecode = nullptr;
	size_t shader_size = 0;
	m_render_system->compileVertexShader(L"Shaders\\VertexMeshLayoutShader.hlsl", "main", &shader_bytecode, &shader_size);
	memcpy(m_mesh_layout_bytecode, shader_bytecode, shader_size);
	m_mesh_layout_size = shader_size;
	m_render_system->releaseCompiledShader();

}

// Release all of the resources used by the graphics engine
GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
	delete m_mesh_manager;
	delete m_tex_manager;
	delete m_render_system; // ALWAYS LAST!
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::m_engine) throw std::exception("Graphics Engine already created!");

	m_engine = new GraphicsEngine();
}

void GraphicsEngine::release()
{
	if (!GraphicsEngine::m_engine) return;
	delete GraphicsEngine::m_engine;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

GraphicsEngine* GraphicsEngine::get()
{
	return m_engine;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return m_mesh_manager;
}

MaterialPtr GraphicsEngine::createMaterial(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	MaterialPtr material = nullptr;

	try
	{
		material = std::make_shared<Material>(vertex_shader_path, pixel_shader_path);
	}
	catch (...) {}

	return material;
}

MaterialPtr GraphicsEngine::createMaterial(const MaterialPtr& other_material)
{
	MaterialPtr material = nullptr;

	try
	{
		material = std::make_shared<Material>(other_material);
	}
	catch (...) {}

	return material;
}

void GraphicsEngine::setMaterial(const MaterialPtr& material)
{
	GraphicsEngine::get()->getRenderSystem()->setRasterizerState(material->m_cull_mode == CULL_MODE_FRONT);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(material->m_vertex_shader, material->m_constant_buffer);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(material->m_pixel_shader, material->m_constant_buffer);

	//Set shaders for the graphics pipeline
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(material->m_vertex_shader);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(material->m_pixel_shader);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(material->m_pixel_shader, &material->m_vec_textures[0], material->m_vec_textures.size());
}

void GraphicsEngine::getVertexMeshLayoutByteCodeAndSize(void** bytecode, size_t* size)
{
	*bytecode = m_mesh_layout_bytecode;
	*size = m_mesh_layout_size;
}
