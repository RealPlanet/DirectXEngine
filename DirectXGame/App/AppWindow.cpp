#include "AppWindow.h"
#include <Windows.h>

void AppWindow::update()
{
	constant cc;
	Matrix4x4 world_cam;
	Matrix4x4 temp;

	cc.m_time = ::GetTickCount();
	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;
	m_delta_scale += m_delta_time / 0.55f;

	cc.m_world.setIdentity();
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D newPos = m_world_cam.getTranslation() + m_world_cam.getZDirection() * (m_forward * 0.3f);
	newPos = newPos + m_world_cam.getXDirection() * (m_rightward * 0.3f);

	world_cam.setTranslation(newPos);
	m_world_cam = world_cam;
	world_cam.inverse();
	cc.m_world = world_cam;
	cc.m_view = world_cam;

	int width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	int height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	cc.m_projection.setPerspectiveFovLH(1.57f, float(width)/float(height), 0.1f, 100.0f);

	m_constant_buffer->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void AppWindow::onCreate()
{
	RECT rect = this->getClientWindowRect();
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top);
	m_world_cam.setTranslation(Vector3D(0, 0, -2));
	// Test cube
	vertex list[] = {
		// X - Y - Z
		// Front face of the cube
		{Vector3D(-0.5f, -0.5f, -0.5f),			Vector3D(1, 1, 1)			,	Vector3D(0, 0, 0)},		//Position 0
		{Vector3D(-0.5f, 0.5f, -0.5f),			Vector3D(0, 0, 0)			,	Vector3D(0, 0, 0)},		//Position 1
		{Vector3D(0.5f, 0.5f, -0.5f),			Vector3D(1, 0, 0)			,	Vector3D(0, 0, 0)},		//Position 2
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
	m_index_buffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, index_size);

	void* shader_bytecode = nullptr;
	size_t shader_size = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"Shaders\\VertexShader.hlsl", "main", &shader_bytecode, &shader_size);
	m_vertex_shader = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_bytecode, shader_size);
	m_vertex_buffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(list, sizeof(vertex), list_size, shader_bytecode, (UINT)shader_size);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"Shaders\\PixelShader.hlsl", "main", &shader_bytecode, &shader_size);
	m_pixel_shader = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_bytecode, shader_size);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_time = 0;
	m_constant_buffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	RECT rect = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rect.right - rect.left, rect.bottom - rect.top);

	update();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, m_constant_buffer);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, m_constant_buffer);

	//Default shaders for Graphics pipeline
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vertex_shader);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_pixel_shader);

	// Set vertices to draw
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	// Set indices to draw
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_index_buffer);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vertex_buffer->getSizeVertexList(), 0);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_index_buffer->getSizeIndexList(),0, 0);
	m_swap_chain->present(false);

	m_old_delta = m_new_delta;
	m_new_delta = GetTickCount();
	m_delta_time = m_old_delta ? (m_new_delta - m_old_delta) / 1000.0f : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		m_rightward = 1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	int width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	int height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	m_rot_x += ( mouse_pos.y - height / 2.0f) * m_delta_time * 0.1f;
	m_rot_y += ( mouse_pos.x - width / 2.0f) * m_delta_time * 0.1f;

	InputSystem::get()->setCursorPosition( Point(int(width / 2.0f), int(height / 2.0f)) );
}

void AppWindow::onLeftMouseDown(const Point& delta_pos)
{
	m_scale_cube -= 0.5f;
}

void AppWindow::onRightMouseDown(const Point& delta_pos)
{
	m_scale_cube += 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& delta_pos)
{
	m_scale_cube = 1.0f;
}

void AppWindow::onRightMouseUp(const Point& delta_pos)
{
}
