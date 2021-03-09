#include "AppWindow.h"
#include "Mesh.h"
#include <Windows.h>
#include <iostream>

/*
* TODO ::
*  - Updated GetTickCount to GetTickCount64
*/

void AppWindow::drawMesh(const MeshPtr& mesh, const VertexShaderPtr& vs, const PixelShaderPtr& ps, const ConstantBufferPtr& cb,
						const TexturePtr* texture, unsigned int num_textures)
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(vs, cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(ps, cb);

	//Default shaders for Graphics pipeline
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(ps, texture, num_textures);

	// Set vertices to draw
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(mesh->getVertexBuffer());
	// Set indices to draw
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(mesh->getIndexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
}

void AppWindow::updateCamera()
{
	Matrix4x4 world_cam, temp;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D newPos = m_world_cam.getTranslation() + m_world_cam.getZDirection() * (m_forward * 0.01f);
	newPos = newPos + m_world_cam.getXDirection() * (m_rightward * 0.01f);
	world_cam.setTranslation(newPos);
	m_world_cam = world_cam;
	world_cam.inverse();

	m_view_cam = world_cam;
	
	int width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	int height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	m_proj_cam.setPerspectiveFovLH(1.57f, float(width) / float(height), 0.1f, 100.0f);
}

void AppWindow::updateModel()
{
	constant cc;
	Matrix4x4 m_light_rot_matrix;
	m_light_rot_matrix.setIdentity();
	m_light_rot_matrix.setRotationY(m_light_rot_y);
	m_light_rot_y += 0.307f * m_delta_time;
	
	//cc.m_world = m_world_cam;
	cc.m_world.setIdentity();
	cc.m_view = m_view_cam;
	cc.m_projection = m_proj_cam;
	cc.m_camera_position = m_world_cam.getTranslation();
	cc.m_light_direction = m_light_rot_matrix.getZDirection();
	cc.m_time = m_time; //GetTickCount();

	m_constant_buffer->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void AppWindow::updateSkybox()
{
	constant cc;
	cc.m_world.setIdentity();
	cc.m_world.setScale(Vector3D(100.0f, 100.0f, 100.0f)); // Same values as zFar value of camera
	cc.m_world.setTranslation(m_world_cam.getTranslation());
	cc.m_view = m_view_cam;
	cc.m_projection = m_proj_cam;
	m_constant_buffer_skybox->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void AppWindow::render()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	RECT rect = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rect.right - rect.left, rect.bottom - rect.top);

	update();
	GraphicsEngine::get()->getRenderSystem()->setRasterizerState(false);

	TexturePtr list_tex[4];
	list_tex[0] = m_earth_c_tex;
	list_tex[1] = m_earth_s_tex;
	list_tex[2] = m_clouds_tex;
	list_tex[3] = m_earth_night_c_tex;
	drawMesh(m_mesh, m_vertex_shader, m_pixel_shader, m_constant_buffer, list_tex, 4);

	GraphicsEngine::get()->getRenderSystem()->setRasterizerState(true);
	list_tex[0] = m_sky_tex;
	drawMesh(m_sky_mesh, m_vertex_shader, m_pixel_shader_skybox, m_constant_buffer_skybox, list_tex, 1);

	m_swap_chain->present(false);

	m_old_delta = m_new_delta;
	m_new_delta = GetTickCount();
	m_delta_time = m_old_delta ? (m_new_delta - m_old_delta) / 1000.0f : 0;
	m_time += m_delta_time;
}

void AppWindow::update()
{
	updateCamera();
	updateModel();
	updateSkybox();
}

void AppWindow::onCreate()
{
	RECT rect = this->getClientWindowRect();
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	m_earth_c_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\Earth\\earth_color.jpg");
	m_earth_night_c_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\Earth\\earth_night.jpg");
	m_earth_s_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\Earth\\earth_spec.jpg");
	m_clouds_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\Earth\\clouds.jpg");
	m_sky_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\skyboxes\\stars_map.jpg");

	m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\sphere_hq.obj");
	m_sky_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\sphere.obj");
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top);
	m_world_cam.setTranslation(Vector3D(0, 0, -3));

	Vector3D position_list[] = 
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }
	};
	// Test cube
	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	UINT list_size = ARRAYSIZE(vertex_list);
	UINT index_size = ARRAYSIZE(index_list);
	m_index_buffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, index_size);

	void* shader_bytecode = nullptr;
	size_t shader_size = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"Shaders\\VertexShader.hlsl", "main", &shader_bytecode, &shader_size);
	m_vertex_shader = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_bytecode, shader_size);
	m_vertex_buffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertex), list_size, shader_bytecode, (UINT)shader_size);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"Shaders\\PixelShader.hlsl", "main", &shader_bytecode, &shader_size);
	m_pixel_shader = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_bytecode, shader_size);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"Shaders\\SkyBoxShader.hlsl", "main", &shader_bytecode, &shader_size);
	m_pixel_shader_skybox = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_bytecode, shader_size);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();


	constant cc;
	cc.m_time = 0;
	m_constant_buffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
	m_constant_buffer_skybox = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	InputSystem::get()->update();
	this->render();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->setFullScreen(false, 1, 1);
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onSize()
{
	RECT rect = this->getClientWindowRect();
	m_swap_chain->resize(rect.right, rect.bottom);
	this->render();
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

	if (key == VK_ESCAPE)
	{
		m_play_state = !m_play_state;
		InputSystem::get()->showCursor(!m_play_state);
	}
	else if (key == 'F')
	{
		m_fullscreen = !m_fullscreen;
		RECT rc = getScreenSize();
		m_swap_chain->setFullScreen(m_fullscreen, rc.right, rc.bottom);
	}
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	if(!m_play_state) return;

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
