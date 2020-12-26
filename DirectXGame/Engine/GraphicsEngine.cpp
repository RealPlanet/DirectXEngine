#include "GraphicsEngine.h"
#include <d3dcompiler.h>


bool GraphicsEngine::init()
{
	/* DirectX devices usable by the graphics engine (from best to worst)
	HARDWARE == GPU
	WARP == HIGH PERFORMANCE CPU INSTRUCTIONS
	REFERENCE == LOWP ERFORMANCE CPU INSTRUCTIONS
	*/
	D3D_DRIVER_TYPE driver_types[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);
		
	/*
		DirectX instruction 
		D3D_FEATURE_LEVEL_11_0 == DirectX 11.0
	*/
	D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);


	HRESULT result = 0;
	/* 
		Loop through all the available devices and stop when an usable one is found
		Creates a D3D11 Device and returns if it succeded or not
	*/

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++)
	{
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(result))
		{
			break;
		}
	}

	if (FAILED(result))
	{
		return false;
	}

	m_imm_device_context = new DeviceContext(m_imm_context);

	m_d3d_device->QueryInterface(_uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(_uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(_uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

// Release all of the resources used by the graphics engine
bool GraphicsEngine::release()
{
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->release();

	m_imm_context->Release();
	m_d3d_device->Release();

	return true;
}


GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine; //Returns the current instance of GraphicsEnngine, only one instance is allowed.
	return &engine;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

void GraphicsEngine::createShaders()
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	m_d3d_device->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	m_d3d_device->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
}

void GraphicsEngine::setShaders()
{
	m_imm_context->VSSetShader(m_vs, nullptr, 0);
	m_imm_context->PSSetShader(m_ps, nullptr, 0);
}

void GraphicsEngine::getShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = (UINT)this->m_vsblob->GetBufferSize();
}
