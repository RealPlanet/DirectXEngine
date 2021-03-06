#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class RenderSystem
{
public:
	// Initialize RenderSystem and DirectX 11 Device
	RenderSystem();
	// Release all the occupied resources
	~RenderSystem();

	DeviceContextPtr	 getImmediateDeviceContext();
	SwapChainPtr		createSwapChain(HWND hwnd, UINT width, UINT height);
	VertexBufferPtr		createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_bytecode, UINT size_byte_shader);
	IndexBufferPtr		createIndexBuffer(void* list_indices, UINT list_size);
	ConstantBufferPtr	createConstantBuffer(void* buffer, UINT buffer_size);
	VertexShaderPtr		createVertexShader(const void* shader_bytecode, size_t bytecode_size);
	PixelShaderPtr		createPixelShader(const void* shader_bytecode, size_t bytecode_size);

	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

	void releaseCompiledShader();
	void setRasterizerState(bool cull_front);

private:
	void initRasterizerState();

	D3D_FEATURE_LEVEL m_feature_level = {};
	ID3D11Device* m_d3d_device = nullptr;
	ID3D11DeviceContext* m_imm_context = nullptr;
	IDXGIDevice* m_dxgi_device = nullptr;
	IDXGIAdapter* m_dxgi_adapter = nullptr;
	IDXGIFactory* m_dxgi_factory = nullptr;
	DeviceContextPtr m_imm_device_context = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3DBlob* m_blob = nullptr;

	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	//States used for back or front culling on triagles
	ID3D11RasterizerState* m_cull_front_state = nullptr;
	ID3D11RasterizerState* m_cull_back_state = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class VertexShader;
	friend class IndexBuffer;
	friend class Texture;
};

