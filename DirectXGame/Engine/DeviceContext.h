#pragma once
#include <d3d11.h>
#include "SwapChain.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool release();

	bool clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
private:
	ID3D11DeviceContext* m_device_context;
};

