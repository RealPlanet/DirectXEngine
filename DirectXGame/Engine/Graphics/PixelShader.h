#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class PixelShader
{
public:
	PixelShader(RenderSystem* system, const void* shader_bytecode, size_t bytecode_size);
	~PixelShader();
private:
	ID3D11PixelShader* m_pixel_shader = nullptr;
	RenderSystem* m_system = nullptr;

	friend class RenderSystem;
	friend class DeviceContext;
};