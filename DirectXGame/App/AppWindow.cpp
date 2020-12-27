#include "AppWindow.h"
#include "generics.h"
#include <Windows.h>


void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rect = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top);

	// Triangle strip aproach
	vertex list[] = {
		// X - Y - Z ---------- X1 - Y1 - Z1	----------  R- G- B --- R-G-B
		{-0.5f, -0.5f, 0.0f,	-0.32f, -0.55f, 0.0f,		1, 0, 0,	0,0,0},	//Position 1
		{-0.5f, 0.5f, 0.0f,		-0.68f, 0.78f, 0.0f,		1, 1, 0,	0,0,1},   //Position 2
		{0.5f, -0.5f, 0.0f,		0.58f, -0.511f, 0.0f,		0, 0, 0,	1,1,1},	//Position 3
		{0.5f, 0.5f, 0.0f,		0.68f, 0.8f, 0.0f,			1, 0, 1,	0,1,0}	//Position 4
	};

	m_vertex_buffer = GraphicsEngine::get()->createVertexBuffer();
	UINT list_size = ARRAYSIZE(list);

	void* shader_bytecode = nullptr;
	size_t shader_size = 0;

	GraphicsEngine::get()->compileVertexShader(L"Shaders\\VertexShader.hlsl", "main", &shader_bytecode, &shader_size);
	m_vertex_shader = GraphicsEngine::get()->createVertexShader(shader_bytecode, shader_size);
	m_vertex_buffer->load(list, sizeof(vertex), list_size, shader_bytecode, (UINT)shader_size );
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"Shaders\\PixelShader.hlsl", "main", &shader_bytecode, &shader_size);
	m_pixel_shader = GraphicsEngine::get()->createPixelShader(shader_bytecode, shader_size);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;
	m_constant_buffer = GraphicsEngine::get()->createConstantBuffer();
	m_constant_buffer->load(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	RECT rect = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rect.right - rect.left, rect.bottom - rect.top);

	constant cc;
	cc.m_time = GetTickCount();
	m_constant_buffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, m_constant_buffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, m_constant_buffer);

	//Default shaders for Graphics pipeline
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vertex_shader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_pixel_shader);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vertex_buffer->getSizeVertexList(), 0);

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	
	m_vertex_buffer->release();
	m_swap_chain->release();
	m_vertex_shader->release();
	m_pixel_shader->release();

	GraphicsEngine::get()->release();
}