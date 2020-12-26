#include "VertexShader.h"
#include "GraphicsEngine.h"

void VertexShader::release()
{
	m_vertex_shader->Release();
	delete this;
}

bool VertexShader::init(const void* shader_bytecode, size_t bytecode_size)
{
	if(FAILED( GraphicsEngine::get()->m_d3d_device->CreateVertexShader(shader_bytecode, bytecode_size, nullptr, &m_vertex_shader)) )
	{
		return false;
	}
	return true;
}
