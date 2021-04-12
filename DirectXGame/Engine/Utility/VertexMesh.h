#pragma once
#include "Vector3.h"
#include "Vector2.h"

class VertexMesh
{
public:
	Vector3 m_position;
	Vector2 m_texcoord;
	Vector3 m_normals;

	VertexMesh() : m_position{}, m_texcoord{}, m_normals{}
	{}

	VertexMesh(Vector3 pos, Vector2 coord, Vector3 normals) : m_position(pos), m_texcoord(coord), m_normals{normals}
	{}

	VertexMesh(const VertexMesh& vm) : m_position(vm.m_position), m_texcoord(vm.m_texcoord), m_normals{vm.m_normals}
	{}

	~VertexMesh()
	{}
};