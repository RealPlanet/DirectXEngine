#pragma once
#include <d3d11.h>
#include <SwapChain.h>
#include "DeviceContext.h"
#include <VertexBuffer.h>
#include <ConstantBuffer.h>
#include <VertexShader.h>
#include <PixelShader.h>

class GraphicsEngine
{
public:
	// Initialize GraphicsEngine and DirectX 11 Device
	bool init();
	// Release all the occupied resources
	bool release();
	static GraphicsEngine* get();

	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	VertexBuffer* createVertexBuffer();
	ConstantBuffer* createConstantBuffer();

	VertexShader* createVertexShader(const void* shader_bytecode, size_t bytecode_size);
	PixelShader*  createPixelShader(const void* shader_bytecode, size_t bytecode_size);

	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

	void releaseCompiledShader();
private:
	D3D_FEATURE_LEVEL m_feature_level = {};
	ID3D11Device* m_d3d_device = nullptr;
	ID3D11DeviceContext* m_imm_context = nullptr;
	IDXGIDevice* m_dxgi_device = nullptr;
	IDXGIAdapter* m_dxgi_adapter = nullptr;
	IDXGIFactory* m_dxgi_factory = nullptr;
	DeviceContext* m_imm_device_context = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3DBlob* m_blob = nullptr;

	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class VertexShader;
};

