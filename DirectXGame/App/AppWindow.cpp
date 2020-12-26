#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rect = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top);

	vertex list[] = {
		// X - Y - Z
		{-0.5f, -0.5f, 0.0f}, //Position 1
		{0.0f, 0.5f, 0.0f},   //Position 2
		{0.5f, -0.5f, 0.0f},  //Position 2
	};
	m_vertex_buffer = GraphicsEngine::get()->createVertexBuffer();
	UINT list_size = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();
	void* shader_bytecode = nullptr;
	UINT shader_size = 0;

	GraphicsEngine::get()->getShaderBufferAndSize(&shader_bytecode, &shader_size);

	

	m_vertex_buffer->load(list, sizeof(vertex), list_size, shader_bytecode, shader_size );
}

void AppWindow::onUpdate()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	RECT rect = this->getClientWindowRect();

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rect.right - rect.left, rect.bottom - rect.top);
	GraphicsEngine::get()->setShaders();

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vertex_buffer->getSizeVertexList(), 0);

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	
	m_vertex_buffer->release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}