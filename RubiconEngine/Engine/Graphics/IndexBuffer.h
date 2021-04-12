#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(RenderSystem* system, void* list_indices, UINT list_size);
	~IndexBuffer();
	UINT getSizeIndexList();
private:
	UINT m_size_list = 0;
	ID3D11Buffer* m_buffer = nullptr;
	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};

