#include "RenderSystem.h"
#include <d3dcompiler.h>

#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"

#include <exception>

RenderSystem::RenderSystem()
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
		throw std::exception("Failed to create D3D11 Device");
	}

	m_imm_device_context = std::make_shared<DeviceContext>(this, m_imm_context);

	m_d3d_device->QueryInterface(_uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(_uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(_uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
}

// Release all of the resources used by the graphics engine
RenderSystem::~RenderSystem()
{
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_context->Release();
	m_d3d_device->Release();
}

DeviceContextPtr RenderSystem::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

SwapChainPtr RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChainPtr sc = nullptr;
	try
	{
		sc = std::make_shared<SwapChain>(this, hwnd, width, height);
	}
	catch (...) {}

	return sc;
}

VertexBufferPtr RenderSystem::createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_bytecode, UINT size_byte_shader)
{
	VertexBufferPtr vb = nullptr;
	try
	{
		vb = std::make_shared<VertexBuffer>(this, list_vertices, size_vertex, size_list, shader_bytecode, size_byte_shader);
	}
	catch (...) {}
	return vb;
}

IndexBufferPtr RenderSystem::createIndexBuffer(void* list_indices, UINT list_size)
{
	IndexBufferPtr ib = nullptr;
	try
	{
		ib = std::make_shared<IndexBuffer>(this, list_indices, list_size);
	}
	catch (...) {}
	return ib;
}

ConstantBufferPtr RenderSystem::createConstantBuffer(void* buffer, UINT buffer_size)
{
	ConstantBufferPtr cb = nullptr;
	try
	{
		cb = std::make_shared<ConstantBuffer>(this, buffer,buffer_size);
	}
	catch (...) {}
	return cb;
}

VertexShaderPtr RenderSystem::createVertexShader(const void* shader_bytecode, size_t bytecode_size)
{
	VertexShaderPtr vb = nullptr;
	try
	{
		vb = std::make_shared<VertexShader>(this, shader_bytecode, bytecode_size);
	}
	catch (...) {}
	return vb;
}

PixelShaderPtr RenderSystem::createPixelShader(const void* shader_bytecode, size_t bytecode_size)
{
	PixelShaderPtr ps = nullptr;
	try
	{
		ps = std::make_shared<PixelShader>(this, shader_bytecode, bytecode_size);
	}
	catch (...) {}
	return ps;
}

bool RenderSystem::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (FAILED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return false;
}

bool RenderSystem::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (FAILED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return false;
}

void RenderSystem::releaseCompiledShader()
{
	if (m_blob) m_blob->Release();
}
