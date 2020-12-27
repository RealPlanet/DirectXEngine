#pragma once
#include "Window.h"
#include "GraphicsEngine.h"

class AppWindow : public Window
{
public:
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
};

