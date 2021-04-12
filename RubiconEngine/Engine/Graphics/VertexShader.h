#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class VertexShader
{
public:
	VertexShader(RenderSystem* system, const void* shader_bytecode, size_t bytecode_size);
	~VertexShader();
private:

	ID3D11VertexShader* m_vertex_shader = nullptr;
	RenderSystem* m_system = nullptr;

	friend class RenderSystem;
	friend class DeviceContext;
};