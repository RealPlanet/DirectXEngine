#include "PixelShader.h"
#include "GraphicsEngine.h"

void PixelShader::release()
{
	/*
		Release used resources,
		getting a nullptr reference error here likely means a shader (.hlsl) didn't compile
	*/
	if(m_pixel_shader) m_pixel_shader->Release();
	delete this;
}
/*
	shader_bytecode == data obtrained from compilePixelShader output
	bytecode_size == data obtrained from compilePixelShader output
*/
bool PixelShader::init(const void* shader_bytecode, size_t bytecode_size)
{
	//Create a pixel shader for the corresponding d3d device and assign it's pointer to m_pixel_shader

	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreatePixelShader(shader_bytecode, bytecode_size, nullptr, &m_pixel_shader)))
	{
		return false;
	}
	return true;
}
