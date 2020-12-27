#pragma once
#include "Window.h"
#include "GraphicsEngine.h"

class AppWindow : public Window
{
public:
	void updateQuadPosition();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain = nullptr;
	VertexBuffer* m_vertex_buffer = nullptr;
	ConstantBuffer* m_constant_buffer = nullptr;

	VertexShader* m_vertex_shader = nullptr;
	PixelShader* m_pixel_shader = nullptr;

	//Time elapsed between previous and current frame
	DWORD m_old_delta = 0;
	DWORD m_new_delta = 0;
	float m_delta_time = 0;

	float m_delta_pos = 0;
	float m_delta_scale = 0;
};

