#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
public:
	Vector3D m_position;
	Vector2D m_texcoord;
	Vector3D m_normals;

	VertexMesh() : m_position{}, m_texcoord{}, m_normals{}
	{}

	VertexMesh(Vector3D pos, Vector2D coord, Vector3D normals) : m_position(pos), m_texcoord(coord), m_normals{normals}
	{}

	VertexMesh(const VertexMesh& vm) : m_position(vm.m_position), m_texcoord(vm.m_texcoord), m_normals{vm.m_normals}
	{}

	~VertexMesh()
	{}
};