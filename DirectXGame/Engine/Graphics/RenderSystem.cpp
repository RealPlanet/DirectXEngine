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

bool RenderSystem::init()
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

	m_imm_device_context = new DeviceContext(this, m_imm_context);

	m_d3d_device->QueryInterface(_uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(_uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(_uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

// Release all of the resources used by the graphics engine
bool RenderSystem::release()
{
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	delete m_imm_device_context;

	m_imm_context->Release();
	m_d3d_device->Release();

	return true;
}

DeviceContext* RenderSystem::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

SwapChain* RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChain* sc = nullptr;
	try
	{
		sc = new SwapChain(this, hwnd, width, height);
	}
	catch (...) {}

	return sc;
}

VertexBuffer* RenderSystem::createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_bytecode, UINT size_byte_shader)
{
	VertexBuffer* vb = nullptr;
	try
	{
		vb = new VertexBuffer(this, list_vertices, size_vertex, size_list, shader_bytecode, size_byte_shader);
	}
	catch (...) {}
	return vb;
}

IndexBuffer* RenderSystem::createIndexBuffer(void* list_indices, UINT list_size)
{
	IndexBuffer* ib = nullptr;
	try
	{
		ib = new IndexBuffer(this, list_indices, list_size);
	}
	catch (...) {}
	return ib;
}

ConstantBuffer* RenderSystem::createConstantBuffer(void* buffer, UINT buffer_size)
{
	ConstantBuffer* cb = nullptr;
	try
	{
		cb = new ConstantBuffer(this, buffer,buffer_size);
	}
	catch (...) {}
	return cb;
}

VertexShader* RenderSystem::createVertexShader(const void* shader_bytecode, size_t bytecode_size)
{
	VertexShader* vb = nullptr;
	try
	{
		vb = new VertexShader(this, shader_bytecode, bytecode_size);
	}
	catch (...) {}
	return vb;
}

PixelShader* RenderSystem::createPixelShader(const void* shader_bytecode, size_t bytecode_size)
{
	PixelShader* ps = nullptr;
	try
	{
		ps = new PixelShader(this, shader_bytecode, bytecode_size);
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
