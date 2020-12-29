#pragma once
#include <d3d11.h>

class IndexBuffer
{
public:
	bool load(void* list_indices, UINT list_size);
	bool release();
	UINT getSizeIndexList();
private:
	UINT m_size_list = 0;
	ID3D11Buffer* m_buffer = 0;
	friend class DeviceContext;
};

