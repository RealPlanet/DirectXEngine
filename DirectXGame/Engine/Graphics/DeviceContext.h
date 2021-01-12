#pragma once
#include <d3d11.h>
#include "SwapChain.h"
#include <VertexBuffer.h>
#include <VertexShader.h>
#include <PixelShader.h>
#include <ConstantBuffer.h>
#include <IndexBuffer.h>

class ConstantBuffer; //Forward declaration

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool release();
	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* index_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index,UINT start_index_loation);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);
	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

private:
	ID3D11DeviceContext* m_device_context;

	friend class ConstantBuffer;
};

