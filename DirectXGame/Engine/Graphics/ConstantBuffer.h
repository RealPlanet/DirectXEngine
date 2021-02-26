#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class ConstantBuffer
{
public:
	ConstantBuffer(RenderSystem* system, void* buffer, UINT buffer_size);
	~ConstantBuffer();
	void update(DeviceContextPtr context, void* buffer);
private:
	ID3D11Buffer* m_buffer = nullptr;
	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};

