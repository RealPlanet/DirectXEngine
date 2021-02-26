#pragma once
#include "Window.h"
#include "Matrix4x4.h"
#include "RenderSystem.h"
#include "InputListener.h"
#include "generics.h"
#include "InputSystem.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DeviceContext.h"

class AppWindow : public Window, public InputListener
{
public:
	void update();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

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

	VertexShaderPtr m_vertex_shader = nullptr;
	PixelShaderPtr m_pixel_shader = nullptr;
	TexturePtr m_wood_tex = nullptr;

	//Time elapsed between previous and current frame
	DWORD m_old_delta = 0;
	DWORD m_new_delta = 0;
	float m_delta_time = 0;

	float m_delta_pos = 0;
	float m_delta_scale = 0;

	float m_rot_x = 0;
	float m_rot_y = 0;
	float m_scale_cube = 1;

	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	Matrix4x4 m_world_cam;
};

