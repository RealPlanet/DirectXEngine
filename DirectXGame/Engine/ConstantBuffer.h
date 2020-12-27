#pragma once
#include <d3d11.h>
#include "DeviceContext.h"

class DeviceContext; //Forward definition

class ConstantBuffer
{
public:
	bool load(void* buffer, UINT buffer_size);
	void update(DeviceContext* context, void* buffer);
	bool release();
private:
	ID3D11Buffer* m_buffer;

	friend class DeviceContext;
};

