#include "PixelShader.h"
#include "RenderSystem.h"
#include <exception>

/*
	shader_bytecode == data obtrained from compilePixelShader output
	bytecode_size == data obtrained from compilePixelShader output
*/
PixelShader::PixelShader(RenderSystem* system, const void* shader_bytecode, size_t bytecode_size)
	: m_system{ system }
{
	//Create a pixel shader for the corresponding d3d device and assign it's pointer to m_pixel_shader

	if (FAILED(m_system->m_d3d_device->CreatePixelShader(shader_bytecode, bytecode_size, nullptr, &m_pixel_shader)))
	{
		throw std::exception("PixelShader not created successfully");
	}
}

PixelShader::~PixelShader()
{
	/*
		Release used resources,
		getting a nullptr reference error here likely means a shader (.hlsl) didn't compile
	*/
	m_pixel_shader->Release();
}
