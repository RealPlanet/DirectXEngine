#pragma once
#include <d3d11.h>
#include "SwapChain.h"
#include <VertexBuffer.h>

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool release();
	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);
private:
	ID3D11DeviceContext* m_device_context;
};

