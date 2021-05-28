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
	

	void drawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_materials);
	void updateModel(Vector3 position, const std::vector<MaterialPtr>& list_materials);
	void updateCamera();
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

#pragma region Textures
	TexturePtr m_wall_tex = nullptr;
	TexturePtr m_bricks_tex = nullptr;
	TexturePtr m_earth_color_tex = nullptr;
	TexturePtr m_sky_tex = nullptr;
	TexturePtr m_sand_tex = nullptr;

	TexturePtr m_barrel_tex = nullptr;
	TexturePtr m_wood_tex = nullptr;
	TexturePtr m_house_brick_tex = nullptr;
	TexturePtr m_window_tex = nullptr;

#pragma endregion
#pragma region Materials
	MaterialPtr m_sky_mtl;
	MaterialPtr m_base_mtl;
	MaterialPtr m_brick_mtl;
	MaterialPtr m_earth_mtl;
	MaterialPtr m_sand_mtl;

	MaterialPtr m_barrel_mtl;
	MaterialPtr m_house_brick_mtl;
	MaterialPtr m_window_mtl;
	MaterialPtr m_wood_mtl;

	std::vector<MaterialPtr> m_list_materials;
#pragma endregion
#pragma region Meshes
	MeshPtr m_mesh = nullptr;
	MeshPtr m_mesh_torus = nullptr;
	MeshPtr m_mesh_suzanne = nullptr;
	MeshPtr m_mesh_plane = nullptr;
	MeshPtr m_sky_mesh = nullptr;
	MeshPtr m_terrain_mesh = nullptr;
	MeshPtr m_house_mesh = nullptr;
#pragma endregion

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

