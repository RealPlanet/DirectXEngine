#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class VertexBuffer
{
public:
	VertexBuffer(RenderSystem* system, void* list_vertices, UINT size_vertex, UINT size_list, void* shader_bytecode, UINT size_byte_shader);
	~VertexBuffer();

	UINT getSizeVertexList();
private:
	UINT m_size_vertex;
	UINT m_size_list;
	ID3D11Buffer* m_buffer = nullptr;
	ID3D11InputLayout* m_layout = nullptr;
	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};

