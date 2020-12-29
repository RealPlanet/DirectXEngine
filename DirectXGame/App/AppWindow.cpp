#include "AppWindow.h"
#include "generics.h"
#include <Windows.h>

void AppWindow::updateQuadPosition()
{
	constant cc;
	cc.m_time = GetTickCount();
	m_delta_pos += m_delta_time  / 5.0f;
	if (m_delta_pos > 1.0f) m_delta_pos = 0;
	m_delta_scale += m_delta_time / 2.0f;

	Matrix4x4 temp;
	temp.setIdentity();
	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_delta_pos));

	//IMPORTANT :: Scale before translation!! OR Invert multiplication S X T = Final Matrix
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0, 0, 0), Vector3D(1.0f, 1.0f, 0), (float)sin(m_delta_scale)));
	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));

	//cc.m_world *= temp;

	cc.m_world.setScale(Vector3D(1, 1, 1));

	temp.setIdentity();
	temp.setRotationZ(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_delta_scale);
	cc.m_world *= temp;

	cc.m_view.setIdentity();
	cc.m_projection.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
		-4.0f,
		4.0f
	);


	m_constant_buffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rect = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top);

	// Test cube
	vertex list[] = {
		// X - Y - Z
		// Front face of the cube
		{Vector3D(-0.5f, -0.5f, -0.5f),			Vector3D(1, 1, 1)			,	Vector3D(0, 0, 0)},		//Position 0
		{Vector3D(-0.5f, 0.5f, -0.5f),			Vector3D(0, 0, 0)			,	Vector3D(0, 0, 0)},		//Position 1
		{Vector3D(0.5f, 0.5f, -0.5f),			Vector3D(1, 0, 0)			,	Vector3D(0, 0, 0)},	//Position 2
		{Vector3D(0.5f, -0.5f, -0.5f),			Vector3D(0, 1, 0)			,	Vector3D(0, 0, 0)},		//Position 3

		// Back face of the cube
		{Vector3D(0.5f, -0.5f, 0.5f),			Vector3D(0, 0, 1)			,	Vector3D(0, 0, 0)},		//Position 4
		{Vector3D(0.5f, 0.5f, 0.5f),			Vector3D(0.5f, 0.5f, 0.5f)	,	Vector3D(0, 0, 0)},		//Position 5
		{Vector3D(-0.5f, 0.5f, 0.5f),			Vector3D(1, 1, 0)			,	Vector3D(0, 0, 0)},		//Position 6
		{Vector3D(-0.5f, -0.5f, 0.5f),			Vector3D(1, 0, 1)			,	Vector3D(0, 0, 0)}		//Position 7
	};
	unsigned int index_list[] = {
		// Front face of cube
		0, 1, 2, // First triangle
		2, 3, 0, // Second triangle

		// Back face
		4, 5, 6,
		6, 7, 4,

		// Top face
		1, 6, 5,
		5, 2, 1,

		// Bottom face

		7, 0, 3,
		3, 4, 7,

		// Right side
		3, 2, 5,
		5, 4, 3,

		//Left side
		7, 6, 1,
		1, 0, 7
	};
	UINT list_size = ARRAYSIZE(list);
	UINT index_size = ARRAYSIZE(index_list);
	m_vertex_buffer = GraphicsEngine::get()->createVertexBuffer();
	m_index_buffer = GraphicsEngine::get()->createIndexBuffer();

	m_index_buffer->load(index_list, index_size);

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

	updateQuadPosition();
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, m_constant_buffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, m_constant_buffer);

	//Default shaders for Graphics pipeline
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vertex_shader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_pixel_shader);

	// Set vertices to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	// Set indices to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_index_buffer);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vertex_buffer->getSizeVertexList(), 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_index_buffer->getSizeIndexList(),0, 0);
	m_swap_chain->present(false);

	m_old_delta = m_new_delta;
	m_new_delta = GetTickCount();
	m_delta_time = m_old_delta ? (m_new_delta - m_old_delta) / 1000.0f : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	
	m_vertex_buffer->release();
	m_index_buffer->release();
	m_constant_buffer->release();
	m_swap_chain->release();
	m_vertex_shader->release();
	m_pixel_shader->release();
	

	GraphicsEngine::get()->release();
}