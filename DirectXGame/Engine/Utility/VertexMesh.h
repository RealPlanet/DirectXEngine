#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
public:
	Vector3D m_position;
	Vector2D m_texcoord;

	VertexMesh() : m_position{}, m_texcoord{}
	{}

	VertexMesh(Vector3D pos, Vector2D coord) : m_position(pos), m_texcoord(coord)
	{}

	VertexMesh(const VertexMesh& vm) : m_position(vm.m_position), m_texcoord(vm.m_texcoord)
	{}

	~VertexMesh()
	{}
};