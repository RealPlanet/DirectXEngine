#include "SwapChain.h"
#include "RenderSystem.h"
#include <exception>

SwapChain::SwapChain(RenderSystem* system, HWND hwnd, UINT width, UINT height)
	: m_system{ system }
{
	ID3D11Device* device = m_system->m_d3d_device;
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

	HRESULT result = m_system->m_dxgi_factory->CreateSwapChain(device, &chain_description, &m_swap_chain);

	if (FAILED(result))
	{
		throw std::exception("SwapChain not created successfully");
	}

	ID3D11Texture2D* buffer = nullptr;
	result = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(result))
	{
		throw std::exception("Could not get buffer for SwapChain");
	}

	result = device->CreateRenderTargetView(buffer, NULL, &m_render_target_view);
	buffer->Release();

	if (FAILED(result))
	{
		throw std::exception("Could not create a renderTarget for SwapChain");
	}
}

SwapChain::~SwapChain()
{
	m_swap_chain->Release();
}

bool SwapChain::present(bool vsynch)
{
	m_swap_chain->Present(vsynch, NULL);
	return true;
}