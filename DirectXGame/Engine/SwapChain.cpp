#include "SwapChain.h"
#include "GraphicsEngine.h"


bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device  =  GraphicsEngine::get()->m_d3d_device;
	DXGI_SWAP_CHAIN_DESC chain_description;
	ZeroMemory(&chain_description, sizeof(chain_description));
	chain_description.BufferCount = 1;
	chain_description.BufferDesc.Width = width;
	chain_description.BufferDesc.Height = height;
	chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	chain_description.BufferDesc.RefreshRate.Numerator = 60;
	chain_description.BufferDesc.RefreshRate.Denominator = 1;
	chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	chain_description.OutputWindow = hwnd;
	chain_description.SampleDesc.Count = 1;
	chain_description.SampleDesc.Quality = 0;
	chain_description.Windowed = true;

	HRESULT result = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &chain_description, &m_swap_chain);

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool SwapChain::release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}
