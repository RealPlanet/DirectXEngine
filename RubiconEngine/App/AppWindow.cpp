#include "AppWindow.h"
#include "..\Engine\ResourceManager\Resources\Mesh.h"
#include <Windows.h>
#include <iostream>

/*
* TODO ::
*  - Updated GetTickCount to GetTickCount64
*/

void AppWindow::drawMesh(const MeshPtr& mesh, const MaterialPtr& material)
{
	GraphicsEngine::get()->setMaterial(material);
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

	Vector3 newPos = m_world_cam.getTranslation() + m_world_cam.getZDirection() * (m_forward * 0.05f);
	newPos = newPos + m_world_cam.getXDirection() * (m_rightward * 0.05f);
	world_cam.setTranslation(newPos);
	m_world_cam = world_cam;
	world_cam.inverse();

	m_view_cam = world_cam;
	
	int width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	int height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	m_proj_cam.setPerspectiveFovLH(1.57f, float(width) / float(height), 0.1f, 100.0f);
}

void AppWindow::updateModel(Vector3 position, const MaterialPtr& material)
{
	constant cc;
	Matrix4x4 m_light_rot_matrix;
	m_light_rot_matrix.setIdentity();
	m_light_rot_matrix.setRotationY(m_light_rot_y);
	
	//cc.m_world = m_world_cam;
	cc.m_world.setIdentity();
	cc.m_world.setTranslation(position);
	cc.m_view = m_view_cam;
	cc.m_projection = m_proj_cam;
	cc.m_camera_position = m_world_cam.getTranslation();

	cc.m_light_position = m_light_position;
	cc.m_light_direction = m_light_rot_matrix.getZDirection();
	cc.m_time = m_time; //GetTickCount();

	material->setData(&cc, sizeof(constant));
}

void AppWindow::updateLight()
{
	m_light_rot_y += 1.57f * m_delta_time;
	float dist_from_origin = 3.0f;
	m_light_position = Vector4(cos(m_light_rot_y) * dist_from_origin, 1.0f, sin(m_light_rot_y) * dist_from_origin, 1.0f);	
}

void AppWindow::updateSkybox()
{
	constant cc;
	cc.m_world.setIdentity();
	cc.m_world.setScale(Vector3(100.0f, 100.0f, 100.0f)); // Same values as zFar value of camera
	cc.m_world.setTranslation(m_world_cam.getTranslation());
	cc.m_view = m_view_cam;
	cc.m_projection = m_proj_cam;
	m_mat_sky->setData(&cc, sizeof(constant));
}

void AppWindow::render()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	RECT rect = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rect.right - rect.left, rect.bottom - rect.top);

	update();

	for (int i = 0; i < 3; i++)
	{
		updateModel(Vector3(0, 0, 4*i), m_mat);
		drawMesh(m_mesh_torus, m_mat); //Render ksybox

		updateModel(Vector3(4, 0, 4*i), m_mat_earth);
		drawMesh(m_sky_mesh, m_mat_earth); //Render model

		updateModel(Vector3(-4, 0, 4*i), m_mat_bricks);
		drawMesh(m_mesh_suzanne, m_mat_bricks); //Render model
	}



	drawMesh(m_sky_mesh, m_mat_sky); //Render model

	updateModel(Vector3(0, -1, 0), m_mat);
	drawMesh(m_mesh_plane, m_mat);

	m_swap_chain->present(false);

	m_old_delta = m_new_delta;
	m_new_delta = GetTickCount();
	m_delta_time = m_old_delta ? (m_new_delta - m_old_delta) / 1000.0f : 0;
	m_time += m_delta_time;
}

void AppWindow::update()
{
	updateCamera();
	updateLight();
	updateSkybox();
}

void AppWindow::onCreate()
{
	RECT rect = this->getClientWindowRect();
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);
	m_play_state = true;

	m_wall_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\_other\\wall.jpg");
	m_bricks_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\_other\\brick.png");
	m_earth_color_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\Earth\\earth_color.jpg");
	m_sky_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\skyboxes\\stars_map.jpg");

	m_mat = GraphicsEngine::get()->createMaterial(L"Shaders\\PointLightVertexShader.hlsl", L"Shaders\\PointLightPixelShader.hlsl");
	m_mat->addTexture(m_wall_tex);
	m_mat->setCullMode(CULL_MODE_BACK);

	m_mat_earth = GraphicsEngine::get()->createMaterial(m_mat);
	m_mat_earth->addTexture(m_earth_color_tex);
	m_mat_earth->setCullMode(CULL_MODE_BACK);

	m_mat_bricks = GraphicsEngine::get()->createMaterial(m_mat);
	m_mat_bricks->addTexture(m_bricks_tex);
	m_mat_bricks->setCullMode(CULL_MODE_BACK);

	m_mat_sky = GraphicsEngine::get()->createMaterial(L"Shaders\\PointLightVertexShader.hlsl", L"Shaders\\SkyBoxShader.hlsl");
	m_mat_sky->addTexture(m_sky_tex);
	m_mat_sky->setCullMode(CULL_MODE_FRONT);

	m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\scene.obj");
	m_sky_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\sphere.obj");
	m_mesh_torus = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\torus.obj");
	m_mesh_suzanne = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\suzanne.obj");
	m_mesh_plane = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\plane.obj");

	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top);
	m_world_cam.setTranslation(Vector3(0, 0, -3));

	Vector3 position_list[] = 
	{
		{ Vector3(-0.5f,-0.5f,-0.5f)},
		{ Vector3(-0.5f,0.5f,-0.5f) },
		{ Vector3(0.5f,0.5f,-0.5f) },
		{ Vector3(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3(0.5f,-0.5f,0.5f) },
		{ Vector3(0.5f,0.5f,0.5f) },
		{ Vector3(-0.5f,0.5f,0.5f)},
		{ Vector3(-0.5f,-0.5f,0.5f) }
	};

	Vector2 texcoord_list[] =
	{
		{ Vector2(0.0f,0.0f) },
		{ Vector2(0.0f,1.0f) },
		{ Vector2(1.0f,0.0f) },
		{ Vector2(1.0f,1.0f) }
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
	m_world_cam.setTranslation(Vector3(0, 0, -2));
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
