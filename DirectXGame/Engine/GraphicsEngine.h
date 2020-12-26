#pragma once
#include <d3d11.h>
#include <SwapChain.h>
#include "DeviceContext.h"
#include <VertexBuffer.h>

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

	void createShaders();
	void setShaders();
	void getShaderBufferAndSize(void** bytecode, UINT* size);

private:
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11Device* m_d3d_device = nullptr;
	ID3D11DeviceContext* m_imm_context = nullptr;
	IDXGIDevice* m_dxgi_device = nullptr;
	IDXGIAdapter* m_dxgi_adapter = nullptr;
	IDXGIFactory* m_dxgi_factory = nullptr;
	DeviceContext* m_imm_device_context = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
};

