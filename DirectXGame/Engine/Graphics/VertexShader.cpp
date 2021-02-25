#include "VertexShader.h"
#include "RenderSystem.h"
#include <exception>

/*
	shader_bytecode == data obtrained from compileVertexShader output
	bytecode_size == data obtrained from compileVertexShader output
*/
VertexShader::VertexShader(RenderSystem* system, const void* shader_bytecode, size_t bytecode_size)
	: m_system{ system }
{
	//Create a vertex shader for the corresponding d3d device and assign it's pointer to m_vertex_shader
	if (FAILED(m_system->m_d3d_device->CreateVertexShader(shader_bytecode, bytecode_size, nullptr, &m_vertex_shader)))
	{
		throw std::exception("VertexShader not created successfully");
	}
}

VertexShader::~VertexShader()
{
	/*
	Release used resources,
	getting a nullptr reference error here likely means a shader (.hlsl) didn't compile
	*/
	m_vertex_shader->Release();
}
