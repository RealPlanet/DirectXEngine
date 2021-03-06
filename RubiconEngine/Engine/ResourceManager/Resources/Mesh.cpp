#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING 1 // Temp fix, codecvt_utf8 is deprecated in c++17

#include "Mesh.h"
#include "..\..\Graphics\GraphicsEngine.h"
#include "..\..\Utility\VertexMesh.h"

#pragma warning (push)
#pragma warning( disable : 26495 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 26498 )
#pragma warning( disable : 26812 )
#pragma warning( disable : 4267 )
#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader\include\tiny_obj_loader.h>
#pragma warning(pop)

#include <locale>
#include <codecvt>

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;

//#pragma warning(suppress : 4996) 
	std::string inputFile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path);

    // TODO, MAYBE //\ \\

	std::string mtl_directory = inputFile.substr(0, inputFile.find_last_of("\\/"));

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputFile.c_str(), mtl_directory.c_str());
	if(!err.empty() || !res) throw std::exception("Unable to load requested Mesh"); // Move err to error handling

	std::vector<VertexMesh> list_verticies;
	std::vector<unsigned int> list_indicies;

	size_t size_vertex_index_lists = 0;
	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_vertex_index_lists += shapes[s].mesh.indices.size();
	}

	//Reserve memory for whole mesh instead of gradually incrementing it
	list_verticies.reserve(size_vertex_index_lists);
	list_indicies.reserve(size_vertex_index_lists);

	m_material_slots.resize(materials.size());
	size_t index_global_offset = 0;

	for (size_t m = 0; m < materials.size(); m++)
	{
		m_material_slots[m].start_index = index_global_offset;
		m_material_slots[m].material_id = m;
		for (size_t s = 0; s < shapes.size(); s++)
		{
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
			{
				// Only consider the same material for each iteration
				if (shapes[s].mesh.material_ids[f] != m)
				{
					continue;
				}

				unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];
				for (unsigned char v = 0; v < num_face_verts; v++)
				{
					tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

					// Vertex coordinates
					tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
					tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
					tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

					//Texture coordinates
					tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];

					//Normals
					tinyobj::real_t nx = attribs.normals[index.normal_index * 3 + 0];
					tinyobj::real_t ny = attribs.normals[index.normal_index * 3 + 1];
					tinyobj::real_t nz = attribs.normals[index.normal_index * 3 + 2];

					Vector3 vert_pos = Vector3(vx, vy, vz);
					Vector2 texcoord = Vector2(tx, ty);
					Vector3 normals = Vector3(nx, ny, nz);

					VertexMesh vertex(vert_pos, texcoord, normals);
					list_verticies.push_back(vertex);
					list_indicies.push_back((unsigned int)index_global_offset + v);

				}
				index_offset += num_face_verts;
				index_global_offset += num_face_verts;
			}
		}

		m_material_slots[m].num_indices = index_global_offset - m_material_slots[m].start_index;
	}

	void* shader_bytecode = nullptr;
	size_t shader_size = 0;
	GraphicsEngine::get()->getVertexMeshLayoutByteCodeAndSize(&shader_bytecode, &shader_size);
	m_vertex_buffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(&list_verticies[0], sizeof(VertexMesh),
																					(UINT)list_verticies.size(), shader_bytecode, (UINT)shader_size);
	m_index_buffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&list_indicies[0], (UINT)list_indicies.size());
}

const MaterialSlot& Mesh::getMaterialSlot(unsigned int slot)
{
	if (slot >= m_material_slots.size())
	{
		return MaterialSlot();
	}

	return m_material_slots[slot];
}

size_t Mesh::getNumMaterialSlots()
{
	return m_material_slots.size();
}

Mesh::~Mesh()
{

}
