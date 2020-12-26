#pragma once
#include <d3d11.h>

class VertexShader
{
public:
	void release();
private:
	bool init(const void* shader_bytecode, size_t bytecode_size);

	ID3D11VertexShader* m_vertex_shader;

	friend class GraphicsEngine;
	friend class DeviceContext;
};