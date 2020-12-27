#include "VertexShader.h"
#include "GraphicsEngine.h"

void VertexShader::release()
{
	/*
		Release used resources,
		getting a nullptr reference error here likely means a shader (.hlsl) didn't compile
	*/
	if(m_vertex_shader) m_vertex_shader->Release();
	delete this;
}

/*
	shader_bytecode == data obtrained from compileVertexShader output
	bytecode_size == data obtrained from compileVertexShader output
*/
bool VertexShader::init(const void* shader_bytecode, size_t bytecode_size)
{
	//Create a vertex shader for the corresponding d3d device and assign it's pointer to m_vertex_shader
	if(FAILED( GraphicsEngine::get()->m_d3d_device->CreateVertexShader(shader_bytecode, bytecode_size, nullptr, &m_vertex_shader)) )
	{
		return false;
	}
	return true;
}
