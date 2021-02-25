#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <d3dcompiler.h>


bool GraphicsEngine::init()
{
	m_render_system = new RenderSystem();
	m_render_system->init();
	return true;
}

// Release all of the resources used by the graphics engine
bool GraphicsEngine::release()
{
	m_render_system->release();
	delete m_render_system;
	return true;
}


GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine; //Returns the current instance of GraphicsEnngine, only one instance is allowed.
	return &engine;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}
