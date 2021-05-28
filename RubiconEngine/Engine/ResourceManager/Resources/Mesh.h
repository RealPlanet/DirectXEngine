#pragma once
#include "Resource.h"
#include "..\..\Graphics\VertexBuffer.h"
#include "..\..\Graphics\IndexBuffer.h"
#include <vector>

struct MaterialSlot
{
	size_t start_index = 0;
	size_t num_indices = 0;
	size_t material_id = 0;
};

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	const VertexBufferPtr& getVertexBuffer() { return m_vertex_buffer; }
	const IndexBufferPtr& getIndexBuffer() { return m_index_buffer; }
	const MaterialSlot& getMaterialSlot(unsigned int slot);
	size_t getNumMaterialSlots();

private:
	VertexBufferPtr m_vertex_buffer;
	IndexBufferPtr m_index_buffer;
	std::vector<MaterialSlot> m_material_slots;

	friend class DeviceContext;
};

