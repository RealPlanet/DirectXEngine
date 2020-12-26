#include "PixelShader.h"
#include "GraphicsEngine.h"

void PixelShader::release()
{
	m_pixel_shader->Release();
	delete this;
}

bool PixelShader::init(const void* shader_bytecode, size_t bytecode_size)
{
	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreatePixelShader(shader_bytecode, bytecode_size, nullptr, &m_pixel_shader)))
	{
		return false;
	}
	return true;
}
