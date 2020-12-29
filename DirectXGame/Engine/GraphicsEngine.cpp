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

IndexBuffer* GraphicsEngine::createIndexBuffer()
{
	return new IndexBuffer();
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_bytecode, size_t bytecode_size)
{
	VertexShader* vertex_shader = new VertexShader();
	if (!vertex_shader->init(shader_bytecode, bytecode_size))
	{
		vertex_shader->release();
		return nullptr;
	}
	return vertex_shader;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_bytecode, size_t bytecode_size)
{
	PixelShader* pixel_shader = new PixelShader();
	if (!pixel_shader->init(shader_bytecode, bytecode_size))
	{
		pixel_shader->release();
		return nullptr;
	}
	return pixel_shader;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (FAILED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if(error_blob)error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return false;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
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

void GraphicsEngine::releaseCompiledShader()
{
	if (m_blob) m_blob->Release();
}
