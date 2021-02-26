#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <d3dcompiler.h>

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
	catch (...) { throw std::exception("Failed to create RenderSystem"); }
}

// Release all of the resources used by the graphics engine
GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
	delete m_tex_manager;
	delete m_render_system;
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
