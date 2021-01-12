#pragma once
#include <d3d11.h>

class SwapChain
{
public:
	//Initialize SwapChain for a window
	bool init(HWND hwnd, UINT width, UINT height);

	bool present(bool vsynch);

	//Release occupied resources
	bool release();
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_render_target_view;

	friend class DeviceContext;
};
