#pragma once
#include <d3d11.h>

class PixelShader
{
public:
	void release();
private:
	bool init(const void* shader_bytecode, size_t bytecode_size);

	ID3D11PixelShader* m_pixel_shader = nullptr;

	friend class GraphicsEngine;
	friend class DeviceContext;
};