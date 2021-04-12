#pragma once
#include "..\Engine\Window.h"
#include "..\Engine\Utility\Matrix4x4.h"
#include "..\Engine\Graphics\RenderSystem.h"
#include "..\Engine\InputSystem\InputListener.h"
#include "..\Engine\InputSystem\InputSystem.h"
#include "..\Engine\Graphics\ConstantBuffer.h"
#include "..\Engine\Graphics\GraphicsEngine.h"
#include "..\Engine\Graphics\SwapChain.h"
#include "..\Engine\Graphics\IndexBuffer.h"
#include "..\Engine\Graphics\VertexBuffer.h"
#include "..\Engine\Graphics\VertexShader.h"
#include "..\Engine\Graphics\PixelShader.h"
#include "..\Engine\Graphics\DeviceContext.h"
#include "Generics.h"

class AppWindow : public Window, public InputListener
{
public:
	

	void drawMesh(const MeshPtr& mesh, const MaterialPtr& material);
	void updateCamera();
	void updateModel(Vector3 position, const MaterialPtr& material);
	void updateSkybox();
	void updateLight();

	void render();
	void update();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	virtual void onSize() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;


private:
	SwapChainPtr m_swap_chain = nullptr;
	VertexBufferPtr m_vertex_buffer = nullptr;
	IndexBufferPtr m_index_buffer = nullptr;
	ConstantBufferPtr m_constant_buffer = nullptr;
	ConstantBufferPtr m_constant_buffer_skybox = nullptr;

	VertexShaderPtr m_vertex_shader = nullptr;
	PixelShaderPtr m_pixel_shader = nullptr;
	PixelShaderPtr m_pixel_shader_skybox = nullptr;

	TexturePtr m_wall_tex = nullptr;
	TexturePtr m_bricks_tex = nullptr;
	TexturePtr m_earth_color_tex = nullptr;
	TexturePtr m_sky_tex = nullptr;

	MeshPtr m_mesh = nullptr;
	MeshPtr m_mesh_torus = nullptr;
	MeshPtr m_mesh_suzanne = nullptr;
	MeshPtr m_mesh_plane = nullptr;

	MeshPtr m_sky_mesh = nullptr;

	MaterialPtr m_mat_sky;
	MaterialPtr m_mat;
	MaterialPtr m_mat_bricks;
	MaterialPtr m_mat_earth;
	
	//Time elapsed between previous and current frame
	DWORD m_old_delta = 0;
	DWORD m_new_delta = 0;
	float m_delta_time = 0;
	float m_time = 0;

	float m_delta_pos = 0;
	float m_delta_scale = 0;

	float m_rot_x = 0;
	float m_rot_y = 0;
	float m_scale_cube = 1;

	float m_light_rot_y = 0.0f;

	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_cam;
	Matrix4x4 m_proj_cam;

	bool m_play_state = false;
	bool m_fullscreen = false;

	Vector4 m_light_position;
};

