#include "Material.h"
#include "../../Graphics/GraphicsEngine.h"
#include <stdexcept>

Material::Material(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	void* shader_bytecode = nullptr;
	size_t shader_size = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(vertex_shader_path, "main", &shader_bytecode, &shader_size);
	m_vertex_shader = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_bytecode, shader_size);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(pixel_shader_path, "main", &shader_bytecode, &shader_size);
	m_pixel_shader = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_bytecode, shader_size);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	if (!m_vertex_shader || !m_pixel_shader) throw std::runtime_error("Material not created successfully");
}

Material::Material(const MaterialPtr& material)
{
	m_vertex_shader = material->m_vertex_shader;
	m_pixel_shader = material->m_pixel_shader;
}

Material::~Material()
{
}

void Material::addTexture(const TexturePtr& texture)
{
	m_vec_textures.push_back(texture);
}

void Material::removeTexture(unsigned int index)
{
	if (index < m_vec_textures.size())
	{
		m_vec_textures.erase(m_vec_textures.begin() + index);
	}
}

void Material::setData(void* data, unsigned int size)
{
	// if the constant buffer wasn't created, create it on the fly
	if (!m_constant_buffer)
	{
		m_constant_buffer = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(data, size);
		return;
	}

	m_constant_buffer->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), data);
}

void Material::setCullMode(CULL_MODE mode)
{
	m_cull_mode = mode;
}

CULL_MODE Material::getCullMode()
{
	return m_cull_mode;
}
